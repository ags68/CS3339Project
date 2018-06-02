CXX = g++
LD = g++
VPI = iverilog-vpi
VER = iverilog
VVP = vvp

CXXFLAGS = -Wall -pipe -std=c++11
OFLAGS = -c -I$(SRC_CPPDIR) -I/usr/include/iverilog -fPIC
LFLAGS = $(CXXFLAGS) -lvpi -shared
VFLAGS = -M$(C_BIN) -m$(C_MODULE)
GTEST_FLAGS = $(CXXFLAGS) -I$(SRC_CPPDIR) -I$(GTEST_DIR) -pthread

ifeq ($(OS),Windows_NT)
	#Windows stuff
	/ := \\
else
	#Linux stuff
	/ := /
endif

SRCDIR := .$(/)src
OBJDIR := .$(/)obj
BINDIR := .$(/)bin
SRC_CPPDIR := $(SRCDIR)$(/)cpp_module
SRC_VDIR := $(SRCDIR)$(/)v_module
CTEST_DIR := $(SRC_CPPDIR)$(/)test
VTEST_DIR := $(SRC_VDIR)$(/)test
GTEST_DIR := /usr/src/gtest/

V_SRCS = $(wildcard $(SRC_VDIR)$(/)*.v)
VTEST_SRCS = $(wildcard $(VTEST_DIR)$(/)*.v)
CPP_SRCS = $(wildcard $(SRC_CPPDIR)$(/)*.cpp)
OBJS = $(CPP_SRCS:$(SRC_CPPDIR)$(/)%.cpp=$(OBJDIR)$(/)%.o)
CTEST_SRCS = $(wildcard $(CTEST_DIR)$(/)*.cpp)
CTEST_OBJS = $(filter-out %interface.o, $(OBJS))
GTEST_SRCS = $(GTEST_DIR)src/gtest-all.cc

CPP_MODULE = $(BINDIR)$(/)cpp_processor.vpi
V_MODULE = $(BINDIR)$(/)processor_tb.vvp
CTEST_BIN = $(BINDIR)$(/)cproc_test
VTEST_BIN = $(BINDIR)$(/)vproc_test

DEPDIR := .d
$(shell mkdir -p $(DEPDIR))
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

.PHONY: all clean run test ctest vtest

all: $(CPP_MODULE) $(V_MODULE)

run: all
	@$(VVP) -M$(BINDIR) -m$(basename $(notdir $(CPP_MODULE))) $(V_MODULE)

$(CPP_MODULE): $(OBJS)
	@$(shell mkdir -p $(BINDIR))
	@$(LD) $^ $(LFLAGS) -o $@

$(OBJDIR)$(/)%.o: $(SRC_CPPDIR)$(/)%.cpp $(DEPDIR)$(/)%.d
	@$(shell mkdir -p $(OBJDIR))
	@$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(OFLAGS) $< -o $@
	@$(POSTCOMPILE)

$(V_MODULE): $(V_SRCS)
	@$(shell mkdir -p $(BINDIR))
	@$(VER) -o$@ $^

$(DEPDIR)$(/)%.d: ;
.PRECIOUS: $(DEPDIR)$(/)%.d

test: ctest vtest

ctest: $(CTEST_BIN)
	@$<

$(CTEST_BIN): $(CTEST_OBJS) $(CTEST_SRCS) $(GTEST_SRCS)
	@$(shell mkdir -p $(BINDIR))
	@$(CXX) $^ $(GTEST_FLAGS) -o $@
	
	
vtest: $(VTEST_BIN)
	@$(VVP) $<

$(VTEST_BIN): $(VTEST_SRCS) $(filter-out %_tb.v %cpp_processor.v, $(V_SRCS))
	@$(shell mkdir -p $(BINDIR))
	@$(VER) -o$@ $^

clean:
	@rm -rf $(OBJDIR) $(BINDIR)

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $CPP_SRCS)))
