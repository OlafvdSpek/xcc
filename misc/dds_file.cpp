#include "stdafx.h"
#include "dds_file.h"

struct DXTColBlock
{
	WORD col0;
	WORD col1;

	// no bit fields - use bytes
	BYTE row[4];
};

struct DXTAlphaBlockExplicit
{
	WORD row[4];
};

struct DXTAlphaBlock3BitLinear
{
	BYTE alpha0;
	BYTE alpha1;

	BYTE stuff[6];
};



// use cast to struct instead of RGBA_MAKE as struct is
//  much
struct Color8888
{
	BYTE r;		// change the order of names to change the 
	BYTE g;		//  order of the output ARGB or BGRA, etc...
	BYTE b;		//  Last one is MSB, 1st is LSB.
	BYTE a;
};


struct Color565
{
	unsigned nBlue  : 5;		// order of names changes
	unsigned nGreen : 6;		//  byte order of output to 32 bit
	unsigned nRed	: 5;
};






void GetColorBlockColors( DXTColBlock * pBlock, Color8888 * col_0, Color8888 * col_1, 
													 Color8888 * col_2, Color8888 * col_3,
													 WORD & wrd  )
{
	// There are 4 methods to use - see the Time_ functions.
	// 1st = shift = does normal approach per byte for color comps
	// 2nd = use freak variable bit field color565 for component extraction
	// 3rd = use super-freak DWORD adds BEFORE shifting the color components
	//  This lets you do only 1 add per color instead of 3 BYTE adds and
	//  might be faster
	// Call RunTimingSession() to run each of them & output result to txt file

 
	// freak variable bit structure method
	// normal math
	// This method is fastest

	Color565 * pCol;

	pCol = (Color565*) & (pBlock->col0 );

	col_0->a = 0xff;
	col_0->r = pCol->nRed;
	col_0->r <<= 3;				// shift to full precision
	col_0->g = pCol->nGreen;
	col_0->g <<= 2;
	col_0->b = pCol->nBlue;
	col_0->b <<= 3;

	pCol = (Color565*) & (pBlock->col1 );
	col_1->a = 0xff;
	col_1->r = pCol->nRed;
	col_1->r <<= 3;				// shift to full precision
	col_1->g = pCol->nGreen;
	col_1->g <<= 2;
	col_1->b = pCol->nBlue;
	col_1->b <<= 3;


	if( pBlock->col0 > pBlock->col1 )
	{
		// Four-color block: derive the other two colors.    
		// 00 = color_0, 01 = color_1, 10 = color_2, 11 = color_3
		// These two bit codes correspond to the 2-bit fields 
		// stored in the 64-bit block.

		wrd = ((WORD)col_0->r * 2 + (WORD)col_1->r )/3;
											// no +1 for rounding
											// as bits have been shifted to 888
		col_2->r = (BYTE)wrd;

		wrd = ((WORD)col_0->g * 2 + (WORD)col_1->g )/3;
		col_2->g = (BYTE)wrd;

		wrd = ((WORD)col_0->b * 2 + (WORD)col_1->b )/3;
		col_2->b = (BYTE)wrd;
		col_2->a = 0xff;

		wrd = ((WORD)col_0->r + (WORD)col_1->r *2 )/3;
		col_3->r = (BYTE)wrd;

		wrd = ((WORD)col_0->g + (WORD)col_1->g *2 )/3;
		col_3->g = (BYTE)wrd;

		wrd = ((WORD)col_0->b + (WORD)col_1->b *2 )/3;
		col_3->b = (BYTE)wrd;
		col_3->a = 0xff;

	}
	else
	{
		// Three-color block: derive the other color.
		// 00 = color_0,  01 = color_1,  10 = color_2,  
		// 11 = transparent.
		// These two bit codes correspond to the 2-bit fields 
		// stored in the 64-bit block. 

		// explicit for each component, unlike some refrasts...
		
		// TRACE("block has alpha\n");

		wrd = ((WORD)col_0->r + (WORD)col_1->r )/2;
		col_2->r = (BYTE)wrd;
		wrd = ((WORD)col_0->g + (WORD)col_1->g )/2;
		col_2->g = (BYTE)wrd;
		wrd = ((WORD)col_0->b + (WORD)col_1->b )/2;
		col_2->b = (BYTE)wrd;
		col_2->a = 0xff;

		col_3->r = 0x00;		// random color to indicate alpha
		col_3->g = 0xff;
		col_3->b = 0xff;
		col_3->a = 0x00;

	}
}			//  Get color block colors (...)



