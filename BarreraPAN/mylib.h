#ifndef MYLIB
#define MYLIB
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    libre = 1,
    ocupado = 0
}estados_t;

typedef struct {
  char estado_inicial[8];  // Estado inicial del circuito
  char configuracion_abierto[8];  // Palabra que representa al circuito abierto en el sensor
  char configuracion_cerrado[8];  // Palabra que representa al circuito cerrado en el sensor
}configuracion_circuito_t;

configuracion_circuito_t f_inicio (estados_t* estado);  // Lee el archivo de configuracion y carga las variables.
estados_t f_libre (configuracion_circuito_t);
estados_t f_ocupado (configuracion_circuito_t);

#endif // MYLIB
