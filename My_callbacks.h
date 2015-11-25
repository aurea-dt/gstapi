////////////////////////////////////////////////////////////////////////////////
//	My_callbacks.h
//	AUTOR
//	Aurea Desarrollo Tecnológico.
//	FECHA
//------------------------------------------------------------------------------
//	DESCRIPCIÓN
//	Notas:	
//		
////////////////////////////////////////////////////////////////////////////////
#ifndef MY_CALLBACKS_H
#define MY_CALLBACKS_H

// your public header include
#include "ADT_GTK.h"
// the declaration of your class...
int on_idle_callback(void *data);
extern "C" void on_main_window_destroy(GtkWidget *object, void* user_data);
extern "C" void hide_on_window_delete_event(GtkWidget *object, void* user_data); //oculatar la ventana en vez de destruirla
extern "C" void on_refresh_button_clicked(GtkWidget *object, void* user_data);
extern "C" void on_device_combobox_changed(GtkWidget *object, void* user_data);
extern "C" void on_connect_togglebutton_toggled(GtkWidget *object, void* user_data);
extern "C" void on_capture_button_clicked(GtkWidget *object, void* user_data);
extern "C" void on_filter_button_clicked(GtkWidget *object, void* user_data);
#endif
