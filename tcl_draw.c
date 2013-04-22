
/* void draw_title (ESContext *esContext, char *text) { */
int tclcmd_draw_title (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 2) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { char *text}");
		return TCL_ERROR;
	}
	char arg_text[1024];
	strncpy(arg_text, Tcl_GetStringFromObj(objv[1], &len), 1024);
	draw_title(GlobalesContext, arg_text);
	return TCL_OK;
}

/* void draw_image_uncache (char *file) { */
int tclcmd_draw_image_uncache (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 1) {
		Tcl_WrongNumArgs (interp, 1, objv, "{char *file}");
		return TCL_ERROR;
	}
	char arg_file[1024];
	strncpy(arg_file, Tcl_GetStringFromObj(objv[1], &len), 1024);
	draw_image_uncache(arg_file);
	return TCL_OK;
}

/* void draw_line_f (ESContext *esContext, float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { */
int tclcmd_draw_line_f (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	if (objc != 9) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float x2} { float y2} { uint8_t r} { uint8_t g} { uint8_t b} { uint8_t a}");
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
	uint8_t arg_r;
	if (Tcl_GetIntFromObj(interp, objv[5], (int *)&arg_r) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_g;
	if (Tcl_GetIntFromObj(interp, objv[6], (int *)&arg_g) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_b;
	if (Tcl_GetIntFromObj(interp, objv[7], (int *)&arg_b) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_a;
	if (Tcl_GetIntFromObj(interp, objv[8], (int *)&arg_a) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_line_f(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_x2, (float)arg_y2, arg_r, arg_g, arg_b, arg_a);
	return TCL_OK;
}

/* void draw_line (ESContext *esContext, int16_t px1, int16_t py1, int16_t px2, int16_t py2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { */
int tclcmd_draw_line (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	if (objc != 9) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { int16_t px1} { int16_t py1} { int16_t px2} { int16_t py2} { uint8_t r} { uint8_t g} { uint8_t b} { uint8_t a}");
		return TCL_ERROR;
	}
	int16_t arg_px1;
	if (Tcl_GetIntFromObj(interp, objv[1], (int *)&arg_px1) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_py1;
	if (Tcl_GetIntFromObj(interp, objv[2], (int *)&arg_py1) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_px2;
	if (Tcl_GetIntFromObj(interp, objv[3], (int *)&arg_px2) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_py2;
	if (Tcl_GetIntFromObj(interp, objv[4], (int *)&arg_py2) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_r;
	if (Tcl_GetIntFromObj(interp, objv[5], (int *)&arg_r) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_g;
	if (Tcl_GetIntFromObj(interp, objv[6], (int *)&arg_g) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_b;
	if (Tcl_GetIntFromObj(interp, objv[7], (int *)&arg_b) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_a;
	if (Tcl_GetIntFromObj(interp, objv[8], (int *)&arg_a) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_line(GlobalesContext, arg_px1, arg_py1, arg_px2, arg_py2, arg_r, arg_g, arg_b, arg_a);
	return TCL_OK;
}

/* void draw_circle_f (ESContext *esContext, float x1, float y1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { */
int tclcmd_draw_circle_f (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	if (objc != 8) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float radius} { uint8_t r} { uint8_t g} { uint8_t b} { uint8_t a}");
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
	double arg_radius;
	if (Tcl_GetDoubleFromObj(interp, objv[3], (double *)&arg_radius) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_r;
	if (Tcl_GetIntFromObj(interp, objv[4], (int *)&arg_r) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_g;
	if (Tcl_GetIntFromObj(interp, objv[5], (int *)&arg_g) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_b;
	if (Tcl_GetIntFromObj(interp, objv[6], (int *)&arg_b) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_a;
	if (Tcl_GetIntFromObj(interp, objv[7], (int *)&arg_a) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_circle_f(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_radius, arg_r, arg_g, arg_b, arg_a);
	return TCL_OK;
}

/* void draw_circle (ESContext *esContext, int16_t x, int16_t y, int16_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { */
int tclcmd_draw_circle (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	if (objc != 8) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { int16_t x} { int16_t y} { int16_t radius} { uint8_t r} { uint8_t g} { uint8_t b} { uint8_t a}");
		return TCL_ERROR;
	}
	int16_t arg_x;
	if (Tcl_GetIntFromObj(interp, objv[1], (int *)&arg_x) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_y;
	if (Tcl_GetIntFromObj(interp, objv[2], (int *)&arg_y) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_radius;
	if (Tcl_GetIntFromObj(interp, objv[3], (int *)&arg_radius) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_r;
	if (Tcl_GetIntFromObj(interp, objv[4], (int *)&arg_r) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_g;
	if (Tcl_GetIntFromObj(interp, objv[5], (int *)&arg_g) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_b;
	if (Tcl_GetIntFromObj(interp, objv[6], (int *)&arg_b) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_a;
	if (Tcl_GetIntFromObj(interp, objv[7], (int *)&arg_a) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_circle(GlobalesContext, arg_x, arg_y, arg_radius, arg_r, arg_g, arg_b, arg_a);
	return TCL_OK;
}

/* void draw_circleFilled_f (ESContext *esContext, float x1, float y1, float radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { */
int tclcmd_draw_circleFilled_f (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	if (objc != 8) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float radius} { uint8_t r} { uint8_t g} { uint8_t b} { uint8_t a}");
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
	double arg_radius;
	if (Tcl_GetDoubleFromObj(interp, objv[3], (double *)&arg_radius) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_r;
	if (Tcl_GetIntFromObj(interp, objv[4], (int *)&arg_r) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_g;
	if (Tcl_GetIntFromObj(interp, objv[5], (int *)&arg_g) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_b;
	if (Tcl_GetIntFromObj(interp, objv[6], (int *)&arg_b) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_a;
	if (Tcl_GetIntFromObj(interp, objv[7], (int *)&arg_a) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_circleFilled_f(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_radius, arg_r, arg_g, arg_b, arg_a);
	return TCL_OK;
}

/* void draw_circleFilled (ESContext *esContext, int16_t x, int16_t y, int16_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { */
int tclcmd_draw_circleFilled (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	if (objc != 8) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { int16_t x} { int16_t y} { int16_t radius} { uint8_t r} { uint8_t g} { uint8_t b} { uint8_t a}");
		return TCL_ERROR;
	}
	int16_t arg_x;
	if (Tcl_GetIntFromObj(interp, objv[1], (int *)&arg_x) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_y;
	if (Tcl_GetIntFromObj(interp, objv[2], (int *)&arg_y) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_radius;
	if (Tcl_GetIntFromObj(interp, objv[3], (int *)&arg_radius) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_r;
	if (Tcl_GetIntFromObj(interp, objv[4], (int *)&arg_r) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_g;
	if (Tcl_GetIntFromObj(interp, objv[5], (int *)&arg_g) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_b;
	if (Tcl_GetIntFromObj(interp, objv[6], (int *)&arg_b) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_a;
	if (Tcl_GetIntFromObj(interp, objv[7], (int *)&arg_a) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_circleFilled(GlobalesContext, arg_x, arg_y, arg_radius, arg_r, arg_g, arg_b, arg_a);
	return TCL_OK;
}

/* void draw_box_f (ESContext *esContext, float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { */
int tclcmd_draw_box_f (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	if (objc != 9) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float x2} { float y2} { uint8_t r} { uint8_t g} { uint8_t b} { uint8_t a}");
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
	uint8_t arg_r;
	if (Tcl_GetIntFromObj(interp, objv[5], (int *)&arg_r) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_g;
	if (Tcl_GetIntFromObj(interp, objv[6], (int *)&arg_g) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_b;
	if (Tcl_GetIntFromObj(interp, objv[7], (int *)&arg_b) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_a;
	if (Tcl_GetIntFromObj(interp, objv[8], (int *)&arg_a) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_box_f(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_x2, (float)arg_y2, arg_r, arg_g, arg_b, arg_a);
	return TCL_OK;
}

/* void draw_box (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { */
int tclcmd_draw_box (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	if (objc != 9) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { int16_t x} { int16_t y} { int16_t w} { int16_t h} { uint8_t r} { uint8_t g} { uint8_t b} { uint8_t a}");
		return TCL_ERROR;
	}
	int16_t arg_x;
	if (Tcl_GetIntFromObj(interp, objv[1], (int *)&arg_x) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_y;
	if (Tcl_GetIntFromObj(interp, objv[2], (int *)&arg_y) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_w;
	if (Tcl_GetIntFromObj(interp, objv[3], (int *)&arg_w) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_h;
	if (Tcl_GetIntFromObj(interp, objv[4], (int *)&arg_h) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_r;
	if (Tcl_GetIntFromObj(interp, objv[5], (int *)&arg_r) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_g;
	if (Tcl_GetIntFromObj(interp, objv[6], (int *)&arg_g) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_b;
	if (Tcl_GetIntFromObj(interp, objv[7], (int *)&arg_b) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_a;
	if (Tcl_GetIntFromObj(interp, objv[8], (int *)&arg_a) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_box(GlobalesContext, arg_x, arg_y, arg_w, arg_h, arg_r, arg_g, arg_b, arg_a);
	return TCL_OK;
}

/* void draw_tria_f (ESContext *esContext, float x1, float y1, float x2, float y2, float x3, float y3, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { */
int tclcmd_draw_tria_f (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	if (objc != 11) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float x2} { float y2} { float x3} { float y3} { uint8_t r} { uint8_t g} { uint8_t b} { uint8_t a}");
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
	double arg_x3;
	if (Tcl_GetDoubleFromObj(interp, objv[5], (double *)&arg_x3) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_y3;
	if (Tcl_GetDoubleFromObj(interp, objv[6], (double *)&arg_y3) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_r;
	if (Tcl_GetIntFromObj(interp, objv[7], (int *)&arg_r) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_g;
	if (Tcl_GetIntFromObj(interp, objv[8], (int *)&arg_g) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_b;
	if (Tcl_GetIntFromObj(interp, objv[9], (int *)&arg_b) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_a;
	if (Tcl_GetIntFromObj(interp, objv[10], (int *)&arg_a) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_tria_f(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_x2, (float)arg_y2, (float)arg_x3, (float)arg_y3, arg_r, arg_g, arg_b, arg_a);
	return TCL_OK;
}

/* void draw_circleFilled_f3_part_end (ESContext *esContext, float x1, float y1, float z1, float radius, float radius_inner, float start, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { */
int tclcmd_draw_circleFilled_f3_part_end (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	if (objc != 11) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float z1} { float radius} { float radius_inner} { float start} { uint8_t r} { uint8_t g} { uint8_t b} { uint8_t a}");
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
	double arg_radius;
	if (Tcl_GetDoubleFromObj(interp, objv[4], (double *)&arg_radius) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_radius_inner;
	if (Tcl_GetDoubleFromObj(interp, objv[5], (double *)&arg_radius_inner) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_start;
	if (Tcl_GetDoubleFromObj(interp, objv[6], (double *)&arg_start) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_r;
	if (Tcl_GetIntFromObj(interp, objv[7], (int *)&arg_r) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_g;
	if (Tcl_GetIntFromObj(interp, objv[8], (int *)&arg_g) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_b;
	if (Tcl_GetIntFromObj(interp, objv[9], (int *)&arg_b) != TCL_OK) {
		return TCL_ERROR;
	}
	uint8_t arg_a;
	if (Tcl_GetIntFromObj(interp, objv[10], (int *)&arg_a) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_circleFilled_f3_part_end(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_z1, (float)arg_radius, (float)arg_radius_inner, (float)arg_start, arg_r, arg_g, arg_b, arg_a);
	return TCL_OK;
}

/* void draw_circleMeter_f3 (ESContext *esContext, float x, float y, float z, float radius, float start1, float start2, float start3, float start4, float value, char *text, char *text2, uint8_t type) { */
int tclcmd_draw_circleMeter_f3 (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 13) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x} { float y} { float z} { float radius} { float start1} { float start2} { float start3} { float start4} { float value} { char *text} { char *text2} { uint8_t type}");
		return TCL_ERROR;
	}
	double arg_x;
	if (Tcl_GetDoubleFromObj(interp, objv[1], (double *)&arg_x) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_y;
	if (Tcl_GetDoubleFromObj(interp, objv[2], (double *)&arg_y) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_z;
	if (Tcl_GetDoubleFromObj(interp, objv[3], (double *)&arg_z) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_radius;
	if (Tcl_GetDoubleFromObj(interp, objv[4], (double *)&arg_radius) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_start1;
	if (Tcl_GetDoubleFromObj(interp, objv[5], (double *)&arg_start1) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_start2;
	if (Tcl_GetDoubleFromObj(interp, objv[6], (double *)&arg_start2) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_start3;
	if (Tcl_GetDoubleFromObj(interp, objv[7], (double *)&arg_start3) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_start4;
	if (Tcl_GetDoubleFromObj(interp, objv[8], (double *)&arg_start4) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_value;
	if (Tcl_GetDoubleFromObj(interp, objv[9], (double *)&arg_value) != TCL_OK) {
		return TCL_ERROR;
	}
	char arg_text[1024];
	strncpy(arg_text, Tcl_GetStringFromObj(objv[10], &len), 1024);
	char arg_text2[1024];
	strncpy(arg_text2, Tcl_GetStringFromObj(objv[11], &len), 1024);
	uint8_t arg_type;
	if (Tcl_GetIntFromObj(interp, objv[12], (int *)&arg_type) != TCL_OK) {
		return TCL_ERROR;
	}
	draw_circleMeter_f3(GlobalesContext, (float)arg_x, (float)arg_y, (float)arg_z, (float)arg_radius, (float)arg_start1, (float)arg_start2, (float)arg_start3, (float)arg_start4, (float)arg_value, arg_text, arg_text2, arg_type);
	return TCL_OK;
}

/* void draw_image_f (ESContext *esContext, float x1, float y1, float x2, float y2, char *file) { */
int tclcmd_draw_image_f (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 6) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float x2} { float y2} { char *file}");
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
	char arg_file[1024];
	strncpy(arg_file, Tcl_GetStringFromObj(objv[5], &len), 1024);
	draw_image_f(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_x2, (float)arg_y2, arg_file);
	return TCL_OK;
}

/* void draw_image (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file) { */
int tclcmd_draw_image (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 6) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { int16_t x} { int16_t y} { int16_t w} { int16_t h} { char *file}");
		return TCL_ERROR;
	}
	int16_t arg_x;
	if (Tcl_GetIntFromObj(interp, objv[1], (int *)&arg_x) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_y;
	if (Tcl_GetIntFromObj(interp, objv[2], (int *)&arg_y) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_w;
	if (Tcl_GetIntFromObj(interp, objv[3], (int *)&arg_w) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_h;
	if (Tcl_GetIntFromObj(interp, objv[4], (int *)&arg_h) != TCL_OK) {
		return TCL_ERROR;
	}
	char arg_file[1024];
	strncpy(arg_file, Tcl_GetStringFromObj(objv[5], &len), 1024);
	draw_image(GlobalesContext, arg_x, arg_y, arg_w, arg_h, arg_file);
	return TCL_OK;
}

/* void draw_pointer (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file) { */
int tclcmd_draw_pointer (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 6) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { int16_t x} { int16_t y} { int16_t w} { int16_t h} { char *file}");
		return TCL_ERROR;
	}
	int16_t arg_x;
	if (Tcl_GetIntFromObj(interp, objv[1], (int *)&arg_x) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_y;
	if (Tcl_GetIntFromObj(interp, objv[2], (int *)&arg_y) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_w;
	if (Tcl_GetIntFromObj(interp, objv[3], (int *)&arg_w) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_h;
	if (Tcl_GetIntFromObj(interp, objv[4], (int *)&arg_h) != TCL_OK) {
		return TCL_ERROR;
	}
	char arg_file[1024];
	strncpy(arg_file, Tcl_GetStringFromObj(objv[5], &len), 1024);
	draw_pointer(GlobalesContext, arg_x, arg_y, arg_w, arg_h, arg_file);
	return TCL_OK;
}

/* void draw_text_f3 (ESContext *esContext, float x1, float y1, float z1, float w, float h, char *file, char *text) { */
int tclcmd_draw_text_f3 (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
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
	draw_text_f3(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_z1, (float)arg_w, (float)arg_h, arg_file, arg_text);
	return TCL_OK;
}

/* void draw_text_f (ESContext *esContext, float x1, float y1, float w, float h, char *file, char *text) { */
int tclcmd_draw_text_f (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 7) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { float x1} { float y1} { float w} { float h} { char *file} { char *text}");
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
	double arg_w;
	if (Tcl_GetDoubleFromObj(interp, objv[3], (double *)&arg_w) != TCL_OK) {
		return TCL_ERROR;
	}
	double arg_h;
	if (Tcl_GetDoubleFromObj(interp, objv[4], (double *)&arg_h) != TCL_OK) {
		return TCL_ERROR;
	}
	char arg_file[1024];
	strncpy(arg_file, Tcl_GetStringFromObj(objv[5], &len), 1024);
	char arg_text[1024];
	strncpy(arg_text, Tcl_GetStringFromObj(objv[6], &len), 1024);
	draw_text_f(GlobalesContext, (float)arg_x1, (float)arg_y1, (float)arg_w, (float)arg_h, arg_file, arg_text);
	return TCL_OK;
}

/* void draw_text (ESContext *esContext, int16_t x, int16_t y, int16_t w, int16_t h, char *file, char *text) { */
int tclcmd_draw_text (ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
	int len = 0;
	if (objc != 7) {
		Tcl_WrongNumArgs (interp, 1, objv, "{ESContext *esContext} { int16_t x} { int16_t y} { int16_t w} { int16_t h} { char *file} { char *text}");
		return TCL_ERROR;
	}
	int16_t arg_x;
	if (Tcl_GetIntFromObj(interp, objv[1], (int *)&arg_x) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_y;
	if (Tcl_GetIntFromObj(interp, objv[2], (int *)&arg_y) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_w;
	if (Tcl_GetIntFromObj(interp, objv[3], (int *)&arg_w) != TCL_OK) {
		return TCL_ERROR;
	}
	int16_t arg_h;
	if (Tcl_GetIntFromObj(interp, objv[4], (int *)&arg_h) != TCL_OK) {
		return TCL_ERROR;
	}
	char arg_file[1024];
	strncpy(arg_file, Tcl_GetStringFromObj(objv[5], &len), 1024);
	char arg_text[1024];
	strncpy(arg_text, Tcl_GetStringFromObj(objv[6], &len), 1024);
	draw_text(GlobalesContext, arg_x, arg_y, arg_w, arg_h, arg_file, arg_text);
	return TCL_OK;
}

void tcl_draw_init (Tcl_Interp *interp) {
	Tcl_CreateObjCommand(interp, "draw_title", tclcmd_draw_title, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_image_uncache", tclcmd_draw_image_uncache, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_line_f", tclcmd_draw_line_f, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_line", tclcmd_draw_line, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_circle_f", tclcmd_draw_circle_f, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_circle", tclcmd_draw_circle, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_circleFilled_f", tclcmd_draw_circleFilled_f, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_circleFilled", tclcmd_draw_circleFilled, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_box_f", tclcmd_draw_box_f, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_box", tclcmd_draw_box, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_tria_f", tclcmd_draw_tria_f, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_circleFilled_f3_part_end", tclcmd_draw_circleFilled_f3_part_end, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_circleMeter_f3", tclcmd_draw_circleMeter_f3, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_image_f", tclcmd_draw_image_f, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_image", tclcmd_draw_image, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_pointer", tclcmd_draw_pointer, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_text_f3", tclcmd_draw_text_f3, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_text_f", tclcmd_draw_text_f, NULL, NULL);
	Tcl_CreateObjCommand(interp, "draw_text", tclcmd_draw_text, NULL, NULL);
}

