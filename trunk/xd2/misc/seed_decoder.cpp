// seed_decoder.cpp: implementation of the Cseed_decoder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "seed_decoder.h"

enum
{
	SAND,
	DUNES,
	ROCK,
	MOUNTAINS,
	SPICE,
};

#define A 0,0
#define B 2,0
#define C 4,0
#define D 0,2
#define E 2,2
#define F 4,2
#define G 0,4
#define H 2,4
#define I 4,4

const int PAIRCOUNT = 21;
int seed;

/* these are offsets used by matrix modifier */

const int offsets[] =
{
	0,
	-1,
	1,
	-16,
	16,
	-17,
	17,
	-15,
	15,
	-2,
	2,
	-32,
	32,
	-4,
	4,
	-64,
	64,
	-30,
	30,
	-34,
	34
};

/* these is array used to find corresponding points */
/*
      A·B·C    00··20··40
      ·····    ··········
      D·E·F    02··22··42
      ·····    ··········
      G·H·I    04··24··44
*/

const int offsets2[] =
{
	A,C, C,I, A,G, G,I, A,D, D,G,
	A,B, B,C, C,F, F,I, G,H, H,I,
	A,I, B,E, A,E, C,E, D,E, E,F,
	E,G, E,I, E,H,
	A,C, C,I, A,G, G,I, A,D, D,G,
	A,B, B,C, C,F, F,I, G,H, H,I,
	C,G, B,E, A,E, C,E, D,E, E,F,
	E,G, E,I, E,H
};

int random()
{
   unsigned char* s = (unsigned char* )&seed, a, b, x, y;

   a = *(s+0);
   x = (a & 0x2) >> 1;
   a >>= 2;
   b = *(s+2);
   y = (b & 0x80) >> 7;
   b <<= 1;
   b |= x;
   *(s+2) = b;
   b = *(s+1);
   x = (b & 0x80) >> 7;
   b <<= 1;
   b |= y;
   *(s+1) = b;
   x = 1 - x;
   b = *(s+0);
   a -= b + x;
   x = a & 0x1;
   a >>= 1;
   b = *(s+0);
   b >>= 1;
   b |= (x << 7);
   *(s+0) = b;
   a = *(s+0);
   b = *(s+1);
   a = (a | b) & (~(a & b));
   a &= 0xFF;
   return a;
}

/*
 * Replaces edges of regions with special numbers
 * (so converter knows which icons to use)
 * The technique is similiar to --> balanceMap
 */

void scanRegions(short map[64][64])
{
	short prevln[64], currln[64];
	for (int i = 0; i < 64; i++)
		currln[i] = map[0][i];
	for (int y = 0; y < 64; y++)
	{
		for (i = 0; i < 64; i++)
		{
			prevln[i] = currln[i];
			currln[i] = map[y][i];
		}
		for (int x = 0; x < 64; x++)
		{
			int middle = map[y][x];
			int left   = x ? currln[x-1] : middle;
			int up     = y ? prevln[x] : middle;
			int right  = x != 63 ? currln[x+1] : middle;
			int down   = y != 63 ? map[y+1][x] : middle;
			int id = (left == middle) << 3 | (down == middle) << 2 | (right == middle) << 1 | up == middle;
			if (middle == ROCK)
				id |= (left == MOUNTAINS) << 3 | (down == MOUNTAINS) << 2 | (right == MOUNTAINS) << 1 | up == MOUNTAINS;
			switch (middle)
			{
            case SAND:
				id = 0;
				break;
            case ROCK:
				id += 1;
				break;
            case DUNES:
				id += 0x11;
				break;
            case MOUNTAINS:
				id += 0x21;
				break;
            case SPICE:
				id += 0x31;
				break;
			}
			map[y][x] = id;
		}
	}
}

/*
 * creates terrain regions by replacing numbers within specified range
 */

void createRegions(short map[64][64])
{
   int rock = random() & 0xf;
   if (rock < 8)
	   rock = 8;
   else if (rock > 0xc)
	   rock = 0xc;
   int mountains = rock + 4;
   int dunes = (random() & 3) - 1;

   for (int y = 0; y < 64; y++)
   {
      for (int x = 0; x < 64; x++)
      {
         int num = map[y][x];
         int reg;
         if (num > mountains)
			 reg = MOUNTAINS;
         else if (num >= rock)
			 reg = ROCK;
         else if (num <= dunes)
			 reg = DUNES;
		 else
			 reg = SAND;
         map[y][x] = reg;
      }
   }
}

