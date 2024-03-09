CXX=g++-13
CXXFLAGS=-g -std=c++20 -DLOCAL -Wall -O2 -I../../ac-library -I. -D_GLIBGCC_DEBUG

VPATH=src
build/%: %.cpp
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@