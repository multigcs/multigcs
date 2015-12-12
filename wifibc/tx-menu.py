#!/usr/bin/python
#
#

import os
import re
import subprocess
import string 
import time
import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306
from PIL import Image
import ImageDraw
import ImageFont
import RPi.GPIO as GPIO
import time
import simplejson

## set defaults ##
setup_data_default = {
        'Wifi': {'Device': "wlan0", 'Channel': 11, 'Port': 0, 'Num-FEC': 4, 'Bytes/Pack.': 1024, 'Pack./Block': 8, 'Rate': 18},
        'Camera': {'Size': '720p', 'Flip-H': 0, 'Flip-V': 0, 'Rotate': 0, 'Sharpness': 0, 'Contrast': 0, 'Brightness': 50, 'Saturation': 0, 'Exposure': 'auto', 'AWB': 'auto', 'FPS': 48, 'Rate': 4000000},
        'Telemetry': {'Port': "/dev/ttyUSB1", 'Baud': 57600, 'Protocol': 'Mavlink'},
        'Display': {'Font': 20, 'Flip': 0, 'Invert': 0},
}

## init inputs ##
GPIO.setmode(GPIO.BCM)
GPIO.setup(7, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)

## set types ##
MENU = "menu"
COMMAND = "command"
BOOL = "bool"
OPTION = "option"
EXITMENU = "exitmenu"

check = {'dev': "", 'channel': "", 'rate': "", 'opt': "", 'opt_tx': ""}

