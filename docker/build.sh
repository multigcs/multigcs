#!/bun/sh
#
#


if ! test -e Makefile
then
	echo "no Makefile found, please link one file" >&2
	echo "Example:" >&2
	echo "" >&2
	echo "	ln -sf Makefile.gl-sdl Makefile" >&2
	echo "" >&2
fi

docker build -t multigcs docker/ubuntu-15.04/
docker run --rm -t -i -v `pwd`:/usr/src/multigcs multigcs


