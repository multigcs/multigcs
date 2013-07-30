


proc init {} {
	puts "## TCL_INIT ##"
}

proc view {} {
	global BASE_DIR
	global ModelData

	draw_title "TCL-Interpreter [clock seconds]"
	draw_text_f3 -0.5 0.0 0.0 0.1 0.1 $BASE_DIR/fonts/font6.png "$ModelData(name)"
	draw_line_f -0.6 -0.6 0.6 -0.6 255 0 0 255
	draw_line_f -0.6 0.6 0.6 0.6 0 255 0 255

}





