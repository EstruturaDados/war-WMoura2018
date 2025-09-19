#include <stdalign.h>
#include <stdio.h>   // biblioteca padrão de entrada/saída (printf, scanf)
#include <string.h>  // biblioteca para funções com strings (opcional aqui, mas útil)

// define a quantidade fixa de territórios que vamos cadastrar
#define MAX_TERRITORIOS 5

// definição da struct Territorio: armazena nome, cor do exército e número de tropas
typedef struct {
    char nome[30]; // nome do território
    char cor[10];  // cor do exército
    int tropas;    // tropas
} Territorio;

// protótipo da função que exibirá os territórios cadastrados
void exibirTerritorios(const Territorio territorios[], int n);

int main(void) {
    Territorio territorios[MAX_TERRITORIOS]; // vetor para armazenar os 5 territórios
    int i, opcao; // índice do laço
    int cadastrados = 0; // contador para saber quantos territórios já foram preenchidos

    do {
        // menu de opções
        printf("\n=== MENU WAR ===\n");
        printf("1 - Cadastrar territorios\n");
        printf("2 - Exibir territorios\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // cadastrar territórios
                for (i = 0; i < MAX_TERRITORIOS; i++) {
                    printf("\nCadastro do territorio %d:\n", i + 1);

                    printf("  Nome: ");
                    scanf(" %29[^\n]", territorios[i].nome);

                    printf("  Cor do exercito: ");
                    scanf(" %9s", territorios[i].cor);

                    printf("  Tropas: ");
                    scanf("%d", &territorios[i].tropas);
                }
                cadastrados = 1; // marca que já temos dados
                break;

            case 2: // exibir territórios
                if (cadastrados) {
                    printf("\n=== Exibindo territorios cadastrados ===\n\n");
                    exibirTerritorios(territorios, MAX_TERRITORIOS);
                } else {
                    printf("\nNenhum territorio cadastrado ainda!\n");
                }
                break;

            case 3: // sair
                printf("\nSaindo do programa...\n");
                break;

            default: // qualquer valor diferente de 1,2,3
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 3); // repete até escolher sair

    printf("=== Cadastro de Territórios (War - nível novato) ===\n\n");

    // laço para cadastrar cada território
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Cadastro do território %d:\n", i + 1); // informa qual território está sendo cadastrado

        printf("  Nome (até 29 caracteres, pode conter espacos): ");
        scanf(" %29[^\n]", territorios[i].nome);

        // lê a cor do exército
        printf("  Cor do exercito (uma palavra, sem espacos): ");
        scanf(" %9s", territorios[i].cor);

        // lê a quantidade de tropas 
        printf("  Quantidade de tropas (numero inteiro): ");
        while (scanf("%d", &territorios[i].tropas) != 1) {
            
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { } // descarta caracteres inválidos
            printf("  Entrada invalida. Digite um numero inteiro para tropas: ");
        }

        printf("\n"); // linha em branco para separar cadastros
    }

    // após o cadastro, exibe todos os territórios cadastrados
    printf("=== Exibindo territorios cadastrados ===\n\n");
    exibirTerritorios(territorios, MAX_TERRITORIOS);

    return 0; // encerra o programa
}

// função que percorre o vetor e imprime os dados de cada territorio
void exibirTerritorios(const Territorio territorios[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome : %s\n", territorios[i].nome);
        printf("  Cor  : %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }
}

