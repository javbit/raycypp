CXX = `which clang++`
CXXFLAGS = -c -Weverything
CXXFLAGS += `libpng-config --cflags`

LD = `which clang++`
LDLIBS = `libpng-config --ldflags`

EXE = raycypp
SRCDIR = src

$(EXE): main.o
	$(LD) $^ $(LDFLAGS) $(LDLIBS) -o $@

main.o: $(SRCDIR)/main.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	$(RM) $(EXE) *.png *.o
