
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <math.h>
#include <linux/version.h>
#include <linux/input.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <ctype.h>
#include <termios.h>
#include <userdata.h>
#include <main.h>
#include <model.h>
#include <screen_tcl.h>
#include <my_mavlink.h>
#include <my_gps.h>
#include <frsky.h>
#include <openpilot.h>
#include <mwi21.h>
#include <jeti.h>
#include <screen_device.h>
#include <screen_baud.h>
#include <tcl.h>


Tcl_Interp *tcl_interp = NULL;
static uint8_t tcl_startup = 0;


void TclUpdateVarFloat (char *name, float val);
void TclUpdateVarInt (char *name, int val);
void TclUpdateVarString (char *name, char *val_str);

#include <tcl_draw.c>
#include <tcl_gl_draw.c>
#include <tcl_modeldata.h>
#include <tcl_modeldatavar.h>


void TclUpdateVarFloat (char *name, float val) {
	char val_str[20];
	sprintf(val_str, "%f", val);
	Tcl_SetVar(tcl_interp, name, val_str, 0);
}

void TclUpdateVarInt (char *name, int val) {
	char val_str[20];
	sprintf(val_str, "%i", val);
	Tcl_SetVar(tcl_interp, name, val_str, 0);
}

void TclUpdateVarString (char *name, char *val_str) {
	Tcl_SetVar(tcl_interp, name, val_str, 0);
}

static int Hello_Cmd (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	long n1;
	long n2;
	Tcl_Obj *res;

	if (objc != 3) {
		Tcl_WrongNumArgs(interp, 1, objv, "n1 n2");
		return TCL_ERROR;
	}

	if (Tcl_GetLongFromObj(interp, objv[1], &n1) != TCL_OK) {
		return TCL_ERROR;
	}
	
	if (Tcl_GetLongFromObj(interp, objv[2], &n2) != TCL_OK) {
		return TCL_ERROR;
	}
	
	res = Tcl_NewLongObj(n1 + n2);
	Tcl_SetObjResult(interp, res);

	return TCL_OK;
}


void tcl_init (void) {
	tcl_startup = 1;
	printf("Init TCL...\n");
	tcl_interp = Tcl_CreateInterp();
	if (Tcl_Init(tcl_interp) != TCL_OK) {
		printf("...failed (%s)\n", Tcl_GetStringResult(tcl_interp));
		return;
	}

	Tcl_CreateObjCommand(tcl_interp, "hello", Hello_Cmd, NULL, NULL);
	Tcl_CreateObjCommand(tcl_interp, "ModelData", ModelData_Cmd, NULL, NULL);

	tcl_draw_init (tcl_interp);
	tcl_gl_draw_init (tcl_interp);

	printf("...done\n");
	return;
}

void tcl_run (char *script) {
	if (tcl_startup == 0) {
		tcl_init();
	}
	tcl_update_modeldata();
	if (Tcl_Eval(tcl_interp, script) != TCL_OK) {
		printf("TCL-ERROR:\n");
		printf("#######################################################\n");
		printf("%s\n", script);
		printf("#######################################################\n");
		printf("%s\n", Tcl_GetStringResult(tcl_interp));
		printf("#######################################################\n");
	}
}

void tcl_runFile (char *file) {
	if (tcl_startup == 0) {
		tcl_init();
		TclUpdateVarString("BASE_DIR", BASE_DIR);
	}
	tcl_update_modeldata();
	if (Tcl_EvalFile(tcl_interp, file) != TCL_OK) {
		printf("TCL-ERROR:\n");
		printf("#######################################################\n");
		printf("%s\n", file);
		printf("#######################################################\n");
		printf("%s\n", Tcl_GetStringResult(tcl_interp));
		printf("#######################################################\n");
	}
}

uint8_t tcl_test (char *name, float x, float y, int8_t button, float data) {
	char script[] = "puts \"[hello 1 2]\"";
	tcl_run(script);
	return 0;
}



#define CLI_MAX_BUFFER 100
#define CLI_MAX_LINES 100
extern char cli_buffer[CLI_MAX_LINES][CLI_MAX_BUFFER];


void screen_tcl (ESContext *esContext) {
#ifndef SDLGL
	ESMatrix modelview;
	UserData *userData = esContext->userData;
#endif

	static uint8_t startup = 0;
	if (startup == 0) {
		startup = 1;

		char scriptfile[1024];
		sprintf(scriptfile, "%s/scripts/screen_tcl.tcl", BASE_DIR);
		tcl_runFile(scriptfile);

		if (Tcl_Eval(tcl_interp, "init") != TCL_OK) {
			printf("TCL-ERROR:\n");
			printf("#######################################################\n");
			printf("%s\n", Tcl_GetStringResult(tcl_interp));
			printf("#######################################################\n");
		}

	}

	tcl_update_modeldata();

	if (Tcl_Eval(tcl_interp, "view") != TCL_OK) {
		printf("TCL-ERROR:\n");
		printf("#######################################################\n");
		printf("%s\n", Tcl_GetStringResult(tcl_interp));
		printf("#######################################################\n");
	}


}


