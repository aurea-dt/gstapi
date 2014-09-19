////////////////////////////////////////////////////////////////////////////////
// filter.cpp
// Mario Chirinos Colunga
// June 21 2010
//------------------------------------------------------------------------------
// Notes:
//	c++ unit tamplate
//
////////////////////////////////////////////////////////////////////////////////
#include "myfilter.h"
//------------------------------------------------------------------------------
void myFilter(unsigned char *data, unsigned int width, unsigned int height, unsigned int nChannels, void* userdata)
{
	int th = 128;
        unsigned int i = width*height;
	for(;i--;)//unsigned int i = 0; i<width*height; i++)
	{
		for(unsigned int c = 0; c < nChannels; c++)
			*data++=(*data < th ? 0 : 255);
	}
}

//------------------------------------------------------------------------------
