# Guardara os códigos fontes dos executáveis
APPS = apps
# Guardará os arquivos binário (compilados) dos códigos fontes da apps
BIN = bin
# Guardará os arquivos de header (.h)
INCLUDE = include
# Guardará a biblioteca estática criada
LIB = lib
# Guardará os objetos dos arquivos fonte (.o)
OBJ = obj
# Guardará os arquivos fonte (.c)
SRC = src

# Nomes
ADT = float_vector
APP_NAME = app
LIB_NAME = fv

# -O3 => Optimization v3; -Wall => Exibe todos os Warnings.
FLAGS = -O3 -Wall

# Referencia todas as libs usadas no programa e que foram compiladas em uma
# lib estática
LIBS = -l$(LIB_NAME) -L $(LIB)

all: build_libs build_apps

# Compila as Estruturas de dados e dependências
# Segunda linha está a diretiva que criará a lib estática
build_libs: $(OBJ)/$(ADT).o
	ar -rcs $(LIB)/lib$(LIB_NAME).a $(OBJ)/*.o

# Compila os programas
build_apps: \
	clean_apps \
	$(BIN)/$(APP_NAME)

# roda o programa
run:
	$(BIN)/$(APP_NAME)

# Limpa os arquivos binários e objetos
clean:
	rm -rf $(BIN)/* $(OBJ)/* $(LIB)/*

clean_apps:
	rm -rf $(BIN)/*

# Mascara (interface) para compilação de dependencias e/ou ADT's
# A primeira linha verifica se o header e o arquivo fonte existe, se existir, compila.
$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(APPS)/%.c
	gcc $(FLAGS) $< $(LIBS) -I $(INCLUDE) -o $@