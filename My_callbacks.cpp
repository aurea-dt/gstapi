//////////////////////////////////////////////////////////////////////////////
//	My_callbacks.cpp
//	Mario Chirinos Colunga
//	Aurea Desarrollo Tecnológico.
//	5 Mayo de 2010
//----------------------------------------------------------------------------
//	DESCRIPCIÓN
//	Notas:	
//		
//////////////////////////////////////////////////////////////////////////////
#include "My_callbacks.h"
#include "My_guiClass.h"
#include <iostream>
#include <sstream>

#include "myfilter.h"
using namespace std;
//------------------------------------------------------------------------------
int on_idle_callback(void *data)
{

 return true;
}
//------------------------------------------------------------------------------
void on_main_window_destroy(GtkObject *object, void* user_data)
{
        gtk_main_quit();
}
//------------------------------------------------------------------------------
void hide_on_window_delete_event(GtkObject *object, void* user_data)
{cout<<"hide"<<endl;
	gtk_widget_hide_on_delete((GtkWidget*)object);
}
//------------------------------------------------------------------------------
void on_refresh_button_clicked(GtkObject *object, void* user_data)
{
	cout<<"refresh"<<endl;
	g_signal_handlers_block_by_func (G_OBJECT (GTKapp->device_combobox), (void *)on_device_combobox_changed, NULL);

		clearComboBox((GtkComboBox*)GTKapp->device_combobox);
	 	video->enumCapDev();cout << "video->enumCapDev();" << " DONE" << endl;
		for(unsigned int n = 0; n<video->getDevListSize(); n++)
		{
			stringstream ss;
			cout << n << ": " << video->getDev(n) << " : " << video->getDevName(n) << endl;
			ss << n << ": " << video->getDev(n) << " : " << video->getDevName(n) << endl;
			string str;
			getline(ss,str);
			comboboxAppendText((GtkComboBox*)GTKapp->device_combobox, str.c_str());
		}
		gtk_combo_box_set_active((GtkComboBox*)GTKapp->device_combobox, 0);		
		GTKapp->fillResCombobox();

	g_signal_handlers_unblock_by_func (G_OBJECT (GTKapp->device_combobox), (void *)on_device_combobox_changed, NULL);
}
//------------------------------------------------------------------------------
void on_device_combobox_changed(GtkObject *object, void* user_data)
{
	g_signal_handlers_block_by_func (G_OBJECT (object), (void *)on_device_combobox_changed, NULL);
		GTKapp->fillResCombobox();
	g_signal_handlers_unblock_by_func (G_OBJECT (object), (void *)on_device_combobox_changed, NULL);
}
//------------------------------------------------------------------------------
void on_connect_togglebutton_toggled(GtkObject *object, void* user_data)
{

 	if(gtk_toggle_button_get_active((GtkToggleButton*)object))
		video->connect(gtk_combo_box_get_active((GtkComboBox*)GTKapp->device_combobox), gtk_combo_box_get_active((GtkComboBox*)GTKapp->res_combobox));
	else
		video->disconnect();
}
//------------------------------------------------------------------------------
void on_capture_button_clicked(GtkObject *object, void* user_data)
{
	//video->captureImage("temp.jpg", "jpg");
}
//------------------------------------------------------------------------------
void on_filter_button_clicked(GtkObject *object, void* user_data)
{
	video->setFilter(&myFilter);
 	if(gtk_toggle_button_get_active((GtkToggleButton*)object))
		video->startFilter();
	else
		video->stopFilter();
}
//------------------------------------------------------------------------------

