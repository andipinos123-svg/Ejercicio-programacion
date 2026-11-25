#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[]){
    int id[10], demanda[10], estado[10], contPlanes = 0, opcion;
    char nombres[10][50], nomRecurso[10][80];
    float tiempo[10];
    int plazo[10];
    char concesionario[10][50], aseguradora[10][50], cliente[10][50];
    char celular[10][11], cedula[10][14], correo[10][60];

    printf("\n" DOBLE);
    printf("   SISTEMA DE PRODUCCION - EVOLUTH S.A.\n");
    printf(DOBLE "\n");

    do{
        printf(LINEA);
        printf("   MENU PRINCIPAL\n");
        printf(LINEA "\n");
        printf("   1. Registrar plan de credito\n");
        printf("   2. Mostrar planes de credito\n");
        printf("   3. Editar plan de credito\n");
        printf("   4. Habilitar/Deshabilitar plan de credito\n");
        printf("   5. Buscar plan de credito\n");
        printf("   6. Calcular produccion\n");
        printf("   7. Salir\n\n");
        printf(LINEA);
        opcion = validarEnteroRango("   Seleccione una opcion: ", 1, 7);

        switch (opcion){
        case 1:
            registrarPlan(id, nombres, nomRecurso, tiempo, demanda, estado, &contPlanes, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
            break;
        case 2:
            mostrarPlanes(id, nombres, nomRecurso, tiempo, demanda, estado, 0, 0, contPlanes, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
            break;
        case 3:
            editarPlan(id, nombres, nomRecurso, tiempo, demanda, estado, contPlanes, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
            break;
        case 4:
            cambiarEstadoPlan(id, nombres, nomRecurso, tiempo, demanda, estado, contPlanes, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
            break;
        case 5:
            buscarPlan(id, nombres, nomRecurso, tiempo, demanda, estado, contPlanes, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
            break;
        case 6:
            calcularProduccion(id, nombres, nomRecurso, tiempo, demanda, estado, contPlanes, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
            break;
        }

        if (opcion != 7){
            printf("\n");
            if (validarEnteroRango("Desea volver a elegir una opcion? 1.Si/2.No: ", 1, 2) == 2){
                opcion = 7;
            }
        }
        printf("\n");
    } while (opcion != 7);

    return 0;
}

