EXE = raycypp
SRCDIR = src
GEOMDIR = $(SRCDIR)/geom

CXX = `which clang++`
CXXFLAGS = -c -Weverything
CXXFLAGS += `libpng-config --cflags`

LD = `which clang++`
LDLIBS = `libpng-config --ldflags`

$(EXE): main.o ray.o sphere.o scene.o
	$(LD) $^ $(LDFLAGS) $(LDLIBS) -o $@

main.o: $(SRCDIR)/main.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

ray.o: $(GEOMDIR)/ray.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

sphere.o: $(GEOMDIR)/sphere.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

scene.o: $(GEOMDIR)/scene.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	$(RM) $(EXE) *.png *.o
