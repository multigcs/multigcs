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

echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" > multigcs.app/Contents/Info.plist
echo "<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" >> multigcs.app/Contents/Info.plist
echo "<plist version=\"1.0\">" >> multigcs.app/Contents/Info.plist
echo "<dict>" >> multigcs.app/Contents/Info.plist
echo "  <key>CFBundleGetInfoString</key>" >> multigcs.app/Contents/Info.plist
echo "  <string>multigcs</string>" >> multigcs.app/Contents/Info.plist
echo "  <key>CFBundleExecutable</key>" >> multigcs.app/Contents/Info.plist
echo "  <string>multigcs</string>" >> multigcs.app/Contents/Info.plist
echo "  <key>CFBundleIdentifier</key>" >> multigcs.app/Contents/Info.plist
echo "  <string>org.multixmedia.www</string>" >> multigcs.app/Contents/Info.plist
echo "  <key>CFBundleName</key>" >> multigcs.app/Contents/Info.plist
echo "  <string>multigcs</string>" >> multigcs.app/Contents/Info.plist
echo "  <key>CFBundleIconFile</key>" >> multigcs.app/Contents/Info.plist
echo "  <string>multigcs.icns</string>" >> multigcs.app/Contents/Info.plist
echo "  <key>CFBundleShortVersionString</key>" >> multigcs.app/Contents/Info.plist
echo "  <string>0.1</string>" >> multigcs.app/Contents/Info.plist
echo "  <key>CFBundleInfoDictionaryVersion</key>" >> multigcs.app/Contents/Info.plist
echo "  <string>6.0</string>" >> multigcs.app/Contents/Info.plist
echo "  <key>CFBundlePackageType</key>" >> multigcs.app/Contents/Info.plist
echo "  <string>APPL</string>" >> multigcs.app/Contents/Info.plist
echo "  <key>IFMajorVersion</key>" >> multigcs.app/Contents/Info.plist
echo "  <integer>0</integer>" >> multigcs.app/Contents/Info.plist
echo "  <key>IFMinorVersion</key>" >> multigcs.app/Contents/Info.plist
echo "  <integer>1</integer>" >> multigcs.app/Contents/Info.plist
echo "</dict>" >> multigcs.app/Contents/Info.plist
echo "</plist>" >> multigcs.app/Contents/Info.plist

otool -L multigcs.app/Contents/MacOS/multigcs.bin | awk '{print $1}' | grep "\.dylib$" | grep -v "^/usr/lib/" | grep -v "^/System/" | while read LIB
do
	echo "$LIB"
	LIBNAME="`echo "$LIB" | sed "s|.*/||g"`"

	cp $LIB multigcs.app/Contents/MacOS/lib

	install_name_tool -change "$LIB" @executable_path/lib/$LIBNAME multigcs.app/Contents/MacOS/multigcs.bin

done

if ! test -e multigcs.icns
then
	rm -rf multigcs.iconset/
	mkdir -p multigcs.iconset/
	for size in 16x16 32x32 128x128 256x256 512x512
	do
		convert -scale $size! icon.png multigcs.iconset/icon_${size}.png 2>/dev/null
	#	convert -scale $size! icon.png multigcs.iconset/icon_${size}@2x.png 2>/dev/null
	done
	png2icns multigcs.icns multigcs.iconset/icon_*png 2>/dev/null
fi

cp multigcs.icns multigcs.app/Contents/

#tiffutil -cathidpicheck multigcs.iconset/icon_32x32.png multigcs.iconset/icon_32x32@2x.png -out multigcs.tiff


umount /Volumes/multigcs

rm -rf multigcs.temp.dmg multigcs.dmg
hdiutil create -srcfolder "multigcs.app" -volname "multigcs" -fs HFS+ -fsargs "-c c=64,a=16,e=16" -format UDRW -size 15M multigcs.temp.dmg

device=$(hdiutil attach -readwrite -noverify -noautoopen "multigcs.temp.dmg" | egrep '^/dev/' | sed 1q | awk '{print $1}')
echo "## $device ##"

mkdir -p /Volumes/multigcs/.background
cp icon.png /Volumes/multigcs/.background/icon.png
cp dmg-background.png /Volumes/multigcs/.background/dmg-background.png
ln -s /Applications /Volumes/multigcs/Applications


applicationName="multigcs"
dmg_back="dmg-background.png"
dmg_width=522
dmg_height=361
dmg_topleft_x=200
dmg_topleft_y=200
dmg_bottomright_x=`expr $dmg_topleft_x + $dmg_width`
dmg_bottomright_y=`expr $dmg_topleft_y + $dmg_height`

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
hdiutil convert "multigcs.temp.dmg" -format UDZO -imagekey zlib-level=9 -o "${applicationName}"
rm -f multigcs.temp.dmg


