SRC_DIR = src 
OBJ_DIR = ./obj
EXE=znax

SRC=$(wildcard *.cpp $(foreach fd, $(SRC_DIR), $(fd)/*.c)) 
OBJS=$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

DEFINES = 
SDL_CONFIG=sdl-config
CPP = gcc
OPT_LEVEL ?= -O2 
CFLAGS ?= -g -Wall -Wextra `$(SDL_CONFIG) --cflags` -Wno-write-strings
LDFLAGS ?= -g
LDLIBS ?=  `$(SDL_CONFIG) --libs` -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL -lSDL_gfx -lm

#MINGW does not have X11 and does not require it
#dont know about cygwin
ifneq ($(OS),Windows_NT)
ifeq ($(NOX11),)
LDLIBS += -lX11
endif
endif

ifeq ($(RG35XX),1)
CFLAGS += -DRG35XX
endif

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJS)
	$(CPP) $(LDFLAGS) $(DEFINES) $(TARGET_ARCH) $(OBJS) -o $@ $(LDLIBS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CPP) $(CFLAGS) $(DEFINES) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) -rv *~ $(OBJS) $(EXE)