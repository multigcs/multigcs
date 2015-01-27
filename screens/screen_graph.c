
#include <all.h>

uint8_t graph_data[10][200];
int16_t graph_pointer = 0;
int16_t graph_size = 128;


void screen_graph (ESContext *esContext) {
	uint16_t n = 0;

	draw_title(esContext, "Graph (Test-Page)");

	for (n = 0; n < 10; n++) {
		graph_data[n][graph_pointer] = rand();

	}

	graph_data[0][graph_pointer] = (uint8_t)(ModelData[ModelActive].gyro_x / 4.0 + 128);
	graph_data[1][graph_pointer] = (uint8_t)(ModelData[ModelActive].gyro_y / 4.0 + 128);
	graph_data[2][graph_pointer] = (uint8_t)(ModelData[ModelActive].gyro_z / 4.0 + 128);
	graph_data[3][graph_pointer] = (uint8_t)(ModelData[ModelActive].acc_x * 128.0 + 128);
	graph_data[4][graph_pointer] = (uint8_t)(ModelData[ModelActive].acc_y * 128.0 + 128);


	if (graph_pointer < graph_size) {
		graph_pointer++;
	} else {
		graph_pointer = 0;
	}

	for (n = 0; n < 10; n++) {
		draw_graph_value(esContext, -1.2, 0.8, 1.2, 0.8 + 0.10, 0.001, graph_data[n], graph_size, graph_pointer, n * 25, n * 25, n * 25, 255);
		draw_graph_value(esContext, -1.2, -0.8 + (float)n * 0.12, 1.2, -0.8 + (float)n * 0.12 + 0.10, 0.001, graph_data[n], graph_size, graph_pointer, 255 - n * 25, n * 25, n * 125, 255);
	}

	draw_rect_f3(esContext, -1.2, 0.8, 0.001, 1.2, 0.8 + 0.10, 0.001, 255, 255, 255, 255);

}

