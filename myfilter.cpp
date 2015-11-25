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
	for(unsigned int i = 0; i<width*height*nChannels; i++)//;i--;)//
	{
//		for(unsigned int c = 0; c < 2; c++)
//			*data++=(*data < th ? 0 : 255);
			data[i]=(data[i] < th ? 0 : 255);
	}
}

//------------------------------------------------------------------------------
