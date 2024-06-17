UNAME_S != uname -s
UNAME_M != uname -m

NAME != cat main.c | grep "const char \*sofname" | awk '{print $$5}' | \
	sed "s/\"//g" | sed "s/;//"
VERSION != cat main.c | grep "const char \*version" | awk '{print $$5}' | \
	sed "s/\"//g" | sed "s/;//"
PREFIX = /usr/local
.if ${UNAME_S} == "Linux"
PREFIX = /usr
.endif

MANPREFIX = ${PREFIX}/share/man

.if ${UNAME_S} == "OpenBSD"
MANPREFIX = ${PREFIX}/man
.endif

CC = cc
FILES = main.c src/*.c
CFLAGS = -Wall -Wextra -O3 -I${PREFIX}/include -L${PREFIX}/lib
.if ${UNAME_S} == "NetBSD"
CFLAGS += -I/usr/pkg/include -L/usr/pkg/lib -I/usr/include -L/usr/lib
.endif
LDFLAGS = 

all:
	${CC} ${CFLAGS} -o ${NAME} ${FILES} ${LDFLAGS}
	strip ${NAME}

clean:
	rm -f ${NAME}

dist: clean
	mkdir -p dist
	mkdir -p ${NAME}-${VERSION}
	cp -R LICENSE.txt Makefile README.md CHANGELOG.md \
		${NAME}-completion.zsh ${NAME}.1 main.c src ${NAME}-${VERSION}
	tar zcfv dist/${NAME}-${VERSION}.tar.gz ${NAME}-${VERSION}
	rm -rf ${NAME}-${VERSION}

depend:
	${DEPS}

release-openbsd:
	mkdir -p release
	${CC} ${CFLAGS} -o release/${NAME}-${VERSION}-openbsd-${UNAME_M} ${FILES} \
		-static ${LDFLAGS} -lc
	strip release/${NAME}-${VERSION}-openbsd-${UNAME_M}

release-freebsd:
	mkdir -p release
	${CC} ${CFLAGS} -o release/${NAME}-${VERSION}-freebsd-${UNAME_M} ${FILES} \
		-static ${LDFLAGS} -lc
	strip release/${NAME}-${VERSION}-freebsd-${UNAME_M}

release-netbsd:
	mkdir -p release
	export LD_LIBRARY_PATH=/usr/pkg/lib:/usr/local/lib:$LD_LIBRARY_PATH
	${CC} ${CFLAGS} -o release/${NAME}-${VERSION}-netbsd-${UNAME_M} ${FILES} \
		-static ${LDFLAGS} -lc
	strip release/${NAME}-${VERSION}-netbsd-${UNAME_M}

release-linux:
	mkdir -p release
	${CC} ${CFLAGS} -o release/${NAME}-${VERSION}-linux-${UNAME_M} ${FILES} \
		-static ${LDFLAGS} -lc
	strip release/${NAME}-${VERSION}-linux-${UNAME_M}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${NAME} ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/${NAME}
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < ${NAME}.1 > ${DESTDIR}${MANPREFIX}/man1/${NAME}.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/${NAME}.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/${NAME}

.PHONY: all clean dist install uninstall
