//////////////////////////////////////////////////////////////////////////////
//	My_guiClass.h
//	Mario Chirinos Colunga
//	Aurea Desarrollo Tecnológico.
//	5 de Mayo del 2010
//----------------------------------------------------------------------------
//	DESCRIPCIÓN
//	Notas:	
//		
//////////////////////////////////////////////////////////////////////////////
#ifndef MY_GUICLASS_H
#define MY_GUICLASS_H
// your public header include
#include "ADT_GTK.h"
#include "ADT_GStreamer.h"
// the declaration of your class...
//------------------------------------------------------------------------------
class T_GTKapp : public ADT_GTK
{
 public:

	GtkWidget *window;
	
	//main window items
	GtkWidget *device_combobox;
	GtkWidget *res_combobox;
	GtkWidget *filter_button;
	GtkWidget *connect_button;
	//member functions
	T_GTKapp();
	T_GTKapp(const char *fileName);

	void guiInit();	
	//const char* fileChooserDialog(vector<char*> filters);
	//void guiRefresh();
	void fillResCombobox() const;

};
//------------------------------------------------------------------------------
extern T_GTKapp *GTKapp;
extern ADT_GstVideo *video;
#endif
