# Barrera Paso a Nivel

### Memoria descriptiva

El sistema desarrollado tiene como objetivo el control de una barrera de paso a nivel para control de tráfico en vías de ferrocarriles.

El principio de funcionamiento está basado en el hecho de que las vías conforman un circuito abierto, en una sección cercana a la barrera.
La barrera comienza levantada, y sin ningún tren en la vía.
Cuando un tren pasa por esta sección, funciona como conector y hace que el circuito se cierre, bajando la barrera. 

La máquina va a constar de 2 estados:

1. Estado inicial con la barrera abierta, esperando a que un tren pase por el circuito.
   - Si pasa, entonces baja la barrera al tener el circuito cerrado, pasando al otro estado.
2. Con la barrera cerrada, esperando a que el tren salga del circuito.
   - Entonces levanta la barrera al tener el circuito abierto, volviendo al estado inicial.

### Máquina de estado de la barrera PAN

 ![Máquina de Estados](./BarreraPANmaqEstado.jpg)

Datos de la máquina de estado:
- `circuito_abierto`> Es verdadero si y solo si hay un tren en el circuito.

Datos del archivo de configuración:
- `estado_inicial_del_circuito`> Indica si el circuito comienza abierto o cerrado.
- `circuito_abierto`> Es la palabra clave, en forma de String, que se usa para indicar que el circuito está abierto.
- `circuito_cerrado`> Es la palabra clave, en forma de String, que se usa para indicar que el circuito está cerrado.

### Código

- Archivo de cabecera __mylib.h__

```c
#ifndef MY_LIB
#define MY_LIB
#include <stdio.h>

typedef enum {
  espera = 0,
  calentar = 1
}estados_t;

typedef struct {
  char t;         // temperatura actual
  char t_set;     // temperatura seteada
  char deltaT;    // Delta de temperatura
}temperatura_t;

temperatura_t f_inicio(void); // lee el archivo de configuración y carga las variables.
estados_t f_espera(temperatura_t);
estados_t f_calentar(temperatura_t);



#endif

```

- Archivo __main.c__
> con Switch case

```c
#include "mylib.h"

int main() {
    temperatura_t config;
    estados_t estado = espera; // primer estado

    config = inicio();
    while(1){
      switch (estado) {
        case espera: estado = f_espera(config);
                     break;
        case calentar: estado = f_calentar(config);
                       break;
      }
    }
  return 0;
}

```
 > Con Punteros a funciones

 ```c
 #include "mylib.h"

 int main() {
     temperatura_t config;
     estados_t estado = espera; // primer estado
     estados_t (*fsm[])(tempertura_t) = {f_espera, f_calentar}
     config = inicio();
     while(1) estado = (*fsm[estado])(config);

   return 0;
 }
