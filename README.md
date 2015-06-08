gstapi
======

ADT GStreamer API

Gstreamer es un marco conceptual multimedia multiplataforma escrito en C, que permite construir una gran variedad de dispositivos para manejar audio y v ́ıdeo, como reproductores multimedia, editores de audio y v ́ıdeo y filtros digitales. En ciertos aspectos GStreamer es a Linux lo que DirectX es a Windows.
Para facilitar el manejo de dispositivos de vıdeo utilizando GStreamer en Linux creamos la interfaz de aplicacion o API ADT_GStreamer. ADT_GStreamer permite 1) Listar todos los dispositivos de
captura de vıdeo compatibles con video for Linux 2 (V4L2), que esten conectados al sistema; 2) Visualizar en vivo el vıdeo proveniente de un dispositivo de captura; 3) Acceder y manipular el buffer de datos del vıdeo y 4) Capturar imagenes.
