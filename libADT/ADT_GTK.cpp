////////////////////////////////////////////////////////////////////////////////
//	ADT_GTK.cpp
//	Mario Chirinos Colunga
//	Aurea Desarrollo Tecnológico.
//	16 Jun 2009 - 
//------------------------------------------------------------------------------
//	Classes y funciones para utilizar GTK+
//	Notas:	
//		
////////////////////////////////////////////////////////////////////////////////
#include "ADT_GTK.h"
#include <iostream>
using namespace std;
//------------------------------------------------------------------------------
ADT_GTK::ADT_GTK()
{
	builder = gtk_builder_new ();
}
//------------------------------------------------------------------------------
void ADT_GTK::buildFromFile(const char *fileName)
{
	gtk_builder_add_from_file (builder, fileName, NULL);          
        gtk_builder_connect_signals (builder, NULL);
        
}
//------------------------------------------------------------------------------
//		Funciones para manipular GtkWidgets
//------------------------------------------------------------------------------
void comboboxAppendText(GtkComboBox* combobox, const char* text)
{
 GtkTreeIter iter;
	GtkCellRenderer *cellRender = gtk_cell_renderer_text_new();
	gtk_cell_layout_clear(GTK_CELL_LAYOUT( combobox ));
	gtk_cell_layout_pack_start( GTK_CELL_LAYOUT( combobox ), cellRender, TRUE );
	 gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT( combobox ), cellRender, "text", 0, NULL );

	GtkListStore *store = GTK_LIST_STORE( gtk_combo_box_get_model(combobox) );
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, text, -1);
}
//------------------------------------------------------------------------------
void comboboxRemoveText(GtkComboBox* combobox, const char* text)
{
}
//------------------------------------------------------------------------------
void clearComboBox(GtkComboBox* combobox)
{
	GtkTreeIter iter;
	GtkListStore *store = GTK_LIST_STORE( gtk_combo_box_get_model(combobox) );

	while(gtk_tree_model_get_iter_first((GtkTreeModel*)store,&iter))
	   gtk_list_store_remove(store,&iter);
}
//------------------------------------------------------------------------------
//			Functions for Gnome Canvas
//------------------------------------------------------------------------------
//void clearGnomeCanvas(GtkWidget *canvas)
//{
//  GnomeCanvasGroup *root;
//  GList *temp_list;

//	root = GNOME_CANVAS_GROUP(gnome_canvas_root(GNOME_CANVAS(canvas)));

//	temp_list = root->item_list;
//	int i=0;
//	while(temp_list != NULL)
//	{
//    		GnomeCanvasItem *item = GNOME_CANVAS_ITEM(temp_list->data);
//    		temp_list = temp_list->next;
//    		gtk_object_destroy(GTK_OBJECT(item));
//		g_object_unref(GTK_OBJECT(item));
//		i++;
//		cout << i << endl;
//	}
//}
//------------------------------------------------------------------------------