## menu-structure ##
menu_data = {
        'title': "fpv-hd", 'type': MENU,
        'options':[
                { 'title': "Wifi", 'type': MENU,
                        'options': [
                                { 'title': "Channel", 'type': MENU,
                                        'options': [
                                        ]
                                },
                                { 'title': "Device", 'type': MENU,
                                        'options': [
                                        ]
                                },
                                { 'title': "Rate", 'type': MENU,
                                        'options': [
                                          { 'title': "6", 'value': 6, 'type': OPTION },
                                          { 'title': "9", 'value': 9, 'type': OPTION },
                                          { 'title': "12", 'value': 12, 'type': OPTION },
                                          { 'title': "18", 'value': 18, 'type': OPTION },
                                          { 'title': "24", 'value': 24, 'type': OPTION },
                                          { 'title': "36", 'value': 36, 'type': OPTION },
                                          { 'title': "48", 'value': 48, 'type': OPTION },
                                          { 'title': "54", 'value': 54, 'type': OPTION },
                                        ]
                                },
                                { 'title': "Port", 'type': MENU,
                                        'options': [
                                          { 'title': "0", 'value': 0, 'type': OPTION },
                                          { 'title': "1", 'value': 1, 'type': OPTION },
                                          { 'title': "3", 'value': 2, 'type': OPTION },
                                          { 'title': "4", 'value': 3, 'type': OPTION },
                                        ]
                                },
                                { 'title': "Num-FEC", 'type': MENU,
                                        'options': [
                                          { 'title': "2", 'value': 2, 'type': OPTION },
                                          { 'title': "4", 'value': 4, 'type': OPTION },
                                          { 'title': "6", 'value': 6, 'type': OPTION },
                                          { 'title': "8", 'value': 8, 'type': OPTION },
                                        ]
                                },
                                { 'title': "Bytes/Pack.", 'type': MENU,
                                        'options': [
                                          { 'title': "512", 'value': 512, 'type': OPTION },
                                          { 'title': "1024", 'value': 1024, 'type': OPTION },
                                          { 'title': "1400", 'value': 1400, 'type': OPTION },
                                        ]
                                },
                                { 'title': "Pack./Block", 'type': MENU,
                                        'options': [
                                          { 'title': "4", 'value': 4, 'type': OPTION },
                                          { 'title': "6", 'value': 6, 'type': OPTION },
                                          { 'title': "8", 'value': 8, 'type': OPTION },
                                          { 'title': "12", 'value': 12, 'type': OPTION },
                                          { 'title': "16", 'value': 16, 'type': OPTION },
                                        ]
                                },
                        ]
                },
                { 'title': "Camera", 'type': MENU,
                        'options': [
                                { 'title': "Flip-V", 'type': BOOL,
                                        'options': [
                                          { 'title': "no", 'value': 0, 'type': OPTION },
                                          { 'title': "yes", 'value': 1, 'type': OPTION },
                                        ]
                                },
                                { 'title': "Flip-H", 'type': BOOL,
                                        'options': [
                                          { 'title': "no", 'value': 0, 'type': OPTION },
                                          { 'title': "yes", 'value': 1, 'type': OPTION },
                                        ]
                                },
                                { 'title': "Rotate", 'type': MENU,
                                        'options': [
                                          { 'title': "0", 'value': 0, 'type': OPTION },
                                          { 'title': "90", 'value': 90, 'type': OPTION },
                                          { 'title': "180", 'value': 180, 'type': OPTION },
                                          { 'title': "270", 'value': 270, 'type': OPTION },
                                        ]
                                },
                                { 'title': "Size", 'type': MENU,
                                        'options': [
                                          { 'title': "680x", 'value': '680x', 'type': OPTION },
                                          { 'title': "720p", 'value': '720p', 'type': OPTION },
                                          { 'title': "1080p", 'value': '1080p', 'type': OPTION },
                                        ]
                                },
								{ 'title': "Sharpness", 'type': MENU,
										'options': [
												{ 'title': "-100", 'value': -100, 'type': OPTION },
												{ 'title': "-75", 'value': -75, 'type': OPTION },
												{ 'title': "-50", 'value': -50, 'type': OPTION },
												{ 'title': "-25", 'value': -25, 'type': OPTION },
												{ 'title': "0", 'value': 0, 'type': OPTION },
												{ 'title': "25", 'value': 25, 'type': OPTION },
												{ 'title': "50", 'value': 50, 'type': OPTION },
												{ 'title': "75", 'value': 75, 'type': OPTION },
												{ 'title': "100", 'value': 100, 'type': OPTION },
										]
								},
								{ 'title': "Contrast", 'type': MENU,
										'options': [
												{ 'title': "-100", 'value': -100, 'type': OPTION },
												{ 'title': "-75", 'value': -75, 'type': OPTION },
												{ 'title': "-50", 'value': -50, 'type': OPTION },
												{ 'title': "-25", 'value': -25, 'type': OPTION },
												{ 'title': "0", 'value': 0, 'type': OPTION },
												{ 'title': "25", 'value': 25, 'type': OPTION },
												{ 'title': "50", 'value': 50, 'type': OPTION },
												{ 'title': "75", 'value': 75, 'type': OPTION },
												{ 'title': "100", 'value': 100, 'type': OPTION },
										]
								},
								{ 'title': "Brightness", 'type': MENU,
										'options': [
												{ 'title': "0", 'value': 0, 'type': OPTION },
												{ 'title': "10", 'value': 10, 'type': OPTION },
												{ 'title': "20", 'value': 20, 'type': OPTION },
												{ 'title': "30", 'value': 30, 'type': OPTION },
												{ 'title': "40", 'value': 40, 'type': OPTION },
												{ 'title': "50", 'value': 50, 'type': OPTION },
												{ 'title': "60", 'value': 60, 'type': OPTION },
												{ 'title': "70", 'value': 70, 'type': OPTION },
												{ 'title': "80", 'value': 80, 'type': OPTION },
												{ 'title': "90", 'value': 90, 'type': OPTION },
												{ 'title': "100", 'value': 100, 'type': OPTION },
										]
								},
								{ 'title': "Saturation", 'type': MENU,
										'options': [
												{ 'title': "-100", 'value': -100, 'type': OPTION },
												{ 'title': "-75", 'value': -75, 'type': OPTION },
												{ 'title': "-50", 'value': -50, 'type': OPTION },
												{ 'title': "-25", 'value': -25, 'type': OPTION },
												{ 'title': "0", 'value': 0, 'type': OPTION },
												{ 'title': "25", 'value': 25, 'type': OPTION },
												{ 'title': "50", 'value': 50, 'type': OPTION },
												{ 'title': "75", 'value': 75, 'type': OPTION },
												{ 'title': "100", 'value': 100, 'type': OPTION },
										]
								},
								{ 'title': "Exposure", 'type': MENU,
										'options': [
												{ 'title': "off", 'type': OPTION },
												{ 'title': "auto", 'type': OPTION },
												{ 'title': "night", 'type': OPTION },
												{ 'title': "nightpreview", 'type': OPTION },
												{ 'title': "backlight", 'type': OPTION },
												{ 'title': "spotlight", 'type': OPTION },
												{ 'title': "sports", 'type': OPTION },
												{ 'title': "snow", 'type': OPTION },
												{ 'title': "beach", 'type': OPTION },
												{ 'title': "verylong", 'type': OPTION },
												{ 'title': "fixedfps", 'type': OPTION },
												{ 'title': "antishake", 'type': OPTION },
												{ 'title': "fireworks", 'type': OPTION },
										]
								},
								{ 'title': "AWB", 'type': MENU,
										'options': [
												{ 'title': "off", 'type': OPTION },
												{ 'title': "auto", 'type': OPTION },
												{ 'title': "sun", 'type': OPTION },
												{ 'title': "cloud", 'type': OPTION },
												{ 'title': "shade", 'type': OPTION },
												{ 'title': "tungsten", 'type': OPTION },
												{ 'title': "fluorescent", 'type': OPTION },
												{ 'title': "incandescent", 'type': OPTION },
												{ 'title': "flash", 'type': OPTION },
												{ 'title': "horizon", 'type': OPTION },
										]
								},
								{ 'title': "FPS", 'type': MENU,
										'options': [
												{ 'title': "12", 'value': 12, 'type': OPTION },
												{ 'title': "24", 'value': 24, 'type': OPTION },
												{ 'title': "25", 'value': 25, 'type': OPTION },
												{ 'title': "48", 'value': 48, 'type': OPTION },
												{ 'title': "50", 'value': 50, 'type': OPTION },
										]
								},
								{ 'title': "Rate", 'type': MENU,
										'options': [
												{ 'title': "1000000", 'value': 1000000, 'type': OPTION },
												{ 'title': "2000000", 'value': 2000000, 'type': OPTION },
												{ 'title': "3000000", 'value': 3000000, 'type': OPTION },
												{ 'title': "4000000", 'value': 4000000, 'type': OPTION },
												{ 'title': "5000000", 'value': 5000000, 'type': OPTION },
												{ 'title': "6000000", 'value': 6000000, 'type': OPTION },
												{ 'title': "7000000", 'value': 7000000, 'type': OPTION },
												{ 'title': "8000000", 'value': 8000000, 'type': OPTION },
										]
								},
                        ]
                },
                { 'title': "Telemetry", 'type': MENU,
                        'options': [
                                { 'title': "Protocol", 'type': MENU,
                                        'options': [
                                          { 'title': "Mavlink", 'value': "Mavlink", 'type': OPTION },
                                          { 'title': "MultiWii", 'value': "MultiWii", 'type': OPTION },
                                          { 'title': "OpenPilot", 'value': "OpenPilot", 'type': OPTION },
                                          { 'title': "FrSky", 'value': "NMEA", 'type': OPTION },
                                          { 'title': "NMEA", 'value': "NMEA", 'type': OPTION },
                                        ]
                                },
                                { 'title': "Port", 'type': MENU,
                                        'options': [
                                        ]
                                },
                                { 'title': "Baud", 'type': MENU,
                                        'options': [
                                          { 'title': "2400", 'value': 2400, 'type': OPTION },
                                          { 'title': "9600", 'value': 9600, 'type': OPTION },
                                          { 'title': "57600", 'value': 57600, 'type': OPTION },
                                          { 'title': "115200", 'value': 115200, 'type': OPTION },
                                        ]
                                },
                        ]
                },
                { 'title': "Display", 'type': MENU,
                        'options': [
                                { 'title': "Font", 'type': MENU,
                                        'options': [
                                          { 'title': "8", 'value': 8, 'type': OPTION },
                                          { 'title': "11", 'value': 11, 'type': OPTION },
                                          { 'title': "20", 'value': 20, 'type': OPTION },
                                        ]
                                },
                                { 'title': "Flip", 'type': BOOL,
                                        'options': [
                                          { 'title': "no", 'value': 0, 'type': OPTION },
                                          { 'title': "yes", 'value': 1, 'type': OPTION },
                                        ]
                                },
                                { 'title': "Invert", 'type': BOOL,
                                        'options': [
                                          { 'title': "no", 'value': 0, 'type': OPTION },
                                          { 'title': "yes", 'value': 1, 'type': OPTION },
                                        ]
                                },
                        ]
                },
                { 'title': "WLAN-Connect", 'type': COMMAND, 'cmd': "sh ap-con.sh 2>&1", 'wait': 1, 'reset': 1},
        ]
}