void DecodeColorBlock( DWORD * pImPos, DXTColBlock * pColorBlock, int width,
								DWORD * col_0,
								DWORD * col_1, DWORD * col_2, DWORD * col_3 )
{
	// width is width of image in pixels


	DWORD bits;
	int r,n;

	// bit masks = 00000011, 00001100, 00110000, 11000000
	const DWORD masks[] = { 3, 12, 3 << 4, 3 << 6 };
	const int   shift[] = { 0, 2, 4, 6 };

	// r steps through lines in y
	for( r=0; r < 4; r++, pImPos += width-4 )	// no width*4 as DWORD ptr inc will *4
	{

		// width * 4 bytes per pixel per line
		// each j dxtc row is 4 lines of pixels

		// pImPos = (DWORD*)((DWORD)pBase + i*16 + (r+j*4) * ddsd.dwWidth * 4 );

		// n steps through pixels
		for( n=0; n < 4; n++ )
		{
			bits =		pColorBlock->row[r] & masks[n];
			bits >>=	shift[n];

			switch( bits )
			{
			case 0 :
				*pImPos = *col_0;
				pImPos++;		// increment to next DWORD
				break;
			case 1 :
				*pImPos = *col_1;
				pImPos++;
				break;
			case 2 :
				*pImPos = *col_2;
				pImPos++;
				break;
			case 3 :
				*pImPos = *col_3;
				pImPos++;
				break;
			default:
				assert(false);
			}
		}
	}
}



void  DecodeAlphaExplicit( DWORD * pImPos, DXTAlphaBlockExplicit * pAlphaBlock,
								  int width, DWORD alphazero )
{
	// alphazero is a bit mask that when & with the image color
	//  will zero the alpha bits, so if the image DWORDs  are
	//  ARGB then alphazero will be 0x00ffffff or if
	//  RGBA then alphazero will be 0xffffff00
	//  alphazero constructed automaticaly from field order of Color8888 structure

	// decodes to 32 bit format only


	int row, pix;

	WORD wrd;

	Color8888 col;
	col.r = col.g = col.b = 0;


	//TRACE("\n");

	for( row=0; row < 4; row++, pImPos += width-4 )
	{
		// pImPow += pImPos += width-4 moves to next row down

		wrd = pAlphaBlock->row[ row ];

		// TRACE("0x%.8x\t\t", wrd);

		for( pix = 0; pix < 4; pix++ )
		{
			// zero the alpha bits of image pixel
			*pImPos &= alphazero;

			col.a = wrd & 0x000f;		// get only low 4 bits
//			col.a <<= 4;				// shift to full byte precision
										// NOTE:  with just a << 4 you'll never have alpha
										// of 0xff,  0xf0 is max so pure shift doesn't quite
										// cover full alpha range.
										// It's much cheaper than divide & scale though.
										// To correct for this, and get 0xff for max alpha,
										//  or the low bits back in after left shifting
			col.a = col.a | (col.a << 4 );	// This allows max 4 bit alpha to be 0xff alpha
											//  in final image, and is crude approach to full 
											//  range scale

			*pImPos |= *((DWORD*)&col);	// or the bits into the prev. nulled alpha

			wrd >>= 4;		// move next bits to lowest 4

			pImPos++;		// move to next pixel in the row

		}
	}
}




BYTE		gBits[4][4];
WORD		gAlphas[8];
Color8888	gACol[4][4];


