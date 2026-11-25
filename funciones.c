#include <stdio.h>
#include <string.h>
#include <strings.h>
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
            printf("Error: el valor ingresado es incorrecto\n\n");
        }
    } while (val != 1 || num < a || num > b);
    return num;
}

int validarEnteroRango(const char *pregunta, int a, int b){
    float num;
    do{
        num = validarFloatRango(pregunta, a, b);
        if (num != (int)num){
            printf("Error: no puede ingresar decimales, debe ser un numero entero\n\n");
        }
    } while (num != (int)num);
    return (int)num;
}

void leercadena(char *cadena, int n){
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    if (len >= 0 && cadena[len] == '\n'){
        cadena[len] = '\0';
    }else{
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

void leerNombre(const char *pregunta, char *cadena, int n){
    do{
        printf("%s", pregunta);
        leercadena(cadena, n);
        limpiarEspacios(cadena);
        if (strlen(cadena) == 0){
            printf("Error: el nombre no puede estar vacio\n\n");
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
                printf("Error: ya existe un registro con ese nombre\n\n");
                break;
            }
        }
    } while (repetido == 1);
    strcpy(destino, temp);
}

void leerDigitos(const char *pregunta, char *destino, int largo1, int largo2, const char *inicio, const char *terminacion, const char *msgError){
    char temp[100];
    int valido, len;
    do{
        printf("%s", pregunta);
        leercadena(temp, 100);
        limpiarEspacios(temp);
        len = strlen(temp);
        valido = (len == largo1 || len == largo2);
        for (int i = 0; valido && i < len; i++){
            if (!isdigit((unsigned char)temp[i])){
                valido = 0;
            }
        }
        if (valido && strncmp(temp, inicio, strlen(inicio)) != 0){
            valido = 0;
        }
        if (valido && len == largo2 && largo2 != largo1 && strcmp(temp + len - strlen(terminacion), terminacion) != 0){
            valido = 0;
        }
        if (!valido){
            printf("%s\n\n", msgError);
        }
    } while (!valido);
    strcpy(destino, temp);
}

void leerCorreo(const char *pregunta, char *destino){
    char temp[100];
    int valido;
    do{
        printf("%s", pregunta);
        leercadena(temp, 100);
        limpiarEspacios(temp);
        char *arroba = strchr(temp, '@');
        valido = (arroba != NULL && arroba != temp && strchr(arroba + 1, '@') == NULL && strchr(temp, ' ') == NULL && strlen(temp) < 60);
        if (valido){
            char *punto = strrchr(arroba, '.');
            valido = (punto != NULL && punto > arroba + 1 && punto[1] != '\0');
        }
        if (!valido){
            printf("Error: ingrese un correo electronico valido (ejemplo: nombre@dominio.com)\n\n");
        }
    } while (!valido);
    strcpy(destino, temp);
}

int cupoDisponible(int *demanda, int *estado, int contPlanes, int excluir){
    int maxCreditos = 200;
    int usado = 0;
    for (int i = 0; i < contPlanes; i++){
        if (estado[i] == 0 && i != excluir){
            usado += demanda[i];
        }
    }
    return maxCreditos - usado;
}

int leerDemanda(const char *pregunta, int *demanda, int *estado, int contPlanes, int excluir){
    int cupo = cupoDisponible(demanda, estado, contPlanes, excluir);
    if (cupo <= 0){
        printf("No se puede ingresar otro, ya no hay creditos disponibles\n\n");
        return -1;
    }
    char texto[150];
    snprintf(texto, sizeof(texto), "%s(hasta %d): ", pregunta, cupo);
    int valor;
    do{
        valor = validarEnteroRango(texto, 1, 100000);
        if (valor > cupo){
            printf("Ya no se pueden realizar mas creditos\n");
            printf("(cupo disponible: %d %s)\n\n", cupo, cupo == 1 ? "credito" : "creditos");
        }
    } while (valor > cupo);
    int resto = cupo - valor;
    printf("El asesor, analista, abogado y gestor solo pueden realizar %d %s mas\n\n", resto, resto == 1 ? "credito" : "creditos");
    return valor;
}

void registrarPlan(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int *contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]){
    if (*contPlanes >= 10){
        printf("Error: ya se registraron los %d planes de credito\n\n", 10);
        return;
    }
    if (cupoDisponible(demanda, estado, *contPlanes, -1) <= 0){
        printf("No se puede ingresar otro, ya no hay creditos disponibles\n\n");
        return;
    }
    printf("Ingrese el plan de credito %d\n\n", *contPlanes);
    id[*contPlanes] = *contPlanes;

    char activos[10][50];
    int nActivos = 0;
    for (int i = 0; i < *contPlanes; i++){
        if (estado[i] == 0){
            strcpy(activos[nActivos++], nombres[i]);
        }
    }
    leerNombreUnico("Cual es el nombre del plan de credito? ", nombres[*contPlanes], 50, activos, nActivos, -1);

    int d = leerDemanda("\nCuantas solicitudes de credito se reciben al mes? ", demanda, estado, *contPlanes, -1);
    if (d == -1){
        return;
    }
    demanda[*contPlanes] = d;

    tiempo[*contPlanes] = validarFloatRango("Cuantas horas toma la aprobacion y entrega de un credito? (0.01 a 1000): ", 0.01, 1000);

    printf("\nRecursos del plan de credito: capital, asesor, analista, abogado, gestor");

    float cap = validarFloatRango("\nIngrese la cantidad de capital?: ", 0.01, 1000000);

    if (cap == (int)cap){
        snprintf(nomRecurso[*contPlanes], 80, "%d capital, 1 asesor, 1 analista, 1 abogado, 1 gestor", (int)cap);
    }else{
        snprintf(nomRecurso[*contPlanes], 80, "%.2f capital, 1 asesor, 1 analista, 1 abogado, 1 gestor", cap);
    }

    leerNombre("\nConcesionario donde se realizara la compra? ", concesionario[*contPlanes], 50);

    int op = validarEnteroRango("\nContrato la aseguradora? 1.Si/2.No: ", 1, 2);
    if (op == 1){
        leerNombre("Nombre de la aseguradora: ", aseguradora[*contPlanes], 50);
    }else{
        aseguradora[*contPlanes][0] = '\0';
    }

    printf("\nLa tasa de interes es de 15.2%% anual. ");
    plazo[*contPlanes] = validarEnteroRango("En cuantos meses pidio pagar el credito? (1 a 120): ", 1, 120);

    leerNombre("\nIngrese el nombre del cliente: ", cliente[*contPlanes], 50);
    leerDigitos("\nIngrese el numero de celular: ", celular[*contPlanes], 10, 10, "09", "", "Error: el celular debe tener 10 digitos y empezar con 09");
    leerDigitos("\nIngrese la cedula/RUC: ", cedula[*contPlanes], 10, 13, "", "001", "Error: la cedula debe tener 10 digitos o el RUC 13 digitos terminado en 001");
    leerCorreo("\nIngrese el correo electronico: ", correo[*contPlanes]);

    estado[*contPlanes] = 0;
    (*contPlanes)++;
}

