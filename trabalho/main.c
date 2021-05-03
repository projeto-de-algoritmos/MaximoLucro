/* Alunos:
Gabriel Alves Hussein   17/0103200
Victor Amaral Cerqueira 17/0164411
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definicoes Gerais
typedef int item;
#define key(A) (A)
#define less(A,B) (key(A) < key(B))
#define exch(A,B) {item t=A; A=B, B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

typedef struct Trabalho{
    char nome[100];
    int horarioInicio;
    int horarioFim;
    double lucro;
}TRABALHO;

// Chamada das Funcoes
void mostraMenu(int totalTrabalhos);
void exibeTrabalhos(TRABALHO *trabalho, int totalTrabalhos);
void ordena(TRABALHO *trabalho, int l, int r);
void merge(TRABALHO *trabalho, int l, int r1, int r2);
void cadastroTrabalho (TRABALHO *trabalho, int totalTrabalhos);
int ultimoSemConflito (TRABALHO *trabalho, int i);
void lucroMax(TRABALHO *trabalho, int totalTrabalhos);
int criaTrabalhos (TRABALHO *Trabalho, int totalTrabalhos);

int main(){
    TRABALHO trabalho[100];
    int totalTrabalhos = 0, opcao;
    
    totalTrabalhos = criaTrabalhos(trabalho, totalTrabalhos);

    do{
        mostraMenu(totalTrabalhos);
        scanf("%d",&opcao);
        system("clear");
        switch(opcao){
        case 1:
            cadastroTrabalho(trabalho, totalTrabalhos);
            totalTrabalhos++;
            getc(stdin);
            printf("Aperte enter para voltar ao menu.");
            break;
        case 2:
            exibeTrabalhos(trabalho, totalTrabalhos);
            getc(stdin);
            break;
        case 3:
            ordena(trabalho, 0, totalTrabalhos-1);
            lucroMax(trabalho, totalTrabalhos);
            break;
        }
  }while(opcao != 0);

    return 0;
}

// Desenvolvimento das funcoes 
void mostraMenu(int totalTrabalhos){
  printf("\n");
  printf(" ====================================================\n");
  printf("|             >>>>>>>>> Menu <<<<<<<<<               |\n");
  printf("| 1 - Adicionar trabalho (%d trabalhos cadastrados)   |\n", totalTrabalhos);
  printf("| 2 - Exibir Trabalhos disponiveis                   |\n");
  printf("| 3 - Calcular Maior lucro possivel                  |\n");
  printf("| 0 - Sair                                           |\n");
  printf(" ====================================================\n");
  printf("Sua opcao: ");
}

void exibeTrabalhos(TRABALHO *trabalho, int totalTrabalhos){
     for(int j = 0; j < totalTrabalhos; j++){
        printf("Codigo: %d\nNome: %s\nHorario: %d - %d\nLucro esperado: %.02lf\n\n", j+1, trabalho[j].nome, trabalho[j].horarioInicio, trabalho[j].horarioFim, trabalho[j].lucro);
    }
}

void ordena(TRABALHO *trabalho, int l, int r){
    if(l>=r) return;
    int meio = (r+l)/2;
    ordena(trabalho, l, meio);
    ordena(trabalho, meio+1, r);
    merge(trabalho, l, meio, r);
}

void merge(TRABALHO *trabalho, int l, int r1, int r2){
    TRABALHO v2[16];
    int k = 0;
    int i = l;
    int j = r1 + 1;

    while (i <= r1 && j <= r2)
    {
        if (less(trabalho[i].horarioFim, trabalho[j].horarioFim))
            v2[k++] = trabalho[i++];
        else
            v2[k++] = trabalho[j++];
    }

    while (i <= r1)
        v2[k++] = trabalho[i++];
    while (j <= r2)
        v2[k++] = trabalho[j++];

    k = 0;
    for (int i = l; i <= r2; i++)
    {
        trabalho[i] = v2[k++];
    }

    return;
}

void cadastroTrabalho (TRABALHO *trabalho, int totalTrabalhos) {
    printf("Digite o nome do trabalho a ser cadastrado: \n");
    scanf(" %[^\n]s", trabalho[totalTrabalhos].nome);
    
    printf("Digite o Horario de inicio do trabalho a ser cadastrado: \n");
    scanf("%d", &trabalho[totalTrabalhos].horarioInicio);

    printf("Digite o Horario de Fim do trabalho a ser cadastrado: \n");
    scanf("%d", &trabalho[totalTrabalhos].horarioFim);
    
    printf("Digite o lucro esperado do trabalho a ser cadastrado: \n");
    scanf("%lf", &trabalho[totalTrabalhos].lucro);
}

int ultimoSemConflito (TRABALHO *trabalho, int i){
    for (int j=i-1; j>=0; j--)
	{
		if (trabalho[j].horarioFim <= trabalho[i].horarioInicio)
			return j;
	}
	return -1;
}

void lucroMax(TRABALHO *trabalho, int totalTrabalhos)
{
	double lucros[totalTrabalhos];
	lucros[0] = trabalho[0].lucro;

	for (int i=1; i<totalTrabalhos; i++)
	{
		double lucroTotal = trabalho[i].lucro;
		int l = ultimoSemConflito(trabalho, i);

		if (l != -1)
			lucroTotal += lucros[l];

        if (lucroTotal >= lucros[i-1])
            lucros[i] = lucroTotal;
        else lucros[i] = lucros[i-1];
	}

	printf("O maior lucro possivel eh de R$%.02lf\n", lucros[totalTrabalhos-1]);
}

int criaTrabalhos (TRABALHO *trabalho, int totalTrabalhos){
    strcpy(trabalho[0].nome, "Manobrista");
    trabalho[0].horarioInicio = 1;
    trabalho[0].horarioFim = 3;
    trabalho[0].lucro = 200.00;
    totalTrabalhos++;

    strcpy(trabalho[1].nome, "Auxiliar");
    trabalho[1].horarioInicio = 1;
    trabalho[1].horarioFim = 6;
    trabalho[1].lucro = 40.00;
    totalTrabalhos++;

    strcpy(trabalho[2].nome, "Revendedor");
    trabalho[2].horarioInicio = 4;
    trabalho[2].horarioFim = 6;
    trabalho[2].lucro = 80.00;
    totalTrabalhos++;

    strcpy(trabalho[3].nome, "Porteiro");
    trabalho[3].horarioInicio = 8;
    trabalho[3].horarioFim = 16;
    trabalho[3].lucro = 90.00;
    totalTrabalhos++;

    strcpy(trabalho[4].nome, "Vigia");
    trabalho[4].horarioInicio = 18;
    trabalho[4].horarioFim = 23;
    trabalho[4].lucro = 100.00;
    totalTrabalhos++;
    
    return totalTrabalhos;
}