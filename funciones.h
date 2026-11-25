#include <stdio.h>

#define R10 "----------"
#define E10 "=========="
#define LINEAT R10 R10 R10 R10 R10 R10 R10 R10 R10 R10 R10 R10 R10 "--------\n"
#define LINEAC R10 R10 R10 R10 R10 R10 R10 R10 R10 "-----\n"
#define LINEAK R10 R10 R10 R10 R10 R10 R10 R10 R10 R10 "---\n"
#define LINEA  R10 R10 R10 R10 R10 R10 "\n"
#define DOBLE  E10 E10 E10 E10 E10 E10 "\n"

void limpiarEspacios(char *cadena);
float validarFloatRango(const char *pregunta, float a, float b);
int validarEnteroRango(const char *pregunta, int a, int b);
void leercadena(char *cadena, int n);
void leerNombre(const char *pregunta, char *cadena, int n);
void leerNombreUnico(const char *pregunta, char *destino, int n, char lista[][50], int total, int excluirIdx);
void leerDigitos(const char *pregunta, char *destino, int largo1, int largo2, const char *inicio, const char *terminacion, const char *msgError);
void leerCorreo(const char *pregunta, char *destino);
int cupoDisponible(int *demanda, int *estado, int contPlanes, int excluir);
int leerDemanda(const char *pregunta, int *demanda, int *estado, int contPlanes, int excluir);

void registrarPlan(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int *contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]);
void mostrarPlanes(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int est, int n, int contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]);
int buscarPlan(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]);
void editarPlan(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]);
void cambiarEstadoPlan(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]);
void calcularProduccion(int *id, char nombres[][50], char nomRecurso[][80], float *tiempo, int *demanda, int *estado, int contPlanes, char concesionario[][50], char aseguradora[][50], int *plazo, char cliente[][50], char celular[][11], char cedula[][14], char correo[][60]);
