# Compilador
FC := gcc
FFLAGS := -Wall -Wextra

# Configurações de diretórios
BUILD_DIR := build
SOURCE_DIR := .

# Nome do execuável final
MAIN_NAME := main

# Busca pelos nomes de arquivos requeridos
SOURCES := $(wildcard $(SOURCE_DIR)/*.c) $(wildcard $(SOURCE_DIR)/*.h)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.o,$(BUILD_DIR)/%.o,$(SOURCES))

#$(patsubst origem/%, destino/%, lista)

# Não são arquivos físicos
.PHONY: all run clean

# Compila tudo
all: $(BUILD_DIR) $(BUILD_DIR)/$(MAIN_NAME)

# Compila tudo e roda
run: all
	./$(BUILD_DIR)/$(MAIN_NAME)

clean:
	rm -rf $(BUILD_DIR)	

# Cria diretório build
$(BUILD_DIR):
	mkdir -p $@

# Regra geral para arquivos .o
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.f90
	$(FC) $(FFLAGS) -c $< -o $@

# Juntar todos os .o para o main
$(BUILD_DIR)/$(MAIN_NAME): $(OBJECTS)
	$(FC) $(FFLAGS) $(OBJECTS) -o $@

