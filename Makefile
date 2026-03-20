CC = cl.exe
CFLAGS = /std:c11 /W3 /WX /Zi
BUILD_DIR = build

SRC = src/main.c
OBJ = $(BUILD_DIR)/main.obj
EXE = $(BUILD_DIR)/renderer.exe

.PHONY: all run clean

all: $(EXE)

$(EXE): $(SRC)
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) /Fd:$(BUILD_DIR)/ /Fo:$(OBJ) /Fe:$(EXE) $(SRC)

run: $(EXE)
	$(EXE)

clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