void mostrarPlanes(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int est, int n, int contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]){
    int mostrados = 0;
    for (int i = n; i < contPlanes; i++){
        if (estado[i] == est){
            mostrados++;
        }
    }
    if (mostrados == 0){
        printf("No hay planes de credito para mostrar\n\n");
        return;
    }

    printf(LINEAT);
    printf("%-3s  %-24s  %-60s  %-25s  %-18s\n", "ID", "Nombre del plan", "Recursos", "Tiempo de fabricacion", "Cantidad demandada");
    printf("%-3s  %-24s  %-60s  %-25s  %-18s\n", "", "(Plan de credito)", "(Cantidad y recurso)", "(Aprobacion y entrega)", "(Solicitudes al mes)");
    printf(LINEAT);
    for (int i = n; i < contPlanes; i++){
        if (estado[i] == est){
            char celdaNombre[60], celdaRecurso[120], celdaTiempo[30], celdaDemanda[30];
            snprintf(celdaNombre, sizeof(celdaNombre), "%.24s", nombres[i]);
            snprintf(celdaRecurso, sizeof(celdaRecurso), "%.60s", nomRecurso[i]);
            if (tiempo[i] == (int)tiempo[i]){
                snprintf(celdaTiempo, sizeof(celdaTiempo), "%d %s", (int)tiempo[i], (int)tiempo[i] == 1 ? "hora" : "horas");
            }else{
                snprintf(celdaTiempo, sizeof(celdaTiempo), "%.2f horas", tiempo[i]);
            }
            celdaTiempo[25] = '\0';
            snprintf(celdaDemanda, sizeof(celdaDemanda), "%d %s", demanda[i], demanda[i] == 1 ? "credito" : "creditos");
            celdaDemanda[18] = '\0';
            printf("%-3d  %-24s  %-60s  %-25s  %-18s\n", id[i], celdaNombre, celdaRecurso, celdaTiempo, celdaDemanda);
        }
    }
    printf(LINEAT);

    printf("\nDatos del cliente\n");
    printf(LINEAC);
    printf("%-3s  %-24s  %-12s  %-14s  %-34s\n", "ID", "Cliente", "Celular", "Cedula/RUC", "Correo");
    printf(LINEAC);
    for (int i = n; i < contPlanes; i++){
        if (estado[i] == est){
            printf("%-3d  %-24.24s  %-12s  %-14s  %-34.34s\n", id[i], cliente[i], celular[i], cedula[i], correo[i]);
        }
    }
    printf(LINEAC);

    printf("\nDatos del credito (tasa de interes anual: 15.2%%)\n");
    printf(LINEAK);
    printf("%-3s  %-24s  %-24s  %-10s  %16s  %16s\n", "ID", "Concesionario", "Aseguradora", "Plazo", "Cuota mensual", "Total a pagar");
    printf(LINEAK);
    for (int i = n; i < contPlanes; i++){
        if (estado[i] == est){
            float capital = 0;
            sscanf(nomRecurso[i], "%f", &capital);
            double tasa = 0.152 / 12;
            double factor = 1;
            for (int k = 0; k < plazo[i]; k++){
                factor *= 1 + tasa;
            }
            double cuota = capital * tasa * factor / (factor - 1);
            char celdaPlazo[20];
            snprintf(celdaPlazo, sizeof(celdaPlazo), "%d %s", plazo[i], plazo[i] == 1 ? "mes" : "meses");
            printf("%-3d  %-24.24s  %-24.24s  %-10s  %16.2f  %16.2f\n", id[i], concesionario[i],
                   aseguradora[i][0] == '\0' ? "Sin aseguradora" : aseguradora[i], celdaPlazo, cuota, cuota * plazo[i]);
        }
    }
    printf(LINEAK);
}

