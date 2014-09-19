////////////////////////////////////////////////////////////////////////////////
// 	ADT_GStreamer.h
// 	Mario Chirinos Colunga
// 	Áurea - Desarrollo Tecnológico
// 	http://www.aurea-dt.com
// 	16 Nov 2009 - 28 Oct 2010
//------------------------------------------------------------------------------
//	Funciones para la manipulación de la biblioteca GStreamer
//	http://gstreamer.freedesktop.org/
// 	Notas:
//	
////////////////////////////////////////////////////////////////////////////////

#ifndef ADTGSTREAMER_H
#define ADTGSTREAMER_H

// your public header include
//------------------------------------------------------------------------------
#include <gst/gst.h>
#include <gtk/gtk.h>
#ifdef GDK_WINDOWING_X11
	#include <gdk/gdkx.h>  // for GDK_WINDOW_XID
#endif
#include <gst/interfaces/xoverlay.h>
#include <string>
#include <vector>
#include "ADT_DataTypes.h"
//------------------------------------------------------------------------------
using namespace std;
typedef void (*pt2Function)(unsigned char*, unsigned int, unsigned int, unsigned int, void*);
//------------------------------------------------------------------------------
class ADT_GstVideo
{
 private:
	int selectedDev;
	int selectedRes;
	unsigned int width;
	unsigned int height;
	vector<ADT_Point2D_ui> getResList(GstElement* videoSrcTmp) const;
	vector<ADT_Point2D_ui> getResList(const char* devName) const;
	pt2Function fpt;

	//video window
	unsigned long int video_window_xid;
	GtkWidget* videoWindow;
	GtkWidget* drawArea;

	//main pipeline
	GstElement* videoSrc;
	GstElement* filter;
        GstElement* filterCaps;
	GstElement* tee;
	GstElement* videoQueue;
	GstElement* colorSpaceConverter;	
        GstElement* videoSink;        
	GstElement* videoPipeline;

	//photo pipleline
	GstElement* photoSrc;	
	GstElement* photoColorSpaceConverter;
	GstElement* encoder;
	GstElement* photoSink;
	GstElement* photoPipeline;

	vector<string> devList;		//Device list
	vector<string> devNameList;	//Device name list
	vector< vector<ADT_Point2D_ui> > resList;//Resolution list for each device
	int enumFormats();
	int createMainPipeline();
//	int createPhotoPipeline();
	
	//callback functions
	static int videoplayer_bus_callback(GstBus* bus, GstMessage* message, void* data);
//	static int photoPipeline_bus_callback(GstBus *bus, GstMessage *message, void *data);
	static int filter_handoff_callback(GstElement* filter, GstBuffer* buffer, void* user_data);
	static void video_widget_realize_cb(GtkWidget* widget, void* user_data);
	static GstBusSyncReply bus_sync_handler_cb(GstBus* bus, GstMessage* message, void* user_data);
	static void hideanddisconnect_cb(GtkObject* object, void* user_data);
	static void hide_cb(GtkObject* object, void* user_data);
	
 public:	
	void* userdata;
//	bool captureRequest;	
	string name;	

	int enumCapDev();
	int connect(const char* devName, unsigned int _width, unsigned int _height);
	int connect(unsigned int devIndex, unsigned int resIndex);
	void disconnect();
//	int captureImage(const char* fileName,  const char *format);
	//int captureVideoStart(const char* fileName);
	//int startCaptureVideoStop();
	
	void setFilter(pt2Function  _fpt);
	void unsetFilter();
	int startFilter();
	int stopFilter();
	int getDevListSize() const;
	int getResListSize(unsigned int i) const;
	int getSelectedDev() const;
	int getSelectedRes() const;
	const char* getDev(unsigned int i) const;
	const char* getDevName(unsigned int i) const;
	const ADT_Point2D_ui getRes(unsigned int d, unsigned int i) const;
	ADT_GstVideo();
	//~ADT_GstVideo();
};
//------------------------------------------------------------------------------
#endif

