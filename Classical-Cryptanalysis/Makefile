SHEDSKIN_LIBDIR=/usr/lib/python2.7/site-packages/shedskin/lib
CC=g++
CCFLAGS=-O2 -march=native -Wno-deprecated $(CPPFLAGS) -I. -I${SHEDSKIN_LIBDIR}
LFLAGS=-lgc -lpcre $(LDFLAGS)

CPPFILES=classicalciphers.cpp \
	${SHEDSKIN_LIBDIR}/time.cpp \
	${SHEDSKIN_LIBDIR}/string.cpp \
	${SHEDSKIN_LIBDIR}/re.cpp \
	${SHEDSKIN_LIBDIR}/random.cpp \
	${SHEDSKIN_LIBDIR}/math.cpp \
	${SHEDSKIN_LIBDIR}/builtin.cpp

HPPFILES=classicalciphers.hpp \
	${SHEDSKIN_LIBDIR}/time.hpp \
	${SHEDSKIN_LIBDIR}/string.hpp \
	${SHEDSKIN_LIBDIR}/re.hpp \
	${SHEDSKIN_LIBDIR}/random.hpp \
	${SHEDSKIN_LIBDIR}/math.hpp \
	${SHEDSKIN_LIBDIR}/builtin.hpp

all:	classicalciphers

classicalciphers:	$(CPPFILES) $(HPPFILES)
	$(CC)  $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o classicalciphers

classicalciphers_prof:	$(CPPFILES) $(HPPFILES)
	$(CC) -pg -ggdb $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o classicalciphers_prof

classicalciphers_debug:	$(CPPFILES) $(HPPFILES)
	$(CC) -g -ggdb $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o classicalciphers_debug

clean:
	rm -f classicalciphers classicalciphers_prof classicalciphers_debug

.PHONY: all clean

