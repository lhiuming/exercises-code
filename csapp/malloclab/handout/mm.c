/*
 * mm-naive.c - The fastest, best memory-efficient malloc package.
 *
 * In this approach, a bunch of segregated free list of fixed size-range
 * is maintained by the allocator. This allow log-time free and constant
 * overhead for the segregated list structure.
 *
 * At the head region of the heap, we maitained a fixed size array of root
 * pointers for all size class.For a
 * SegList of size k, it store free blocks of size at least 2^k bytes.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    " ",
    /* First member's full name */
    " ",
    /* First member's email address */
    " ",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};


/************************************************************
 * Useful constant and macros for implementing the allocator
 ************************************************************/

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8
#define CHUNK (1 << 12)

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

/* size of some general data type */
#define SIZE_T_SIZE sizeof(size_t)
#define POINTER_SIZE (sizeof(void *))

/* size of overheads */
#define SEGLIST_ROOT_SIZE  (SIZE_T_SIZE + POINTER_SIZE)  /* mimics a header */
#define HDR_SIZE           SIZE_T_SIZE   /* size for block header */
#define LINK_SIZE          (POINTER_SIZE + POINTER_SIZE)  /* bi-direction */
#define FTR_SIZE           SIZE_T_SIZE   /* size for free block footer */
#define EPIL_SIZE          HDR_SIZE         /* epilogue padding */
#define PROL_SIZE          (ALIGN(HDR_SIZE) - EPIL_SIZE)  /* prologue padding */
#define MIN_BLOCK_SIZE     ALIGN(HDR_SIZE + LINK_SIZE + FTR_SIZE)  /* free */

/* pack a size, a allocated bit and a prev-allocated bit into a word */
#define PACK(size, alloc_prev, alloc) ((size)|(alloc_prev)|(alloc))

/* read and write a word at address p */
#define GETW(p) (*(uint32 *) (p))  /* a word is 4 bytes */
#define GETD(p) (*(uint64 *) (p))  /* a dword is 8 bytes */
#define GETS(p) (*(size_t *) (p))  /* access as a size_t */
#define GETP(p) (*(char **)  (p))  /* access as a pointer */

/* access the size and allocaterd fileds from block header p */
#define GET_SIZE(p)       (GETS(p) & ~0x7)
#define GET_ALLOC(p)      (GETS(p) & 0x1)
#define GET_ALLOC_PREV(p) (GETS(p) & 0x2)

/* locate header and footer for a block address bp.
 * the footer locating is only safe for free block pointer ! */
#define HDRP(bp)  ((char *) (bp))
#define FTRP(fbp) ((char *) (fbp) + GET_SIZE(HDRP(fbp)) - FTR_SIZE)
#define PAYL(bp)  ((char *) (bp) + HDR_SIZE)
#define PAYL_TO_BP(p) ( (char *) (p) - HDR_SIZE );

/* locate the slot for 'next' and 'prev' for a free block address fbp */
#define SUCCP(fbp) (HDRP(fbp) + SIZE_T_SIZE)
#define PREDP(fbp) (HDRP(fbp) + SIZE_T_SIZE + POINTER_SIZE)

/* access the slot of a list root */
#define GET_CLASS_SIZE(rp) GETS(rp)
#define LARGER_CLASS(rp)  ((char *)(rp) + SEGLIST_ROOT_SIZE)
#define SMALLER_CLASS(rp) ((char *)(rp) - SEGLIST_ROOT_SIZE)

/* get the address of successor or predecessor block in a list.
 * used for jumping around seglist for a free block address fbp */
#define SUCC_BLKP(fbp) GETP(SUCCP(fbp))
#define PRED_BLKP(fbp) GETP(PREDP(fbp))

/* get the address of next of prevous block in the memory.
 * used for moving around blocks for a block address bp.
 * The second command works only if the previous block is free
 * (check this by GET_ALLOC_PREV ) */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(fbp) ((char *)(fbp) - GET_SIZE(HDRP(fbp) - SIZE_T_SIZE))

/* size range of SegList as power of 2 */
#define SEGLIST_NUM  15

/* some general purpose macro */
#define MIN(i, j) ((i) < (j) ? (i) : (j))
#define MAX(i, j) ((i) > (j) ? (i) : (j))
#define MM_NODEBUG

/**************************************
 * Implementing the interface alocator
 **************************************/

/*
 * Private variables and functions
 */
static char *mm_seglist_root;  /* points to root of the smallest SegList */
static char *mm_listp;         /* points to prologue block */
void mm_distribute(char *);    /* distribute a free block to seg lists */
void mm_check(void);           /* debug checking */
void mm_insert(char *, char *);/* insert the new block into a list */
void mm_remove(char *node_hdr);/* remove a free block from seg list */
char *mm_split(char *, size_t);/* split a free block */

/*
 * mm_init - Initialize the malloc package.
 */
