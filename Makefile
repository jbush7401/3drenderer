CC = cl.exe
CFLAGS = /std:c11 /W3 /WX /Zi /I$(SDL_INCLUDE)
BUILD_DIR = build
SDL_DIR = vendor/sdl3
SDL_INCLUDE = $(SDL_DIR)/include
SDL_LIB = $(SDL_DIR)/SDL3.lib
SDL_DLL = $(SDL_DIR)/SDL3.dll

SRC = src/main.c src/display.c
OBJ = $(BUILD_DIR)/main.obj $(BUILD_DIR)/display.obj
EXE = $(BUILD_DIR)/renderer.exe

.PHONY: all run clean

all: $(EXE)

$(BUILD_DIR)/SDL3.dll: $(SDL_DLL)
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	copy vendor\sdl3\SDL3.dll $(BUILD_DIR)\SDL3.dll

$(BUILD_DIR)/main.obj: src/main.c src/display.h
	$(CC) $(CFLAGS) /c /Fo:$(BUILD_DIR)/main.obj src/main.c

$(BUILD_DIR)/display.obj: src/display.c src/display.h
	$(CC) $(CFLAGS) /c /Fo:$(BUILD_DIR)/display.obj src/display.c

$(EXE): $(OBJ) $(BUILD_DIR)/SDL3.dll
	$(CC) $(CFLAGS) /Fd:$(BUILD_DIR)/ /Fe:$(EXE) $(OBJ) /link $(SDL_LIB)


run: $(EXE)
	$(EXE)

clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