/*
 * Replaces each short with arithmetic mean of itself
 * and all eight neighbours.
 * As the new numbers are stored in the same array
 * the original line is stored in 'currln' and then copied
 * to 'prevln'.
 */

void balanceMap(short map[64][64])
{
   short prevln[64], currln[64];
   for (int i = 0; i < 64; i++)
      currln[i] = 0;
   for (int y = 0; y < 64; y++)
   {
      for (i = 0; i < 64; i++)
      {
         prevln[i] = currln[i];
         currln[i] = map[y][i];
      }
      for (int x = 0; x < 64; x++)
      {
         int lu = prevln[x-1],   u = prevln[x],   ru = prevln[x+1];
         int l  = currln[x-1],   c = currln[x],   r  = currln[x+1];
         int rd = map[y+1][x+1], d = map[y+1][x], ld = map[y+1][x-1];
         if (!x)  lu = l = ld = c; /* left edge */
         if (!y)  lu = u = ru = c; /* top edge*/
         if (x == 63) ru = r = rd = c; /* right edge */
         if (y == 63) ld = d = rd = c; /* bottom edge */
         map[y][x] = (lu + u + ru + r + rd + d + ld + l + c) / 9;
      }
   }
}

/*
 * "spreads" the matrix by replacing empty shorts with arithmetic
 * mean of two neighbors. Offsets needed to locate neighbors
 * are stored in 'offsets2' array.
 * in this part the generator has a tend to use 65 row of the map.
 * also the right border shorts are inproperly calculated.
 */

void spreadMatrix(short map[64][64])
{
   int diag = 0;
   for (int y = 0; y < 64; y += 4)
   {
      for (int x = 0; x < 64; x += 4)
      {
		 const int* offs = diag ? offsets2 : offsets2 + 4 * PAIRCOUNT;
         diag = 1 - diag;
         for (int i = 0; i < 21; i++)
         {
            int bx = x + *offs;
			int by = y + offs[1];
            int ex = x + offs[2];
			int ey = y + offs[3];
            int medx = bx + ex >> 1;
			int medy = by + ey >> 1;
            if (medx + 64 * medy < 64 * 64)
               map[medy][medx] = map[by][bx & 0x3f] + map[ey][ex & 0x3f] + 1 >> 1;
            offs += 4;
         }
      }
   }
}

/*
 * copies matrix on map
 * the height of 65 should be used to be best compatible
 * (the generator has a tend to use that extra row in spreadMatrix :)
 */

void copyMatrix(char* matrix, short map[65][64])
{
	for (int y = 0; y < 65; y++)
	{
		for (int x = 0; x < 64; x++)
			map[y][x] = 0;
	}
	int i = 0;
	for (y = 0; y < 64; y += 4)
	{
		for (int x = 0; x < 64; x += 4)
			map[y][x] = matrix[i++];
	}
}

void createMatrix(char* matrix)
{
	for (int i = 0; i < 16 * 17; i++)
	{
		int v = random();
		matrix[i] = min(v & 0xf, 10);
	}
	matrix[i] = 0;
}

void addNoise1(char* matrix)
{
   for (int count = random() & 0xf; count >= 0 ; count--)
   {
      int ncell = random() & 0xff;
      for (int i = 0; i < 21; i++)
      {
         int cell = min(max(ncell + offsets[i], 0), 16 * 17);
         matrix[cell] = matrix[cell] + random() & 0xf;
      }
   }
}

void addNoise2(char* matrix)
{
	for (int count = random() & 3; count >= 0; count--)
	{
		int ncell = random() & 0xff;
		for (int i = 0; i < 21; i++)
			matrix[min(max(ncell + offsets[i], 0), 16 * 17)] = random() & 3;
	}
}

void Cseed_decoder::decode(int seed, byte* _map)
{
	::seed = seed;
	char matrix[16 * 17 + 1];
	createMatrix(matrix);
	addNoise1(matrix);
	addNoise2(matrix);

	short map[65][64];
	copyMatrix(matrix, map);
	spreadMatrix(map);

	balanceMap(map);
	createRegions(map);
	scanRegions(map);

	for (int i = 0; i < 0x1000; i++)
		_map[i] = map[i >> 6][i & 0x3f];
}