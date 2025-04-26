CC       := gcc
CFLAGS   := -Wall -Wextra -Werror
LDFLAGS  := -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/
TARGET   := app
INCLUDE  := -Iinclude/
SRC      := $(wildcard src/*.c)
OBJECTS  := $(SRC:src/%.c=$(OBJ_DIR)/%.o)

# Regra padrão: compila e executa
.PHONY: default
default: all run

# Regra para compilar tudo
.PHONY: all
all: build $(APP_DIR)/$(TARGET)

# Regra para compilar arquivos .c em .o
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

# Regra para linkar o programa final
$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: build clean debug release run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O3
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -r output.dat

run:
	./$(BUILD)/$(TARGET)