def serial_update_device_list():
        for menu_main in menu_data['options']:
                if menu_main['title'] == "Telemetry":
                        for menu_tele in menu_main['options']:
                                if menu_tele['title'] == "Port":
                                        menu_tele['options'] = []
                                        devlist = os.popen("ls /dev/tty[A-Z]* | cat").read()
                                        for device in devlist.splitlines():
                                                menu_tele['options'].append({ 'title': device, 'type': OPTION, 'value': device})
                                        break


def wlan_update_device_list():
        for menu_main in menu_data['options']:
                if menu_main['title'] == "Wifi":
                        for menu_wifi in menu_main['options']:
                                if menu_wifi['title'] == "Device":
                                        menu_wifi['options'] = []
                                        devlist = os.popen("iwconfig 2>/dev/null | grep \"^[a-zA-Z]\" | awk '{print $1}'").read()
                                        for device in devlist.splitlines():
                                                menu_wifi['options'].append({ 'title': device, 'type': OPTION, 'value': device})
                                        break


def wlan_update_channel_list():
        aFreq = list() 
        wiphy = int(os.popen("iw " + str(setup_data['Wifi']['Device']) + " info | grep wiphy | awk '{print $2}'").read())
        cmd = "iw phy%s info | grep 'MHz \\['" % (wiphy)
        ret_list = os.popen(cmd).read()
        for line in ret_list.splitlines():
                m = re.search(r'([0-9][0-9]*) MHz \[([0-9][0-9]*)\] \((.*)\)', line)
                mhz = int(m.group(1))
                channel = int(m.group(2))
                comment = m.group(3)
                aFreq.append([channel, mhz, comment])
        for menu_main in menu_data['options']:
                if menu_main['title'] == "Wifi":
                        for menu_wifi in menu_main['options']:
                                if menu_wifi['title'] == "Channel":
                                        menu_wifi['options'] = []
                                        for freq in aFreq:
                                                title = "ch%i %i MHz" % (freq[0], freq[1])
                                                command = "iwconfig %s channel %i" % (str(setup_data['Wifi']['Device']), freq[0])
                                                menu_wifi['options'].append({ 'title': title, 'type': OPTION, 'value': freq[0]})
                                        break

