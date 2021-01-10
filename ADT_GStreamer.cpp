////////////////////////////////////////////////////////////////////////////////
// 	ADT_GStreamer.cpp
// 	Mario Chirinos Colunga
// 	Áurea - Desarrollo Tecnológico
// 	http://www.aurea-dt.com
// 	16 Nov 2009 - 28 Oct 2010
//	16 Jun 2014, 24 Nov 2015
//------------------------------------------------------------------------------
//	Funciones para la manipulación de la biblioteca GStreamer
//	http://gstreamer.freedesktop.org/
//	Notas:
//
////////////////////////////////////////////////////////////////////////////////
#include "ADT_GStreamer.h"
#include "ADT_Tools.h"
#include "ADT_GTK.h"
#include <iostream>
#include <sstream>

#include <sys/types.h>
#include <dirent.h>
//------------------------------------------------------------------------------
ADT_GstVideo::ADT_GstVideo()
{	
	userdata = NULL;
	video_window_xid = 0;

	//GTK+ video window
	videoWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	drawArea = gtk_drawing_area_new();
	gtk_widget_set_double_buffered (drawArea, FALSE);
	gtk_container_add (GTK_CONTAINER (videoWindow), drawArea);
	g_signal_connect(drawArea, "realize", G_CALLBACK (video_widget_realize_cb), this);
	g_signal_connect(videoWindow, "delete-event", G_CALLBACK (hideanddisconnect_cb), this);
	g_signal_connect(videoWindow, "hide", G_CALLBACK (hide_cb), this);
	gtk_widget_realize (drawArea);
	g_assert(video_window_xid != 0);
  	
	//GST components
	videoPipeline = gst_pipeline_new("video-player");
	photoPipeline = gst_pipeline_new("photo-capture");

	GstBus* bus;
	bus = gst_pipeline_get_bus(GST_PIPELINE (videoPipeline));
	gst_bus_add_watch(bus, videoplayer_bus_callback, NULL);
	gst_bus_set_sync_handler(bus, (GstBusSyncHandler) bus_sync_handler_cb, this, NULL);

	bus = gst_pipeline_get_bus(GST_PIPELINE (photoPipeline));
//	gst_bus_add_watch (bus, photoPipeline_bus_callback, NULL);

	gst_object_unref(GST_OBJECT (bus));
	createMainPipeline();
//	createPhotoPipeline();
	
//	g_object_set (G_OBJECT (photoSink), "signal-handoffs", TRUE, NULL);
//		g_signal_connect (photoSink, "handoff", G_CALLBACK (photosink_handoff_callback), this);
//	captureRequest = false;
	fpt = NULL;
	//name = "ADT_video_API";
}
//------------------------------------------------------------------------------
int ADT_GstVideo::createMainPipeline()
{
	videoSrc = gst_element_factory_make("v4l2src", "video_source_main");
 	filterCaps = gst_element_factory_make("capsfilter", "filter_cap");
		GstCaps *fc = gst_caps_new_full(gst_structure_new ("video/x-raw", NULL), NULL);
 		g_object_set(G_OBJECT (filterCaps), "caps", fc, NULL);
		//gst_object_unref(GST_OBJECT (fc));
	rgbConverter  = gst_element_factory_make("videoconvert", "rgbConverter");
	filter = gst_element_factory_make("identity", "video_filter");
//	tee = gst_element_factory_make("tee", "tee");
	videoQueue = gst_element_factory_make("queue", "video_queue");
	colorSpaceConverter  = gst_element_factory_make("videoconvert", "colorSpaceConverter");
	videoSink = gst_element_factory_make("autovideosink", "video_sink");

	gst_bin_add_many(GST_BIN (videoPipeline), videoSrc, rgbConverter, filterCaps, filter/*, tee*/, videoQueue, colorSpaceConverter, videoSink, NULL);
	if(!gst_element_link_many(videoSrc, rgbConverter, filterCaps, filter/*, tee*/, videoQueue, colorSpaceConverter, videoSink, NULL))
	{
		cerr << "ADT_GstVideo.createMainPipeline: Failed to link elements in the pipeline" << endl;
		return 1;
	}


	/* add ghostpad */
//  	GstPad* pad = gst_element_get_request_pad(tee, "src%d");
//		gst_element_add_pad(videoPipeline, gst_ghost_pad_new ("src", pad));
//		gst_object_unref(GST_OBJECT (pad));

 return 0;
}
//------------------------------------------------------------------------------
//int ADT_GstVideo::createPhotoPipeline()
//{
//	photoSrc = gst_element_factory_make("fakesrc", "photo_src");
//	photoColorSpaceConverter = gst_element_factory_make("ffmpegcolorspace", "photoColorSpaceConverter");
//	encoder = gst_element_factory_make("pngenc", "photo_encoder");
//	photoSink  = gst_element_factory_make("filesink", "photo_sink");

