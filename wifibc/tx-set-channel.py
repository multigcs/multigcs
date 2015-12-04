#!/usr/bin/python
#
#

import os
import re
import string 
import time
import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306
import Image
import ImageDraw
import ImageFont
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)

RST = 24
DC = 23
SPI_PORT = 0
SPI_DEVICE = 0
font = ImageFont.load_default()
disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST)
width = disp.width
height = disp.height

n = 0
aFreq = list() 

wiphy = int(os.popen("iw wlan0 info | grep wiphy | awk '{print $2}'").read())
cmd = "iw phy%s info | grep 'MHz \\['" % (wiphy)
ret_list = os.popen(cmd).read()

for line in ret_list.splitlines():
    m = re.search(r'([0-9][0-9]*) MHz \[([0-9][0-9]*)\] \((.*)\)', line)
    mhz = int(m.group(1))
    channel = int(m.group(2))
    comment = m.group(3)
    aFreq.append([channel, mhz, comment])

source = open("setup.txt", 'r')
n = int(source.read())
source.close()
cmd = "iwconfig %s channel %d" % ("wlan0", aFreq[n][0])
os.popen(cmd).read()

disp.begin()
disp.clear()
disp.display()
image = Image.new('1', (width, height))
draw = ImageDraw.Draw(image)
draw.rectangle((0, 0,  width, height), outline=0, fill=0)
buf = "Channel: %d" % (aFreq[n][0])
draw.text((0, 0), buf,  font=font, fill=255)
buf = "Frequenz: %d MHz" % (aFreq[n][1])
draw.text((0, 0 + 10), buf, font=font, fill=255)
draw.text((0, 0 + 20), aFreq[n][2], font=font, fill=255)
disp.image(image)
disp.display()

while True:
    if GPIO.input(18) == False:
        time.sleep(0.1)
        while GPIO.input(18) == False:
           time.sleep(0.1)
        if n < len(aFreq) - 1:
            n = n + 1
        else:
            n = 0
        cmd = "iwconfig %s channel %d" % ("wlan0", aFreq[n][0])
        os.popen(cmd).read()
        target = open("setup.txt", 'w')
        target.write(str(n))
        target.close()
        draw.rectangle((0, 0,  width, height), outline=0, fill=0)
        buf = "Channel: %d" % (aFreq[n][0])
        draw.text((0, 0), buf,  font=font, fill=255)
        buf = "Frequenz: %d MHz" % (aFreq[n][1])
        draw.text((0, 0 + 10), buf, font=font, fill=255)
        draw.text((0, 0 + 20), aFreq[n][2], font=font, fill=255)
        disp.image(image)
        disp.display()

