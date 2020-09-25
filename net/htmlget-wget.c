
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int htmlget(char *url, char *file) {
    char cmd_str[8192];
    sprintf(cmd_str, "wget -U 'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)' -O '%s' '%s' || rm -f '%s'", file, url, file);
    system(cmd_str);
	return 0;
}

/*
void main () {
	htmlget("http://maps.google.com/mapfiles/kml/pal3/icon21.png", "/tmp/test.png");
}
*/
