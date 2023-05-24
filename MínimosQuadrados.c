/*
Erick Miranda Viana - 211857
Leonardo Kuntz Oliveira - 222831
Tiago Tavares de Lima Gonçalves - 222566

Um programa capaz de encontrar um polinômio p(x) que se ajuste a um conjunto de pontos
tabelados (x e f(x)) de uma função desconhecida.

Obs.: Fotos para melhor entendimento do código podem ser encontradas em: https://github.com/scuiki/MetodosNumericos/wiki
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
float *sx = NULL; //Somatória
float *csx = NULL; //Cópia de "sx"
float *ccsx = NULL;
float *cccsx = NULL;
float *sy = NULL;
float *csy = NULL;
float *ccsy = NULL;
float *cccsy = NULL;
float *p = NULL; //Pivô
float *a = NULL;
	
	do {
		
		//Obter o tamanho da tabela
		do {
			system ("cls");
			printf ("Quantidade de colunas na tabela: ");
			scanf ("%i", &n);
		}	while (n < 1);
	
		//Alocação
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
		
		//Somatória
		for (i = 0; i < 5; i++) {
		soma = 0;
			for (j = 0; j < n; j++) {
				soma = soma + pow (*(x + j), i);
			}
		*(sx + i) = soma; //Criação de um novo vetor com os valores obtidos pelas somatórias
		}
		
		//Somatória do produto y*x^i
		for (i = 0; i < 3; i++) {
		soma = 0;
			for (j = 0; j < n; j++) {
				soma = soma + (*(y + j) * pow (*(x + j), i));
			}
		*(sy + i) = soma; //Criação de um novo vetor com os valores obtidos pelas somatórias
		}
		
		//Tabela
		for (i = 0; i < 3; i++) {
			printf ("\n|");
			for (j = 0 + i; j < 3 + i; j++) {
				printf (" %.3f |", *(sx + j));
			}
			printf (" A%i ", i);
			printf ("| %.3f |", *(sy + i));
		}
	
		do {
		printf ("\n\nFamilia a qual o p(x) pertence (1/2): ");
		fflush (stdin);
		scanf ("%i", &f);
		}	while (f < 1 || f > 2);
		
		*p = *(sx + 1)/ *sx; //Primeiro pivô
		
		
			*(p + 1) = *(sx + 2)/ *sx; //Segundo pivô
			
			for (i = 0; i < 3; i++) {
				*(csx + i) = *(sx + 1 + i) - (*(sx + i) * *(p)); //Linha 2 (x)
				*(ccsx + i) = *(sx + 2 + i) - (*(sx + i) * *(p + 1)); //Linha 3 (x)
			}
			
			*(p + 2) = *(ccsx + 1)/ *(csx + 1); //Terceiro pivô
			
			for (i = 0; i < 3; i++) {
				*(cccsx + i) = *(ccsx + i) - (*(csx + i) * *(p + 2)); //Nova linha 3 (x)
			}
		
			*csy = *(sy + 1) - (*sy * (*p)); //y
			
			*ccsy = *(sy + 2) - (*sy * *(p + 1)); //y * x^1
			
			*cccsy = *ccsy - (*csy * *(p + 2)); //y * x^2
			
		//Caso para parábolas	
		if (f == 2) {	
			
			//Tabela
			for (i = 0; i < 3; i++) {
			printf ("\n");
				for (j = 0; j < 3; j++) {
					if (i == 0) {
						printf ("| %.3f ", *(sx + j));
					}
					if (i == 1) {
						printf ("| %.3f ", *(csx + j));
					}
					if (i == 2) {
						printf ("| %.3f ", *(cccsx + j));
					}
				}
				printf ("| A%i ", i);
				if (i == 0) {
					printf ("| %.3f |", *sy);
				}
				if (i == 1) {
					printf ("| %.3f |", *csy);
				}
				if (i == 2) {
					printf ("| %.3f |", *cccsy);
				}	
			}
		
			*(a + 2) = *cccsy / *(cccsx + 2); //A2
			printf ("\n\nA2: %f", *(a + 2));
			
			*(a + 1) = (*csy - *(csx + 2) * *(a + 2))/ (*(csx + 1)); //A1
			printf ("\nA1: %f", *(a + 1));
			
			*a = (*sy - ( *(sx + 2) * *(a + 2) ) -  *(sx + 1) * *(a + 1) )/ *sx; //A0
			printf ("\nA0: %f", *a);
			printf ("\n\n%fx^2 + %fx^1 + %fx^0", *(a + 2), *(a + 1), *a);
		}
		
		//Caso para retas
		if (f == 1) {
			
			//Tabela
			for (i = 0; i < 2; i++) {
				printf ("\n");
				for (j = 0; j < 2; j++) {
					if (i == 0) {
						printf ("| %.3f ", *(sx + j));
					}
					if (i == 1) {
						printf ("| %.3f ", *(csx + j));
					}
				}
				printf ("| A%i ", i);
				if (i == 0) {
					printf ("| %.3f |", *sy);
				}
				if (i == 1) {
					printf ("| %.3f |", *csy);
				}	
			}
			
			*(a + 1) = *csy / *(csx + 1); //A1
			printf ("\n\nA1: %f", *(a + 1));
			
			*a = (*sy - *(sx + 1) * *(a + 1)) / *sx; //A0
			printf ("\nA0: %f", *a);
			printf ("\n\n%fx^1 + %fx^0", *(a + 1), *a);
		}
	
		//Caso o usuário queira, executar o programa de novo
		printf ("\n\nInserir nova funcao? (S/N)");
		fflush (stdin);	
		scanf ("%c", &c);
		
		if (c == 's' || c == 'S')
			system ("cls");
	}	while (c == 's' || c == 'S');
}	
