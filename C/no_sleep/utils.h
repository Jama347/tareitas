#ifndef UTILS_H
#define UTILS_H

// Variable global para almacenar el último mensaje
extern char last_message[256];

// Función para establecer el último mensaje
void set_message(const char* mensaje);

// Función para limpiar la terminal
void limpiar_terminal(void);

#endif // UTILS_H
