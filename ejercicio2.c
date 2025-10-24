#include <stdio.h>
#include <string.h>
#include <ctype.h> //Permite utilizar ispunct()

#define MAX_PALABRA 100

// Función para eliminar signos de puntuación del inicio y final de una palabra
void eliminarSignos(char *palabra) {
    	char *inicio = palabra;
    	char *fin = palabra + strlen(palabra) - 1;

    	// Eliminar puntuación al inicio de la palabra
    	while (*inicio && ispunct((unsigned char)*inicio)) {
        	inicio++; //El puntero apunta a la primera letra de la palabra (ignorando signos)
    	}

   	 // Eliminar puntuación al final de la palabra
    	while (fin >= inicio && ispunct((unsigned char)*fin)) {
        	*fin = '\0';
        	fin--;
    	}

    // Mover palabra sin signo, en caso de haber eliminado el primer caracter
    	if (inicio != palabra) {
        	memmove(palabra, inicio, strlen(inicio) + 1);
    	}
}

int main(int argc, char *argv[]) {
	    if (argc != 4) {
        	fprintf(stderr, "Faltan argumentos. \n Uso correcto: %s <archivo_txt_original> <palabra_buscar> <palabra_reemplazo>\n", argv[0]);
        	return 1;
    	}

    	FILE *txt_original = fopen(argv[1], "r");
    	if (!txt_original) {
        	fprintf(stderr,"Error al abrir el archivo de txt_original \n");
        	return 1;
    	}

    	FILE *txt_reemplazado = fopen("texto_txt_reemplazado.txt", "w");
    	if (!txt_reemplazado) {
        	perror("Error al crear el archivo de salida");
        	fclose(txt_original);
        	return 1;
    	}

    	char palabra[MAX_PALABRA];
    	char palabra_limpia[MAX_PALABRA];
    	char *buscar = argv[2];
    	char *reemplazo = argv[3];

    	// Leer palabra por palabra
    	while (fscanf(txt_original, "%s", palabra) == 1) {
        	strcpy(palabra_limpia, palabra);
        	eliminarSignos(palabra_limpia);

        	// Si la palabra (sin puntuación) coincide con la que se busca, se procede a reemplazar
        	if (strcmp(palabra_limpia, buscar) == 0) {
            	
            	int inicio = 0;
	   	int  fin = strlen(palabra);
            	// Detectar si tenía puntuación al inicio o final
            	while (inicio < fin && ispunct((unsigned char)palabra[inicio])) inicio++;
            	while (fin > 0 && ispunct((unsigned char)palabra[fin - 1])) fin--;

            	// Imprimir respetando los signos de puntuación txt_originales
            	// Parte inicial (puntuación)
            	for (int i = 0; i < inicio; i++) fputc(palabra[i], txt_reemplazado);
            	// Palabra reemplazada
            	fputs(reemplazo, txt_reemplazado);
            	// Parte final (puntuación)
            	for (int i = fin; palabra[i] != '\0'; i++) 
			fputc(palabra[i], txt_reemplazado);
		}
		else {
        	    fputs(palabra, txt_reemplazado);
        }

        fputc(' ', txt_reemplazado); // Separa palabras con espacio
    }

    fclose(txt_original);
    fclose(txt_reemplazado);

    printf("Se ha reemplazado la palabra indicada correctamente. \nEl archivo reemplazado se llama: salida.txt\n");
    return 0;
}