int buscarPlan(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]){
    int activos = 0;
    for (int i = 0; i < contPlanes; i++){
        if (estado[i] == 0){
            activos++;
        }
    }
    if (contPlanes == 0 || activos == 0){
        printf("Error: no hay planes de credito activos registrados\n\n");
        return -1;
    }
    int opc = validarEnteroRango("Seleccione el metodo de busqueda 1.ID/2.Nombre: ", 1, 2);
    int indice = -1;
    if (opc == 1){
        int idsDisp[10], nDisp = 0, primero = 1;
        for (int i = 0; i < contPlanes; i++){
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
        printf("\n\n");
        int busqId, validoId;
        do{
            validoId = 0;
            busqId = validarEnteroRango("Ingrese el ID del plan de credito: ", 0, contPlanes - 1);
            for (int i = 0; i < contPlanes; i++){
                if (estado[i] == 0 && id[i] == busqId){
                    indice = i;
                    validoId = 1;
                    break;
                }
            }
            if (!validoId){
                printf("Error: el ID ingresado no esta disponible\n\n");
            }
        } while (!validoId);
    }else{
        char nombre[50];
        leerNombre("Ingrese el nombre del plan de credito: ", nombre, 50);
        for (int i = 0; i < contPlanes; i++){
            if (estado[i] == 0 && strcasecmp(nombres[i], nombre) == 0){
                indice = i;
                break;
            }
        }
    }
    if (indice == -1){
        printf("No se encontro ningun plan de credito activo con ese dato\n\n");
    }else{
        mostrarPlanes(id, nombres, nomRecurso, tiempo, demanda, estado, 0, indice, indice + 1, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
    }
    return indice;
}

void editarPlan(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]){
    int pos = buscarPlan(id, nombres, nomRecurso, tiempo, demanda, estado, contPlanes, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
    if (pos == -1){
        return;
    }
    printf("\nSeleccione el dato a editar:\n");
    printf("   1. Nombre\n");
    printf("   2. Recursos\n");
    printf("   3. Tiempo\n");
    printf("   4. Demanda\n");
    printf("   5. Concesionario\n");
    printf("   6. Aseguradora\n");
    printf("   7. Plazo\n");
    printf("   8. Nombre del cliente\n");
    printf("   9. Celular\n");
    printf("  10. Cedula/RUC\n");
    printf("  11. Correo electronico\n\n");
    int opc = validarEnteroRango("Opcion: ", 1, 11);
    switch (opc){
    case 1:{
        char activos[10][50];
        int nActivos = 0;
        int idxEnActivos = -1;
        for (int i = 0; i < contPlanes; i++){
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
            snprintf(nomRecurso[pos], 80, "%d capital, 1 asesor, 1 analista, 1 abogado, 1 gestor", (int)cap);
        }else{
            snprintf(nomRecurso[pos], 80, "%.2f capital, 1 asesor, 1 analista, 1 abogado, 1 gestor", cap);
        }
        break;
    }
    case 3:
        tiempo[pos] = validarFloatRango("Nuevas horas de aprobacion y entrega por credito (horas): ", 0.01, 1000);
        break;
    case 4:{
        int d = leerDemanda("Nueva cantidad de solicitudes al mes ", demanda, estado, contPlanes, pos);
        if (d == -1){
            printf("No se modifico la demanda\n\n");
            return;
        }
        demanda[pos] = d;
        break;
    }
    case 5:
        leerNombre("Nuevo concesionario: ", concesionario[pos], 50);
        break;
    case 6:{
        int op = validarEnteroRango("Contrato la aseguradora? 1.Si/2.No: ", 1, 2);
        if (op == 1){
            leerNombre("Nombre de la aseguradora: ", aseguradora[pos], 50);
        }else{
            aseguradora[pos][0] = '\0';
        }
        break;
    }
    case 7:
        printf("La tasa de interes es de 15.2%% anual\n\n");
        plazo[pos] = validarEnteroRango("Nuevo plazo en meses (1 a 120): ", 1, 120);
        break;
    case 8:
        leerNombre("Nuevo nombre del cliente: ", cliente[pos], 50);
        break;
    case 9:
        leerDigitos("Nuevo numero de celular: ", celular[pos], 10, 10, "09", "", "Error: el celular debe tener 10 digitos y empezar con 09");
        break;
    case 10:
        leerDigitos("Nueva cedula/RUC: ", cedula[pos], 10, 13, "", "001", "Error: la cedula debe tener 10 digitos o el RUC 13 digitos terminado en 001");
        break;
    case 11:
        leerCorreo("Nuevo correo electronico: ", correo[pos]);
        break;
    }
    printf("\nPlan de credito editado correctamente:\n\n");
    mostrarPlanes(id, nombres, nomRecurso, tiempo, demanda, estado, 0, pos, pos + 1, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
}

void cambiarEstadoPlan(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]){
    if (contPlanes == 0){
        printf("Error: no hay planes de credito registrados\n\n");
        return;
    }

    int activos = 0, inactivos = 0;
    for (int i = 0; i < contPlanes; i++){
        if (estado[i] == 0){
            activos++;
        }else if (estado[i] == 1){
            inactivos++;
        }
    }

    printf("\nSeleccione la accion:\n");
    printf("   1. Deshabilitar plan de credito\n");
    printf("   2. Habilitar plan de credito\n\n");
    int accion = validarEnteroRango("Opcion: ", 1, 2);

    int estadoBuscado = (accion == 1) ? 0 : 1;
    int cantDisponibles = (accion == 1) ? activos : inactivos;

    if (cantDisponibles == 0){
        if (accion == 1){
            printf("Error: no hay planes de credito activos para deshabilitar\n\n");
        }else{
            printf("Error: no hay planes de credito inactivos para habilitar\n\n");
        }
        return;
    }

    int cupoActual = cupoDisponible(demanda, estado, contPlanes, -1);
    if (cupoActual < 0){
        cupoActual = 0;
    }

    if (accion == 2){
        int caben = 0;
        for (int i = 0; i < contPlanes; i++){
            if (estado[i] == 1 && demanda[i] <= cupoActual){
                caben++;
            }
        }
        if (caben == 0){
            printf("Ya no se pueden realizar mas creditos\n");
            printf("(ningun plan deshabilitado cabe en el cupo disponible: %d %s)\n\n", cupoActual, cupoActual == 1 ? "credito" : "creditos");
            return;
        }
        printf("\nPlanes de credito deshabilitados:\n\n");
        mostrarPlanes(id, nombres, nomRecurso, tiempo, demanda, estado, 1, 0, contPlanes, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
        printf("Cupo disponible actual: %d %s\n\n", cupoActual, cupoActual == 1 ? "credito" : "creditos");
    }

    int opc = validarEnteroRango("Seleccione el metodo de busqueda 1.ID/2.Nombre: ", 1, 2);
    int indice = -1;

    if (opc == 1){
        int primero = 1;
        printf("IDs disponibles: ");
        for (int i = 0; i < contPlanes; i++){
            if (estado[i] == estadoBuscado && (accion == 1 || demanda[i] <= cupoActual)){
                if (!primero){
                    printf(", ");
                }
                printf("%d", id[i]);
                primero = 0;
            }
        }
        printf("\n\n");

        int busqId, validoId;
        do{
            validoId = 0;
            busqId = validarEnteroRango("Ingrese el ID del plan de credito: ", 0, contPlanes - 1);
            for (int i = 0; i < contPlanes; i++){
                if (estado[i] == estadoBuscado && id[i] == busqId && (accion == 1 || demanda[i] <= cupoActual)){
                    indice = i;
                    validoId = 1;
                    break;
                }
            }
            if (!validoId){
                printf("Error: el ID ingresado no esta disponible para esta accion\n\n");
            }
        } while (!validoId);
    }else{
        char nombre[50];
        leerNombre("Ingrese el nombre del plan de credito: ", nombre, 50);
        for (int i = 0; i < contPlanes; i++){
            if (estado[i] == estadoBuscado && strcasecmp(nombres[i], nombre) == 0){
                indice = i;
                break;
            }
        }
        if (indice == -1){
            printf("No se encontro ningun plan de credito con ese nombre en ese estado\n\n");
            return;
        }
    }

    if (accion == 1){
        int conf = validarEnteroRango("Desea deshabilitar el plan de credito? 1.Si/2.No: ", 1, 2);
        if (conf == 1){
            estado[indice] = 1;
            int cupoNuevo = cupoDisponible(demanda, estado, contPlanes, -1);
            printf("El plan de credito con el ID: %d (%s) esta deshabilitado\n\n", id[indice], nombres[indice]);
            printf("Se liberaron %d creditos del cupo mensual\n\n", demanda[indice]);
            printf("El asesor, analista, abogado y gestor solo pueden realizar %d creditos mas\n\n", cupoNuevo);
            printf("Para volver a habilitar este plan se necesitan %d creditos libres en el cupo\n\n", demanda[indice]);
        }
    }else{
        int cupo = cupoDisponible(demanda, estado, contPlanes, -1);
        if (demanda[indice] > cupo){
            printf("Ya no se pueden realizar mas creditos\n");
            printf("(el plan necesita %d creditos y el cupo disponible es %d)\n\n", demanda[indice], cupo < 0 ? 0 : cupo);
            return;
        }
        int conf = validarEnteroRango("Desea habilitar el plan de credito? 1.Si/2.No: ", 1, 2);
        if (conf == 1){
            estado[indice] = 0;
            printf("El plan de credito con el ID: %d (%s) esta habilitado\n\n", id[indice], nombres[indice]);
            printf("El asesor, analista, abogado y gestor solo pueden realizar %d creditos mas\n\n", cupoDisponible(demanda, estado, contPlanes, -1));
        }
    }
}

void calcularProduccion(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]){
    float tiempoTotal = 0, capitalTotal = 0, tiempoDisp, capitalDisp;
    int activos = 0, creditosTotal = 0;
    for (int i = 0; i < contPlanes; i++){
        if (estado[i] == 0){
            float capPlan = 0;
            sscanf(nomRecurso[i], "%f", &capPlan);
            tiempoTotal += tiempo[i] * demanda[i];
            capitalTotal += capPlan * demanda[i];
            creditosTotal += demanda[i];
            activos++;
        }
    }
    if (activos == 0){
        printf("Error: no hay planes de credito activos registrados\n\n");
        return;
    }
    tiempoDisp = validarFloatRango("Ingrese el tiempo disponible (horas): ", 0, 100000000);
    capitalDisp = validarFloatRango("Ingrese el capital disponible: ", 0, 1000000000);
    int hayAsesor = validarEnteroRango("Hay asesor disponible? 1.Si/2.No: ", 1, 2);
    int hayAnalista = validarEnteroRango("Hay analista disponible? 1.Si/2.No: ", 1, 2);
    int hayAbogado = validarEnteroRango("Hay abogado disponible? 1.Si/2.No: ", 1, 2);
    int hayGestor = validarEnteroRango("Hay gestor disponible? 1.Si/2.No: ", 1, 2);
    int cumple = (tiempoTotal <= tiempoDisp && capitalTotal <= capitalDisp && creditosTotal <= 200 &&
                  hayAsesor == 1 && hayAnalista == 1 && hayAbogado == 1 && hayGestor == 1);

    printf("\n" DOBLE);
    printf("   EVOLUTH S.A. - EVALUACION DE LA PRODUCCION\n");
    printf("   RESULTADO: %s\n", cumple ? "PUEDE CUMPLIR con la demanda" : "NO PUEDE CUMPLIR con la demanda");
    printf(DOBLE "\n");
    mostrarPlanes(id, nombres, nomRecurso, tiempo, demanda, estado, 0, 0, contPlanes, concesionario, aseguradora, plazo, cliente, celular, cedula, correo);
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
    sprintf(a, "%d", creditosTotal);
    sprintf(c, "%d", creditosTotal <= 200 ? 200 - creditosTotal : creditosTotal - 200);
    printf("%-9s %16s %16s %16s  %-8s\n", "Creditos", a, "200", c, creditosTotal <= 200 ? "Sobrante" : "Faltante");
    printf("%-9s %16s %16s %16s  %-8s\n", "Asesor", "1", hayAsesor == 1 ? "1" : "0", "-", hayAsesor == 1 ? "Si" : "No");
    printf("%-9s %16s %16s %16s  %-8s\n", "Analista", "1", hayAnalista == 1 ? "1" : "0", "-", hayAnalista == 1 ? "Si" : "No");
    printf("%-9s %16s %16s %16s  %-8s\n", "Abogado", "1", hayAbogado == 1 ? "1" : "0", "-", hayAbogado == 1 ? "Si" : "No");
    printf("%-9s %16s %16s %16s  %-8s\n", "Gestor", "1", hayGestor == 1 ? "1" : "0", "-", hayGestor == 1 ? "Si" : "No");
    printf("------------------------------------------------------------------------\n");
}
