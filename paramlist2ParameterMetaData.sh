#!/bin/sh
#
#
#

#echo "" > autoquad-parameter.txt.new

echo "<?xml version=\"1.0\"?>"
echo "<Params>"
echo "  <ArduCopter2>"

grep ".." $1 | while read LINE
do

	PARAM="`echo "$LINE" | awk '{print $1}'`"
	DEFAULT="`echo "$LINE" | awk '{print $2}'`"
	MIN="`echo "$LINE" | awk '{print $3}'`"
	MAX="`echo "$LINE" | awk '{print $4}'`"
	DESC="`echo "$LINE" | grep "//" | sed "s|.*// *||g" | sed "s|&| and |g"`"

#	test "$MIN" = "" && MIN="-32300"
#	test "$MAX" = "" && MAX="32300"
#	if test -r "$2"
#	then
#		DEFINE="`grep "^#define DEFAULT_$PARAM\>" $2`"
#		DEFAULT="`echo "$DEFINE" | awk '{print $3}' | sed "s|^+||g" | sed "s|f$||g"`"
#		DESC="`echo "$DEFINE" | grep "//" | sed "s|.*// *||g" | sed "s|&| and |g"`"
#	fi

        echo "    <$PARAM>"
        echo "      <DisplayName>$PARAM</DisplayName>"
        echo "      <Description>$DESC</Description>"
        echo "      <Units></Units>"
        echo "      <Default>$DEFAULT</Default>"
        echo "      <Range>$MIN $MAX</Range>"
        echo "      <Increment>1</Increment>"
        echo "      <User>Advanced</User>"
        echo "    </$PARAM>"

#	echo "$PARAM		$DEFAULT	-33333	33333	// $DESC" >> autoquad-parameter.txt.new

done

echo "  </ArduCopter2>"
echo "</Params>"




