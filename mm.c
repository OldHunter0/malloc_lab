/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
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
    "Coding Never Giveup",
    /* First member's full name */
    "Fu Yuan",
    /* First member's email address */
    "707162858@qq.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1 << 12)

#define MAX(x, y) ((x) > (y) ? (x) : (y))

 /* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p) (*(unsigned int*)(p))
#define PUT(p, val) (*(unsigned int*)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char*)(bp)-WSIZE)
#define FTRP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE(((char*)(bp)-WSIZE)))
#define PREV_BLKP(bp) ((char*)(bp)-GET_SIZE(((char*)(bp)-DSIZE)))

/*Explicit free list,LIFO
Given free block ptr bp, compute address of next and previous free blocks in
free list*/
#define NEXT_FREE(bp) (GET((char*)(bp) + WSIZE))
#define PREV_FREE(bp) (GET(bp))

/* Given free block ptr bp, set the address of next and previous free blocks*/
#define SET_NEXT_FREE(bp,addr) PUT(((char*)(bp) + WSIZE), addr)
#define SET_PREV_FREE(bp, addr) PUT(bp, addr)

void *free_list_head;
void *free_list_tail;

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{

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

/* Given a block ptr bp, remove it from the explicit free list*/
void free_list_remove(void* bp)
{
    void* next = NEXT_FREE(bp);
    void* prev = PREV_FREE(bp);
    SET_NEXT_FREE(prev, next);
    SET_PREV_FREE(next, prev);
}

/* Given a new free block ptr bp, add it  */
void free_list_add(void* bp)
{
    
}

/* void *find_fit(size_t asize)
{
    char *bp;
    for(bp=heap_listp;GET_SIZE(HDRP(bp))>0;bp=NEXT_BLKP(bp)){
        if(!GET_ALLOCA(HDRP(bp))&&GET_SIZE(HDRP(bp))>=asize){
            return bp;
        }
    }
} */

/* static void place(void *bp,size_t asize)
{
    size_t origin_size=GET_SIZE(HDRP(bp));
    size_t next_size=origin_size-asize;
    if(next_size>16){
        PUT(HDRP(bp),PACK(asize,1));
        PUT(FTRP(bp),PACK(asize,1));
        bp=NEXT_BLKP(bp);
        PUT(HDRP(bp),PACK(next_size,0));
        PUT(FTRP(bp),PACK(next_size,0));
    }else{
        PUT(HDRP(bp),PACK(origin_size,0));
        PUT(FTRP(bp),PACK(origin_size,0));
    }
} */