//	gst_bin_add_many (GST_BIN (photoPipeline), photoSrc, photoColorSpaceConverter, encoder, photoSink, NULL);
//	if(!gst_element_link_many(photoSrc, photoColorSpaceConverter, encoder, photoSink, NULL))
//		cerr << "ADT_GstVideo(): Failed to link elements in the photo pipeline" << endl;

//	gst_element_set_state (photoPipeline, GST_STATE_NULL);


////	/* add ghostpad */
////  	GstPad *pad = gst_element_get_static_pad (photoQueue, "sink");
////  		gst_element_add_pad (photoPipeline, gst_ghost_pad_new ("sink", pad));
////  		gst_object_unref (GST_OBJECT (pad));
// return 0;
//}
//------------------------------------------------------------------------------
void ADT_GstVideo::disconnect()//disconnect device
{
	gst_element_set_state(videoPipeline, GST_STATE_NULL);
}
//------------------------------------------------------------------------------
//			connect to selected camera device
int ADT_GstVideo::connect(const char* devName, unsigned int _width, unsigned int _height)
{	cout<< "connecting "<< devName << " at " << _width <<" x " << _height<<endl;
	disconnect();
	width = _width;
	height= _height;
	//int FPS = 25;
	g_object_set(G_OBJECT (videoSrc), "device", devName, NULL);
	gst_element_set_state(videoPipeline, GST_STATE_READY); // connection bug fixed 26/08/2010, set state must be after set device
	GstCaps *fc = gst_caps_new_full(gst_structure_new ("video/x-raw",
						"width", G_TYPE_INT, width,
						"height", G_TYPE_INT, height,	
						"format", G_TYPE_STRING, "RGB",//"format", GST_TYPE_FOURCC, GST_MAKE_FOURCC ('I', '4', '2', '0'),
						//"framerate", GST_TYPE_FRACTION, FPS, 1,
//						"bpp", G_TYPE_INT, 24,
//				   		"depth", G_TYPE_INT, 24,					 
						NULL),
      						NULL);

 	g_object_set(G_OBJECT (filterCaps), "caps", fc, NULL);
	gst_element_set_state(videoPipeline, GST_STATE_PLAYING);

	char* str;
	g_object_get(G_OBJECT (videoSrc), "device", &str, NULL);
	cout << "connected to: "<<  str << endl;
	gtk_widget_show_all(videoWindow);
	g_object_get(G_OBJECT (videoSrc), "device-name", &str, NULL);
	gtk_window_set_title((GtkWindow *)videoWindow, str);
return 0;
}
//------------------------------------------------------------------------------
//			connect to selected camera device
int ADT_GstVideo::connect(unsigned int devIndex, unsigned int resIndex)
{cout<< "connecting dev:"<< devIndex << " at resolution: " << resIndex <<endl;
	selectedDev=devIndex;
	selectedRes=resIndex;
	char* devicePath = (char*)devList[devIndex].c_str();
	cout << "devicePath: " << devicePath<<", devIndex: "<< devIndex<<endl;
	int widthTmp = resList[devIndex][resIndex].x;
	int heightTmp = resList[devIndex][resIndex].y;

	if(devList.size()<devIndex)
	{
		cerr << "Device not listed" << endl;
		return 1;
	}
	
	if (devIndex < 0 || !checkPath(devicePath))
	{
		cerr << devicePath << " do not exist" << endl;
		return 1;
	}

	if(resIndex >= (unsigned int)getResListSize(devIndex))
	{
		cerr << "Format not available! " << resList.size() << endl;
		return 1;
	}

	connect(devicePath, widthTmp, heightTmp);
return 0;
}
//------------------------------------------------------------------------------
int ADT_GstVideo::enumCapDev()//enumerate installed capture devices
{
	cout << "ADT_GstVideo::enumCapDev()" << endl;
//	char* 
	string str;
	DIR* Dir;
	dirent* DirEntry;
	string fname;
	
    	devList.clear();
	devNameList.clear();
    	Dir = opendir("/dev");
	while((DirEntry=readdir(Dir)))
	{
		fname=string(DirEntry->d_name);
		if(fname.length()>=5)
			if(fname.substr(0,5)=="video")
			{
				
				string dev = "/dev/"+fname;
				cout << dev << endl;
				GstElement* tempVideoSrc;
					tempVideoSrc  = gst_element_factory_make("v4l2src", "video_source_enumCapDev");

				g_object_set(G_OBJECT (tempVideoSrc), "device", dev.c_str(), NULL);
				g_object_get(G_OBJECT (tempVideoSrc), "device-name", &str, NULL);
				cout << str << ": " << endl;
				vector<ADT_Point2D_ui> rlTemp = getResList(tempVideoSrc);
				if(rlTemp.size() > 0)
				{	
					cout << str << ": " ;
					cout << dev << endl;
					devNameList.push_back(str);		
					devList.push_back(dev);
					resList.push_back(rlTemp);
				}
				gst_object_unref(GST_OBJECT (tempVideoSrc));
			}
	}
	closedir(Dir);
return devNameList.size();
}
//------------------------------------------------------------------------------
//int ADT_GstVideo::captureImage(const char* fileName,  const char *format)
//{
//	captureRequest = true;
//	

