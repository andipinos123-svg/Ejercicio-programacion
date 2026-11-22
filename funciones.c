#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

void limpiarEspacios(char *cadena){
    int inicio = 0;
    int fin = 0;
    int i;

    while (cadena[fin] != '\0'){
        fin++;
    }
    while (fin > 0 && (cadena[fin-1] == ' ' || cadena[fin-1] == '\t')){
        fin--;
    }
    cadena[fin] = '\0';

    while (cadena[inicio] == ' ' || cadena[inicio] == '\t'){
        inicio++;
    }
    if (inicio > 0){
        for (i = 0; i <= fin - inicio; i++){
            cadena[i] = cadena[i + inicio];
        }
    }
}

float validarFloatRango(const char *pregunta, float a, float b){
    float num;
    int val;
    do{
        printf("%s", pregunta);
        val = scanf("%f", &num);
        while (getchar() != '\n');
        if (val != 1 || num < a || num > b){
            printf("Error: el valor ingresado es incorrecto\n");
        }
    } while (val != 1 || num < a || num > b);
    return num;
}

int validarEnteroRango(const char *pregunta, int a, int b){
    float num;
    do{
        num = validarFloatRango(pregunta, a, b);
        if (num != (int)num){
            printf("Error: no puede ingresar decimales, debe ser un numero entero\n");
        }
    } while (num != (int)num);
    return (int)num;
}

void leercadena(char *cadena, int n){
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    if (len >= 0 && cadena[len] == '\n'){
        cadena[len] = '\0';
    }
}

void leerNombre(const char *pregunta, char *cadena, int n){
    do{
        printf("%s", pregunta);
        leercadena(cadena, n);
        limpiarEspacios(cadena);
        if (strlen(cadena) == 0){
            printf("Error: el nombre no puede estar vacio\n");
        }
    } while (strlen(cadena) == 0);
}

void leerNombreUnico(const char *pregunta, char *destino, int n, char lista[][50], int total, int excluirIdx){
    char temp[50];
    int repetido;
    do{
        repetido = 0;
        leerNombre(pregunta, temp, n);
        for (int i = 0; i < total; i++){
            if (i != excluirIdx && strcasecmp(temp, lista[i]) == 0){
                repetido = 1;
                printf("Error: ya existe un registro con ese nombre\n");
                break;
            }
        }
    } while (repetido == 1);
    strcpy(destino, temp);
}

void registrarProducto(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int *contP){
    if (*contP >= 10){
        printf("Error: ya se registraron los %d productos\n", 10);
        return;
    }
    printf("Ingrese el producto %d\n", *contP);
    id[*contP] = *contP;

    char activos[10][50];
    int nActivos = 0;
    for (int i = 0; i < *contP; i++){
        if (estado[i] == 0){
            strcpy(activos[nActivos++], nombres[i]);
        }
    }
    leerNombreUnico("Cual es el nombre del producto (plan de credito)? ", nombres[*contP], 50, activos, nActivos, -1);

    tiempo[*contP] = validarFloatRango("Cuantas horas toma la aprobacion y entrega de un credito? (0.01 a 1000): ", 0.01, 1000);

    printf("Recursos del producto: capital, asesor, analista, gestor\n");
   
    float cap = validarFloatRango("Ingrese la cantidad de capital?: ", 0.01, 1000000);

    if (cap == (int)cap){
        snprintf(nomRecurso[*contP], 50, "%d capital, 1 asesor, 1 analista, 1 gestor", (int)cap);
    }else{
        snprintf(nomRecurso[*contP], 50, "%.2f capital, 1 asesor, 1 analista, 1 gestor", cap);
    }

    demanda[*contP] = validarEnteroRango("Cuantas solicitudes de credito se reciben al mes? (creditos): ", 1, 100000);
    estado[*contP] = 0;
    (*contP)++;
}

