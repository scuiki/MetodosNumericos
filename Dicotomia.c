/*
Erick Miranda Viana - 211857
Leonardo Kuntz Oliveira - 222831
Tiago Tavares de Lima Gonçalves - 222566

Um programa que descobre os zeros de equações através do método da dicotomia ou bissecção,
dada uma equação de qualquer grau, um intervalo e um erro. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Protótipo das funções
//Criar uma função para calcular a DICOTOMIA
float dicotomia (float a, float b, int cont, float k);
float CalculaValorK(float a, float b, float erro);
float funcaoX(float ponto);
void ImprimirCabecalhoTabela();
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB);

//Variável global pois está presente em múltiplas funções
int grau;
//Criar uma variável do tipo ponteiro
float *multi = NULL;

main () {
int i;
float a, b, e, k;

	//Receber o grau da função (entre 2 a 6)
	do {
		system ("cls");
    	printf("Informe o grau da funcao (2 a 6): ");
    	fflush (stdin);
    	scanf("%i", &grau);
	}	while (grau < 2 || grau > 6);
	
//Alocação do tamanho solicitado (grau indicado)
multi = (float *)malloc(grau * sizeof(float));

	//Receber os multiplicadores
	//aX^0 + bX^1 + cX^2 ---> Índice do vetor igual ao expoente
    for (i = grau; i >= 0; i--) {
        printf ("\nInforme o fator multiplicador de x^%i: ", i);
        scanf ("%f", (multi + i));
    }

    //Exibindo a função recebida
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
    
    //Prosseguir apenas se no intervalo "[A, B]" existir zero de função
	}	while ((funcaoX(a) * funcaoX(b)) > 0);

	//Encontrar o valor de K
	//K = CalculaValorK(A, B, Erro)
	k = CalculaValorK (a, b, e);

    //Exibindo o cabeçalho
    ImprimirCabecalhoTabela();

	//Dicotomia
	dicotomia (a, b, 1, k);
	
	//Liberando a memória
	free(multi);
	
    system("pause");
}


//Realiza o cálculo do k (número de passo)
float CalculaValorK (float a, float b, float erro)
{
    float fValorK;

    //Realizar o cálculo do valor do K
    fValorK = (log10(b - a) - log10(erro))/(log10(2));


    return ceil(fValorK);
}

//Função que realiza o cálculo em um determinado ponto
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

//Criação de duas variáveis do tipo "char" para mostrar se o resultado da multiplicação de funções é positivo ou negativo
char fma, fmb;

//Atribuindo o valor da função à variáveis para facilitar o desenvolvimento do programa
fa = funcaoX(a);
fb = funcaoX(b);

	//Executar "k" iterações
	while (cont <= k) {
	//Encontrando o ponto médio
	m = (a + b)/2;
	
	//Atribuindo o valor da função à variáveis para facilitar o desenvolvimento do programa	
	fm = funcaoX(m);

		//Lógica para mostrar na tabela se o sinal da multiplicação de "f(a) * f(m)" é positivo ou negativo
		if ((fa * fm) < 0)
			fma = '-';
		else fma = '+';
		//Mesma lógica mostrada anteriormente, mas para "f(b) * f(m)"
		if ((fb * fm) < 0)
			fmb = '-';
		else fmb = '+';

		//Exibindo os valores na tabela
	    ImprimirTabela(cont, a, b, m, fa, fb, fm, fma, fmb);
	    
	    //Lógica da dicotomia
		if ((fa * fm) < 0) {
			b = m;
			fb = funcaoX(b);
		}	else if ((fb * fm) < 0) {
				a = m;
				fa = funcaoX(a);
			}
			
	//Acrescentando 1 à variável contadora		
	cont++;
	}
}

//Imprimindo o cabeçalho
void ImprimirCabecalhoTabela () {
    //Impressão do cabeçalho
    printf("I |  a\t|  b\t|  m\t|  f(a)\t|  f(b)\t|  f(m)\t| fa*fm\t| fm*fb\t|\n");
    printf("--+-----+-------+-------+-------+-------+-------+-------+-------+\n");
}

//Imprimindo a tabela com os valores
void ImprimirTabela (int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB) {
    printf("%i|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%c\t|%c\t|\n", iteracao, a, b, m, fA, fB, fM, fAfM, fMfB);
}
