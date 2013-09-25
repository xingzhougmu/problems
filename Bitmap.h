#include <string.h>
#define NULL 0

class Bitmap
{
	public:

	Bitmap::Bitmap(void)
	{
		g_bitmap = NULL;
		g_size = 0;
		g_base = 0;
	}

	Bitmap::~Bitmap(void)
	{
	}

	//Function: initialize bitmap
	//Parameters: size: size of bitmap (number of bits)
	//			  start: start point
	// Return value; 0-fail; 1-succeed
	int init(int size, int start){
		g_size = (size - 1) / 8 + 1;
		g_base = start;
		g_bitmap = new unsigned char[g_size];
		if (g_bitmap == NULL)
			return 0;
		memset(g_bitmap,0x0, g_size);
		//g_bitmap = new char[g_size];
		return 1;
	}

	//Function: set bit index to 1
	//Parameters: index
	// Return value; 0-fail; 1-succeed
	int set(int index){
		int quo = (index - g_base) / 8;
		int remainder = (index - g_base) % 8;
		unsigned char x = (0x1 << remainder);
		if (quo > g_size)
			return 0;
		g_bitmap[quo] |= x;
		return 1;
	}

	//Function: get the value at bit i
	//Parameters: index
	// Return value; -1-fail; otherwise return value at bit i
	int get(int index){
		index = index - g_base;
		int quo = (index) / 8;
		int remainder = index % 8;
		unsigned char x = (0x1<<remainder);
		unsigned char res;
		if (quo > g_size)
			return -1;
		res = g_bitmap[quo] & x;
		return res>0 ? 1 : 0;
	}

	//Function: return value at position index 
	//Parameters: index
	int bitmap_data(int index){
		return (index+g_base);
	}

	// free memory
	int free(){
		delete[] g_bitmap;
		return 0;
	}

	public:
	unsigned char* g_bitmap;
	int g_size;
	int g_base;

};
