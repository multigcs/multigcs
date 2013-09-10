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


umount /Volumes/multigcs

rm -rf multigcs.temp.dmg multigcs.dmg
hdiutil create -srcfolder "multigcs.app" -volname "multigcs" -fs HFS+ -fsargs "-c c=64,a=16,e=16" -format UDRW -size 15M multigcs.temp.dmg

device=$(hdiutil attach -readwrite -noverify -noautoopen "multigcs.temp.dmg" | egrep '^/dev/' | sed 1q | awk '{print $1}')
echo "## $device ##"

mkdir -p /Volumes/multigcs/.background
cp icon.png /Volumes/multigcs/.background/
convert -modulate 10 icon.png /Volumes/multigcs/.background/multigcs.png

title="multigcs"
backgroundPictureName="multigcs.png"
applicationName="multigcs"
finalDMGName="multigcs"

echo '
   tell application "Finder"
     tell disk "'${title}'"
           open
           set current view of container window to icon view
           set toolbar visible of container window to false
           set statusbar visible of container window to false
           set the bounds of container window to {400, 100, 885, 430}
           set theViewOptions to the icon view options of container window
           set arrangement of theViewOptions to not arranged
           set icon size of theViewOptions to 72
           set position of item "'${applicationName}'" of container window to {100, 100}
           set position of item "Applications" of container window to {375, 100}
           close
           open
           set background picture of theViewOptions to file ".background:'${backgroundPictureName}'"
           make new alias file at container window to POSIX file "/Applications" with properties {name:"Applications"}
           set position of item "'${applicationName}'" of container window to {100, 100}
           set position of item "Applications" of container window to {375, 100}
           update without registering applications
           delay 5
           eject
     end tell
   end tell
' | osascript

chmod -Rf go-w /Volumes/"${title}"
sync
sync
hdiutil detach ${device}
hdiutil convert "multigcs.temp.dmg" -format UDZO -imagekey zlib-level=9 -o "${finalDMGName}"
rm -f multigcs.temp.dmg