void DecodeAlpha3BitLinear( DWORD * pImPos, DXTAlphaBlock3BitLinear * pAlphaBlock,
									int width, DWORD alphazero)
{

	gAlphas[0] = pAlphaBlock->alpha0;
	gAlphas[1] = pAlphaBlock->alpha1;

	
	// 8-alpha or 6-alpha block?    

	if( gAlphas[0] > gAlphas[1] )
	{
		// 8-alpha block:  derive the other 6 alphas.    
		// 000 = alpha_0, 001 = alpha_1, others are interpolated

		gAlphas[2] = ( 6 * gAlphas[0] +     gAlphas[1]) / 7;	// bit code 010
		gAlphas[3] = ( 5 * gAlphas[0] + 2 * gAlphas[1]) / 7;	// Bit code 011    
		gAlphas[4] = ( 4 * gAlphas[0] + 3 * gAlphas[1]) / 7;	// Bit code 100    
		gAlphas[5] = ( 3 * gAlphas[0] + 4 * gAlphas[1]) / 7;	// Bit code 101
		gAlphas[6] = ( 2 * gAlphas[0] + 5 * gAlphas[1]) / 7;	// Bit code 110    
		gAlphas[7] = (     gAlphas[0] + 6 * gAlphas[1]) / 7;	// Bit code 111
	}    
	else
	{
		// 6-alpha block:  derive the other alphas.    
		// 000 = alpha_0, 001 = alpha_1, others are interpolated

		gAlphas[2] = (4 * gAlphas[0] +     gAlphas[1]) / 5;	// Bit code 010
		gAlphas[3] = (3 * gAlphas[0] + 2 * gAlphas[1]) / 5;	// Bit code 011    
		gAlphas[4] = (2 * gAlphas[0] + 3 * gAlphas[1]) / 5;	// Bit code 100    
		gAlphas[5] = (    gAlphas[0] + 4 * gAlphas[1]) / 5;	// Bit code 101
		gAlphas[6] = 0;										// Bit code 110
		gAlphas[7] = 255;									// Bit code 111
	}


	// Decode 3-bit fields into array of 16 BYTES with same value

	// first two rows of 4 pixels each:
	// pRows = (Alpha3BitRows*) & ( pAlphaBlock->stuff[0] );
	const DWORD mask = 0x00000007;		// bits = 00 00 01 11

	DWORD bits = *( (DWORD*) & ( pAlphaBlock->stuff[0] ));

	gBits[0][0] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[0][1] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[0][2] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[0][3] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[1][0] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[1][1] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[1][2] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[1][3] = (BYTE)( bits & mask );

	// now for last two rows:

	bits = *( (DWORD*) & ( pAlphaBlock->stuff[3] ));		// last 3 bytes

	gBits[2][0] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[2][1] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[2][2] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[2][3] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[3][0] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[3][1] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[3][2] = (BYTE)( bits & mask );
	bits >>= 3;
	gBits[3][3] = (BYTE)( bits & mask );


	// decode the codes into alpha values
	int row, pix;


	for( row = 0; row < 4; row++ )
	{
		for( pix=0; pix < 4; pix++ )
		{
			gACol[row][pix].a = (BYTE) gAlphas[ gBits[row][pix] ];

			assert( gACol[row][pix].r == 0 );
			assert( gACol[row][pix].g == 0 );
			assert( gACol[row][pix].b == 0 );
		}
	}



	// Write out alpha values to the image bits

	for( row=0; row < 4; row++, pImPos += width-4 )
	{
		// pImPow += pImPos += width-4 moves to next row down

		for( pix = 0; pix < 4; pix++ )
		{
			// zero the alpha bits of image pixel
			*pImPos &=  alphazero;

			*pImPos |=  *((DWORD*) &(gACol[row][pix]));	// or the bits into the prev. nulled alpha
			pImPos++;
		}
	}
}

