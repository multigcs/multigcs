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


