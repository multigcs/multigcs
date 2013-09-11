#!/bin/sh
#
#


EXE="gcs"

applicationName="multigcs"
dmg_back="dmg-background.png"
dmg_width=522
dmg_height=361
dmg_topleft_x=200
dmg_topleft_y=200
dmg_bottomright_x=`expr $dmg_topleft_x + $dmg_width`
dmg_bottomright_y=`expr $dmg_topleft_y + $dmg_height`


mkdir -p ${applicationName}.app/Contents/Resources
mkdir -p ${applicationName}.app/Contents/MacOS/lib
cp "$EXE" ${applicationName}.app/Contents/MacOS/${applicationName}.bin

echo "#!/bin/bash" > ${applicationName}.app/Contents/MacOS/${applicationName}
echo "cd \`dirname \$0\`" >> ${applicationName}.app/Contents/MacOS/${applicationName}
echo "./${applicationName}.bin" >> ${applicationName}.app/Contents/MacOS/${applicationName}
chmod 755 ${applicationName}.app/Contents/MacOS/${applicationName}

echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" > ${applicationName}.app/Contents/Info.plist
echo "<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" >> ${applicationName}.app/Contents/Info.plist
echo "<plist version=\"1.0\">" >> ${applicationName}.app/Contents/Info.plist
echo "<dict>" >> ${applicationName}.app/Contents/Info.plist
echo "  <key>CFBundleGetInfoString</key>" >> ${applicationName}.app/Contents/Info.plist
echo "  <string>${applicationName}</string>" >> ${applicationName}.app/Contents/Info.plist
echo "  <key>CFBundleExecutable</key>" >> ${applicationName}.app/Contents/Info.plist
echo "  <string>${applicationName}</string>" >> ${applicationName}.app/Contents/Info.plist
echo "  <key>CFBundleIdentifier</key>" >> ${applicationName}.app/Contents/Info.plist
echo "  <string>org.multixmedia.www</string>" >> ${applicationName}.app/Contents/Info.plist
echo "  <key>CFBundleName</key>" >> ${applicationName}.app/Contents/Info.plist
echo "  <string>${applicationName}</string>" >> ${applicationName}.app/Contents/Info.plist
echo "  <key>CFBundleIconFile</key>" >> ${applicationName}.app/Contents/Info.plist
echo "  <string>${applicationName}.icns</string>" >> ${applicationName}.app/Contents/Info.plist
echo "  <key>CFBundleShortVersionString</key>" >> ${applicationName}.app/Contents/Info.plist
echo "  <string>0.1</string>" >> ${applicationName}.app/Contents/Info.plist
echo "  <key>CFBundleInfoDictionaryVersion</key>" >> ${applicationName}.app/Contents/Info.plist
echo "  <string>6.0</string>" >> ${applicationName}.app/Contents/Info.plist
echo "  <key>CFBundlePackageType</key>" >> ${applicationName}.app/Contents/Info.plist
echo "  <string>APPL</string>" >> ${applicationName}.app/Contents/Info.plist
echo "  <key>IFMajorVersion</key>" >> ${applicationName}.app/Contents/Info.plist
echo "  <integer>0</integer>" >> ${applicationName}.app/Contents/Info.plist
echo "  <key>IFMinorVersion</key>" >> ${applicationName}.app/Contents/Info.plist
echo "  <integer>1</integer>" >> ${applicationName}.app/Contents/Info.plist
echo "</dict>" >> ${applicationName}.app/Contents/Info.plist
echo "</plist>" >> ${applicationName}.app/Contents/Info.plist

otool -L ${applicationName}.app/Contents/MacOS/${applicationName}.bin | awk '{print $1}' | grep "\.dylib$" | grep -v "^/usr/lib/" | grep -v "^/System/" | while read LIB
do
	echo "$LIB"
	LIBNAME="`echo "$LIB" | sed "s|.*/||g"`"
	cp $LIB ${applicationName}.app/Contents/MacOS/lib
	install_name_tool -change "$LIB" @executable_path/lib/$LIBNAME ${applicationName}.app/Contents/MacOS/${applicationName}.bin
