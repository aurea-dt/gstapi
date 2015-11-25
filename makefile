#-------------------------------------------------------------------------------
#	Mario Chirinos Colunga
#	Aurea Desarrollo Tecnológico.
#	16 Nov 2009 - 28 Oct 2010
#	Notas:
#-------------------------------------------------------------------------------
APPNAME = GTKapp
#Compiler:
	CC=g++

#Compiler flags
	CFLAGS=-c -g -Wall
	INCLUIDES=$(shell pkg-config --cflags gtk+-3.0  gstreamer-1.0 gstreamer-video-1.0 gstreamer-plugins-base-1.0)
	LIBS=$(shell pkg-config --libs gtk+-3.0 gstreamer-1.0 gstreamer-video-1.0 gstreamer-plugins-base-1.0)

#Directories
	DIRlib= /usr/local/lib	
	incDIR= /usr/local/include
	libADT= libADT/
	INCLUIDES+= -IlibADT

#main function
	mainP= main
	callbacks = My_callbacks
	guiClass = My_guiClass
#-------------------------------------------------------------------------------
all: Project

Project: mainP.o guiClass.o callbacks.o ADT_GStreamer.o myfilter.o ADT_GTK.o ADT_DataTypes.o ADT_Tools.o
	$(CC) -export-dynamic -o $(APPNAME) \
	$(LIBS) \
	$(mainP).o \
	$(guiClass).o \
	$(callbacks).o \
	ADT_GStreamer.o \
	myfilter.o \
	$(libADT)ADT_GTK.o \
	$(libADT)ADT_DataTypes.o \
	$(libADT)ADT_Tools.o \
	-lgstinterfaces-0.10
	
mainP.o: $(mainP).cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	$(mainP).cpp
	
guiClass.o: $(guiClass).cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	$(guiClass).cpp 

callbacks.o: $(callbacks).cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	$(callbacks).cpp 

ADT_GStreamer.o: ADT_GStreamer.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	ADT_GStreamer.cpp 

myfilter.o: myfilter.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	myfilter.cpp 	

ADT_GTK.o: $(libADT)ADT_GTK.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) -o $(libADT)$@ \
	$(libADT)ADT_GTK.cpp 

ADT_DataTypes.o: $(libADT)ADT_DataTypes.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) -o $(libADT)$@ \
	$(libADT)ADT_DataTypes.cpp 

ADT_Tools.o: $(libADT)ADT_Tools.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) -o $(libADT)$@ \
	$(libADT)ADT_Tools.cpp

