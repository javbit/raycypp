EXE = raycypp
SRCDIR = src
GEOMDIR = $(SRCDIR)/geom
UTILDIR = $(SRCDIR)/util

CXX = `which clang++`
CXXFLAGS = -c -Weverything
CXXFLAGS += `libpng-config --cflags`

LD = `which clang++`
LDLIBS = `libpng-config --ldflags`

$(EXE): main.o ray.o sphere.o scene.o triangle.o quadrangle.o perscam.o orthcam.o
	$(LD) $^ $(LDFLAGS) $(LDLIBS) -o $@

main.o: $(SRCDIR)/main.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

ray.o: $(GEOMDIR)/ray.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

sphere.o: $(GEOMDIR)/sphere.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

triangle.o: $(GEOMDIR)/triangle.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

quadrangle.o: $(GEOMDIR)/quadrangle.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

scene.o: $(GEOMDIR)/scene.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

perscam.o: $(UTILDIR)/perscam.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

orthcam.o: $(UTILDIR)/orthcam.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	$(RM) $(EXE) *.png *.o