int mm_init(void)
{
  /* total initial break */
  size_t seglist_region = ALIGN(SEGLIST_ROOT_SIZE * SEGLIST_NUM);
  size_t padding_region = PROL_SIZE + EPIL_SIZE;
  mm_seglist_root = mem_sbrk(seglist_region + padding_region);
  mm_listp = mm_seglist_root + seglist_region;

  if (mm_seglist_root == (void *)-1) {
    printf("Failled to initialize mm ... \n");
    return -1;
  }

  /* initialize all SegList root with a null pointer.
   * the first slot in a root node is the class-size */
  for (size_t i = 0; i < SEGLIST_NUM; i++) {
    char *root_p = mm_seglist_root + i * SEGLIST_ROOT_SIZE;
    GETS(root_p) = MIN_BLOCK_SIZE << i;
    GETP(root_p + SIZE_T_SIZE) = 0;
  }

  /* padding consists of two allocated blocks. Both marked with a 0 size-bit.
   *   one is a prologue block with unaligned size (reserved for epilogue).
   *   the other one is epilogue block with a size equal to header. */
  GETS(mm_listp) = PACK(0, 0x2, 0x1);
  GETS(mm_listp + PROL_SIZE) = PACK(0, 0x2, 0x1);

  #ifndef MM_NODEBUG
  printf(">>> Finished initialization <<< \n");
  printf("mm_listp is %lx \n", (unsigned long) mm_listp);
  #endif

  return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
  #ifndef MM_NODEBUG
  printf("malloc(%zu) requested.\n", size);
  #endif

  size_t blocksize = ALIGN(SIZE_T_SIZE + size);

  /* find a size class k that fits blocksize.
   * that is, find the the largest class such that blocksize >= class_min. */
  size_t target_class;
  for (target_class = 0; target_class < SEGLIST_NUM; target_class++)
    if (blocksize < GET_CLASS_SIZE(mm_seglist_root + target_class * SEGLIST_ROOT_SIZE)) {
      target_class--;
      break;
    }

  #ifndef MM_NODEBUG
  printf("\t %zu fit to class %zu (min %lu)\n", blocksize, target_class, MIN_BLOCK_SIZE << target_class);
  #endif

  /* search the segList for a free block. */
  char *targer_root = mm_seglist_root + SEGLIST_ROOT_SIZE * target_class;
  char *node_bp = targer_root;
  while (target_class < SEGLIST_NUM) {

    /* follow the link */
    node_bp = SUCC_BLKP(node_bp);

    /* if reach the end of list, use a larger-size-class */
    if (node_bp == 0) {
      target_class++;
      node_bp = (mm_seglist_root + SEGLIST_ROOT_SIZE * target_class);
      continue;
    }

    /* if hit a free block that is big enough, allocated it. */
    size_t node_size;
    if ( (node_size = GET_SIZE(HDRP(node_bp)) ) >= blocksize ) {

      #ifndef MM_NODEBUG
      printf("\t got a usable free block in class %zu \n", target_class);
      #endif

      /* TODO: split the block if more than 1/4 of the space is wasted.
       * this must happend if the block comes from a larger-size-class. */
      if ( (node_size - blocksize) > (node_size >> 2) ) {
        #ifndef MM_NODEBUG
        printf("\t too mush wasted; going to split the node of size %zu \n", node_size);
        #endif
        mm_distribute(mm_split(node_bp, blocksize));
      }

      /* remove it from free list */
      mm_remove(node_bp);

      /* return the propieary address */
      return PAYL(node_bp);
    }

  } /* end while */

  /* even the biggest-size-class have no space,
   * so we have to expand the heap */

  #ifndef MM_NODEBUG
  printf("\t no space in any class! ");
  #endif

  /* ask memlib for a new chunk. */
  size_t brk_size = MAX(CHUNK, blocksize);
  void *p = mem_sbrk(brk_size);
  if (p == (void *)-1) {

    #ifndef MM_NODEBUG
    printf("failed to break for %i \n", (int) brk_size);
    #endif

    return NULL;
  } else {

    #ifndef MM_NODEBUG
    printf("\t expand the heap to 0x%lx + %i = 0x%lx, \n", (unsigned long)p, (int) brk_size, (unsigned long)p + brk_size);
    #endif

    /* make up the return block.
     * NOTE: also take care of the epilogue block */
    char *retn_bp = (char *)p - EPIL_SIZE;
    char *epil_bp = retn_bp + brk_size;
    size_t prev_alloc = GET_ALLOC_PREV(retn_bp); /* forom the epilogue */
    GETS(HDRP(retn_bp)) = PACK(brk_size, prev_alloc, 0x1);
    GETS(HDRP(epil_bp)) = PACK(0, 0x1, 0x1);  /* recover the epilogue */

    /* split the new block if there is more space than required */
    if ( (brk_size - blocksize) >= MIN_BLOCK_SIZE) {
      #ifndef MM_NODEBUG
      printf("\t expand too much, let split the new block. \n");
      #endif
      mm_distribute(mm_split(retn_bp, blocksize));
    }

    /* return the payload address */
    return PAYL(retn_bp);

  } /* end if */
}

/*
 * mm_free - Freeing a by marking it free and distribute it.
 * TODO: do coallase to improve performance
 */