def restart_tx():
        opt = "" 
        opt_tx = "" 
        w = 1920
        h = 1080 
        if setup_data['Camera']['Size'] == '640x':
                w = 640 
                h = 480
        if setup_data['Camera']['Size'] == '720p':
                w = 1280
                h = 720
        if setup_data['Camera']['Flip-H']:
                opt += " -hf " 
        if setup_data['Camera']['Flip-V']:
                opt += " -vf " 
        opt += " -rot " + str(setup_data['Camera']['Rotate'])
        opt += " -sh " + str(setup_data['Camera']['Sharpness'])
        opt += " -co " + str(setup_data['Camera']['Contrast'])
        opt += " -br " + str(setup_data['Camera']['Brightness'])
        opt += " -sa " + str(setup_data['Camera']['Saturation'])
        opt += " -ex " + str(setup_data['Camera']['Exposure'])
        opt += " -awb " + str(setup_data['Camera']['AWB'])
        opt += " -fps " + str(setup_data['Camera']['FPS'])
        opt += " -g " + str(setup_data['Camera']['FPS'])
        opt += " -b " + str(setup_data['Camera']['Rate'])
        opt += " -w " + str(w)
        opt += " -h " + str(h)

        opt_tx += " -p " + str(setup_data['Wifi']['Port'])
        opt_tx += " -r " + str(setup_data['Wifi']['Num-FEC'])
        opt_tx += " -f " + str(setup_data['Wifi']['Bytes/Pack.'])
        opt_tx += " -b " + str(setup_data['Wifi']['Pack./Block'])
        opt_tx += " " + str(setup_data['Wifi']['Device'])

        if check['opt'] != opt or check['opt_tx'] != opt_tx or check['dev'] != setup_data['Wifi']['Device'] or check['rate'] != setup_data['Wifi']['Rate']:
                os.system('killall raspivid 2>/dev/null || true')
                os.system('killall tx 2>/dev/null || true')
        if check['dev'] != setup_data['Wifi']['Device']:
                print 'ifconfig %s down || true' % (setup_data['Wifi']['Device'])
                os.system('ifconfig %s down || true' % (setup_data['Wifi']['Device']))
                print 'iw dev %s set monitor otherbss fcsfail || true' % (setup_data['Wifi']['Device'])
                os.system('iw dev %s set monitor otherbss fcsfail || true' % (setup_data['Wifi']['Device']))
                print 'ifconfig %s up 2>/dev/null || true' % (setup_data['Wifi']['Device'])
                os.system('ifconfig %s up 2>/dev/null || true' % (setup_data['Wifi']['Device']))
                print 'iw reg set US 2>/dev/null || true'
                os.system('iw reg set US 2>/dev/null || true')
        if check['dev'] != setup_data['Wifi']['Device'] or check['rate'] != setup_data['Wifi']['Rate']:
                print 'iwconfig %s rate %sM fixed 2>/dev/null || true' % (setup_data['Wifi']['Device'], str(setup_data['Wifi']['Rate']))
                os.system('iwconfig %s rate %sM fixed 2>/dev/null || true' % (setup_data['Wifi']['Device'], str(setup_data['Wifi']['Rate'])))
        if check['dev'] != setup_data['Wifi']['Device'] or check['channel'] != setup_data['Wifi']['Channel']:
                print 'iwconfig %s channel %i 2>/dev/null || true' % (setup_data['Wifi']['Device'], setup_data['Wifi']['Channel'])
                os.system('iwconfig %s channel %i 2>/dev/null || true' % (setup_data['Wifi']['Device'], setup_data['Wifi']['Channel']))
        if check['opt'] != opt or check['opt_tx'] != opt_tx or check['dev'] != setup_data['Wifi']['Device'] or check['rate'] != setup_data['Wifi']['Rate']:
                cmd = "raspivid -t 0 -ih -n -pf medium %s -o - | /home/pi/wifibroadcast/tx %s > /tmp/tx.log 2>&1 &" % (opt, opt_tx)
                print cmd
                os.system(cmd)
        check['dev'] = setup_data['Wifi']['Device']
        check['channel'] = setup_data['Wifi']['Channel']
        check['rate'] = setup_data['Wifi']['Rate']
        check['opt'] = opt
        check['opt_tx'] = opt_tx


