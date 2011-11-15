CPPFLAGS=-I.. -I../map -g
LDFLAGS=

test: path_test
	path_test

path_test:LDLIBS=../sexp/*.o \
	../AI.o      ../game.o     ../MapCPP.o    ../Player.o  ../Tile.o \
	../BaseAI.o  ../getters.o  ../Mappable.o  ../rrbase.o  ../util.o \
	../Base.o    ../network.o   ../shell.o   ../Virus.o
path_test: path.o

copy:path.o
	cp path.cpp path.hpp ..
	$(MAKE) -C ..

path.o: path.hpp


pq:pq_test
	pq_test

pq_test:
