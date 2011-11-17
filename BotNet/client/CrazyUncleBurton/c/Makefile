sources = $(wildcard *.cpp)
headers = $(wildcard *.h)
objects = $(sources:%.cpp=%.o)
deps = $(sources:%.cpp=%.d)
CFLAGS += -g -D_DEBUG_OFFICER
CXXFLAGS += -g

#Uncomment this line  to get a boatload of debug output.
#CPPFLAGS = -DSHOW_NETWORK
#override CPPFLAGS += -DSHOW_WARNINGS

override CPPFLAGS += -Isexp

all: client

submit: client
	@echo "$(shell cd ..;sh submit.sh c)"

.PHONY: clean all subdirs

libclient_%.o: override CXXFLAGS += -fPIC
libclient_%.o: %.cpp *$(headers)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(objects) client libclient_network.o libclient_game.o libclient_getters.o libclient_util.o libclient.so
	$(MAKE) -C sexp clean

client:LDLIBS+=-lm
client: $(objects) sexp/sexp.a
	$(CXX) $(LDFLAGS) $(LOADLIBES) $(LDLIBS) $^ -g -o client

libclient.so: libclient_network.o libclient_game.o libclient_getters.o libclient_util.o sexp/libclient_sexp.a
	$(CXX) -shared -Wl,-soname,libclient.so $(LDFLAGS) $(LOADLIBES) $(LDLIBS) $^ -o libclient.so

sexp/sexp.a sexp/libclient_sexp.a:
	$(MAKE) -C $(dir $@) $(notdir $@)

-include $(deps)

AI.o:CPPFLAGS+=-D_DEBUG_OFFICER
AI.o: Officer.o RandomOfficer.o

Officer.o:CPPFLAGS+=-D_DEBUG_OFFICER

RandomOfficer.o:CPPFLAGS+=-D_DEBUG_OFFICER

LemmingOfficer.o:CPPFLAGS+=-D_DEBUG_OFFICER

ofc:
	$(MAKE) -C officers copy