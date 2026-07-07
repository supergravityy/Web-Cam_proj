APP_NAME ?= webcam_app

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
TARGET := $(BUILD_DIR)/$(APP_NAME)

CC ?= gcc
CXX ?= g++
CXXSTD ?= c++17

CPP_SOURCES := $(shell find code -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' \) 2>/dev/null)
C_SOURCES := $(shell find code -type f -name '*.c' 2>/dev/null)
OBJECTS := $(patsubst %,$(OBJ_DIR)/%.o,$(CPP_SOURCES) $(C_SOURCES))
DEPS := $(OBJECTS:.o=.d)

PACKAGE_INCLUDE_DIRS := $(shell find packages -type d -name include 2>/dev/null)
PACKAGE_LIB_DIRS := $(shell find packages -type d \( -name lib -o -name lib64 \) 2>/dev/null)
PACKAGE_PKGCONFIG_DIRS := $(shell find packages -type d -name pkgconfig 2>/dev/null)
PACKAGE_LIBS := $(wildcard packages/*/lib/lib*.so packages/*/lib/*.a packages/*/lib64/lib*.so packages/*/lib64/*.a)

PACKAGE_INCLUDE_FLAGS := $(addprefix -I,$(PACKAGE_INCLUDE_DIRS))
PACKAGE_LIB_FLAGS := $(addprefix -L,$(PACKAGE_LIB_DIRS))
COMMA := ,
PACKAGE_RPATH_FLAGS := $(foreach dir,$(PACKAGE_LIB_DIRS),-Wl$(COMMA)-rpath=$(abspath $(dir)))

PKG_CONFIG_PATH_VALUE := $(shell IFS=:; echo "$(PACKAGE_PKGCONFIG_DIRS)")
OPENCV_CFLAGS := $(shell PKG_CONFIG_PATH="$(PKG_CONFIG_PATH_VALUE):$$PKG_CONFIG_PATH" pkg-config --cflags opencv4 2>/dev/null)
OPENCV_LIBS := $(shell PKG_CONFIG_PATH="$(PKG_CONFIG_PATH_VALUE):$$PKG_CONFIG_PATH" pkg-config --libs opencv4 2>/dev/null)

CPPFLAGS += -Icode/Inc $(PACKAGE_INCLUDE_FLAGS) $(OPENCV_CFLAGS)
CFLAGS ?= -Wall -Wextra -g -O0
CXXFLAGS ?= -Wall -Wextra -g -O0 -std=$(CXXSTD)
LDFLAGS += $(PACKAGE_LIB_FLAGS) $(PACKAGE_RPATH_FLAGS)
LDLIBS += $(OPENCV_LIBS) $(PACKAGE_LIBS)

.PHONY: all clean run debug print-config

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR)/%.cc.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR)/%.cxx.o: %.cxx
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

run: all
	./$(TARGET)

debug: all
	gdb ./$(TARGET)

clean:
	$(RM) -r $(OBJ_DIR) $(TARGET)

print-config:
	@echo "TARGET=$(TARGET)"
	@echo "CPP_SOURCES=$(CPP_SOURCES)"
	@echo "C_SOURCES=$(C_SOURCES)"
	@echo "CPPFLAGS=$(CPPFLAGS)"
	@echo "CXXFLAGS=$(CXXFLAGS)"
	@echo "LDFLAGS=$(LDFLAGS)"
	@echo "LDLIBS=$(LDLIBS)"

-include $(DEPS)
