CC=gcc
CFLAGS=-Wall -Wextra -g3
SRCS=main.c tablero.c armas.c spawn.c entidades.c utils.c
OBJS=$(SRCS:.c=.o)
TARGET=output/main.exe

# Create output directory if it doesn't exist
$(TARGET): | output

output:
	mkdir -p output

# Main target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Object files
%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

# Clean target
clean:
	del /F /Q *.o
	if exist output\main.exe del /F /Q output\main.exe

# Run target
run: $(TARGET)
	.\$(TARGET)
