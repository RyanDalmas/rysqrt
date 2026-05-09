CXX := g++
BUILD_DIR := build
BUILD_STAMP := $(BUILD_DIR)/.dir
CPPFLAGS := -Isrc/lib
CXXFLAGS := -Ofast -march=native -Wall -Wextra -std=c++17

BENCH_BIN := $(BUILD_DIR)/benchmark

.PHONY: all build benchmark fast acc clean

all: build

build: $(BENCH_BIN)

$(BUILD_STAMP):
	mkdir -p $(BUILD_DIR)
	touch $@

$(BENCH_BIN): src/benchmark.cpp src/lib/rysqrt.h | $(BUILD_STAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

benchmark: $(BENCH_BIN)
	./$(BENCH_BIN)

bench: benchmark

clean:
	rm -rf $(BUILD_DIR)
