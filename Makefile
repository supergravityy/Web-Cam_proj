BUILD_DIR ?= build
BUILD_TYPE ?= Debug
CMAKE ?= cmake
CTEST ?= ctest

.PHONY: all configure build test run-client run-server clean

all: build

configure:
	$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build: configure
	$(CMAKE) --build $(BUILD_DIR)

test: build
	$(CTEST) --test-dir $(BUILD_DIR) --output-on-failure

run-client: build
	./$(BUILD_DIR)/bin/camera_client

run-server: build
	./$(BUILD_DIR)/bin/camera_server

clean:
	$(CMAKE) -E rm -rf $(BUILD_DIR)
