/*
Erick Miranda Viana - 211857
Leonardo Kuntz Oliveira - 222831
Tiago Tavares de Lima Gonçalves - 222566

Um programa capaz de descobrir um valor não tabelado de uma função desconhecida através de um
conjunto de medidas de x e f(x). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main () {
int pontos, grau, cont, i, j;
float valorCalcular, Li, Px;
char resp;

//Usando Vetores
float *x = NULL;
float *y = NULL;


    printf ("Digite o grau da funcao que deseja obter: ");
    scanf ("%i", &grau);

//Obtendo o número de pontos a partir do grau indicado
pontos = grau + 1;
    
    //Alocação do tamanho solicitado
    x = (float *)malloc(pontos * sizeof(float));
    y = (float *)malloc(pontos * sizeof(float));

    for(cont = 0; cont < pontos; cont++) {
	//x	
        printf ("\nx[%d] = ", cont);
        fflush (stdin);
        scanf ("%f", (x + cont));
    //f(x)
    	printf ("\ny[%d] = ", cont);
    	fflush (stdin);
    	scanf ("%f", (y + cont));
    }
    
    do {
    	//Definindo "Px" como 0 (necessário caso o usuário queira calcular vários valores)
    	Px = 0;
    	
    	//Pedindo o valor de "x" que será calculado
        printf ("\nDigite o valor que deseja calcular: ");
        scanf ("%f", &valorCalcular);
        
        //Início do método de Lagrange
        for (i = 0; i < pontos; i++) {
        //Definir "Li" como 1 por conta da produtória
        Li = 1;
        
        //"i" corresponde à linha e "j" à coluna
        	for (j = 0; j < pontos; j++) {
        		if (i != j) {
        			//Cálculo do "Li" (contanto que "i" seja diferente de "j"
        			//Acessando os valores do ponteiro através de *(x + i)
        			Li = Li * (valorCalcular - *(x + j))/(*(x + i) - *(x + j)); 
				}
			}
			//Cálculo final do "Px"
			Px = Px + (Li * *(y + i));
		}
		
		//Exibir o resultado
		printf ("\nPx = %f\n", Px);

        fflush(stdin);
        printf("\nDeseja calcular outro valor (s/n)? ");
        scanf("%c", &resp);
    }	while (resp == 's' || resp == 'S');

//Liberando a memória
free (x);
free (y);

    system("pause");
}
