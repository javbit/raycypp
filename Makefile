EXE = raycypp
SRCDIR = src
GEOMDIR = $(SRCDIR)/geom

CXX = `which clang++`
CXXFLAGS = -c -Weverything
CXXFLAGS += `libpng-config --cflags`

LD = `which clang++`
LDLIBS = `libpng-config --ldflags`

$(EXE): main.o ray.o
	$(LD) $^ $(LDFLAGS) $(LDLIBS) -o $@

main.o: $(SRCDIR)/main.cpp $(SRCDIR)/main.hpp
	$(CXX) $^ $(CXXFLAGS) -o $@

ray.o: $(GEOMDIR)/ray.cpp $(GEOMDIR)/ray.hpp
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	$(RM) $(EXE) *.png *.o
