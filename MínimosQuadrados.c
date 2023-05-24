/*
Erick Miranda Viana - 211857
Leonardo Kuntz Oliveira - 222831
Tiago Tavares de Lima Gon�alves - 222566

Um programa capaz de encontrar um polin�mio p(x) que se ajuste a um conjunto de pontos
tabelados (x e f(x)) de uma fun��o desconhecida.
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main () {
int i, j, n, f;
float soma;
char c;
	
//Usando Vetores
float *x = NULL; //x
float *y = NULL; //f(x)
float *sx = NULL; //Somat�ria
float *csx = NULL; //C�pia de "sx"
float *ccsx = NULL;
float *cccsx = NULL;
float *sy = NULL;
float *csy = NULL;
float *ccsy = NULL;
float *cccsy = NULL;
float *p = NULL; //Piv�
float *a = NULL;
	
	do {
		
		//Obter o tamanho da tabela
		do {
			system ("cls");
			printf ("Quantidade de colunas na tabela: ");
			scanf ("%i", &n);
		}	while (n < 1);
	
		//Aloca��o
		x = (float *)malloc(n * sizeof(float));
		y = (float *)malloc(n * sizeof(float));
		sx = (float *)malloc(5 * sizeof(float));
		csx = (float *)malloc(3 * sizeof(float));
		ccsx = (float *)malloc(3 * sizeof(float));
		cccsx = (float *)malloc(3 * sizeof(float));
		sy = (float *)malloc(3 * sizeof(float));
		csy = (float *)malloc(1 * sizeof(float));
		ccsy = (float *)malloc(1 * sizeof(float));
		cccsy = (float *)malloc(1 * sizeof(float));
		p = (float *)malloc(3 * sizeof(float));
		a = (float *)malloc(3 * sizeof(float));
		
		//Tabela inicial
		for (i = 0; i < n; i++) {
			
			printf ("\nx%i: ", (i + 1));
			fflush (stdin);
			scanf ("%f", (x + i));
			
			printf ("f(x%i): ", (i + 1));
			fflush (stdin);
			scanf ("%f", (y + i));
		}
		
		//Somat�ria
		for (i = 0; i < 5; i++) {
		soma = 0;
			for (j = 0; j < n; j++) {
				soma = soma + pow (*(x + j), i);
			}
		*(sx + i) = soma; //Cria��o de um novo vetor com os valores obtidos pelas somat�rias
		}
		
		//Somat�ria do produto y*x^i
		for (i = 0; i < 3; i++) {
		soma = 0;
			for (j = 0; j < n; j++) {
				soma = soma + (*(y + j) * pow (*(x + j), i));
			}
		*(sy + i) = soma; //Cria��o de um novo vetor com os valores obtidos pelas somat�rias
		}
	
		do {
		printf ("\nFamilia a qual o p(x) pertence (1/2): ");
		fflush (stdin);
		scanf ("%i", &f);
		}	while (f < 1 || f > 2);
		
		*p = *(sx + 1)/ *sx; //Primeiro piv�
		
		
			*(p + 1) = *(sx + 2)/ *sx; //Segundo piv�
			
			for (i = 0; i < 3; i++) {
				*(csx + i) = *(sx + 1 + i) - (*(sx + i) * *(p)); //Linha 2 (x)
				*(ccsx + i) = *(sx + 2 + i) - (*(sx + i) * *(p + 1)); //Linha 3 (x)
			}
			
			*(p + 2) = *(ccsx + 1)/ *(csx + 1); //Terceiro piv�
			
			for (i = 0; i < 3; i++) {
				*(cccsx + i) = *(ccsx + i) - (*(csx + i) * *(p + 2)); //Nova linha 3 (x)
			}
		
			*csy = *(sy + 1) - (*sy * (*p)); //y
			
			*ccsy = *(sy + 2) - (*sy * *(p + 1)); //y * x^1
			
			*cccsy = *ccsy - (*csy * *(p + 2)); //y * x^2
			
		//Caso para par�bolas	
		if (f == 2) {	
			*(a + 2) = *cccsy / *(cccsx + 2); //A2
			printf ("\nA2: %f", *(a + 2));
			
			*(a + 1) = (*csy - *(csx + 2) * *(a + 2))/ (*(csx + 1)); //A1
			printf ("\nA1: %f", *(a + 1));
			
			*a = (*sy - ( *(sx + 2) * *(a + 2) ) -  *(sx + 1) * *(a + 1) )/ *sx; //A0
			printf ("\nA0: %f", *a);
		}
		
		//Caso para retas
		if (f == 1) {
			*(a + 1) = *csy / *(csx + 1); //A1
			printf ("\nA1: %f", *(a + 1));
			
			*a = (*sy - *(sx + 1) * *(a + 1)) / *sx; //A0
			printf ("\nA0: %f", *a);
		}
	
		//Caso o usu�rio queira, executar o programa de novo
		printf ("\n\nInserir nova funcao? (S/N)");
		fflush (stdin);	
		scanf ("%c", &c);
		
		if (c == 's' || c == 'S')
			system ("cls");
	}	while (c == 's' || c == 'S');
	
}	
