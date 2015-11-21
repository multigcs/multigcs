#!/bun/sh
#
#


docker build -t multigcs docker/ubuntu-15.04/

docker run --rm -t -i -v `pwd`:/usr/src/multigcs multigcs


