//////////////////////////////////////////////////////////////////////////////
// 	main.cpp
// 	Mario Chirinos Colunga
// 	Aurea Desarrollo Tecnológico.
// 	http://www.aurea-dt.com
// 	16 Nov 2009 - 30 April 2010
//----------------------------------------------------------------------------
//	Parogrma para probar ADT_GSreamer
// 	Notas:	
//		Banderas:
//		gcc -Wall -g -o tutorial main.c -export-dynamic `pkg-config --cflags --libs gtk+-2.0`
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <gtk/gtk.h>
#include "My_guiClass.h"
#include "My_callbacks.h"
#include "ADT_GStreamer.h"

using namespace std;
//------------------------------------------------------------------------------
int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	gst_init (&argc, &argv);

	GTKapp =new T_GTKapp("ui.glade");
	//g_idle_add(on_idle_callback, NULL);
        gtk_widget_show (GTKapp->window);

	video = new ADT_GstVideo();	
	
	GTKapp->guiInit();
        gtk_main ();

 return 0;
}
//------------------------------------------------------------------------------

