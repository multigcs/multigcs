
/* void draw_image_f3 (ESContext *esContext, float x1, float y1, float x2, float y2, float z, char *file) { */
int tclcmd_draw_image_f3 (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 7) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float x2} { float y2} { float z} { char *file}");
		return TCL_ERROR;
	}
	double arg_x1;
	if (Tcl_GetDoubleFromObj(interp, objv[1], (double *)&arg_x1) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_y1;
	if (Tcl_GetDoubleFromObj(interp, objv[2], (double *)&arg_y1) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_x2;
	if (Tcl_GetDoubleFromObj(interp, objv[3], (double *)&arg_x2) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_y2;
	if (Tcl_GetDoubleFromObj(interp, objv[4], (double *)&arg_y2) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_z;
	if (Tcl_GetDoubleFromObj(interp, objv[5], (double *)&arg_z) != TCL_OK) {
		return TCL_ERROR;
	}
	char arg_file[1024];
	strncpy(arg_file, Tcl_GetStringFromObj(objv[6], &len), 1024);
	draw_image_f3(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_x2, (float)arg_y2, (float)arg_z, arg_file);
	return TCL_OK;
}

/* void draw_text_f3_fast (ESContext *esContext, float x1, float y1, float z1, float w, float h, char *file, char *text) { */
int tclcmd_draw_text_f3_fast (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 8) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float z1} { float w} { float h} { char *file} { char *text}");
		return TCL_ERROR;
	}
	double arg_x1;
	if (Tcl_GetDoubleFromObj(interp, objv[1], (double *)&arg_x1) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_y1;
	if (Tcl_GetDoubleFromObj(interp, objv[2], (double *)&arg_y1) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_z1;
	if (Tcl_GetDoubleFromObj(interp, objv[3], (double *)&arg_z1) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_w;
	if (Tcl_GetDoubleFromObj(interp, objv[4], (double *)&arg_w) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_h;
	if (Tcl_GetDoubleFromObj(interp, objv[5], (double *)&arg_h) != TCL_OK) {
		return TCL_ERROR;
	}
	char arg_file[1024];
	strncpy(arg_file, Tcl_GetStringFromObj(objv[6], &len), 1024);
	char arg_text[1024];
	strncpy(arg_text, Tcl_GetStringFromObj(objv[7], &len), 1024);
	draw_text_f3_fast(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_z1, (float)arg_w, (float)arg_h, arg_file, arg_text);
	return TCL_OK;
}

/* void draw_char_f3 (ESContext *esContext, float x1, float y1, float z1, float x2, float y2, float z2, char *file, char num) { */
int tclcmd_draw_char_f3 (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 9) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float z1} { float x2} { float y2} { float z2} { char *file} { char num}");
		return TCL_ERROR;
	}
	double arg_x1;
	if (Tcl_GetDoubleFromObj(interp, objv[1], (double *)&arg_x1) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_y1;
	if (Tcl_GetDoubleFromObj(interp, objv[2], (double *)&arg_y1) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_z1;
	if (Tcl_GetDoubleFromObj(interp, objv[3], (double *)&arg_z1) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_x2;
	if (Tcl_GetDoubleFromObj(interp, objv[4], (double *)&arg_x2) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_y2;
	if (Tcl_GetDoubleFromObj(interp, objv[5], (double *)&arg_y2) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_z2;
	if (Tcl_GetDoubleFromObj(interp, objv[6], (double *)&arg_z2) != TCL_OK) {
		return TCL_ERROR;
	}
	char arg_file[1024];
	strncpy(arg_file, Tcl_GetStringFromObj(objv[7], &len), 1024);
	char arg_num;
	if (Tcl_GetIntFromObj(interp, objv[8], (int *)&arg_num) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_char_f3(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_z1, (float)arg_x2, (float)arg_y2, (float)arg_z2, arg_file, (char)arg_num);
	return TCL_OK;
}

void tcl_gl_draw_init (Tcl_Interp *interp) {
	Tcl_CreateObjCommand(interp, "draw_image_f3", tclcmd_draw_image_f3, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_text_f3_fast", tclcmd_draw_text_f3_fast, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_char_f3", tclcmd_draw_char_f3, NULL, NULL);
}

