root=.
default: all

BUILD_DIRS += 

include $(root)/src/Makefile.public
include $(root)/swl/Makefile.public
include $(root)/Makefile.common

TARGET = $(CFG)/demo

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
