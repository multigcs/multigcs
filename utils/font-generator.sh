#!/bin/sh
#
#

#FONT="/usr/share/fonts/truetype/freefont/FreeSans.ttf"
#FONT="/usr/share/fonts/truetype/ttf-dejavu/DejaVuSans.ttf"
FONT="/usr/lib/cinelerra/fonts/ariblk.ttf"
FONT="/usr/share/fonts/truetype/ttf-dejavu/DejaVuSans-Bold.ttf"

make -f Makefile.gl-sdl font-generator

./font-generator -bgcol 0,255,0 -fgcol 255,255,255 "$FONT"
mv /tmp/font.png fonts/font1.png

#exit 0

./font-generator -trans -fgcol 255,255,255 "$FONT"
mv /tmp/font.png fonts/font2.png

./font-generator -bgcol 0,0,0 -fgcol 255,255,255 "$FONT"
mv /tmp/font.png fonts/font3.png

./font-generator -effect -fgcol 255,255,255 "$FONT"
mv /tmp/font.png fonts/font4.png

./font-generator -effect -fgcol 0,255,0 "$FONT"
mv /tmp/font.png fonts/font5.png

./font-generator -fgcol "255,51,252" "$FONT"
mv /tmp/font.png fonts/font6.png

