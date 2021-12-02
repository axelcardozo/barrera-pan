#include "mylib.h"

// Configuracion del sistema y estados
int main()
{
    configuracion_circuito_t configuracion;
    estados_t estado;
    estados_t (*funciones[]) (configuracion_circuito_t) = {f_ocupado, f_libre};
    configuracion = f_inicio(&estado);
    while (true) estado = (*funciones[estado]) (configuracion);

    return 0;
}