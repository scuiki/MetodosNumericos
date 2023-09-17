/*
Erick Miranda Viana - 211857
Leonardo Kuntz Oliveira - 222831
Tiago Tavares de Lima Gon�alves - 222566

Um programa que descobre os zeros de equa��es atrav�s do m�todo da dicotomia ou bissec��o,
dada uma equa��o de qualquer grau, um intervalo e um erro. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Prot�tipo das fun��es
//Criar uma fun��o para calcular a DICOTOMIA
float dicotomia (float a, float b, int cont, float k);
float CalculaValorK(float a, float b, float erro);
float funcaoX(float ponto);
void ImprimirCabecalhoTabela();
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB);

//Vari�vel global pois est� presente em m�ltiplas fun��es
int grau;
//Criar uma vari�vel do tipo ponteiro
float *multi = NULL;

main () {
int i;
float a, b, e, k;

	//Receber o grau da fun��o (entre 2 a 6)
	do {
		system ("cls");
    	printf("Informe o grau da funcao (2 a 6): ");
    	fflush (stdin);
    	scanf("%i", &grau);
	}	while (grau < 2 || grau > 6);
	
//Aloca��o do tamanho solicitado (grau indicado)
multi = (float *)malloc(grau * sizeof(float));

	//Receber os multiplicadores
	//aX^0 + bX^1 + cX^2 ---> �ndice do vetor igual ao expoente
    for (i = grau; i >= 0; i--) {
        printf ("\nInforme o fator multiplicador de x^%i: ", i);
        scanf ("%f", (multi + i));
    }

    //Exibindo a fun��o recebida
    printf ("\nA funcao recebida foi: ");
    for (i = grau; i >= 0; i--) {
        if (i==0)
            printf ("%.2f = 0", *(multi + i), i);
        else
            printf ("%.2fx^%i + ", *(multi + i), i);
    }
    printf ("\n\n");
    system ("pause");
    printf ("\n\n");

    printf ("Resultado: %f %f %f\n", funcaoX(0), funcaoX(1), funcaoX(2));
    system ("pause");
    
    do {
    //Receber os valores de "a"
    printf ("\na = ");
    fflush (stdin);
    scanf ("%f", &a);
    
    //Receber os valores de "b"
    printf ("\nb = ");
    fflush (stdin);
    scanf ("%f", &b);
    
    //Receber os valores de "erro"
    printf ("\nerro = ");
    fflush (stdin);
    scanf ("%f", &e);
    
    //Prosseguir apenas se no intervalo "[A, B]" existir zero de fun��o
	}	while ((funcaoX(a) * funcaoX(b)) > 0);

	//Encontrar o valor de K
	//K = CalculaValorK(A, B, Erro)
	k = CalculaValorK (a, b, e);

    //Exibindo o cabe�alho
    ImprimirCabecalhoTabela();

	//Dicotomia
	dicotomia (a, b, 1, k);
	
	//Liberando a mem�ria
	free(multi);
	
    system("pause");
}


//Realiza o c�lculo do k (n�mero de passo)
float CalculaValorK (float a, float b, float erro)
{
    float fValorK;

    //Realizar o c�lculo do valor do K
    fValorK = (log10(b - a) - log10(erro))/(log10(2));


    return ceil(fValorK);
}

//Fun��o que realiza o c�lculo em um determinado ponto
float funcaoX(float ponto) {
int i;
float resultado = 0;

    for (i = 0; i <= grau; i++) {
        resultado = resultado + *(multi + i) * pow(ponto, i);
    }

return resultado;
}

//Implementando a dicotomia
float dicotomia (float a, float b, int cont, float k) {
float m, fa, fb, fm;

//Cria��o de duas vari�veis do tipo "char" para mostrar se o resultado da multiplica��o de fun��es � positivo ou negativo
char fma, fmb;

//Atribuindo o valor da fun��o � vari�veis para facilitar o desenvolvimento do programa
fa = funcaoX(a);
fb = funcaoX(b);

	//Executar "k" itera��es
	while (cont <= k) {
	//Encontrando o ponto m�dio
	m = (a + b)/2;
	
	//Atribuindo o valor da fun��o � vari�veis para facilitar o desenvolvimento do programa	
	fm = funcaoX(m);

		//L�gica para mostrar na tabela se o sinal da multiplica��o de "f(a) * f(m)" � positivo ou negativo
		if ((fa * fm) < 0)
			fma = '-';
		else fma = '+';
		//Mesma l�gica mostrada anteriormente, mas para "f(b) * f(m)"
		if ((fb * fm) < 0)
			fmb = '-';
		else fmb = '+';

		//Exibindo os valores na tabela
	    ImprimirTabela(cont, a, b, m, fa, fb, fm, fma, fmb);
	    
	    //L�gica da dicotomia
		if ((fa * fm) < 0) {
			b = m;
			fb = funcaoX(b);
		}	else if ((fb * fm) < 0) {
				a = m;
				fa = funcaoX(a);
			}
			
	//Acrescentando 1 � vari�vel contadora		
	cont++;
	}
}

//Imprimindo o cabe�alho
void ImprimirCabecalhoTabela () {
    //Impress�o do cabe�alho
    printf("I |  a\t|  b\t|  m\t|  f(a)\t|  f(b)\t|  f(m)\t| fa*fm\t| fm*fb\t|\n");
    printf("--+-----+-------+-------+-------+-------+-------+-------+-------+\n");
}

//Imprimindo a tabela com os valores
void ImprimirTabela (int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB) {
    printf("%i|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%c\t|%c\t|\n", iteracao, a, b, m, fA, fB, fM, fAfM, fMfB);
}
