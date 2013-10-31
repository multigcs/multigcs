

all:
	cc -Wall -fPIC -g -I./ -c -o dpf.o dpf.c
	cc -Wall -fPIC -g -I./ -c -o dpflib.o dpflib.c
	cc -Wall -fPIC -g -I./ -c -o rawusb.o rawusb.c
	cc -o dpf dpf.o dpflib.o rawusb.o -lusb

clean:
	rm -rf *.o


