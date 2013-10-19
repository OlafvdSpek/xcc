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

static int g_seed;

static int random()
{
	unsigned char* s = reinterpret_cast<unsigned char*>(&g_seed);
	char t[3];
	t[0] = ~(s[0] >> 2 ^ s[0] ^ s[1] >> 7) << 7 | s[0] >> 1;
	t[1] = s[1] << 1 | s[2] >> 7;
	t[2] = s[2] << 1 | s[0] >> 1 & 1;
	memcpy(&g_seed, t, 3);
	return s[0] ^ s[1];
}

/*
 * Replaces edges of regions with special numbers
 * (so converter knows which icons to use)
 * The technique is similiar to --> balanceMap
 */

static void scanRegions(byte map[64][64])
{
	byte prevln[64], currln[64];
	for (int i = 0; i < 64; i++)
		currln[i] = map[0][i];
	for (int y = 0; y < 64; y++)
	{
		for (int i = 0; i < 64; i++)
		{
			prevln[i] = currln[i];
			currln[i] = map[y][i];
		}
		for (int x = 0; x < 64; x++)
		{
			int middle = map[y][x];
			int left   = x ? currln[x - 1] : middle;
			int up     = y ? prevln[x] : middle;
			int right  = x != 63 ? currln[x + 1] : middle;
			int down   = y != 63 ? map[y + 1][x] : middle;
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

static void createRegions(byte map[64][64])
{
	int rock = min(max(random() & 0xf, 8), 0xc);
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
 * Replaces each byte with arithmetic mean of itself
 * and all eight neighbours.
 * As the new numbers are stored in the same array
 * the original line is stored in 'currln' and then copied
 * to 'prevln'.
 */

static void balanceMap(byte map[64][64])
{
	byte prevln[64], currln[64];
	for (int i = 0; i < 64; i++)
		currln[i] = 0;
	for (int y = 0; y < 64; y++)
	{
		for (int i = 0; i < 64; i++)
		{
			prevln[i] = currln[i];
			currln[i] = map[y][i];
		}
		for (int x = 0; x < 64; x++)
		{
			int lu = prevln[x-1],   u = prevln[x],   ru = prevln[x+1];
			int l  = currln[x-1],   c = currln[x],   r  = currln[x+1];
			int rd = map[y+1][x+1], d = map[y+1][x], ld = map[y+1][x-1];
			if (!x)
				lu = l = ld = c; /* left edge */
			else if (x == 63)
				ru = r = rd = c; /* right edge */
			if (!y)
				lu = u = ru = c; /* top edge*/
			else if (y == 63)
				ld = d = rd = c; /* bottom edge */
			map[y][x] = (lu + u + ru + r + rd + d + ld + l + c) / 9;
		}
	}
}

#define A 0,0
#define B 2,0
#define C 4,0
#define D 0,2
#define E 2,2
#define F 4,2
#define G 0,4
#define H 2,4
#define I 4,4

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

/*
 * "spreads" the matrix by replacing empty bytes with arithmetic
 * mean of two neighbors. Offsets needed to locate neighbors
 * are stored in 'offsets2' array.
 * in this part the generator has a tend to use 65 row of the map.
 * also the right border bytes are inproperly calculated.
 */

static void spreadMatrix(byte map[64][64])
{
	int diag = 0;
	for (int y = 0; y < 64; y += 4)
	{
		for (int x = 0; x < 64; x += 4)
		{
			const int* offs = diag ? offsets2 : offsets2 + 84;
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

static void copyMatrix(char* matrix, byte map[65][64])
{
	for (int y = 0; y < 65; y++)
	{
		for (int x = 0; x < 64; x++)
			map[y][x] = 0;
	}
	int i = 0;
	for (int y = 0; y < 64; y += 4)
	{
		for (int x = 0; x < 64; x += 4)
			map[y][x] = matrix[i++];
	}
}

static void createMatrix(char* matrix)
{
	for (int i = 0; i < 16 * 17; i++)
	{
		int v = random();
		matrix[i] = min(v & 0xf, 10);
	}
	matrix[272] = 0;
}

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

static void addNoise1(char* matrix)
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

static void addNoise2(char* matrix)
{
	for (int count = random() & 3; count >= 0; count--)
	{
		int ncell = random() & 0xff;
		for (int i = 0; i < 21; i++)
			matrix[min(max(ncell + offsets[i], 0), 16 * 17)] = random() & 3;
	}
}

void decode_seed(int seed, byte* _map)
{
	g_seed = seed;
	char matrix[16 * 17 + 1];
	createMatrix(matrix);
	addNoise1(matrix);
	addNoise2(matrix);

	byte map[65][64];
	copyMatrix(matrix, map);
	spreadMatrix(map);

	balanceMap(map);
	createRegions(map);
	scanRegions(map);

	memcpy(_map, map, 0x1000);
}