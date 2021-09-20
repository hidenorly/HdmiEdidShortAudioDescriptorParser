# compiler env.
UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	CXX=ccache clang++
	LDLIBS=-ldl -lasound
	CXXFLAGS=-std=c++2a -MMD -MP -Wall -fPIC
	SHARED_CXXFLAGS= -fPIC -shared
endif
ifeq ($(UNAME),Darwin)
	CXX=ccache clang++
	LDLIBS=-stdlib=libc++
	CXXFLAGS=-std=c++2a -MMD -MP -Wall
#	SHARED_CXXFLAGS= -flat_namespace -dynamiclib
	SHARED_CXXFLAGS=-dynamiclib
endif

LDFLAGS=-pthread

# project config
AFW_DIR=../audioframework
AFW_INC_DIR=$(AFW_DIR)/include
AFW_LIB_DIR=$(AFW_DIR)/lib

SAD_SRC_DIR ?= ./src
SAD_LIB_DIR=./lib
BIN_DIR=./bin
OBJ_DIR=./out
TEST_DIR=./test

# --- source code config --------------
SAD_HELPER_SRCS = $(wildcard $(SAD_SRC_DIR)/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)

# --- the object files config --------------
SAD_HELPER_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SAD_HELPER_SRCS:.cpp=.o)))
TEST_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRCS:.cpp=.o)))

# --- Build for sink example(shared) ------------
UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	SAD_SO_TARGET = $(SAD_LIB_DIR)/libhdmisadhelper.so
	AFW_SO_TARGET = $(AFW_LIB_DIR)/libafw.so
endif
ifeq ($(UNAME),Darwin)
	SAD_SO_TARGET = $(SAD_LIB_DIR)/libhdmisadhelper.dylib
	AFW_SO_TARGET = $(AFW_LIB_DIR)/libafw.dylib
endif

SAD_HELPER_DEPS = $(SAD_HELPER_OBJS:.o=.d)

default: $(SAD_SO_TARGET)
.PHONY: default

$(SAD_SO_TARGET): $(SAD_HELPER_OBJS)
	@[ -d $(AFW_LIB_DIR) ] || mkdir -p $(AFW_LIB_DIR)
	@[ -d $(SAD_LIB_DIR) ] || mkdir -p $(SAD_LIB_DIR)
	$(CXX) $(LDFLAGS) $(SHARED_CXXFLAGS) $(SAD_HELPER_OBJS) -o $@ $(LDLIBS) $(AFW_SO_TARGET)

$(SAD_HELPER_OBJS): $(SAD_HELPER_SRCS)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I $(AFW_INC_DIR) -c $(SAD_SRC_DIR)/$(notdir $(@:.o=.cpp)) -o $@

-include $(SAD_HELPER_DEPS)

# --- Build for test cases w/libafw.so ---
TEST_TARGET = $(BIN_DIR)/sadParser
TEST_LDLIBS = $(LDLIBS) -L$(AFW_LIB_DIR)
TEST_LIBS = $(AFW_SO_TARGET) $(SAD_SO_TARGET)

test: $(TEST_TARGET)
.PHONY: test

$(TEST_TARGET): $(TEST_OBJS)
	@[ -d $(BIN_DIR) ] || mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) $(TEST_LDLIBS) $(TEST_OBJS) $(TEST_LIBS) -o $@

$(TEST_OBJS): $(TEST_SRCS)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I $(AFW_INC_DIR) -I $(SAD_SRC_DIR) -c $(TEST_DIR)/$(notdir $(@:.o=.cpp)) -o $@


# --- clean up ------------------------
clean:
	rm -f $(SAD_HELPER_OBJS) $(SAD_SO_TARGET)
