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
#define CHUNK 1 << 12

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

/* size of some overhead */
#define SIZE_T_SIZE sizeof(size_t)
#define POINTER_SIZE (sizeof(void *))
#define HDR_SIZE SIZE_T_SIZE
#define LINK_SIZE (POINTER_SIZE + POINTER_SIZE)
#define FTR_SIZE SIZE_T_SIZE
#define MIN_BLOCK_SIZE ALIGN(HDR_SIZE + LINK_SIZE + FTR_SIZE)

/* Pack a size, a allocated bit and a prev-allocated bit into a word */
#define PACK(size, alloc_prev, alloc) ((size)|(alloc_prev)|(alloc))

/* Read and write a word at address p */
#define GETW(p) (*(uint32 *) (p))  /* a word is 4 bytes */
#define GETD(p) (*(uint64 *) (p))  /* a dword is 8 bytes */
#define GETD(p) (*(uint64 *) (p))
#define GETS(p) (*(size_t *) (p))  /* a size_t length memory */

/* Read the size and allocaterd fileds from block header p */
#define GET_SIZE(p)       (GETS(p) & ~0x7)
#define GET_ALLOC(p)      (GETS(p) & 0x1)
#define GET_ALLOC_PREV(p) (GETS(p) & 0x2)

/* locate header and footer for a block address bp */
#define HDRP(bp)  ((char *) (bp))
#define FTRP(bp)  ((char *) (bp) + GET_SIZE(HDRP(bp)) - SIZE_T_SIZE)

/* Read and write node address at the 'next' and 'prev' slot for a free bp */
#define GET_SUCC_ADDR(fbp) (* ((char *) (fbp) + SIZE_T_SIZE))
#define GET_PRED_ADDR(fbp) (* ((char *) (fbp) + SIZE_T_SIZE + POINTER_SIZE))

/*
 * moving around blocks for a block address bp. The second command works only
 * if the previous block is free (check it by GET_ALLOC_PREV )
 */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(HDRP(bp) - SIZE_T_SIZE))

/* size range of SegList as power of 2 */
#define SIZE_SEGLIST_MIN 0
#define SIZE_SEGLIST_MAX (SIZE_SEGLIST_MIN)

/* a debug function, used privately */
void mm_check(void);

/*
 * private variables used by the allocator package.
 */
static char *mm_seglist_root;  /* points to root of the smallest SegList */
static char *mm_listp;         /* points to prologue block */

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
  /* alocate the root-nodes region */
  int total_roots = SIZE_SEGLIST_MAX - SIZE_SEGLIST_MIN + 1;
  mm_seglist_root = mem_sbrk(ALIGN(POINTER_SIZE * total_roots));

  /* initialize all SegList root with a null pointer */
  for (int i = 0; i < total_roots; i++) {
    *(mm_seglist_root + i) = 0;
  }

  /*
   * alway reserved two padding blcok to save boundary check
   *     One is prologue block, which is at a minimun size.
   *     The other one is epilogue block , which have a size 0 to indicate
   * the end.
   */
  mm_listp = mem_sbrk(ALIGN(SIZE_T_SIZE + SIZE_T_SIZE));
  GETS(mm_listp) = PACK(HDR_SIZE, 0x2, 0x1);
  GETS(HDRP(NEXT_BLKP(mm_listp))) = PACK(0, 0x2, 0x1);

  return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
  int newsize = ALIGN(size + SIZE_T_SIZE);
  void *p = mem_sbrk(newsize);
  if (p == (void *)-1)
	  return NULL;
  else {
    /* discard the epilogue block */
    GETS((char *) p - SIZE_T_SIZE) = PACK(newsize, 0x2, 0x1);
    /* reconstruct the epilogue block at the end */
    GETS((char *) p + newsize) = PACK(0, 0x2, 0x1);
    return p;
  }
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
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
   printf("(mm_check) Checks nothing.\n");
 }
