CPPFLAGS=-g -I.. -D_DEBUG_OFFICER

all: Officer.o RandomOfficer.o

Officer.o: strutil.h

RandomOfficer.o: RandomOfficer.h Officer.h

LemmingOfficer.o: officerutil.h Officer.h

copy: RandomOfficer.o Officer.o
	cp RandomOfficer.cpp RandomOfficer.h Officer.cpp Officer.h strutil.h officerutil.h LemmingOfficer.cpp LemmingOfficer.h ..
	$(MAKE) -C ..

ZoneChain.o: Chain.h ZoneChain.h

Chain.o: Chain.h

clean:
	rm -f *.o

randtest:
	randtest