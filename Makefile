root=.
default: all

BUILD_DIRS += Demo

include $(root)/src/Makefile.public
include $(root)/swl/Makefile.public
include $(root)/Makefile.common

TARGET = $(CFG)/reindeer-demo

SOURCES = \
	Demo/main.cpp \
	$(NULL)

OBJECTS = $(patsubst %.cpp, $(CFG)/%.o, $(SOURCES) )

$(TARGET): Reindeer $(OBJECTS)
	@$(CXX) $(CFLAGS) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $@

all: build-dirs $(TARGET)

.PHONY: clean 
clean: Reindeer-clean
	@rm -f $(OBJECTS) $(TARGET)
