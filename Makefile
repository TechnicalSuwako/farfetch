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
CFLAGS = -Wall -Wextra -O3

LDFLAGS = -static -lc
.if ${UNAME_S} == "Haiku" || ${UNAME_S} == "Darwin" || ${UNAME_S} == "SunOS"\
	|| ${UNAME_S} == "Minix"
LDFLAGS = -lc
.endif

all:
	${CC} ${CFLAGS} -o ${NAME} ${FILES} ${LDFLAGS}
	strip ${NAME}

clean:
	rm -rf ${NAME}

dist:
	mkdir -p ${NAME}-${VERSION} release/src
	cp -R LICENSE.txt Makefile README.md CHANGELOG.md\
		${NAME}.conf ${NAME}.1 ${NAME}-en.1 ${NAME}.conf.5 ${NAME}.conf-en.5\
		main.c src ${NAME}-${VERSION}
	tar zcfv release/src/${NAME}-${VERSION}.tar.gz ${NAME}-${VERSION}
	rm -rf ${NAME}-${VERSION}

man:
	mkdir -p release/man/${VERSION}
	sed "s/VERSION/${VERSION}/g" < ${NAME}.1 > release/man/${VERSION}/${NAME}.1
	sed "s/VERSION/${VERSION}/g" < ${NAME}-en.1 > release/man/${VERSION}/${NAME}-en.1
	sed "s/VERSION/${VERSION}/g" < ${NAME}.conf.5 >\
		release/man/${VERSION}/${NAME}.conf.5
	sed "s/VERSION/${VERSION}/g" < ${NAME}.conf-en.5 >\
		release/man/${VERSION}/${NAME}.conf-en.5

release:
	mkdir -p release/bin/${VERSION}/${OS}/${UNAME_M}
	${CC} ${CFLAGS} -o release/bin/${VERSION}/${OS}/${UNAME_M}/${NAME} ${FILES}\
		-static ${LDFLAGS}
	strip release/bin/${VERSION}/${OS}/${UNAME_M}/${NAME}

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin ${DESTDIR}${MANPREFIX}/man1\
		${DESTDIR}${MANPREFIX}/man5
	cp -rf ${NAME} ${DESTDIR}${PREFIX}/bin
	cp -rf ${NAME}.conf ${DESTDIR}${CNFPREFIX}
	chmod 755 ${DESTDIR}${PREFIX}/bin/${NAME}
	sed "s/VERSION/${VERSION}/g" < ${NAME}.1 > ${DESTDIR}${MANPREFIX}/man1/${NAME}.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/${NAME}.1
	sed "s/VERSION/${VERSION}/g" < ${NAME}-en.1 >\
		${DESTDIR}${MANPREFIX}/man1/${NAME}-en.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/${NAME}-en.1
	sed "s/VERSION/${VERSION}/g" < ${NAME}.conf.5 >\
		${DESTDIR}${MANPREFIX}/man5/${NAME}.conf.5
	chmod 644 ${DESTDIR}${MANPREFIX}/man5/${NAME}.conf.5
	sed "s/VERSION/${VERSION}/g" < ${NAME}.conf-en.5 >\
		${DESTDIR}${MANPREFIX}/man5/${NAME}.conf-en.5
	chmod 644 ${DESTDIR}${MANPREFIX}/man5/${NAME}.conf-en.5

uninstall:
	rm -rf ${DESTDIR}${PREFIX}/bin/${NAME}
	rm -rf ${DESTDIR}${MANPREFIX}/man1/${NAME}.1
	rm -rf ${DESTDIR}${MANPREFIX}/man1/${NAME}-en.1
	rm -rf ${DESTDIR}${MANPREFIX}/man5/${NAME}.conf.5
	rm -rf ${DESTDIR}${MANPREFIX}/man5/${NAME}-en.conf.5

.PHONY: all clean dist man release install uninstall
