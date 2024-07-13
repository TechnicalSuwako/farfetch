UNAME_S != uname -s
UNAME_M != uname -m
OS = ${UNAME_S}

.if ${UNAME_S} == "OpenBSD"
OS = openbsd
.elif ${UNAME_S} == "NetBSD"
OS = netbsd
.elif ${UNAME_S} == "FreeBSD"
OS = freebsd
.elif ${UNAME_S} == "Linux"
OS = linux
.endif

.if ${UNAME_M} == "x86_64"
UNAME_M = amd64
.endif

NAME != cat main.c | grep "const char \*sofname" | awk '{print $$5}' |\
	sed "s/\"//g" | sed "s/;//"
VERSION != cat main.c | grep "const char \*version" | awk '{print $$5}' |\
	sed "s/\"//g" | sed "s/;//"

PREFIX = /usr/local
.if ${UNAME_S} == "Linux"
PREFIX = /usr
.elif ${UNAME_S} == "Haiku"
PREFIX = /boot/home/config/non-packaged
.endif

MANPREFIX = ${PREFIX}/share/man
.if ${UNAME_S} == "OpenBSD"
MANPREFIX = ${PREFIX}/man
.elif ${UNAME_S} == "Haiku"
MANPREFIX = ${PREFIX}/documentation/man
.endif

CNFPREFIX = /etc
.if ${UNAME_S} == "FreeBSD" || ${UNAME_S} == "NetBSD" || ${UNAME_S} == "Dragonfly"
CNFPREFIX = ${PREFIX}/etc
.elif ${UNAME_S} == "Haiku"
CNFPREFIX = /boot/home/config/settings
.endif

CC = cc
FILES = main.c src/*.c src/logo/*.c
CFLAGS = -Wall -Wextra -O3 -I${PREFIX}/include -L${PREFIX}/lib
.if ${UNAME_S} == "NetBSD"
CFLAGS += -I/usr/pkg/include -L/usr/pkg/lib -I/usr/include -L/usr/lib
.endif
LDFLAGS = -lc

all:
	${CC} ${CFLAGS} -o ${NAME} ${FILES} ${LDFLAGS}
	strip ${NAME}

clean:
	rm -f ${NAME}

dist:
	mkdir -p ${NAME}-${VERSION} release/src
	cp -R LICENSE.txt Makefile README.md CHANGELOG.md\
		${NAME}.conf ${NAME}.1 main.c src ${NAME}-${VERSION}
	tar zcfv release/src/${NAME}-${VERSION}.tar.gz ${NAME}-${VERSION}
	rm -rf ${NAME}-${VERSION}

man:
	mkdir -p release/man
	sed "s/VERSION/${VERSION}/g" < ${NAME}.1 > release/man/${NAME}-${VERSION}.1
	sed "s/VERSION/${VERSION}/g" < ${NAME}.conf.5 > release/man/${NAME}.conf-${VERSION}.5

depend:
	${DEPS}

release:
	mkdir -p release/bin
	${CC} ${CFLAGS} -o release/bin/${NAME}-${VERSION}-${OS}-${UNAME_M} ${FILES}\
		-static ${LDFLAGS}
	strip release/bin/${NAME}-${VERSION}-${OS}-${UNAME_M}

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${NAME} ${DESTDIR}${PREFIX}/bin
	cp -f ${NAME}.conf ${DESTDIR}${CNFPREFIX}/examples
	chmod 755 ${DESTDIR}${PREFIX}/bin/${NAME}
	mkdir -p ${DESTDIR}${MANPREFIX}/man1 ${DESTDIR}${MANPREFIX}/man5
	sed "s/VERSION/${VERSION}/g" < ${NAME}.1 > ${DESTDIR}${MANPREFIX}/man1/${NAME}.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/${NAME}.1
	sed "s/VERSION/${VERSION}/g" < ${NAME}.conf.5 >\
		${DESTDIR}${MANPREFIX}/man5/${NAME}.conf.5
	chmod 644 ${DESTDIR}${MANPREFIX}/man5/${NAME}.conf.5

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/${NAME}

.PHONY: all clean dist man release install uninstall
