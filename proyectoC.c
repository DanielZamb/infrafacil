/*
PROYECTO 1 FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - 201820
Daniel Ernesto Zambrano Huertas - 201914912
Juan David Becerra - 201911588 
Juan Pablo Romero - 201730361
*/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//-- Definicion de la estructura para los datos del archivo de entrada y el de salida
typedef struct datos
{
	int tamanio;
	unsigned char *informacion;
} Datos;


//-- Prototipos de las funciones
int readFile(Datos * archivo, char *);
void writeFile(Datos * archivoEnBinario, char *);
void convertirABinario(Datos * archivo, Datos * archivoEnBinario);


//-- Funciones

// Esta funcion se encarga de abrir un datos y leerlo en el vector informacion.
// Retorna el numero de bytes leidos.
// No hay que completar nada en esta funcion.
int readFile(Datos * archivo, char * nombreArchivo)
{
	FILE *file;
	int n;

	file = fopen(nombreArchivo, "rb");

	if (!file)
	{
		printf("No se pudo abrir el archivo para leer: %s\n", nombreArchivo);
        system("PAUSE");
		exit(EXIT_FAILURE);
	}
	fseek(file, 0, SEEK_END);
	n = ftell(file);
	fseek(file, 0, SEEK_SET);

	archivo->tamanio = n;
	archivo->informacion = (unsigned char *)calloc(n, sizeof(unsigned char));

	fread(archivo->informacion, sizeof(unsigned char), n, file);

	fclose(file);

	return n;
}


// Esta funcion se encarga de escribir un datos a partir del vector datos.
// El numero de bytes que se deben escribir viene en el parametro n.
// No hay que completar nada en esta funcion.
void writeFile(Datos * archivoEnOctal, char *nombreArchivo)
{
	FILE *file;

	file = fopen(nombreArchivo, "wb");

	if (!file) {
		printf("No se pudo abrir el archivo para escribir: %s\n", nombreArchivo);
        system("PAUSE");
		exit(EXIT_FAILURE);
	}

	fwrite(archivoEnOctal->informacion, sizeof(char), archivoEnOctal->tamanio, file);

	fclose(file);
}
// Funcion que define en que escribe el k-esimo bit dentro de un arreglo de char A
//k se cuenta de izquierda a derecha por lo que escribir 001 seria setBit(A[], 2)
void SetBit(char *A, int k )
{
      int i = k/8;            // i = array en el indice (use: A[i])
      int pos = k%8;          // pos = posicion del bit en A[i]
      unsigned int flag = 1;   
	  flag =  flag << 7; 	   // flag = 10000000
      flag = flag >> pos;      // flag = 0..010...000   (desplazado a la derecha pos posiciones)
      printf("\nAi: %c, pos: %d, i: %d",A[i],pos,i);
      A[i] = A[i] | flag;      // Poner el bit en la k-th posicion de A[i] 
}

// Esta funcion se encarga de convertir a binario cada uno de los caracteres que se
// encuentran en la estructura datosOct->informacion y asignar los nuevos valores a la estructura datosBin->informacion.
// Deben desarrollar esta funcion en su totalidad.
void convertirABinario(Datos * datosOct, Datos * datosBin)
{
	int tam = datosOct->tamanio; //Cantidad de caracteres que vamos a leer
	unsigned char * caracter = (datosOct->informacion);// Apuntador a los caracteres que estamos leyendo
    printf("\nCaracter:%s",caracter);
	printf("\ntamano:%d",tam);
	int k = 0; // Posicion del bit que estamos escribiendo
	int cantidadBytes=0; // Calculo de cuantos bytes vamos a requerir para escribir en un arreglo de char
	if(((tam*3)/8) % 8 != 0)
	{
		cantidadBytes = ((int)(tam*3)/8) + 1; // Cantidad de bytes necesarios
	}
	else
	{
		cantidadBytes = ((int)(tam*3)/8); // Cantidad de bytes necesarios
	}
	unsigned char * A; 
	printf("\n tamano destino: %d",cantidadBytes);
	A = (char*)calloc(cantidadBytes,sizeof(unsigned char));// Creacion del arreglo de char donde vamos a escribir 
	memset(A,'0',cantidadBytes*sizeof(unsigned char));
	printf("\nArreglo: %s",A);
	char car;
	for(int i = 0; i < tam;i++)
	{
		car = caracter[i]; // Caracter actual que estamos leyendo
		printf("\ncar: %c",car);
		//Para cada uno de los casos se deja en cero las posciones necesarias y se asigna en uno para representar el valor en binario usando 3 bits
		if(car == '0')
		{
			k = k+3; 
		}
		else if(car == '1')
		{
			k= k+2;
			SetBit(A,k);
			k++;
		}
		else if(car == '2')
		{
			k++;
			SetBit(A,k);
			k = k+2;
		}
		else if(car == '3')
		{
			k++;
			SetBit(A,k);
			k++;
			SetBit(A,k);
			k++;
		}
		else if(car == '4')
		{
			SetBit(A,k);
			k=k+3;
		}
		else if(car == '5')
		{
			SetBit(A,k);
			k = k+2;
			SetBit(A,k);
			k++;
		}
		else if(car == '6')
		{
			SetBit(A,k);
			k++;
			SetBit(A,k);
			k = k+2;
		}
		else if(car == '7')
		{
			SetBit(A,k);
			k++;
			SetBit(A,k);
			k++;
			SetBit(A,k);
			k++;
		}

		
	}
	datosBin->informacion = A;//Se asignan las respuestas
	datosBin->tamanio = cantidadBytes;	
}


//-- Funcion main de la aplicacion
// No hay que completar nada en esta funcion.
int main()
{
	// Mensaje inicial
	printf("PROYECTO 1 - INFRATEC (ISIS-1304)");

	// Declaracion de todas las variables necesarias.
	int tamanio;
	int tamanioRepBinario;
	char nombreArchivo[200];
	char nombreArchivoBinario[200];
	Datos * archivoOctal = (Datos *)malloc(sizeof(Datos));
	Datos * archivoEnBinario = (Datos *)malloc(sizeof(Datos));

	printf("\n\nIngrese el nombre del archivo a leer (incluya el formato. i.e. archivo.txt): \n");
	scanf("%s", nombreArchivo);
	tamanio = readFile(archivoOctal, nombreArchivo);
	printf("\nEl tamanio del archivo es de %d bytes\n", tamanio);
	tamanioRepBinario = ((tamanio * 3) / 8) + (((tamanio*3) % 8 == 0)? 0 : 1);
	archivoEnBinario->informacion = (unsigned char *)calloc(tamanioRepBinario, sizeof(unsigned char));
	archivoEnBinario->tamanio = tamanioRepBinario;
	printf("\nIngrese el nombre del archivo para guardar la representacion en octales del archivo origen (incluya el .txt): \n");
	scanf("%s", nombreArchivoBinario);
	printf("\ncall convertir archivo");
	convertirABinario(archivoOctal, archivoEnBinario);
	printf("\nfin convertir archivo");
	writeFile(archivoEnBinario, nombreArchivoBinario);
	printf("\nEl archivo se transformo en su representacion a octal exitosamente!\n\n");
	printf("Revisa el archivo con nombre '%s' para ver el resultado!\n", nombreArchivoBinario);

	// Terminar
	system("PAUSE");
	return 0;
}