//return 0;	
//}
//------------------------------------------------------------------------------
void ADT_GstVideo::setFilter(pt2Function _fpt)
{
	fpt = _fpt;
}
//------------------------------------------------------------------------------
void ADT_GstVideo::unsetFilter()
{
	fpt = NULL;
}
//------------------------------------------------------------------------------
int ADT_GstVideo::startFilter()
{
	cout << "startFilter()"  << endl;
	g_object_set(G_OBJECT (filter), "signal-handoffs", TRUE, NULL);
	return g_signal_connect(filter, "handoff", G_CALLBACK (filter_handoff_callback), this);
}
//------------------------------------------------------------------------------
int ADT_GstVideo::stopFilter()
{
	return g_signal_handlers_disconnect_by_func(G_OBJECT (filter), (void *)filter_handoff_callback, this);
}
//------------------------------------------------------------------------------
int ADT_GstVideo::getDevListSize() const
{
	return devList.size();
}
//------------------------------------------------------------------------------
int ADT_GstVideo::getResListSize(unsigned int i) const
{
	if(i<0 || i>= getDevListSize())
		return 0;
	return resList[i].size();
}
//------------------------------------------------------------------------------
int ADT_GstVideo::getSelectedDev() const
{
	return selectedDev;
}
//------------------------------------------------------------------------------
int ADT_GstVideo::getSelectedRes() const
{
	return selectedRes;
}
//------------------------------------------------------------------------------
const char* ADT_GstVideo::getDev(unsigned int i) const
{
	if(devList.size()<0 || i > devList.size())
		return "";
 	return devList[i].c_str();
}
//------------------------------------------------------------------------------
const char* ADT_GstVideo::getDevName(unsigned int i) const
{
	if(devNameList.size()<0 || i > devNameList.size())
		return "";
 	return devNameList[i].c_str();
}
//------------------------------------------------------------------------------
const ADT_Point2D_ui ADT_GstVideo::getRes(unsigned int d, unsigned int i) const
{
	if(resList[d].size()<0 || i > resList[d].size())
		return ADT_Point2D_ui(0,0);
 	return resList[d][i];
}
//------------------------------------------------------------------------------
vector<ADT_Point2D_ui> ADT_GstVideo::getResList(const char* devName) const
{
	cout << "ADT_GstVideo::getResList(" << devName << ")" << endl;
	GstElement* videoSrcTmp;
	videoSrcTmp  = gst_element_factory_make("v4l2src", "video_source_tmp");
	g_object_set (G_OBJECT (videoSrcTmp), "device", devName, NULL);
	
	vector<ADT_Point2D_ui> tmp = getResList(videoSrcTmp);	
	gst_object_unref(GST_OBJECT (videoSrcTmp));
	return tmp;
}
//------------------------------------------------------------------------------
vector<ADT_Point2D_ui> ADT_GstVideo::getResList(GstElement* videoSrcTmp) const
{
	cout << "ADT_GstVideo::getResList(videoSrcTmp)" << endl;
	vector<ADT_Point2D_ui> resListTemp;
	GstElement* pipeLineTmp;

	pipeLineTmp  = gst_pipeline_new("video-player-tmp");
	gst_bin_add_many(GST_BIN (pipeLineTmp), videoSrcTmp, NULL);
	gst_element_set_state(pipeLineTmp, GST_STATE_READY);

	GstPad* srcPad = gst_element_get_static_pad(videoSrcTmp, "src");
	GstCaps* videoCaps = gst_pad_query_caps(srcPad, NULL);
	cout << gst_caps_to_string (videoCaps) << endl;
	unsigned int nCaps = gst_caps_get_size(videoCaps);
	const GstStructure* str;
	int width, height, depth, fpsNumerator, fpsDenominator;
	char* formatName;
	guint32 format;

	resListTemp.clear();
	for(unsigned int i=0; i < nCaps; i++)
	{
		str = gst_caps_get_structure (videoCaps, i);
		if (!gst_structure_get_int(str, "width", &width) || !gst_structure_get_int(str, "height", &height))
			width = height = 0;
		if(!gst_structure_get_int(str, "bpp", &depth))
			depth = 0;
//		if(!gst_structure_get_string(str, "format", &format))
//			format=GST_STR_FOURCC ("NONE");

		if(!gst_structure_get_fraction(str, "framerate", &fpsNumerator, &fpsDenominator))
		{
			fpsNumerator=0;
			fpsDenominator=0;
		}

		formatName = (char*)gst_structure_get_name(str);
		cout << formatName << endl;
		if((string)formatName == "video/x-raw")// && format==GST_MAKE_FOURCC ('I', '4', '2', '0'))
		{
			ADT_Point2D_ui resolution;
			resolution.x = width;
			resolution.y = height;
			bool found = false;
			for(unsigned int n=0; n<resListTemp.size(); n++)
			{	
				if(resListTemp[n].x==resolution.x && resListTemp[n].y==resolution.y)
				{
					found =true;
					break;				
				}
			}
			if(!found)
			{
				resListTemp.push_back(resolution);
				//cout << devName << ": "<< width << "x" << height<< " @ " << fpsNumerator <<"/" <<fpsDenominator <<" : "<< depth << " bits, " << formatName << ", ";
				//printf ("%" GST_FOURCC_FORMAT "\n", GST_FOURCC_ARGS (format));
			}	
		}
	}
	gst_object_unref(GST_OBJECT (srcPad));
	//gst_object_unref(GST_OBJECT (videoCaps));
	//gst_object_unref(GST_OBJECT (str));
	gst_object_unref(GST_OBJECT (pipeLineTmp));

return resListTemp;
}
//------------------------------------------------------------------------------
int ADT_GstVideo::videoplayer_bus_callback(GstBus* bus, GstMessage* message, void* data)
{
	printf("videoplayer Got %s message\n", GST_MESSAGE_TYPE_NAME (message));
	return 0;
}
//------------------------------------------------------------------------------
void ADT_GstVideo::video_widget_realize_cb(GtkWidget* widget, void* user_data)
{
	#if GTK_CHECK_VERSION(2,18,0)
	  if (!gdk_window_ensure_native (gtk_widget_get_parent_window(widget)))
	    g_error ("Couldn't create native window needed for GstXOverlay!");
	#endif

	#ifdef GDK_WINDOWING_X11
	  ((ADT_GstVideo*)user_data)->video_window_xid = GDK_WINDOW_XID (gtk_widget_get_parent_window(widget));
	#endif
}
//------------------------------------------------------------------------------
GstBusSyncReply ADT_GstVideo::bus_sync_handler_cb(GstBus* bus, GstMessage* message, void* user_data)
{
	if (GST_MESSAGE_TYPE(message) != GST_MESSAGE_ELEMENT)
		return GST_BUS_PASS;
//	if (!gst_structure_has_name(message->structure, "prepare-xwindow-id"))
 	if (!gst_is_video_overlay_prepare_window_handle_message (message))
		return GST_BUS_PASS;
 
	if (((ADT_GstVideo*)user_data)->video_window_xid != 0)
	{
		GstVideoOverlay *xoverlay;
		xoverlay = GST_VIDEO_OVERLAY(GST_MESSAGE_SRC (message));
		//gst_x_overlay_set_xwindow_id (xoverlay, ((ADT_GstVideo*)user_data)->video_window_xid);
		gst_video_overlay_set_window_handle (xoverlay, ((ADT_GstVideo*)user_data)->video_window_xid);
		g_object_set (xoverlay, "force-aspect-ratio", TRUE, NULL);
 	}
	else
	{
		g_warning ("Should have obtained video_window_xid by now!");
		cerr << "Should have obtained video_window_xid by now!" << endl;
	}
 
	gst_message_unref (message);
	return GST_BUS_DROP;
}
//------------------------------------------------------------------------------
void ADT_GstVideo::hide_cb(GtkWidget* object, void* user_data)
{
	((ADT_GstVideo*)user_data)->disconnect();
}
//------------------------------------------------------------------------------
void ADT_GstVideo::hideanddisconnect_cb(GtkWidget* object, void* user_data)
{
	gtk_widget_hide_on_delete((GtkWidget*)object);
}
//------------------------------------------------------------------------------
int ADT_GstVideo::filter_handoff_callback(GstElement* filter, GstBuffer* buffer, void* user_data)
{

	cout << "filter_handoff_callback" << endl;
	int width, height;
	GstPad* srcPad = gst_element_get_static_pad(filter, "src");
	GstCaps* videoCaps = gst_pad_query_caps(srcPad, NULL);
	const GstStructure* str;
	str = gst_caps_get_structure(videoCaps, 0);
	cout << gst_caps_to_string (videoCaps) << endl;
	if (!gst_structure_get_int(str, "width", &width) || !gst_structure_get_int (str, "height", &height))
		return 1;
	cout << width << ", " << height << endl;
//	unsigned char* data = (unsigned char*)GST_BUFFER_DATA (buffer);        

	GstMapInfo map;
	if (gst_buffer_map (buffer, &map, GST_MAP_WRITE))
	{ 

		if(((ADT_GstVideo*)user_data)->fpt!=NULL)// check if initialized
		{			
			unsigned char* data = map.data; 
			cout << width * height *3<< " => " << map.size << endl; 
			((ADT_GstVideo*)user_data)->fpt(data, width, height, 3, user_data);
			gst_buffer_unmap (buffer, &map); 
		}
		else
		{
			cout << "fpt == NULL" << endl;
		}
	}
	else
	{
		cout << "gst_buffer_map failed" << endl;
	}

//	if(((ADT_GstVideo*)user_data)->captureRequest)
//	{
//		
//		cout << "pohoto taken"<<endl;
//		gst_element_set_state (((ADT_GstVideo*)user_data)->photoPipeline, GST_STATE_NULL);
//		((ADT_GstVideo*)user_data)->captureRequest = false;
//		g_object_set (((ADT_GstVideo*)user_data)->photoSrc, "filltype", 5, NULL);
//		g_object_set (((ADT_GstVideo*)user_data)->photoSrc, "sizetype", 2, NULL);
//		g_object_set (((ADT_GstVideo*)user_data)->photoSrc, "sizemax", width*height*3, NULL);
//		g_object_set (((ADT_GstVideo*)user_data)->photoSrc, "pattern", &data, NULL);
//		g_object_set (((ADT_GstVideo*)user_data)->photoSink, "location", "temp.png", NULL);
//		gst_element_set_state (((ADT_GstVideo*)user_data)->photoPipeline, GST_STATE_PLAYING);
//		
//	}

	

return 0;
}

//------------------------------------------------------------------------------

