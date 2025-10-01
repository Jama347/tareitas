#include "utils.h"
#include <stdio.h>
#include <string.h>

// Variable global para almacenar el último mensaje
char last_message[256] = "";

void set_message(const char* mensaje) {
    strncpy(last_message, mensaje, 255);
    last_message[255] = '\0';  // Asegurar que termina en null
}

void limpiar_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    // Si hay un mensaje, mostrarlo en la parte superior
    if (last_message[0] != '\0') {
        printf("\n===============================================\n");
        printf("%s", last_message);
        printf("\n===============================================\n\n");
    }
}
