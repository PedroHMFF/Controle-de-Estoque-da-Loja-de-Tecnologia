# Nome do executável final
TARGET = programa_marcas

# Compilador
CC = gcc

# Flags de compilação (-Wall mostra todos os avisos/erros)
CFLAGS = -Wall -Wextra -g

# Arquivos fonte
SRCS = main.c funcoes.c

# Arquivos de objeto (transforma .c em .o)
OBJS = $(SRCS:.c=.o)

# Regra principal (o que acontece quando você digita apenas 'make')
all: $(TARGET)

# Linkagem do executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilação dos arquivos .c para .o
%.o: %.c funcoes.h
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos temporários e do executável
clean:
	rm -f $(OBJS) $(TARGET)

# Rodar o programa
run: all
	./$(TARGET)