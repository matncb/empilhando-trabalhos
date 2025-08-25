# Compilador
FC := gcc
FFLAGS := -Wall -Wextra

# Configurações de diretórios
BUILD_DIR := build
SOURCE_DIR := src
INCLUDES_DIR := includes

# Nome do execuável final
MAIN_NAME := main

# Busca pelos nomes de arquivos requeridos
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

FFLAGS := $(FFLAGS) -I $(INCLUDES_DIR)

#$(patsubst origem/%, destino/%, lista)

# Não são arquivos físicos
.PHONY: all run clean

# Compila tudo
all: $(BUILD_DIR) $(BUILD_DIR)/$(MAIN_NAME)

# Compila tudo e roda
run: all
	./$(BUILD_DIR)/$(MAIN_NAME) $(ARGS)

clean:
	rm -rf $(BUILD_DIR)	

# Cria diretório build
$(BUILD_DIR):
	mkdir -p $@

# Regra geral para arquivos .o
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(FC) $(FFLAGS) -c $< -o $@

# Juntar todos os .o para o main
$(BUILD_DIR)/$(MAIN_NAME): $(OBJECTS)
	$(FC) $(FFLAGS) $(OBJECTS) -o $@

