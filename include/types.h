#ifndef TYPES_H
#define TYPES_H

/** @file include/types.h Basic definitions and data types. */

#define BIT_S8  int8
#define BIT_S16 int16
#define BIT_S32 int32
#define BIT_U8  uint8
#define BIT_U16 uint16
#define BIT_U32 uint32

typedef unsigned char  uint8;
typedef   signed char   int8;
typedef unsigned short uint16;
typedef   signed short  int16;
typedef unsigned int   uint32;
typedef   signed int    int32;

typedef uint32 tile32;

#ifndef bool
typedef unsigned char bool;
#define false 0
#define true 1
#endif /* bool */

#endif /* TYPES_H */
