# CC=g++
CC=C:/mingw/bin/g++
# CC=C:/dev/llvm/bin/clang++

CFLAGS=-Wall -Wpedantic
CFLAGS+= -std=c++2a -m32

include_dir=./include

link_dir=./lib

LFLAGS=-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

main.exe: main.cpp include/*
	${CC} ${CFLAGS} -I ${include_dir} -L ${link_dir} -o $@ main.cpp ${LFLAGS}

clean:
	del *.exe
	del *.o