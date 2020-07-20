/*
 *  string.h
 *
 *  Copyright 1987, 1992 by Sierra Systems.  All rights reserved.
 */

#ifndef STRING_H
#define STRING_H

#ifndef size_t
typedef unsigned long size_t;	/* type returned by sizeof operator	   */
#endif /* size_t */

#define NULL (void *)0

void* memcpy(void *s1, const void *s2, size_t count);
void *memmove(void *s1, const void *s2, size_t count);
void *memset(void *str, int c, size_t count);

/*--------------------------------- memcpy() --------------------------------*/

/*
 * memcpy is a standard C library function which performs fast memory
 * from a source buffer to a destination buffer.  memcpy() does as much of
 * the data transfer as possible using integer assignments, and minimizes
 * loop overhead by grouping several assignments within each control loop.
 * For the most efficient copy, buffer alignments must permit integer
 * transfers.  For instance, if one begins at an odd address, and the other
 * begins at an even address, it is not possible to do integer data
 * transfers.  On the other hand, if the buffer locations are equal mod 2,
 * int data type transfers can be used.
 *
 * (1) Alignment of the buffers is checked first.  If they are both at
 * even or both at odd addresses, 0-3 byte copies are done to align the
 * destination buffer to a long boundary.  Otherwise control moves to the
 * byte transfer part of the function.	(2) Next, 0-7 int copies are done so
 * that the remaining number of integers to be copied is a multiple of 8.
 * (3) Integer copies are done 8 at a time within a single loop.  (4) The
 * remaining bytes are copied using the same algorithm.
 *
 * Usage:
 *
 *	void *memcpy(void *dest, const void *src, size_t count)
 *
 *	dest ---- a pointer to the destination location
 *	src ----- a pointer to the source location
 *	count --- the number of bytes to be initialized
 *	return -- returns the value of dest
 */

void *memcpy(void *dest, const void *src, register size_t count)
{
    register long *idest;
    register long *isource;
    register long num_iter;
    register long num_longs;
    register char *dest1;
    register char *source;

    source = src;
    dest1 = dest;

    if( (long)count < 0 )
	count = 0;

    /* Test to see if buffer boundaries allow integer transfers.  If so, */
    /* do the alignment, otherwise, skip to the byte transfer part of	 */
    /* of the function.							 */

    if( !((dest1 - source) & 0x1) && (count >= 4) ) {
	switch( (int)dest1 & 0x3 ) {
	case 1: *dest1++ = *source++; --count;
	case 2: *dest1++ = *source++; --count;
	case 3: *dest1++ = *source++; --count;
	}

	num_longs = count >> 2;
	num_iter = num_longs >> 3;
	idest = (long *)dest1;
	isource = (long *)source;

	switch( num_longs & 0x07 ) {	
	    while( --num_iter != -1 ) {
		*idest++ = *isource++;
	case 7: *idest++ = *isource++;
	case 6: *idest++ = *isource++;
	case 5: *idest++ = *isource++;
	case 4: *idest++ = *isource++;
	case 3: *idest++ = *isource++;
	case 2: *idest++ = *isource++;
	case 1: *idest++ = *isource++;
	case 0: ;
	    }
	}

	dest1 = (char *)idest;
	source = (char *)isource;

	/* there are at most 3 characters left -- copy them */

	switch( count & 0x3 ) {
	case 3: *dest1++ = *source++;
	case 2: *dest1++ = *source++;
	case 1: *dest1++ = *source++;
	}
    }
    else {
	num_iter = count >> 3;

	/* Reaching here indicates boundaries were not equal mod 2 or */
	/* there were fewer than 4 bytes to be transfered.	      */

	switch(count & 0x7) {
	    while( --num_iter != -1 ) {
		*dest1++ = *source++;
	case 7: *dest1++ = *source++;
	case 6: *dest1++ = *source++;
	case 5: *dest1++ = *source++;
	case 4: *dest1++ = *source++;
	case 3: *dest1++ = *source++;
	case 2: *dest1++ = *source++;
	case 1: *dest1++ = *source++;
	case 0: ;
	    }
	}
    }
    return(dest);
}

/*-------------------------------- memmove() --------------------------------*/

/*
 * memmove copies count characters from the object pointed to by s2 into the
 * object pointed to by s1.  The copying takes place as if the count
 * characters from the object pointed to by s2 are copied into a buffer that
 * does not overlap the objects pointed to by either s1 or s2, and then count
 * characters from the buffer are copied into the object pointed to by s2.
 * memmove() returns the value of s1.
 *
 * If it is known that the objects do not overlap, a much faster (but larger)
 * function memcpy() can be used.
 */

void *memmove(void *s1, const void *s2, register size_t count)
{
    register char *ptr1;
    register char *ptr2;

    ptr1 = s1;
    ptr2 = s2;

    if( ptr2 > ptr1 ) {
	while( --count != -1 )
	    *ptr1++ = *ptr2++;
	return(s1);
    }

    ptr2 += count;
    ptr1 += count;
    while( --count != -1 )
	*--ptr1 = *--ptr2;
    return(s1);
}

/*--------------------------------- memset() --------------------------------*/

/*
 * memset is a standard C library function which initializes a memory area
 * with a specified character.	memset() does as much of the initialization
 * as possible using integer assignments, and minimizes loop overhead by
 * grouping several assignments within each control loop.  Note, memset() has
 * a smaller but slower counterpart _memset() in the library that is about
 * 10 times slower than this version.
 *
 * Usage:
 *
 *	void *memset(void *dest, int c, size_t count)
 *
 *	dest ---- a pointer to the destination location
 *	c ------- the character with which the memory is to be initialized
 *	count --- the number of bytes to be initialized
 *	return -- returns the value of dest
 */

void *memset(void *dest, register int c, register size_t count)
{
    register long *ldest;
    register long fourbytes;
    register long num_long_iter;
    register long num_longs;
    register long temp;
    register char *dest1;

    dest1 = dest;

    if( count <= 3 )
	goto three_or_less;

    temp = (unsigned char)c;
    fourbytes = temp;
    fourbytes += temp << 8;
    fourbytes += fourbytes << 16;

    switch( (int)dest1 & 0x03 ) {	/* align to an integer boundary */
    case 1: *dest1++ = c; --count;
    case 2: *dest1++ = c; --count;
    case 3: *dest1++ = c; --count;
    }
    num_longs = count >> 2;		/* remaining number of longs	*/
    num_long_iter = num_longs >> 3;	/* number of 8-at-a-time loops	*/
    ldest = (long *)dest1;

    /* align to multiple of 8 assignments at a time using switch */

    switch( num_longs & 0x7 ) {

	while( --num_long_iter != -1 ) {
	    *ldest++ = fourbytes;
    case 7: *ldest++ = fourbytes;
    case 6: *ldest++ = fourbytes;
    case 5: *ldest++ = fourbytes;
    case 4: *ldest++ = fourbytes;
    case 3: *ldest++ = fourbytes;
    case 2: *ldest++ = fourbytes;
    case 1: *ldest++ = fourbytes;
    case 0: ;
	}
    }

    dest1 = (char *)ldest;

    /* there are now at most 3 characters remaining */

three_or_less:
    switch( (int)count & 0x3 ) {
	case 3:	*dest1++ = c;
	case 2:	*dest1++ = c;
	case 1:	*dest1++ = c;
    }

    return(dest);
}

#endif /* STRING_H */
