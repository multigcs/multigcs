

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <libgen.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

#ifndef WINDOWS
#include <termios.h>
#include <sys/times.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#else
#include <windows.h>
#include <shlobj.h>
#endif

#include <sys/time.h>
#include <sys/stat.h>
#include <png.h>

#ifdef RPI_NO_X
#include <linux/input.h>
#endif


#ifndef ANDROID
#include <tcl.h>
#endif

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#ifdef ANDROID
#include <SDL.h>
#include <android_gles.h>
#include <SDL_opengles.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_events.h>

#include <android/sensor.h>
#include <android/log.h>
#include <jni_functions.h>

#else

#ifdef OSX
#include <SDL_main.h>
#endif
#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_events.h>
#ifndef SDLGL
#include "esUtil.h"
#else
#ifndef OSX
#define NO_SDL_GLEXT
#include <GL/glew.h>
#ifndef WINDOWS
#include <GL/glext.h>
#endif
#include <GL/gl.h>
#else
#include <OpenGL/glu.h>
#endif
#include <SDL_image.h>
#ifndef ANDROID
#include <SDL_opengl.h>
#else
#include <SDL_opengles.h>
#endif
#endif

#endif

#ifndef OSX
#ifdef SDLGL
#include <videocapture.h>
#include <savepng.h>
#endif
#endif

#include <model.h>
#include <serial.h>
#include <geomag70.h>
#include <webclient.h>
#include <my_mavlink.h>
#include <userdata.h>
#include <main.h>
#include <my_gps.h>
#include <mwi21.h>
#include <simplebgc.h>
#include <brugi.h>
#include <openpilot.h>
#include <jeti.h>
#include <frsky.h>
#include <tracker.h>
#include <webserv.h>
#include <logging.h>
#include <openpilot_xml.h>
#include <htmlget.h>

#include <screen_background.h>
#include <screen_baseflightcli.h>
#include <screen_baud.h>
#include <screen_brugi.h>
#include <screen_simplebgc.h>
#include <screen_calibration.h>
#include <screen_cli.h>
#include <screen_device.h>
#include <screen_filesystem.h>
#include <screen_fms.h>
#include <screen_graph.h>
#include <screen_hud.h>
#include <screen_keyboard.h>
#include <screen_map.h>
#include <screen_mavlink_menu.h>
#include <screen_model.h>
#include <screen_mwi_menu.h>
#include <screen_openpilot_menu.h>
#include <screen_rcflow.h>
#include <screen_system.h>
#include <screen_telemetry.h>
#include <screen_tracker.h>
#include <screen_videolist.h>
#include <screen_wpedit.h>
#ifndef ANDROID
#include <screen_tcl.h>
#endif

#ifndef ANDROID
#include <screen_tcl.h>
#endif


#ifndef SDLGL
#include "gles_draw.h"
#else
#ifdef ANDROID
#include "glesa_draw.h"
#else
#include "gl_draw.h"
#endif
#endif
#include "draw.h"

