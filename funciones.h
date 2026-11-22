#define funciones_h

#define LINEA  "----------------------------------------------------------------------\n"
#define DOBLE  "======================================================================\n"
#define LINEAT "-----------------------------------------------------------------------------------------------------------------------------\n"

float validarFloatRango(const char *pregunta, float a, float b);
int validarEnteroRango(const char *pregunta, int a, int b);
void leercadena(char *cadena, int n);
void leerNombre(const char *pregunta, char *cadena, int n);
void leerNombreUnico(const char *pregunta, char *destino, int n, char lista[][50], int total, int excluirIdx);
void registrarProducto(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int *contP);
void mostrarProductos(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int n, int contP);
int buscarProducto(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int contP);
void editarProducto(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int contP);
void cambiarEstadoProducto(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int contP);
void calcularProduccion(int *id, char nombres[][50], char nomRecurso[][50], float *tiempo, int *demanda, int *estado, int contP);