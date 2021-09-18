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
SAD_HELPER_DIR ?= ./src
AFW_DIR=../audioframework
INC_DIR=$(AFW_DIR)/include
LIB_DIR=$(AFW_DIR)/lib
LIB_SAD_HELPER_DIR=./lib
OBJ_DIR=./out

# --- source code config --------------
SAD_HELPER_SRCS = $(wildcard $(SAD_HELPER_DIR)/*.cpp)

# --- the object files config --------------
SAD_HELPER_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SAD_HELPER_SRCS:.cpp=.o)))

# --- Build for sink example(shared) ------------
UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	SAD_HELPER_SO_TARGET = $(LIB_SAD_HELPER_DIR)/libhdmisadhelper.so
	AFW_SO_TARGET = $(LIB_DIR)/libafw.so
endif
ifeq ($(UNAME),Darwin)
	SAD_HELPER_SO_TARGET = $(LIB_SAD_HELPER_DIR)/libhdmisadhelper.dylib
	AFW_SO_TARGET = $(LIB_DIR)/libafw.dylib
endif
SAD_HELPER_DEPS = $(SAD_HELPER_OBJS:.o=.d)

default: $(SAD_HELPER_SO_TARGET)
.PHONY: default

$(SAD_HELPER_SO_TARGET): $(SAD_HELPER_OBJS)
	@[ -d $(LIB_DIR) ] || mkdir -p $(LIB_DIR)
	@[ -d $(LIB_SAD_HELPER_DIR) ] || mkdir -p $(LIB_SAD_HELPER_DIR)
	$(CXX) $(LDFLAGS) $(SHARED_CXXFLAGS) $(SAD_HELPER_OBJS) -o $@ $(LDLIBS) $(AFW_SO_TARGET)

$(SAD_HELPER_OBJS): $(SAD_HELPER_SRCS)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -I $(INC_DIR) -c $(SAD_HELPER_DIR)/$(notdir $(@:.o=.cpp)) -o $@

-include $(SAD_HELPER_DEPS)

# --- clean up ------------------------
clean:
	rm -f $(SAD_HELPER_OBJS) $(SAD_HELPER_SO_TARGET)