def runmenu(menu, parent):
        if parent is None:
                lastoption = "Exit"
        else:
                lastoption = "Return"
        optioncount = len(menu['options'])
        pos = 0
        active = 0

        if 'last' in menu:
                pos = menu['last']
        else:
                menu['last'] = 0

        ## check active value ##
        if parent != None:
                pkey = str(parent['title'])
                mkey = str(menu['title'])
                if pkey in setup_data and mkey in setup_data[pkey]:
                        for index in range(optioncount):
                                if 'value' in menu['options'][index] and setup_data[pkey][mkey] == menu['options'][index]['value']:
                                        pos = index
                                        active = index
                                        break
                                elif setup_data[pkey][mkey] == menu['options'][index]['title']:
                                        menu['options'][index]['value'] = menu['options'][index]['title']
                                        pos = index
                                        active = index
                                        break

        x = None
        while x != 5:
                if pos == optioncount:
                        menu['last'] = 0
                else:
                        menu['last'] = pos
                fg = 255
                bg = 0
                if setup_data['Display']['Invert']:
                        fg = 0
                        bg = 255
                disp_line_h = int(setup_data['Display']['Font']) + 1
                disp_line_n = disp.height / disp_line_h
                disp_line_nh = (disp_line_n - 1) / 2
                font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeMono.ttf", int(setup_data['Display']['Font']))
                draw.rectangle((0, 0,  disp.width, disp.height), outline=bg, fill=bg)
