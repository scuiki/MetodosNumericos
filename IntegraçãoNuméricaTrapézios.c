/*
Erick Miranda Viana - 211857
Leonardo Kuntz Oliveira - 222831
Tiago Tavares de Lima Gon�alves - 222566

Um programa capaz de calcular a integral de um polin�mio (exemplo: x� - 2x� +3) em um dado
intervalo (exemplo 0 a 2).
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Prot�tipo das fun��es
float funcao (float valor);
float altura (float a, float b, float n);

//Ponteiro
float *multi = NULL;

//Grau
int grau;

main () {
int i;
float a, b, h, n, soma, p, integral;
char s;	

	do {
	//Limpar o conte�do das vari�veis	
	integral = 0;
	soma = 0;	
		//Receber o grau da fun��o entre 2 a 10
		do {
			system ("cls");
		   	printf ("Informe o grau da funcao (2 a 10): ");
		   	fflush (stdin);
		   	scanf ("%i", &grau);
		}	while (grau < 2 || grau > 10);
		
		//Aloca��o do tamanho solicitado (grau indicado)
		multi = (float *)malloc(grau * sizeof(float));
			
		
		//Receber os multiplicadores. Dica: Armazenar os valores em um vetor.
		//aX^0 + bX^1 + cX^2 --->Indice do vetor igual ao expoente
		for (i = 0; i <= grau; i++)	{
		    printf ("Informe o fator multiplicador de x^%i: ", i);
		    fflush (stdin);
		    scanf ("%f", (multi + i));
		}
		
		system ("cls");
		//Exibindo a fun��o recebida
		printf("A funcao recebida foi: ");
		for (i = 0; i <= grau; i++)	{
		    printf ("%.2fx^%i", *(multi + i), i);
		        
		    if (i < grau)
		        printf (" + ");
		    else
		        printf (" = 0\n");
		}
		    
		//Limites
		printf ("\nLimite superior: ");
		fflush (stdin);
		scanf ("%f", &b);
		printf ("Limite inferior: ");
		fflush (stdin);
		scanf ("%f", &a);
		    
		//Subintervalos
		printf ("Numero de subintervalos: ");
		fflush (stdin);
		scanf ("%f", &n);
		    
		//Altura
		h = (b - a)/n;
		printf ("\nh = %f\n", h);
		    
		//Somat�ria
		for (i = 1; i <= n - 1; i++) {
		  	p = a + (h * i); //"p" � a progress�o de subintervalos
		    	
		   	soma = soma + (2 * funcao (p));
		}
			
		//Obtendo a integral
		integral = (h/2) * (funcao (a) + funcao (b) + soma);
		
		//Resultado
		printf ("\nIntegral: %f\n", integral);
		
		//Continua��o do programa
		printf ("\nContinuar? (S/N)\n");
		fflush (stdin);
		scanf ("%c", &s);
	}	while (s == 's' || s == 'S');
    
}


//Fun��o que realiza o c�lculo em um determinado ponto
float funcao (float valor) {
    int i;
    float resultado = 0;

    for(i = 0; i <= grau; i++)
    {
        resultado = resultado + *(multi + i)*pow(valor, i);
    }

return resultado;
}
