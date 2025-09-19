#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERRITORIOS 5

typedef struct {
    char nome[30]; // nome do território
    char cor[10];  // cor do exército
    int tropas;    // tropas
} Territorio;

void exibirTerritorios(const Territorio territorios[], int n);
void simularBatalha(Territorio *atacante, Territorio *defensor);

int main(void) {
    // usamos calloc para alocar dinamicamente os territórios
    Territorio *territorios = (Territorio*) calloc(MAX_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    srand(time(NULL)); // inicializa a semente para números aleatórios

    int i, opcao;
    int cadastrados = 0;

    do {
        printf("\n=== MENU WAR ===\n");
        printf("1 - Cadastrar territorios\n");
        printf("2 - Exibir territorios\n");
        printf("3 - Atacar\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                for (i = 0; i < MAX_TERRITORIOS; i++) {
                    printf("\nCadastro do territorio %d:\n", i + 1);

                    printf("  Nome: ");
                    scanf(" %29[^\n]", territorios[i].nome);

                    printf("  Cor do exercito: ");
                    scanf(" %9s", territorios[i].cor);

                    printf("  Tropas: ");
                    scanf("%d", &territorios[i].tropas);
                }
                cadastrados = 1;
                break;

            case 2:
                if (cadastrados) {
                    printf("\n=== Exibindo territorios cadastrados ===\n\n");
                    exibirTerritorios(territorios, MAX_TERRITORIOS);
                } else {
                    printf("\nNenhum territorio cadastrado ainda!\n");
                }
                break;

            case 3:
                if (cadastrados) {
                    int atacante, defensor;
                    printf("\n=== Simulacao de Ataque ===\n");
                    printf("Escolha o territorio atacante (1 a %d): ", MAX_TERRITORIOS);
                    scanf("%d", &atacante);
                    printf("Escolha o territorio defensor (1 a %d): ", MAX_TERRITORIOS);
                    scanf("%d", &defensor);

                    if (atacante < 1 || atacante > MAX_TERRITORIOS ||
                        defensor < 1 || defensor > MAX_TERRITORIOS ||
                        atacante == defensor) {
                        printf("\nEscolha invalida!\n");
                    } else {
                        simularBatalha(&territorios[atacante - 1], &territorios[defensor - 1]);

                        // exibir territórios após a batalha
                        printf("\n=== Territorios apos a batalha ===\n");
                        exibirTerritorios(territorios, MAX_TERRITORIOS);
                    }
                } else {
                    printf("\nNenhum territorio cadastrado ainda!\n");
                }
                break;

            case 4:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    free(territorios);
    return 0;
}

void exibirTerritorios(const Territorio territorios[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome   : %s\n", territorios[i].nome);
        printf("  Cor    : %s\n", territorios[i].cor);
        printf("  Tropas : %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }
}

void simularBatalha(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\nO atacante precisa ter mais de 1 tropa para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n%s (%s) ataca %s (%s)!\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        printf("Atacante venceu esta rodada!\n");
        defensor->tropas--;

        if (defensor->tropas <= 0) {
            printf("%s foi conquistado por %s!\n", defensor->nome, atacante->cor);
            defensor->tropas = 1; // pelo menos 1 tropa fica no território conquistado
            strcpy(defensor->cor, atacante->cor);
        }
    } else {
        printf("Defensor resistiu!\n");
        atacante->tropas--;
    }
}