void mm_free(void *ptr)
{
  #ifndef MM_NODEBUG
  printf("free(%lx) requested. \n", (unsigned long) ptr);
  #endif

  char *this_bp = PAYL_TO_BP(ptr);
  char *next_bp = NEXT_BLKP(this_bp);
  size_t alloc_prev = GET_ALLOC_PREV(HDRP(this_bp));

  /* mark the block as free */
  GETS(HDRP(this_bp)) = PACK(GET_SIZE(HDRP(this_bp)), alloc_prev,  0x0);

  /* TODO: colaseing ? */
  #ifndef MM_NODEBUG
  if ((alloc_prev == 0x0) || (GET_ALLOC(HDRP(next_bp)) == 0x0))
    printf("\t we might want to coallse this. \n");
  #endif

  /* distribute it into seg lists */
  #ifndef MM_NODEBUG
  printf("\t distribute this block with size %zu. \n", GET_SIZE(HDRP(this_bp)));
  #endif
  mm_distribute(this_bp);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}

/*
 * mm_check - A debug function to check a bunch of conditions to make sure the
 *     program is working (written) correctly.
 */
 void mm_check(void)
 {
   #ifndef MM_NODEBUG
   printf("(mm_check) Checks nothing.\n");
   #endif
 }

 /*
  * mm_distribute - Add a free block to a seg list.
  * TODO: we may improve this by spliting the free block before insert.
  */
 void mm_distribute(char *free_hdr)
 {

   size_t fb_size = GET_SIZE(free_hdr);

   #ifndef MM_NODEBUG
   printf("\t distributing a free block with size %i \n", (int) fb_size);
   #endif

   /* find the largest seglist that can populate this free block.
    * then insert it */
   char *last_list = mm_seglist_root + SEGLIST_ROOT_SIZE * (SEGLIST_NUM - 1);
   /* get a small enough class */
   while (fb_size < GET_CLASS_SIZE(last_list))
     last_list = SMALLER_CLASS(last_list);
   #ifndef MM_NODEBUG
   printf("\t target list is %lu with size %lu\n", (last_list - mm_seglist_root)/SEGLIST_ROOT_SIZE, GET_CLASS_SIZE(last_list));
   #endif
   /* insert the block */
   mm_insert(free_hdr, last_list);

 }

 /*
  * mm_insert - Insert a new free block into the provided seg list.
  * Currently implementation just put the block at the head
  */
void mm_insert(char *free_bp, char *target_list)
{
  // DEBUG checks
  #ifndef MM_NODEBUG
  printf("\t inserting at target list %lu \n", ((char *)target_list - mm_seglist_root)/SEGLIST_ROOT_SIZE);
  #endif

  /* currently we just put it at the head */
  char *first_node = SUCC_BLKP(target_list);  /* address to first node */
  SUCC_BLKP(target_list) = (char *)free_bp; /* root -> new  */
  PRED_BLKP(free_bp) = target_list;         /* new  -> root */
  SUCC_BLKP(free_bp) = first_node;          /* new -> old */
  if (first_node != 0)
    PRED_BLKP(first_node) = free_bp;        /* old -> new (optional) */

}

/*
 * mm_remove - Remove a node from the seg list, and mark it as allocated
 *     given the block pointer.
 */
void mm_remove(char *node_bp)
{
  /* remove it from the list */
  char *pred_node_bp = PRED_BLKP(node_bp);
  char *succ_node_bp = SUCC_BLKP(node_bp);
  SUCC_BLKP(pred_node_bp) = succ_node_bp;
  if (succ_node_bp != 0) PRED_BLKP(succ_node_bp) = pred_node_bp;

  /* mark it as allocated by overwriting the alloc bit.
   * thus we insure that all free block are inside the seg lists */
  GETS(HDRP(node_bp)) = ( GETS(HDRP(node_bp)) | 0x1 );

}

/*
 * mm_split - Split a block into two blocks by the given size of the
 *     first half, and return the block pointer to the second half.
 * After splitting, the second half is marked as free.
 * The split_size must be aligned and larger than MIN_BLOCK_SIZE.
 */
char *mm_split(char *first_bp, size_t split_size)
{
  char *second_bp = first_bp + split_size;
  size_t second_size = GET_SIZE(HDRP(first_bp)) - split_size;
  size_t first_alloc = GET_ALLOC(first_bp);

  /* set up the first block; we keeps the status of the inpu block */
  GETS(HDRP(first_bp)) = PACK(split_size, GET_ALLOC_PREV(first_bp), first_alloc);
  if (first_alloc == 0) /* only free block has footer */
    GETS(FTRP(first_bp)) = PACK(split_size, 0x0, 0x0);

  /* set up the second block; mark it as free */
  GETS(HDRP(second_bp)) = PACK(second_size, first_alloc >> 1, 0x0);
  GETS(FTRP(second_bp)) = PACK(second_size, 0x0, 0x0);

  /* update the header of next block in the heap */
  char * next_bp_hdr = HDRP(second_bp + second_size);
  GETS(next_bp_hdr) = PACK(GET_SIZE(next_bp_hdr), 0x0, GET_ALLOC(next_bp_hdr));

  /* return pointer to the second block */
  return second_bp;
}
