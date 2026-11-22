#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[]){
    int id[10], demanda[10], estado[10], contP = 0, opcion;
    char nombres[10][50], nomRecurso[10][50];
    float tiempo[10];

    printf("\n" DOBLE);
    printf("   SISTEMA DE PRODUCCION - EVOLUTH S.A.\n");
    printf(DOBLE "\n");

    do{
        printf(LINEA);
        printf("   MENU PRINCIPAL\n");
        printf(LINEA "\n");
        printf("   1. Registrar producto\n");
        printf("   2. Mostrar productos\n");
        printf("   3. Editar producto\n");
        printf("   4. Habilitar/Deshabilitar producto\n");
        printf("   5. Buscar producto\n");
        printf("   6. Calcular produccion\n");
        printf("   7. Salir\n\n");
        printf(LINEA);
        opcion = validarEnteroRango("   Seleccione una opcion: ", 1, 7);

        switch (opcion){
        case 1:
            registrarProducto(id, nombres, nomRecurso, tiempo, demanda, estado, &contP);
            break;
        case 2:
            mostrarProductos(id, nombres, nomRecurso, tiempo, demanda, estado, 0, contP);
            break;
        case 3:
            editarProducto(id, nombres, nomRecurso, tiempo, demanda, estado, contP);
            break;
        case 4:
            cambiarEstadoProducto(id, nombres, nomRecurso, tiempo, demanda, estado, contP);
            break;
        case 5:
            buscarProducto(id, nombres, nomRecurso, tiempo, demanda, estado, contP);
            break;
        case 6:
            calcularProduccion(id, nombres, nomRecurso, tiempo, demanda, estado, contP);
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