Cvirtual_binary DecompressDXT1(const DDSURFACEDESC2& ddsd, const byte* s)
{	
	Cvirtual_binary d(NULL, ddsd.dwWidth * ddsd.dwHeight << 2);
	int xblocks = ddsd.dwWidth / 4;
	int yblocks = ddsd.dwHeight / 4;

	int i,j;

	byte* m_pCompBytes = const_cast<byte*>(s);
	byte* m_pDecompBytes = d.data_edit();

	DWORD * pBase  = (DWORD*)  m_pDecompBytes;
	DWORD * pImPos = (DWORD*)  pBase;			// pos in decompressed data
	WORD  * pPos   = (WORD*)   m_pCompBytes;	// pos in compressed data

	DXTColBlock * pBlock;

	Color8888 col_0, col_1, col_2, col_3;

	WORD wrd;
	for( j=0; j < yblocks; j++ )
	{
		// 8 bytes per block
		pBlock = (DXTColBlock*) ( (DWORD)m_pCompBytes + j * xblocks * 8 );


		for( i=0; i < xblocks; i++, pBlock++ )
		{
			GetColorBlockColors( pBlock, &col_0, &col_1, &col_2, &col_3, wrd );

			// now decode the color block into the bitmap bits
			// inline func:

			pImPos = (DWORD*)((DWORD)pBase + i*16 + (j*4) * ddsd.dwWidth * 4 );

			DecodeColorBlock( pImPos, pBlock, ddsd.dwWidth, (DWORD*)&col_0, (DWORD*)&col_1,
								(DWORD*)&col_2, (DWORD*)&col_3 );


			// Set to RGB test pattern
			//	pImPos = (DWORD*)((DWORD)pBase + i*4 + j*ddsd.dwWidth*4);
			//	*pImPos = ((i*4) << 16) | ((j*4) << 8 ) | ( (63-i)*4 );

			// checkerboard of only col_0 and col_1 basis colors:
			//	pImPos = (DWORD*)((DWORD)pBase + i*8 + j*ddsd.dwWidth*8);
			//	*pImPos = *((DWORD*)&col_0);
			//	pImPos += 1 + ddsd.dwWidth;
			//	*pImPos = *((DWORD*)&col_1);

		}
	}
	return d;
}

Cvirtual_binary DecompressDXT2(const DDSURFACEDESC2& ddsd, const byte* s)
{
	// Cvirtual_binary d(NULL, ddsd.dwWidth * ddsd.dwHeight << 2);
	// Can do color & alpha same as dxt3, but color is pre-multiplied 
	//   so the result will be wrong unless corrected. 
	// DecompressDXT3();

	assert(false);
	return Cvirtual_binary();
}

Cvirtual_binary DecompressDXT3(const DDSURFACEDESC2& ddsd, const byte* s)
{
	Cvirtual_binary d(NULL, ddsd.dwWidth * ddsd.dwHeight << 2);
	int xblocks = ddsd.dwWidth / 4;
	int yblocks = ddsd.dwHeight / 4;
	
	int i,j;

	byte* m_pCompBytes = const_cast<byte*>(s);
	byte* m_pDecompBytes = d.data_edit();

	DWORD * pBase  = (DWORD*)  m_pDecompBytes;
	DWORD * pImPos = (DWORD*)  pBase;			// pos in decompressed data
	WORD  * pPos   = (WORD*)   m_pCompBytes;	// pos in compressed data

	DXTColBlock				* pBlock;
	DXTAlphaBlockExplicit	* pAlphaBlock;

	Color8888 col_0, col_1, col_2, col_3;


	WORD wrd;

	// fill alphazero with appropriate value to zero out alpha when
	//  alphazero is ANDed with the image color 32 bit DWORD:
	col_0.a = 0;
	col_0.r = col_0.g = col_0.b = 0xff;
	DWORD alphazero = *((DWORD*) &col_0);



	//	TRACE("blocks: x: %d    y: %d\n", xblocks, yblocks );

	for( j=0; j < yblocks; j++ )
	{
		// 8 bytes per block
		// 1 block for alpha, 1 block for color

		pBlock = (DXTColBlock*) ( (DWORD)m_pCompBytes + j * xblocks * 16 );

		for( i=0; i < xblocks; i++, pBlock ++ )
		{

			// inline
			// Get alpha block

			pAlphaBlock = (DXTAlphaBlockExplicit*) pBlock;

			// inline func:
			// Get color block & colors
			pBlock++;
			GetColorBlockColors( pBlock, &col_0, &col_1, &col_2, &col_3, wrd );

			// Decode the color block into the bitmap bits
			// inline func:

			pImPos = (DWORD*)((DWORD)pBase + i*16 + (j*4) * ddsd.dwWidth * 4 );


			DecodeColorBlock( pImPos, pBlock, ddsd.dwWidth, (DWORD*)&col_0, (DWORD*)&col_1,
								(DWORD*)&col_2, (DWORD*)&col_3 );

			// Overwrite the previous alpha bits with the alpha block
			//  info
			// inline func:
			DecodeAlphaExplicit( pImPos, pAlphaBlock, ddsd.dwWidth, alphazero );


		}
	}
	return d;
}