void mostrarProductos(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int n, int contP){
    printf(LINEAT);
    printf("%-3s  %-24s  %-46s  %-25s  %-18s\n", "ID", "Nombre de producto", "Recursos", "Tiempo de fabricacion", "Cantidad demandada");
    printf("%-3s  %-24s  %-46s  %-25s  %-18s\n", "", "(Plan de credito)", "(Cantidad y recurso)", "(Aprobacion y entrega)", "(Solicitudes al mes)");
    printf(LINEAT);
    for (int i = n; i < contP; i++){
        if (estado[i] == 0){
            char celdaNombre[60], celdaRecurso[120], celdaTiempo[30], celdaDemanda[30];
            snprintf(celdaNombre, sizeof(celdaNombre), "%.24s", nombres[i]);
            snprintf(celdaRecurso, sizeof(celdaRecurso), "%.46s", nomRecurso[i]);
            if (tiempo[i] == (int)tiempo[i]){
                snprintf(celdaTiempo, sizeof(celdaTiempo), "%d %s", (int)tiempo[i], (int)tiempo[i] == 1 ? "hora" : "horas");
            }else{
                snprintf(celdaTiempo, sizeof(celdaTiempo), "%.2f horas", tiempo[i]);
            }
            celdaTiempo[25] = '\0';
            sprintf(celdaDemanda, "%d %s", demanda[i], demanda[i] == 1 ? "credito" : "creditos");
            celdaDemanda[18] = '\0';
            printf("%-3d  %-24s  %-46s  %-25s  %-18s\n", id[i], celdaNombre, celdaRecurso, celdaTiempo, celdaDemanda);
        }
    }
    printf(LINEAT);
}

int buscarProducto(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int contP){
    int activos = 0;
    for (int i = 0; i < contP; i++){
        if (estado[i] == 0){
            activos++;
        }
    }
    if (contP == 0 || activos == 0){
        printf("Error: no hay productos activos registrados\n");
        return -1;
    }
    int opc = validarEnteroRango("Seleccione el metodo de busqueda 1.ID/2.Nombre: ", 1, 2);
    int indice = -1;
    if (opc == 1){
        int idsDisp[10], nDisp = 0, primero = 1;
        for (int i = 0; i < contP; i++){
            if (estado[i] == 0){
                idsDisp[nDisp++] = id[i];
            }
        }
        printf("IDs disponibles: ");
        for (int j = 0; j < nDisp; j++){
            if (!primero){
                printf(", ");
            }
            printf("%d", idsDisp[j]);
            primero = 0;
        }
        printf("\n");
        int busqId, validoId;
        do{
            validoId = 0;
            busqId = validarEnteroRango("Ingrese el ID del producto: ", 0, contP - 1);
            for (int i = 0; i < contP; i++){
                if (estado[i] == 0 && id[i] == busqId){
                    indice = i;
                    validoId = 1;
                    break;
                }
            }
            if (!validoId){
                printf("Error: el ID ingresado no esta disponible\n");
            }
        } while (!validoId);
    }else{
        char nombre[50];
        leerNombre("Ingrese el nombre del producto: ", nombre, 50);
        for (int i = 0; i < contP; i++){
            if (estado[i] == 0 && strcasecmp(nombres[i], nombre) == 0){
                indice = i;
                break;
            }
        }
    }
    if (indice == -1){
        printf("No se encontro ningun producto activo con ese dato\n");
    }else{
        mostrarProductos(id, nombres, nomRecurso, tiempo, demanda, estado, indice, indice + 1);
    }
    return indice;
}

void editarProducto(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int contP){
    int pos = buscarProducto(id, nombres, nomRecurso, tiempo, demanda, estado, contP);
    if (pos == -1){
        return;
    }
    printf("\nSeleccione el dato a editar:\n");
    printf("   1. Nombre\n");
    printf("   2. Recursos\n");
    printf("   3. Tiempo\n");
    printf("   4. Demanda\n");
    int opc = validarEnteroRango("Opcion: ", 1, 4);
    switch (opc){
    case 1:{
        char activos[10][50];
        int nActivos = 0;
        int idxEnActivos = -1;
        for (int i = 0; i < contP; i++){
            if (estado[i] == 0){
                if (i == pos){
                    idxEnActivos = nActivos;
                }
                strcpy(activos[nActivos++], nombres[i]);
            }
        }
        leerNombreUnico("Nuevo nombre: ", nombres[pos], 50, activos, nActivos, idxEnActivos);
        break;
    }
    case 2:{
        float cap = validarFloatRango("Nueva cantidad de capital: ", 0.01, 1000000);
        if (cap == (int)cap){
            snprintf(nomRecurso[pos], 50, "%d capital, 1 asesor, 1 analista, 1 gestor", (int)cap);
        }else{
            snprintf(nomRecurso[pos], 50, "%.2f capital, 1 asesor, 1 analista, 1 gestor", cap);
        }
        break;
    }
    case 3:
        tiempo[pos] = validarFloatRango("Nuevas horas de aprobacion y entrega por credito (horas): ", 0.01, 1000);
        break;
    case 4:
        demanda[pos] = validarEnteroRango("Nueva cantidad de solicitudes al mes (creditos): ", 1, 100000);
        break;
    }
    printf("\nProducto editado correctamente:\n");
    mostrarProductos(id, nombres, nomRecurso, tiempo, demanda, estado, pos, pos + 1);
}

