#!/bin/sh
#
#


echo "cleaning map directory"
rm -rfv /usr/share/gl-gcs/MAPS/osm_[a-z]*
rm -rfv /usr/share/gl-gcs/MAPS/*.tmp
sh clean-badmaps.sh

echo "From local to server"
rsync -avr /usr/share/gl-gcs/MAPS/ root@rcos.eu:/srv/www/www.multixmedia/htdocs/MAPS/


echo "From server to local"
rsync -avr root@rcos.eu:/srv/www/www.multixmedia/htdocs/MAPS/ /usr/share/gl-gcs/MAPS/


