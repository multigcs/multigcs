#!/bin/sh
#
#

test -e android/jni/SDL2 || test -e android-libs.tgz || wget http://www.multixmedia.org/test/android-libs.tgz
test -e android/jni/SDL2 || tar xzvpf android-libs.tgz

mkdir -p android/jni/src

apt-get install openjdk-7-jdk bunzip unzip ant
mkdir -p android-dev
(
	cd android-dev
	## SDK
	test -e android-sdk/ || test -e adt-bundle-linux-x86-20140702.zip || wget http://dl.google.com/android/adt/adt-bundle-linux-x86-20140702.zip
	test -e android-sdk/ || unzip adt-bundle-linux-x86-20140702.zip
	test -e android-sdk/ || mv adt-bundle-linux-x86-20140702/sdk android-sdk/
	rm -rf adt-bundle-linux-x86-20140702
	## NDK
	test -e android-ndk/ || test -e android-ndk-r9b-linux-x86.tar.bz2 || wget http://dl.google.com/android/ndk/android-ndk-r9b-linux-x86.tar.bz2
	test -e android-ndk/ || tar xjvpf android-ndk-r9b-linux-x86.tar.bz2
	test -e android-ndk/ || mv android-ndk-r9b android-ndk
	## OpenCV
	test -e opencv-android-sdk || test -e opencv-android.tgz || wget http://www.multixmedia.org/test/opencv-android.tgz
	test -e opencv-android-sdk || tar xzvpf opencv-android.tgz
)

android-dev/android-sdk/tools/android update sdk -u -t android-18

echo 'export PATH="$PATH:android-dev/android-ndk:android-dev/android-sdk/tools:android-dev/android-sdk/platform-tools"'

