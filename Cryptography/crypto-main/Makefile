CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Iinclude
CXXFLAGS = -Wall -Wextra -Iinclude

TARGET = program
SRC = main.cpp src/CSR.c src/CSK.c src/VGN.c src/DFH.c
HELPERS = helpers/file.cpp helpers/utils.cpp helpers/colorise.cpp helpers/c_utils.c helpers/randonm.c
LIBS = lib/math_x.c lib/table_log.c lib/ext_gcd.c
TESTS = test/test_math.c

# Объединяем все исходные файлы
ALL_SRCS = $(SRC) $(HELPERS) $(LIBS) $(TESTS)

.PHONY: all clean run

all: $(TARGET) dist/crypto

$(TARGET): $(ALL_SRCS)
	$(CXX) $(CXXFLAGS) $(ALL_SRCS) -o $(TARGET)

dist/crypto: $(TARGET)
	@mkdir -p dist
	cp $(TARGET) $@

clean:
	rm -f $(TARGET) dist/crypto

run: all
	./$(TARGET)
