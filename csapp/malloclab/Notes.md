# Notes for malloclab

The lab implements a segregated free list, with size classes partitioned by
power of 2. That is, each size class have block size ranges like {8~15},
{16 ~ 31}, etc.

The segregated lists are accessed from a list of root nodes allocated at the
bottom of heap. Each root node is just a pointer pointing to a free successor
block or equal to NULL pointer is no free block exists in its size class.

## Reminder
- try to use advanced gdb if having hard time in debugging! (see recitation for
  malloc).

## Progress (TODOs)

- complete malloc to look up free list 
- implement free