void cambiarEstadoProducto(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int contP){
    if (contP == 0){
        printf("Error: no hay productos registrados\n");
        return;
    }

    int activos = 0, inactivos = 0;
    for (int i = 0; i < contP; i++){
        if (estado[i] == 0){
            activos++;
        }else if (estado[i] == 1){
            inactivos++;
        }
    }

    printf("\nSeleccione la accion:\n");
    printf("   1. Deshabilitar producto\n");
    printf("   2. Habilitar producto\n");
    int accion = validarEnteroRango("Opcion: ", 1, 2);

    int estadoBuscado = (accion == 1) ? 0 : 1;
    int cantDisponibles = (accion == 1) ? activos : inactivos;

    if (cantDisponibles == 0){
        if (accion == 1){
            printf("Error: no hay productos activos para deshabilitar\n");
        }else{
            printf("Error: no hay productos inactivos para habilitar\n");
        }
        return;
    }

    if (accion == 2){
        printf("\nProductos deshabilitados:\n");
        printf(LINEAT);
        printf("%-3s  %-24s  %-46s  %-25s  %-18s\n", "ID", "Nombre de producto", "Recursos", "Tiempo de fabricacion", "Cantidad demandada");
        printf("%-3s  %-24s  %-46s  %-25s  %-18s\n", "", "(Plan de credito)", "(Cantidad y recurso)", "(Aprobacion y entrega)", "(Solicitudes al mes)");
        printf(LINEAT);
        for (int i = 0; i < contP; i++){
            if (estado[i] == 1){
                char celdaNombre[60], celdaRecurso[120], celdaTiempo[30], celdaDemanda[30];
                snprintf(celdaNombre, sizeof(celdaNombre), "%.24s", nombres[i]);
                snprintf(celdaRecurso, sizeof(celdaRecurso), "%.46s", nomRecurso[i]);
                if (tiempo[i] == (int)tiempo[i]){
                    snprintf(celdaTiempo, sizeof(celdaTiempo), "%d %s", (int)tiempo[i], (int)tiempo[i] == 1 ? "hora" : "horas");
                }else{
                    snprintf(celdaTiempo, sizeof(celdaTiempo), "%.2f horas", tiempo[i]);
                }
                celdaTiempo[25] = '\0';
                sprintf(celdaDemanda, "%d %s", demanda[i], demanda[i] == 1 ? "credito" : "creditos");
                celdaDemanda[18] = '\0';
                printf("%-3d  %-24s  %-46s  %-25s  %-18s\n", id[i], celdaNombre, celdaRecurso, celdaTiempo, celdaDemanda);
            }
        }
        printf(LINEAT);
    }

    int opc = validarEnteroRango("Seleccione el metodo de busqueda 1.ID/2.Nombre: ", 1, 2);
    int indice = -1;

    if (opc == 1){
        int primero = 1;
        printf("IDs disponibles: ");
        for (int i = 0; i < contP; i++){
            if (estado[i] == estadoBuscado){
                if (!primero){
                    printf(", ");
                }
                printf("%d", id[i]);
                primero = 0;
            }
        }
        printf("\n");

        int busqId, validoId;
        do{
            validoId = 0;
            busqId = validarEnteroRango("Ingrese el ID del producto: ", 0, contP - 1);
            for (int i = 0; i < contP; i++){
                if (estado[i] == estadoBuscado && id[i] == busqId){
                    indice = i;
                    validoId = 1;
                    break;
                }
            }
            if (!validoId){
                printf("Error: el ID ingresado no esta disponible para esta accion\n");
            }
        } while (!validoId);
    }else{
        char nombre[50];
        leerNombre("Ingrese el nombre del producto: ", nombre, 50);
        for (int i = 0; i < contP; i++){
            if (estado[i] == estadoBuscado && strcasecmp(nombres[i], nombre) == 0){
                indice = i;
                break;
            }
        }
        if (indice == -1){
            printf("No se encontro ningun producto con ese nombre en ese estado\n");
            return;
        }
    }

    if (accion == 1){
        int conf = validarEnteroRango("Desea deshabilitar el producto? 1.Si/2.No: ", 1, 2);
        if (conf == 1){
            estado[indice] = 1;
            printf("El producto con el ID: %d (%s) esta deshabilitado\n", id[indice], nombres[indice]);
        }
    }else{
        int conf = validarEnteroRango("Desea habilitar el producto? 1.Si/2.No: ", 1, 2);
        if (conf == 1){
            estado[indice] = 0;
            printf("El producto con el ID: %d (%s) esta habilitado\n", id[indice], nombres[indice]);
        }
    }
}

