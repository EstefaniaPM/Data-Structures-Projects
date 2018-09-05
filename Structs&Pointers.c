#include <stdio.h>
#include <string.h>
struct alumno
{
	char nombre[40];
	int matricula;
	float promedio;
};
//struct punto2D { int x, y; };
int main(int argc, char const *argv[])
{
	struct alumno arr[3];

	strcpy(arr[0].nombre, "Juanito");
	arr[0].matricula = 3456;
	arr[0].promedio = 99.72;

	strcpy(arr[1].nombre, "Pepito");
	arr[1].matricula = 9999;
	arr[1].promedio = 69.92;

	strcpy(arr[2].nombre, "Fiacro");
	arr[2].matricula = 0000;
	arr[2].promedio = 95.27;

	struct alumno * pts;
	pts = arr;

	strcpy((pts + 2) -> nombre, "Holis");
	(pts + 2) -> matricula = 1111;
	(pts + 2) -> promedio = 90.45;

	printf("El alumno 0 es %s, prom: %.2f, mat: %d \n", pts -> nombre, pts -> promedio, pts -> matricula);
	pts++;
	printf("El alumno 1 es %s, prom: %.2f, mat: %d \n", pts -> nombre, pts -> promedio, pts -> matricula);
	pts++;
	printf("El alumno 2 es %s, prom: %.2f, mat: %d \n", pts -> nombre, pts -> promedio, pts -> matricula);
	pts++;
	printf("El alumno 3 es %s, prom: %.2f, mat: %d \n", pts -> nombre, pts -> promedio, pts -> matricula);
	pts++;

	/*

	int x;
	x = 255;
	char *ptc;
	ptc = (char *)&x;

	printf("%d\n", *ptc);
	ptc++;
	printf("%d\n", *ptc);
	ptc++;
	printf("%d\n", *ptc);
	ptc++;
	printf("%d\n", *ptc);
	ptc++;

	char nombre[20];
	printf("Como te llamas? ");
	fgets(nombre, 20, stdin);
	printf("Hola %s\n", nombre); 

	char *ptc;
	ptc = nombre;

	while(*ptc != '\0')
	{
		printf("%c\n", *ptc);
		ptc++;
	}

	// Dobles apuntadores

	//int** pp = (int**)malloc(sizeof(int*)*n);
	//for()
		//*(pp+i) = (int*)malloc(sizeof(int)*n);	
	*/
	return 0;
}