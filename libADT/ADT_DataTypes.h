//////////////////////////////////////////////////////////////////////////////
//	ADT_DataType.h
//	Mario Chirinos Colunga
//	School of Computer Science and Information Systems.
//	Birkbeck, Univerity of London.
//	29 May 2007 - 07 Oct 2008
//----------------------------------------------------------------------------
//	Base classes
//	Notes:
//		ADT_Pixel renamed to ADT_Point2Dui 25 Ago 2008
//		ADT_Point renamed to ADT_PointD2d  25 Ago 2008
//////////////////////////////////////////////////////////////////////////////
#ifndef ADT_DATATYPES_H
#define ADT_DATATYPES_H

class ADT_Point2D_d
{
  public:
	double x;
	double y;
	ADT_Point2D_d();
	ADT_Point2D_d(double x_, double y_);
};
//----------------------------------------------------------------------------
class ADT_Point2D_ui// antes Pixel
{	
 public:
	unsigned int x;
	unsigned int y;
	ADT_Point2D_ui();
	ADT_Point2D_ui(unsigned int x_, unsigned int y_);
	~ADT_Point2D_ui();
};
#endif // ADT_DATATYPES_H
// EOF