void calcularProduccion(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int contP){
    float tiempoTotal = 0, capitalTotal = 0, tiempoDisp, capitalDisp;
    int activos = 0;
    for (int i = 0; i < contP; i++){
        if (estado[i] == 0){
            float capProd = 0;
            sscanf(nomRecurso[i], "%f", &capProd);
            tiempoTotal += tiempo[i] * demanda[i];
            capitalTotal += capProd * demanda[i];
            activos++;
        }
    }
    if (activos == 0){
        printf("Error: no hay productos activos registrados\n");
        return;
    }
    tiempoDisp = validarFloatRango("Ingrese el tiempo disponible (horas): ", 0, 100000000);
    capitalDisp = validarFloatRango("Ingrese el capital disponible: ", 0, 1000000000);
    int hayAsesor = validarEnteroRango("Hay asesor disponible? 1.Si/2.No: ", 1, 2);
    int hayAnalista = validarEnteroRango("Hay analista disponible? 1.Si/2.No: ", 1, 2);
    int hayGestor = validarEnteroRango("Hay gestor disponible? 1.Si/2.No: ", 1, 2);
    int cumple = (tiempoTotal <= tiempoDisp && capitalTotal <= capitalDisp && hayAsesor == 1 && hayAnalista == 1 && hayGestor == 1);

    printf("\n" DOBLE);
    printf("   EVOLUTH S.A. - EVALUACION DE LA PRODUCCION\n");
    printf("   RESULTADO: %s\n", cumple ? "PUEDE CUMPLIR con la demanda" : "NO PUEDE CUMPLIR con la demanda");
    printf(DOBLE "\n");
    mostrarProductos(id, nombres, nomRecurso, tiempo, demanda, estado, 0, contP);
    float diferenciaT = tiempoDisp - tiempoTotal;
    float diferenciaC = capitalDisp - capitalTotal;
    char a[40], b[40], c[40];
    printf("\n%-9s %16s %16s %16s  %-8s\n", "Concepto", "Requerido", "Disponible", "Diferencia", "Estado");
    printf("------------------------------------------------------------------------\n");
    sprintf(a, "%.2f horas", tiempoTotal);
    sprintf(b, "%.2f horas", tiempoDisp);
    sprintf(c, "%.2f horas", diferenciaT < 0 ? -diferenciaT : diferenciaT);
    printf("%-9s %16s %16s %16s  %-8s\n", "Tiempo", a, b, c, diferenciaT >= 0 ? "Sobrante" : "Faltante");
    sprintf(a, "%.2f", capitalTotal);
    sprintf(b, "%.2f", capitalDisp);
    sprintf(c, "%.2f", diferenciaC < 0 ? -diferenciaC : diferenciaC);
    printf("%-9s %16s %16s %16s  %-8s\n", "Capital", a, b, c, diferenciaC >= 0 ? "Sobrante" : "Faltante");
    printf("%-9s %16s %16s %16s  %-8s\n", "Asesor", "1", hayAsesor == 1 ? "1" : "0", "-", hayAsesor == 1 ? "Si" : "No");
    printf("%-9s %16s %16s %16s  %-8s\n", "Analista", "1", hayAnalista == 1 ? "1" : "0", "-", hayAnalista == 1 ? "Si" : "No");
    printf("%-9s %16s %16s %16s  %-8s\n", "Gestor", "1", hayGestor == 1 ? "1" : "0", "-", hayGestor == 1 ? "Si" : "No");
    printf("------------------------------------------------------------------------\n");
}