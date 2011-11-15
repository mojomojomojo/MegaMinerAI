#ifndef ENUMSH_H
#define ENUMSH_H

typedef enum
{
	EMPTY,   // 0 No one owns
	WALL,    // 1 Can not traverse onto
	OPBASE,  // 2 Opponents base
	MYBASE,  // 3 My base
	OP,      // 4 Opponent owned computer
	MY,      // 5 a computer I own resides here
	MYVIRUS, // 6 my virus
	OPVIRUS, // 7 Opponent virus
	VOID     // 8 VOID TYPE
}MAPCODE;

typedef enum {
  North = 0,
  East,
  South,
  West,
  NumDirections, // non-obvious, but legal
} Direction_t;

typedef enum {
  FoundPath,
  NoPath,
  NoPathRightNow,
} PathType;

#endif