Cvirtual_binary DecompressDXT4(const DDSURFACEDESC2& ddsd, const byte* s)
{
	Cvirtual_binary d(NULL, ddsd.dwWidth * ddsd.dwHeight << 2);
	// Can do color & alpha same as dxt5, but color is pre-multiplied 
	//   so the result will be wrong unless corrected. 
	// DecompressDXT5();

	assert(false);
	return Cvirtual_binary();	
}

Cvirtual_binary DecompressDXT5(const DDSURFACEDESC2& ddsd, const byte* s)
{
	Cvirtual_binary d(NULL, ddsd.dwWidth * ddsd.dwHeight << 2);
	int xblocks = ddsd.dwWidth / 4;
	int yblocks = ddsd.dwHeight / 4;

	int i,j;

	byte* m_pCompBytes = const_cast<byte*>(s);
	byte* m_pDecompBytes = d.data_edit();
	
	DWORD * pBase  = (DWORD*)  m_pDecompBytes;
	DWORD * pImPos = (DWORD*)  pBase;			// pos in decompressed data
	WORD  * pPos   = (WORD*)   m_pCompBytes;	// pos in compressed data

	DXTColBlock				* pBlock;
	DXTAlphaBlock3BitLinear * pAlphaBlock;

	Color8888 col_0, col_1, col_2, col_3;
	WORD wrd;

	// fill alphazero with appropriate value to zero out alpha when
	//  alphazero is ANDed with the image color 32 bit DWORD:
	col_0.a = 0;
	col_0.r = col_0.g = col_0.b = 0xff;
	DWORD alphazero = *((DWORD*) &col_0);

	////////////////////////////////
	//	TRACE("blocks: x: %d    y: %d\n", xblocks, yblocks );

	for( j=0; j < yblocks; j++ )
	{
		// 8 bytes per block
		// 1 block for alpha, 1 block for color

		pBlock = (DXTColBlock*) ( (DWORD)m_pCompBytes + j * xblocks * 16 );

		for( i=0; i < xblocks; i++, pBlock ++ )
		{

			// inline
			// Get alpha block

			pAlphaBlock = (DXTAlphaBlock3BitLinear*) pBlock;

			// inline func:
			// Get color block & colors
			pBlock++;

			// TRACE("pBlock:   0x%.8x\n", pBlock );

			GetColorBlockColors( pBlock, &col_0, &col_1, &col_2, &col_3, wrd );

			// Decode the color block into the bitmap bits
			// inline func:

			pImPos = (DWORD*)((DWORD)pBase + i*16 + (j*4) * ddsd.dwWidth * 4 );


			DecodeColorBlock( pImPos, pBlock, ddsd.dwWidth, (DWORD*)&col_0, (DWORD*)&col_1,
								(DWORD*)&col_2, (DWORD*)&col_3 );

			// Overwrite the previous alpha bits with the alpha block
			//  info

			DecodeAlpha3BitLinear( pImPos, pAlphaBlock, ddsd.dwWidth, alphazero );


		}
	}
	return d;
}

Cvirtual_binary Decompress(const DDSURFACEDESC2& ddsd, const byte* s)
{	
	switch(ddsd.ddpfPixelFormat.dwFourCC)
	{
	case '1TXD':
		return DecompressDXT1(ddsd, s);
	case '2TXD':
		return DecompressDXT2(ddsd, s);
	case '3TXD':
		return DecompressDXT3(ddsd, s);	
	case '4TXD':
		return DecompressDXT4(ddsd, s);
	case '5TXD':
		return DecompressDXT5(ddsd, s);
	}
	return Cvirtual_binary();
}

Cvirtual_binary Cdds_file::decode() const
{
	return Decompress(ddsd(), image());
}

Cvirtual_image Cdds_file::vimage() const
{
	Cvirtual_image image;
	Cvirtual_binary d = decode();
	if (d.data())
		image.load(d.data(), cx(), cy(), 4, NULL);
	return image;
}
