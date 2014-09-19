////////////////////////////////////////////////////////////////////////////////
//	ADT_GTK.h
//	Mario Chirinos Colunga
//	Aurea Desarrollo Tecnológico.
//	16 Jun 2009 - 
//------------------------------------------------------------------------------
//	Classes y funciones para utilizar GTK+
//	Notas:	
//		
////////////////////////////////////////////////////////////////////////////////
#ifndef ADT_GTK_H
#define ADT_GTK_H

// your public header include
//------------------------------------------------------------------------------
#include <gtk/gtk.h>
#include <gnome.h> //for canvas
//------------------------------------------------------------------------------

// the declaration of your class...
//------------------------------------------------------------------------------
class ADT_GTK
{ 
 protected:
  	GtkBuilder *builder;
 public:
 	ADT_GTK();
 	void buildFromFile(const char *fileName);
};
//------------------------------------------------------------------------------
//		Funciones para manipular GtkWidgets
//------------------------------------------------------------------------------
void clearComboBox(GtkComboBox* comboBox);
void comboboxAppendText(GtkComboBox* combobox, const char* text);
//------------------------------------------------------------------------------
//			Functions for Gnome Canvas
//------------------------------------------------------------------------------
void clearGnomeCanvas(GtkWidget *canvas);
#endif
