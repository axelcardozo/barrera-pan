#include "mylib.h"

// Configuracion del sistema, estados
int main()
{
    // Indica si un tren cerró el circuito pasando por él
    configuracion_circuito_t configuracion;
    estados_t estado;
    estados_t (*funciones[])(configuracion_circuito_t) = {f_ocupado, f_libre};  // *funciones[ocupado] -> f_ocupado

    configuracion = f_inicio ();

    // ¿El estado inicial del circuito equivale a la palabra que el sensor usa para indicar que éste está abierto?
    if (strcmp(configuracion.estado_inicial, configuracion.configuracion_abierto) == 0){
        estado = libre;
    } else {
        estado = ocupado;
    }

    while (true)
        estado = (*funciones[estado]) (configuracion);

    return 0;
}

bool consultar_al_sensor_si_el_circuito_esta_abierto(configuracion_circuito_t configuracion) {
    char respuesta[8];
    printf(
        "Cual es el estado actual del circuito? Indicar \"%s\" si esta libre, o \"%s\" si hay un tren. \n",
        configuracion.configuracion_abierto,
        configuracion.configuracion_cerrado
    );
    fgets(respuesta, 8, stdin);  // Leer lo que devuelve el sensor (el usuario de la consola)
    fflush(stdin);  // Limpia el stream de entrada estándar por si quedan cosas sin guardar

    if(strcmp(respuesta, configuracion.configuracion_abierto) == 0){  // Caso en el que el circuito está abierto
        return true;
    } else if(strcmp(respuesta, configuracion.configuracion_cerrado) == 0) {  // Caso en el que el circuito está cerrado
        return false;
    } else {  // Caso en el que el sensor devuelve una palabra inválida
        printf("Error en el sensor. Se considera ocupado. \n");
        return false;  // Ante un error del sensor, se considera que el circuito está cerrado para que la barrera permanezca baja y no crucen los vehículos
    }
}

configuracion_circuito_t f_inicio ()
{
    printf("Inicio.\n");

    FILE* archivo_de_configuracion = fopen("config.conf", "r");

    // Obtiene el estado inicial del circuito
    char estado_inicial_leido_del_archivo[8];
    fseek(archivo_de_configuracion, 30, SEEK_SET);
    fgets(estado_inicial_leido_del_archivo, 8, archivo_de_configuracion);

    // Obtiene la palabra que representa el estado abierto del circuito
    char estado_abierto_leido_del_archivo[8];
    fseek(archivo_de_configuracion, 58, SEEK_SET);
    fgets(estado_abierto_leido_del_archivo, 8, archivo_de_configuracion);

    // Obtiene la palabra que representa el estado cerrado del circuito
    char estado_cerrado_leido_del_archivo[8];
    fseek(archivo_de_configuracion, 86, SEEK_SET);
    fgets(estado_cerrado_leido_del_archivo, 8, archivo_de_configuracion);

    fclose(archivo_de_configuracion);

    configuracion_circuito_t configuracion;
    strcpy(configuracion.estado_inicial, estado_inicial_leido_del_archivo);
    strcpy(configuracion.configuracion_abierto, estado_abierto_leido_del_archivo);
    strcpy(configuracion.configuracion_cerrado, estado_cerrado_leido_del_archivo);

    return configuracion;
}

estados_t f_ocupado (configuracion_circuito_t configuracion)
{
    printf("Ocupado. \n");

    bool circuito_abierto = consultar_al_sensor_si_el_circuito_esta_abierto(configuracion);
    if(circuito_abierto)
        return libre;
    return ocupado;
}

estados_t f_libre (configuracion_circuito_t configuracion)
{
    printf("Libre. \n");

    bool circuito_abierto = consultar_al_sensor_si_el_circuito_esta_abierto(configuracion);
    if(circuito_abierto)
        return libre;
    return ocupado;
}
