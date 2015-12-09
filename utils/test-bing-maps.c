
#include <stdio.h>
#include <stdint.h>


char *tileXYZToQuadKey(char *quadKey, int x, int y, int z) {
	int i = 0;
	int n = 0;
	for (i = z; i > 0; i--) {
		int digit = 0;
		uint8_t mask = 1 << (i - 1);
		if ((x & mask) != 0) {
			digit += 1;
		}
		if ((y & mask) != 0) {
			digit += 2;
		}
		//		printf("__ %i __\n", digit);
		quadKey[n++] = (digit + 48);
		quadKey[n] = 0;
	}
	return quadKey;
}


int main(void) {
	char quadKey[20];
	printf("http://t0.tiles.virtualearth.net/tiles/a%s.jpeg?g=854&mkt=en-US&token=Anz84uRE1RULeLwuJ0qKu5amcu5rugRXy1vKc27wUaKVyIv1SVZrUjqaOfXJJoI0\n", tileXYZToQuadKey(quadKey, 2, 6, 4));
	printf("http://t0.tiles.virtualearth.net/tiles/a%s.jpeg?g=854&mkt=en-US&token=Anz84uRE1RULeLwuJ0qKu5amcu5rugRXy1vKc27wUaKVyIv1SVZrUjqaOfXJJoI0\n", tileXYZToQuadKey(quadKey, 35, 24, 6));
http://services.arcgisonline.com/ArcGIS/rest/services/World_Topo_Map/MapServer/tile/6/35/24.png
	return 0;
}

