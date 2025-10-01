#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

// Se definen las bibliotecas stb_image como de solo lectura
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Estructura para representar una imagen
struct Imagen {
    unsigned char* data;
    int width, height, channels;
};

/* ****
* Imagen load
******
* Carga una imagen desde un archivo
******
* Input:
* const char* filename: Nombre del archivo a cargar
******
* Returns:
* Imagen, estructura que contiene los datos de la imagen cargada
**** */
Imagen load(const char* filename) {
    Imagen img;
    img.data = stbi_load(filename, &img.width, &img.height, &img.channels, 0);
    
    if (img.data == NULL) {
        std::cerr << "Error al cargar la imagen: " << filename << std::endl;
        exit(1);
    }
    
    return img;
}

/* ****
* void save
******
* Guarda una imagen en un archivo
******
* Input:
* Imagen img: Estructura que contiene los datos de la imagen
* const char* filename: Nombre del archivo donde se guardará la imagen
******
* Returns:
* void
**** */
void save(Imagen img, const char* filename) {
    stbi_write_png(filename, img.width, img.height, img.channels, img.data, img.width * img.channels);
}

/* ****
* void operacion_1
******
* Refleja la imagen horizontalmente (efecto espejo)
******
* Input:
* Imagen& img: Referencia a la estructura que contiene los datos de la imagen
******
* Returns:
* void
**** */
void operacion_1(Imagen& img) {
    // Reflejar horizontalmente la imagen (efecto espejo)
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width / 2; x++) {
            for (int c = 0; c < img.channels; c++) {
                int pos1 = (y * img.width + x) * img.channels + c;
                int pos2 = (y * img.width + (img.width - 1 - x)) * img.channels + c;
                
                // Intercambiar los valores
                unsigned char temp = img.data[pos1];
                img.data[pos1] = img.data[pos2];
                img.data[pos2] = temp;
            }
        }
    }
}

/* ****
* void operacion_2
******
* Rota la imagen 90 grados en sentido horario
******
* Input:
* Imagen& img: Referencia a la estructura que contiene los datos de la imagen
******
* Returns:
* void
**** */
void operacion_2(Imagen& img) {
    // Crear un nuevo arreglo para la imagen rotada
    unsigned char* rotated = new unsigned char[img.width * img.height * img.channels];
    
    // Rotar la imagen 90 grados en sentido horario
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (int c = 0; c < img.channels; c++) {
                // En la imagen rotada, la coordenada y se convierte en x, y la coordenada x se convierte en (height - 1 - y)
                int pos_original = (y * img.width + x) * img.channels + c;
                int pos_rotada = (x * img.height + (img.height - 1 - y)) * img.channels + c;
                
                rotated[pos_rotada] = img.data[pos_original];
            }
        }
    }
    
    // Liberar la memoria de la imagen original
    delete[] img.data;
    
    // Actualizar la imagen con los nuevos datos
    img.data = rotated;
    
    // Intercambiar width y height
    int temp = img.width;
    img.width = img.height;
    img.height = temp;
}

/* ****
* void operacion_3
******
* Atenúa el brillo de una imagen multiplicando cada valor de pixel por un factor
******
* Input:
* Imagen& img: Referencia a la estructura que contiene los datos de la imagen
* float factor: Factor de atenuación entre 0 y 1
******
* Returns:
* void
**** */
void operacion_3(Imagen& img, float factor) {
    // Verificar que el factor esté en el rango [0,1]
    if (factor < 0.0f) factor = 0.0f;
    if (factor > 1.0f) factor = 1.0f;
    
    // Atenuar el brillo de la imagen
    for (int i = 0; i < img.width * img.height * img.channels; i++) {
        img.data[i] = static_cast<unsigned char>(img.data[i] * factor);
    }
}

/* ****
* void operacion_4
******
* Binariza una imagen según un umbral
******
* Input:
* Imagen& img: Referencia a la estructura que contiene los datos de la imagen
* int umbral: Valor umbral para la binarización (0-255)
******
* Returns:
* void
**** */
void operacion_4(Imagen& img, int umbral) {
    // Verificar que el umbral esté en el rango [0,255]
    if (umbral < 0) umbral = 0;
    if (umbral > 255) umbral = 255;
    
    // Primero convertimos la imagen a escala de grises si tiene al menos 3 canales
    if (img.channels >= 3) {
        for (int i = 0; i < img.width * img.height; i++) {
            int pos = i * img.channels;
            // Calculamos el valor en escala de grises
            unsigned char gris = static_cast<unsigned char>(
                0.299f * img.data[pos] + 
                0.587f * img.data[pos + 1] + 
                0.114f * img.data[pos + 2]
            );
            
            // Aplicamos la binarización
            unsigned char valor = (gris > umbral) ? 255 : 0;
            
            // Asignamos el valor binario a todos los canales
            for (int c = 0; c < img.channels; c++) {
                img.data[pos + c] = valor;
            }
        }
    } else {
        // Para imágenes que ya están en escala de grises
        for (int i = 0; i < img.width * img.height * img.channels; i++) {
            img.data[i] = (img.data[i] > umbral) ? 255 : 0;
        }
    }
}

