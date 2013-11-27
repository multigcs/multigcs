#!/bin/sh
#
#

test -e android/jni/SDL2 || test -e android-libs.tgz || wget http://www.multixmedia.org/test/android-libs.tgz
test -e android/jni/SDL2 || tar xzvpf android-libs.tgz

apt-get install openjdk-7-jdk bunzip unzip ant
mkdir -p android-dev
(
	cd android-dev
	## SDK
	test -e android-sdk/ || test -e adt-bundle-linux-x86-20131030.zip || wget http://dl.google.com/android/adt/adt-bundle-linux-x86-20131030.zip
	test -e android-sdk/ || unzip adt-bundle-linux-x86-20131030.zip
	test -e android-sdk/ || mv adt-bundle-linux-x86-20131030/sdk android-sdk/
	rm -rf adt-bundle-linux-x86-20131030
	## NDK
	test -e android-ndk/ || test -e android-ndk-r9b-linux-x86.tar.bz2 || wget http://dl.google.com/android/ndk/android-ndk-r9b-linux-x86.tar.bz2
	test -e android-ndk/ || tar xjvpf android-ndk-r9b-linux-x86.tar.bz2
	test -e android-ndk/ || mv android-ndk-r9b android-ndk
	## OpenCV
	test -e opencv-android-sdk || test -e opencv-android.tgz || wget http://www.multixmedia.org/test/opencv-android.tgz
	test -e opencv-android-sdk || tar xzvpf opencv-android.tgz
)

export PATH="$PATH:android-dev/android-ndk:android-dev/android-sdk/tools:android-dev/android-sdk/platform-tools"
android update sdk -u

