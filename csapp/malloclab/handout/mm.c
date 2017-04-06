/*
 * mm-naive.c - The fastest, best memory-efficient malloc package.
 *
 * In this approach, a bunch of segregated free list of fixed size-range
 * is maintained by the allocator. This allow log-time free and constant
 * overhead for the segregated list structure.
 *
 * At the head region of the heap, we maitained a fixed size array of root
 * pointers for all size class.For a
 * SegList of size k, it store free blocks of size up to 2^k bytes.
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

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

/* Pack a size, a allocated bit and a prev-allocated bit into a word */
#define PACK(size, alloc, allco_prev) ((size)|(alloc)|(allco_prev))

/* Read and write a word at address p */
#define GET(p)      (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

/* Read and write node address at the 'next' and 'prev' slot */
//#define GET_NEXT(p)  

/* size of some overhead */
#define SIZE_T_SIZE 8
#define POINTER_SIZE (sizeof(void *))
#define ROOT_NODE_SIZE POINTER_SIZE
#define HDR_SIZE (SIZE_T_SIZE + POINTER_SIZE + POINTER_SIZE)

/* size range of SegList as power of 2 */
#define SIZE_SEGLIST_MIN 1
#define SIZE_SEGLIST_MAX (SIZE_SEGLIST_MIN)

/* a debug function, used privately */
void mm_check(void);

/*
 * private variables used by the allocator package.
 */
static char *mm_seglist_root;  /* points to root of the smallest SegList */

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
  /* alocate the root-nodes block */
  int total_roots = SIZE_SEGLIST_MAX - SIZE_SEGLIST_MIN + 1;
  mm_seglist_root = mem_sbrk(ALIGN(ROOT_NODE_SIZE * total_roots));

  /* initialize all SegList with a free block of maximum size */
  size_t max_size = 1 << SIZE_SEGLIST_MIN;
  for (int i = 0; i < total_roots; i++, max_size << 1) {
    char *block_start = (char *)mem_sbrk(ALIGN(HEADER_SIZE + max_size));
    PUT(block_start, PACK(max_size, 0x2, 0);
    *(block_start + 1) = 0;                    /* points next to null */
    *(block_start + 2) = mm_seglist_root + i;  /* points back to root */
    *(mm_seglist_root + i) = block_start;      /* root points to this block */
  }

    mm_check();
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
        *(size_t *)p = size;
        return (void *)((char *)p + SIZE_T_SIZE);
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