#                draw.text((0, 0), menu['title'],  font=font, fill=fg)

                ## display menu ##
                #os.system('clear')
                print "################################################"
                print "--" + menu['title'] + "--"
                y = 0
                for index in range(optioncount):
                        d = optioncount - pos
                        if d > disp_line_nh:
                                d = disp_line_nh
                        d = disp_line_nh - d
                        if index > pos - (disp_line_nh + 1) - d and y < disp_line_n * disp_line_h:
                                if menu['options'][index]['type'] == MENU or menu['options'][index]['type'] == BOOL:
                                        txt = "%s" % (menu['options'][index]['title'])
                                        pkey = str(menu['title'])
                                        mkey = str(menu['options'][index]['title'])
                                        if pkey in setup_data and mkey in setup_data[pkey]:
                                                txt += ": " + str(setup_data[pkey][mkey]);
                                        if menu['options'][index]['type'] == BOOL:
                                                txt += " <->"
                                        else:
                                                txt += " ->"
                                elif index == active:
                                        txt = "%s *" % (menu['options'][index]['title'])
                                else:
                                        txt = "%s" % (menu['options'][index]['title'])
                                if index == pos:
                                        draw.rectangle((0, y, disp.width - 1, y + disp_line_h - 1), outline=fg, fill=bg)
                                draw.text((2, y), txt, font=font, fill=fg)
                                y = y + disp_line_h
                                print txt

                if y < disp_line_n * disp_line_h:
                        txt = "%s <-" % (lastoption)
                        if pos == optioncount:
                                draw.rectangle((0, y, disp.width - 1, y + disp_line_h - 1), outline=fg, fill=bg)
                        draw.text((2, y), txt, font=font, fill=fg)
                        y = y + disp_line_h
                        print txt

                ## debug ##
                print ""
                print setup_data
                print ""
                print "################################################"

                if setup_data['Display']['Flip']:
                        disp.image(image.rotate(180))
                else:
                        disp.image(image)
                disp.display()

                ## read input ##
