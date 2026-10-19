CC = gcc
CXX = g++
AR = ar

CPPFLAGS = -Iinclude
CFLAGS = -Wall -Wextra -std=c11
CXXFLAGS = -Wall -Wextra -std=c++17
DEPFLAGS = -MMD -MP
LDLIBS = -lm

PROGRAM = program
DIST_PROGRAM = dist/crypto
DISCRETE_LOG = discrete_log

EXP_MOD_LIBRARY = lib/libexpmod.a
INV_MOD_LIBRARY = lib/libinvmod.a
LOG_DIS_LIBRARY = lib/liblogdis.a
LIBRARIES = $(LOG_DIS_LIBRARY) $(INV_MOD_LIBRARY) $(EXP_MOD_LIBRARY)

PROGRAM_OBJECTS = \
	build/main.o \
	build/src/CSR.o \
	build/src/CSK.o \
	build/src/VGN.o \
	build/src/DFH.o \
	build/helpers/file.o \
	build/helpers/randonm.o \
	build/test/test_math.o

LIBRARY_OBJECTS = \
	build/lib/math_x.o \
	build/lib/ext_gcd.o \
	build/lib/table_log.o
DEPENDENCY_FILES = $(PROGRAM_OBJECTS:.o=.d) $(LIBRARY_OBJECTS:.o=.d)

.PHONY: all clean run demo libraries

all: $(PROGRAM) $(DIST_PROGRAM) $(DISCRETE_LOG) libraries

libraries: $(LIBRARIES)

$(PROGRAM): $(PROGRAM_OBJECTS) $(LIBRARIES)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

$(DIST_PROGRAM): $(PROGRAM)
	mkdir -p $(@D)
	cp $< $@

$(DISCRETE_LOG): src/discrete_log.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

$(EXP_MOD_LIBRARY): build/lib/math_x.o
	mkdir -p $(@D)
	$(AR) rcs $@ $<

$(INV_MOD_LIBRARY): build/lib/ext_gcd.o
	mkdir -p $(@D)
	$(AR) rcs $@ $<

$(LOG_DIS_LIBRARY): build/lib/table_log.o
	mkdir -p $(@D)
	$(AR) rcs $@ $<

build/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

build/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEPENDENCY_FILES)

clean:
	rm -rf build
	rm -f $(PROGRAM) $(DIST_PROGRAM) $(DISCRETE_LOG) $(LIBRARIES)

run: $(PROGRAM)
	./$(PROGRAM)

demo: all
	sh demo.sh
