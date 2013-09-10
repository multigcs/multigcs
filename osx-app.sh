#!/bin/sh
#
#


EXE="gcs"

mkdir -p multigcs.app/Contents/MacOS/lib
cp "$EXE" multigcs.app/Contents/MacOS/multigcs.bin

echo "#!/bin/bash" > multigcs.app/Contents/MacOS/multigcs
echo "cd \`dirname \$0\`" >> multigcs.app/Contents/MacOS/multigcs
echo "./multigcs.bin" >> multigcs.app/Contents/MacOS/multigcs
chmod 755 multigcs.app/Contents/MacOS/multigcs


otool -L multigcs.app/Contents/MacOS/multigcs.bin | awk '{print $1}' | grep "\.dylib$" | grep -v "^/usr/lib/" | grep -v "^/System/" | while read LIB
do
	echo "$LIB"
	LIBNAME="`echo "$LIB" | sed "s|.*/||g"`"

	cp $LIB multigcs.app/Contents/MacOS/lib

	install_name_tool -change "$LIB" @executable_path/lib/$LIBNAME multigcs.app/Contents/MacOS/multigcs.bin

done

mkdir -p multigcs.iconset/
for size in 16x16 32x32 128x128 256x256 512x512
do
	convert -scale $size icon.png multigcs.iconset/icon_${size}.png 2>/dev/null
	convert -scale $size icon.png multigcs.iconset/icon_${size}@2x.png 2>/dev/null
done

#tiffutil -cathidpicheck multigcs.iconset/icon_32x32.png multigcs.iconset/icon_32x32@2x.png -out multigcs.tiff

#hdiutil create -srcfolder "multigcs.app" -volname "multigcs" -fs HFS+ -fsargs "-c c=64,a=16,e=16" -format UDRW -size 15M multigcs.temp.dmg

device=$(hdiutil attach -readwrite -noverify -noautoopen "pack.temp.dmg" | egrep '^/dev/' | sed 1q | awk '{print $1}')