#               x = input("")
                while True: 
                        time.sleep(0.05)
                        if GPIO.input(7) == False:
                                if setup_data['Display']['Flip']:
                                        x = 2
                                else:
                                        x = 8
                                break
                        elif GPIO.input(17) == False:
                                if setup_data['Display']['Flip']:
                                        x = 8
                                else:
                                        x = 2
                                break
                        elif GPIO.input(18) == False:
                                x = 5 
                                break

                if x == 2:
                        if pos < optioncount:
                                pos += 1
                        else:
                                pos = 0
                elif x == 8:
                        if pos > 0:
                                pos += -1
                        else:
                                pos = optioncount
                elif x == 5:
                        if pos != optioncount and parent != None:
                                if menu['options'][pos]['type'] == OPTION:
                                        pkey = str(parent['title'])
                                        mkey = str(menu['title'])
                                        if not 'value' in menu['options'][pos]:
                                                menu['options'][pos]['value'] = menu['options'][pos]['title']
                                        setup_data[pkey][mkey] = menu['options'][pos]['value']
                                        if menu['options'][pos]['type'] == OPTION:
                                                restart_tx()
                                        x = 5
                                        pos = optioncount

        return pos


def processmenu(menu, parent=None):
        optioncount = len(menu['options'])
        exitmenu = False
        while not exitmenu:
                getin = runmenu(menu, parent)

                ## update ##
                wlan_update_channel_list()

                if getin == optioncount:
                        exitmenu = True
                elif menu['options'][getin]['type'] == MENU:
                        processmenu(menu['options'][getin], menu)
                elif menu['options'][getin]['type'] == COMMAND:
                        if 'reset' in menu['options'][getin] and menu['options'][getin]['reset'] == 1:
                                os.system('ifconfig %s down || true' % (setup_data['Wifi']['Device']))
                                os.system("killall -9 raspivid")
                                os.system("killall -9 tx")
                        print "execute..."
                        image = Image.open('logo.gif').resize((disp.width, disp.height), Image.ANTIALIAS).convert('1')
                        draw = ImageDraw.Draw(image)
                        draw.text((0, 0), "running command...", font=font, fill=255)
                        if setup_data['Display']['Flip']:
                                disp.image(image.rotate(180))
                        else:
                                disp.image(image)
                        disp.display()

                        tl = ["", "", "", "", "", "", "", "", "", "", "", "", ""]
                        proc = subprocess.Popen([menu['options'][getin]['cmd']], stdout=subprocess.PIPE, shell=True)
                        for line in iter(proc.stdout.readline,''):
                                font2 = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 8)
                                draw.rectangle((0, 0,  disp.width, disp.height), outline=0, fill=0)
                                tl[7] = tl[6];
                                tl[6] = tl[5];
                                tl[5] = tl[4];
                                tl[4] = tl[3];
                                tl[3] = tl[2];
                                tl[2] = tl[1];
                                tl[1] = tl[0];
                                tl[0] = line.rstrip()
                                print tl[0]
                                draw.text((0, 0), tl[7], font=font2, fill=255)
                                draw.text((0, 8), tl[6], font=font2, fill=255)
                                draw.text((0, 16), tl[5], font=font2, fill=255)
                                draw.text((0, 24), tl[4], font=font2, fill=255)
                                draw.text((0, 32), tl[3], font=font2, fill=255)
                                draw.text((0, 40), tl[2], font=font2, fill=255)
                                draw.text((0, 48), tl[1], font=font2, fill=255)
                                draw.text((0, 56), tl[0], font=font2, fill=255)
                                if setup_data['Display']['Flip']:
                                        disp.image(image.rotate(180))
                                else:
                                        disp.image(image)
                                disp.display()

                        if 'wait' in menu['options'][getin] and menu['options'][getin]['wait'] == 1:
                                font2 = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 8)
                                draw.rectangle((0, 0,  disp.width, disp.height), outline=0, fill=0)
                                tl[7] = tl[6];
                                tl[6] = tl[5];
                                tl[5] = tl[4];
                                tl[4] = tl[3];
                                tl[3] = tl[2];
                                tl[2] = tl[1];
                                tl[1] = tl[0];
                                tl[0] = "press ENTER..."
                                print tl[0]
                                draw.text((0, 0), tl[7], font=font2, fill=255)
                                draw.text((0, 8), tl[6], font=font2, fill=255)
                                draw.text((0, 16), tl[5], font=font2, fill=255)
                                draw.text((0, 24), tl[4], font=font2, fill=255)
                                draw.text((0, 32), tl[3], font=font2, fill=255)
                                draw.text((0, 40), tl[2], font=font2, fill=255)
                                draw.text((0, 48), tl[1], font=font2, fill=255)
                                draw.text((0, 56), tl[0], font=font2, fill=255)
                                if setup_data['Display']['Flip']:
                                        disp.image(image.rotate(180))
                                else:
                                        disp.image(image)
                                disp.display()
                                time.sleep(0.5)
                                while GPIO.input(18) != False:
                                        time.sleep(0.05)
                                time.sleep(0.1)
                        if 'cmd_post' in menu['options'][getin]:
                                os.system(menu['options'][getin]['cmd_post'])
                        if 'reset' in menu['options'][getin] and menu['options'][getin]['reset'] == 1:
                                print "reset"
                                check['dev'] = ""
                                check['channel'] = ""
                                check['rate'] = ""
                                check['opt'] = ""
                                check['opt_tx'] = ""
                                #os.system('ifconfig %s down || true' % (setup_data['Wifi']['Device']))
                                #os.system('rmmod rt2800usb 2>/dev/null || true')
                                #os.system('modprobe rt2800usb 2>/dev/null || true')
                                restart_tx()
                elif menu['options'][getin]['type'] == BOOL:
                        pkey = str(menu['title'])
                        mkey = str(menu['options'][getin]['title'])
                        setup_data[pkey][mkey] = 1 - setup_data[pkey][mkey]
                        if menu['options'][getin]['type'] == BOOL:
                                restart_tx()
                elif menu['options'][getin]['type'] == EXITMENU:
                        exitmenu = True

                ## write setup ##
                f = open('setup.inc', 'w')
                simplejson.dump(setup_data, f)
                f.close()


