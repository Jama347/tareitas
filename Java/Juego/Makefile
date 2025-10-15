# Compilador de Java
JCC = javac

# Directorio de salida para los archivos .class
BIN_DIR = bin

# Directorio de fuentes
SRC_DIR = .

# Flags del compilador: -d especifica el directorio de salida, -sourcepath la raíz de los fuentes
JFLAGS = -d $(BIN_DIR) -sourcepath $(SRC_DIR)

# Clase principal que contiene el método main
MAIN_CLASS = Juego.Main

# Encontrar todos los archivos .java recursivamente
SOURCES = $(shell find $(SRC_DIR) -type f -name "*.java")

# Target por defecto: compila el proyecto
all: compile

# Target para compilar todos los archivos fuente
compile:
	@echo "Creando directorio de salida $(BIN_DIR)..."
	@mkdir -p $(BIN_DIR)
	@echo "Compilando archivos .java..."
	$(JCC) $(JFLAGS) $(SOURCES)
	@echo "Compilación finalizada."

# Target para ejecutar el programa
run:
	@echo "Ejecutando el programa..."
	java -cp $(BIN_DIR) $(MAIN_CLASS)

# Target para limpiar los archivos compilados
clean:
	@echo "Limpiando archivos compilados..."
	@rm -rf $(BIN_DIR)
	@echo "Limpieza finalizada."

# Targets que no representan archivos
.PHONY: all compile run clean