done

N=0
while test "$N" -lt "3"
do
	echo $N
	ls ${applicationName}.app/Contents/MacOS/lib/*.dylib | while read LIBFILE
	do
		otool -L $LIBFILE | awk '{print $1}' | grep "\.dylib$" | grep "^/opt/" | grep -v "^/System/" | while read LIB
		do
			echo "$LIB"
			LIBNAME="`echo "$LIB" | sed "s|.*/||g"`"
			cp $LIB ${applicationName}.app/Contents/MacOS/lib
			install_name_tool -change "$LIB" @executable_path/lib/$LIBNAME ${applicationName}.app/Contents/MacOS/${applicationName}.bin
		done
	done
done

otool -L ${applicationName}.app/Contents/MacOS/${applicationName}.bin | awk '{print $1}' | grep "\.dylib$" | grep -v "^/usr/lib/" | grep -v "^/System/" | while read LIB
do
	echo "$LIB"
	LIBNAME="`echo "$LIB" | sed "s|.*/||g"`"
	cp $LIB ${applicationName}.app/Contents/MacOS/lib
	install_name_tool -change "$LIB" @executable_path/lib/$LIBNAME ${applicationName}.app/Contents/MacOS/${applicationName}.bin
done

if ! test -e ${applicationName}.icns
then
	rm -rf ${applicationName}.iconset/
	mkdir -p ${applicationName}.iconset/
	for size in 16x16 32x32 128x128 256x256 512x512
	do
		convert -scale $size! icon.png ${applicationName}.iconset/icon_${size}.png 2>/dev/null
	#	convert -scale $size! icon.png ${applicationName}.iconset/icon_${size}@2x.png 2>/dev/null
	done
	png2icns ${applicationName}.icns ${applicationName}.iconset/icon_*png 2>/dev/null
fi

cp ${applicationName}.icns ${applicationName}.app/Contents/Resources

#tiffutil -cathidpicheck ${applicationName}.iconset/icon_32x32.png ${applicationName}.iconset/icon_32x32@2x.png -out ${applicationName}.tiff


umount /Volumes/${applicationName}

rm -rf ${applicationName}.temp.dmg ${applicationName}.dmg
hdiutil create -srcfolder "${applicationName}.app" -volname "${applicationName}" -fs HFS+ -fsargs "-c c=64,a=16,e=16" -format UDRW -size 15M ${applicationName}.temp.dmg

device=$(hdiutil attach -readwrite -noverify -noautoopen "${applicationName}.temp.dmg" | egrep '^/dev/' | sed 1q | awk '{print $1}')
echo "## $device ##"

mkdir -p /Volumes/${applicationName}/.background
cp icon.png /Volumes/${applicationName}/.background/icon.png
cp dmg-background.png /Volumes/${applicationName}/.background/dmg-background.png
ln -s /Applications /Volumes/${applicationName}/Applications


echo '
   tell application "Finder"
     tell disk "'${applicationName}'"
           open
           set current view of container window to icon view
           set toolbar visible of container window to false
           set statusbar visible of container window to false
           set the bounds of container window to {'${dmg_topleft_x}', '${dmg_topleft_y}', '${dmg_bottomright_x}', '${dmg_bottomright_y}'}
           set theViewOptions to the icon view options of container window
           set arrangement of theViewOptions to not arranged
           set icon size of theViewOptions to 104
           set background picture of theViewOptions to file ".background:'${dmg_back}'"
           set position of item "'${applicationName}'" of container window to {120, 180}
           set position of item "'Applications'" of container window to {400, 180}
           close
           open
           update without registering applications
           delay 5
           eject
     end tell
   end tell
' | osascript

chmod -Rf go-w /Volumes/"${applicationName}"
sync
sync
hdiutil detach ${device}
hdiutil convert "${applicationName}.temp.dmg" -format UDZO -imagekey zlib-level=9 -o "${applicationName}"
rm -f ${applicationName}.temp.dmg