/* ****
* char** to_ascii
******
* Convierte una imagen a arte ASCII
******
* Input:
* Imagen& img: Referencia a la estructura que contiene los datos de la imagen
* const char* chars: Arreglo de caracteres ASCII ordenados por luminosidad
* int num_chars: Número de caracteres en el arreglo
******
* Returns:
* char**, matriz bidimensional de caracteres que representa la imagen en ASCII
**** */
char** to_ascii(Imagen& img, const char* chars, int num_chars) {
    // Crear una copia de la imagen para no modificar la original
    Imagen img_copia;
    img_copia.width = img.width;
    img_copia.height = img.height;
    img_copia.channels = img.channels;
    
    // Asignar memoria para la copia
    int size = img.width * img.height * img.channels;
    img_copia.data = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        img_copia.data[i] = img.data[i];
    }
    
    // Convertir la imagen a escala de grises
    for (int i = 0; i < img_copia.width * img_copia.height; i++) {
        int pos = i * img_copia.channels;
        
        if (img_copia.channels >= 3) {
            // Calculamos el valor en escala de grises
            unsigned char gris = static_cast<unsigned char>(
                0.299f * img_copia.data[pos] + 
                0.587f * img_copia.data[pos + 1] + 
                0.114f * img_copia.data[pos + 2]
            );
            
            // Para simplificar, solo consideramos el primer canal para el arte ASCII
            img_copia.data[pos] = gris;
        }
    }
    
    // Crear la matriz de caracteres ASCII
    char** ascii_art = new char*[img_copia.height];
    for (int y = 0; y < img_copia.height; y++) {
        ascii_art[y] = new char[img_copia.width + 1]; // +1 para el caracter nulo al final
        for (int x = 0; x < img_copia.width; x++) {
            int pos = (y * img_copia.width + x) * img_copia.channels;
            
            // Mapear el valor del pixel (0-255) al índice correspondiente en el arreglo de caracteres
            int index = static_cast<int>((static_cast<float>(img_copia.data[pos]) / 255.0f) * (num_chars - 1));
            ascii_art[y][x] = chars[index];
        }
        ascii_art[y][img_copia.width] = '\0'; // Agregar caracter nulo al final de cada fila
    }
    
    // Liberar la memoria de la copia
    delete[] img_copia.data;
    
    return ascii_art;
}

/* ****
* void save_ascii
******
* Guarda una representación ASCII de una imagen en un archivo de texto
******
* Input:
* char** ascii_art: Matriz bidimensional de caracteres que representa la imagen en ASCII
* int height: Altura de la matriz
* int width: Ancho de la matriz
* const char* filename: Nombre del archivo donde se guardará la representación ASCII
******
* Returns:
* void
**** */
void save_ascii(char** ascii_art, int height, int width, const char* filename) {
    std::ofstream outfile(filename);
    
    if (!outfile) {
        std::cerr << "Error al abrir el archivo para escritura: " << filename << std::endl;
        return;
    }
    
    for (int y = 0; y < height; y++) {
        outfile << ascii_art[y] << std::endl;
    }
    
    outfile.close();
}

/* ****
* void liberar_ascii
******
* Libera la memoria utilizada por una matriz de caracteres ASCII
******
* Input:
* char** ascii_art: Matriz bidimensional de caracteres
* int height: Altura de la matriz
******
* Returns:
* void
**** */
void liberar_ascii(char** ascii_art, int height) {
    for (int y = 0; y < height; y++) {
        delete[] ascii_art[y];
    }
    delete[] ascii_art;
}

int main() {
    // Cargar la imagen
    Imagen img = load("Pikachu.png");
    
    std::cout << "Imagen cargada: " << img.width << "x" << img.height << " con " << img.channels << " canales" << std::endl;
    
    // Crear copias de la imagen para cada operación para no modificar la original
    Imagen img1, img2, img3, img4;
    
    // Para cada copia, asignamos memoria y copiamos los datos
    img1.width = img.width;
    img1.height = img.height;
    img1.channels = img.channels;
    img1.data = new unsigned char[img.width * img.height * img.channels];
    
    img2.width = img.width;
    img2.height = img.height;
    img2.channels = img.channels;
    img2.data = new unsigned char[img.width * img.height * img.channels];
    
    img3.width = img.width;
    img3.height = img.height;
    img3.channels = img.channels;
    img3.data = new unsigned char[img.width * img.height * img.channels];
    
    img4.width = img.width;
    img4.height = img.height;
    img4.channels = img.channels;
    img4.data = new unsigned char[img.width * img.height * img.channels];
    
    // Copiar los datos de la imagen original a las copias
    int size = img.width * img.height * img.channels;
    for (int i = 0; i < size; i++) {
        img1.data[i] = img.data[i];
        img2.data[i] = img.data[i];
        img3.data[i] = img.data[i];
        img4.data[i] = img.data[i];
    }
    
    // Aplicar operación 1: Reflejar horizontalmente (efecto espejo)
    operacion_1(img1);
    save(img1, "operacion1.png");
    
    // Aplicar operación 2: Rotar 90 grados en sentido horario
    operacion_2(img2);
    save(img2, "operacion2.png");
    
    // Aplicar operación 3: Atenuar brillo (factor 0.5)
    operacion_3(img3, 0.5f);
    save(img3, "operacion3.png");
    
    // Aplicar operación 4: Binarizar (umbral 128)
    operacion_4(img4, 128);
    save(img4, "operacion4.png");
    
    // Crear arte ASCII
    // Definir caracteres ASCII ordenados por luminosidad (de menos a más luminoso)
    const char ascii_chars[] = "@%#*+=-:. ";
    int num_chars = sizeof(ascii_chars) - 1; // -1 para excluir el caracter nulo
    
    // Convertir a ASCII
    char** ascii_art = to_ascii(img, ascii_chars, num_chars);
    
    // Guardar el arte ASCII
    save_ascii(ascii_art, img.height, img.width, "ascii_art.txt");
    
    // Liberar memoria
    liberar_ascii(ascii_art, img.height);
    delete[] img1.data;
    delete[] img2.data;
    delete[] img3.data;
    delete[] img4.data;
    stbi_image_free(img.data);
    
    std::cout << "Procesamiento completado. Archivos generados: operacion1.png, operacion2.png, operacion3.png, operacion4.png, ascii_art.txt" << std::endl;
    
    return 0;
}