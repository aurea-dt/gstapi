//////////////////////////////////////////////////////////////////////////////
//	My_guiClass.cpp
//	AUTOR
//	Aurea Desarrollo Tecnológico.
//	FECHA
//----------------------------------------------------------------------------
//	DESCRIPCIÓN
//	Notas:	
//		
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "My_guiClass.h"
#include "My_callbacks.h"
#include <sstream>
using namespace std;
T_GTKapp *GTKapp;
ADT_GstVideo *video;
//------------------------------------------------------------------------------
T_GTKapp::T_GTKapp()
{
}
//------------------------------------------------------------------------------
T_GTKapp::T_GTKapp(const char *fileName)
{
        buildFromFile(fileName);
	window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));

        //add your code here...
     	//myTheme=  gtk_icon_theme_get_default();
	//gtk_icon_theme_append_search_path(myTheme, "icons/");  
	
	//main window items
	device_combobox = GTK_WIDGET (gtk_builder_get_object (builder, "device_combobox"));
	res_combobox = GTK_WIDGET (gtk_builder_get_object (builder, "res_combobox"));
	filter_button = GTK_WIDGET (gtk_builder_get_object (builder, "filter_togglebutton"));
	connect_button = GTK_WIDGET (gtk_builder_get_object (builder, "connect_togglebutton"));


	g_object_unref (G_OBJECT (builder));
}
//------------------------------------------------------------------------------
//		Member functions
//------------------------------------------------------------------------------
void T_GTKapp::guiInit()
{
       //gtk_combo_box_entry_set_text_column( GTK_COMBO_BOX_ENTRY(GTKapp->device_combobox ), 0 ); 
	//guiRefresh() ;
}
//------------------------------------------------------------------------------
void T_GTKapp::fillResCombobox() const
{
	cout << "fillResCombobox()" <<endl;
	int dev = gtk_combo_box_get_active((GtkComboBox*)GTKapp->device_combobox);
	clearComboBox((GtkComboBox*)GTKapp->res_combobox);

	for(unsigned int n = 0; n<video->getResListSize(dev); n++)
	{
		stringstream ss;
		ss << n << ": " << video->getRes(dev,n).x << ", " << video->getRes(dev,n).y << endl;
		string str;
		getline(ss,str);
		comboboxAppendText((GtkComboBox*)GTKapp->res_combobox, str.c_str());
	}
	gtk_combo_box_set_active((GtkComboBox*)GTKapp->res_combobox, 0);
cout << "fillResCombobox() END" <<endl;
}
//------------------------------------------------------------------------------
/*void T_GTKapp::guiRefresh()
{	

}
//------------------------------------------------------------------------------
const char* T_GTKapp::fileChooserDialog(vector<char*> filters)
{
	char *filename = NULL;
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Open Image",
					      (GtkWindow*)window,
					      GTK_FILE_CHOOSER_ACTION_OPEN,
					      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					      NULL);

	for(unsigned int i=0; i<filters.size(); i++)
	{
		GtkFileFilter *filter = gtk_file_filter_new ();
		gtk_file_filter_add_pattern (filter, filters[i]);
		gtk_file_chooser_add_filter((GtkFileChooser*)dialog, filter);
	}

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
	}
	gtk_widget_destroy (dialog);
	return filename;
}
//------------------------------------------------------------------------------
*/
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
