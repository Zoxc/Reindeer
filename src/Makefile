root=..
default: all

BUILD_DIRS += 

include $(root)/Makefile.common
include $(root)/src/Makefile.shared

TARGET = $(CFG)/libReindeer.a

SOURCES = \
	Buffer.cpp \
	Canvas.cpp \
	CanvasFriend.cpp \
	Common.cpp \
	ContentSerializer.cpp \
	GL.cpp \
	Layer.cpp \
	LayerContext.cpp \
	MaskNone.cpp \
	MaskSolid.cpp \
	MaskTexture.cpp \
	SourceSolid.cpp \
	SourceTexture.cpp \
	$(NULL)

OBJECTS = $(patsubst %.cpp, $(CFG)/%.o, $(SOURCES) )

$(TARGET): $(OBJECTS)
	@$(AR) rsc $@ $(OBJECTS)

.PHONY: clean 
clean:
	@rm -f $(OBJECTS) $(TARGET)

all: build-dirs $(TARGET)
