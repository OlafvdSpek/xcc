#include <iomanip>
#include <iostream>
#include <windows.h>

using namespace std;

const int patch[] = 
{
	0x00091a10, 0x83, 0xb0,
	0x00091a11, 0xec, 0x01,
	0x00091a12, 0x10, 0xc3,
	0x00142715, 0xff, 0x01,
	0x00142716, 0xff, 0x00,
	0x00142717, 0xff, 0x00,
	0x00142718, 0xff, 0x00,
	0x00143a89, 0xff, 0x01,
	0x00143a8a, 0xff, 0x00,
	0x00143a8b, 0xff, 0x00,
	0x00143a8c, 0xff, 0x00,
	0x001b46be, 0xff, 0x00,
	0x001b46bf, 0xff, 0x00,
	0x001b46c0, 0xff, 0x00,
	0x001b46c1, 0xff, 0x00,
	0x0028e70f, 0x75, 0xeb,
	0x0029053f, 0x75, 0xeb,
	0x003db604, 0x57, 0x00,

	0x003457cc, 0x0f, 0xe9,
	0x003457cd, 0x8e, 0xc4,
	0x003457ce, 0xc3, 0x00,
	0x00359e87, 0x0f, 0xe9,
	0x00359e88, 0x8e, 0xc1,
	0x00359e89, 0xc0, 0x00,

	0xffffffff
};

void read_patch(FILE* f, FILE* g)
{
	int ofs = 0;
	int s = 0;
	int d = 0;
	cout << hex << setfill('0');
	while (fread(&s, 1, 1, f) == 1 && fread(&d, 1, 1, g) == 1)
	{
		if (s != d)
			cout << "0x" << setw(8) << ofs << ", 0x" << setw(2) << s << ", 0x" << setw(2) << d << "," << endl;
		ofs++;
	}
	cout << "0xffffffff" << endl;
}

int write_patch(FILE* f, const int* p)
{
	int b = 0;
	const int* r = p;
	while (*r != -1)
	{
		if (fseek(f, *r++, SEEK_SET)
			|| fread(&b, 1, 1, f) != 1
			|| b != *r++ && b != *r++)
			return 1;
	}
	r = p;
	while (*r != -1)
	{
		if (fseek(f, *r++, SEEK_SET)
			|| fwrite(r + 1, 1, 1, f) != 1)
			return 1;
		r += 2;
	}
	return 0;
}

int main()
{
	// return read_patch(fopen("c:/games/ra2/game.exe", "rb"), fopen("c:/games/ra2/game.exe.bak", "rb")), 0;
	char b[MAX_PATH];
	if (GetModuleFileName(NULL, b, MAX_PATH))
	{
		strcpy(strrchr(b, '\\') + 1, "game.exe");
		FILE* f = fopen(b, "r+b");
		if (f)
		{
			if (write_patch(f, patch))
				cerr << "Unable to patch game" << endl;
			fclose(f);
		}
		else
			cerr << "Unable to open game" << endl;
	}
	return 0;
}