## read setup ##
setup_data = {}
if os.path.isfile("setup.inc"):
        f = open('setup.inc', 'r')
        setup_data = simplejson.load(f)
        f.close()

## update setup_data ##
for key in setup_data_default:
        if not key in setup_data:
                setup_data[key] = {}
        for key2 in setup_data_default[key]:
                if not key2 in setup_data[key]:
                        setup_data[key][key2] = setup_data_default[key][key2] 


## init display ##
disp = Adafruit_SSD1306.SSD1306_128_64(rst=24)
disp_line_h = int(setup_data['Display']['Font']) + 1
disp_line_n = disp.height / disp_line_h
disp_line_nh = (disp_line_n - 1) / 2
font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeMono.ttf", int(setup_data['Display']['Font']))
disp.begin()
disp.clear()
image = Image.open('logo.gif').resize((disp.width, disp.height), Image.ANTIALIAS).convert('1')
draw = ImageDraw.Draw(image)
draw.text((0, 0), "startup...",  font=font, fill=255)
if setup_data['Display']['Flip']:
        disp.image(image.rotate(180))
else:
        disp.image(image)
disp.display()

## init wifi ##
os.system('killall raspivid 2>/dev/null || true')
os.system('killall tx 2>/dev/null || true')
os.system('killall /usr/sbin/ifplugd 2>/dev/null || true')
os.system('killall dhcpcd 2>/dev/null || true')
os.system('killall dhclient 2>/dev/null || true')
os.system('killall wpa_supplicant 2>/dev/null || true')
#os.system('ifconfig %s down || true' % (setup_data['Wifi']['Device']))
#os.system('rmmod rt2800usb 2>/dev/null || true')
#os.system('modprobe rt2800usb 2>/dev/null || true')

## start vid+tx ##
restart_tx()

## update wifi infos ##
serial_update_device_list()
wlan_update_device_list()
wlan_update_channel_list()

## start main-menu ##
processmenu(menu_data)


