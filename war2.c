//nível aventureiro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\nCadastro do Território %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir todos os territórios
void exibirTerritorios(Territorio* mapa, int tamanho) {
    printf("\n===== TERRITÓRIOS ATUAIS =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. Nome: %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("==============================\n");
}

// Função de ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\nSimulando ataque entre %s (ATACANTE) e %s (DEFENSOR)...\n",
           atacante->nome, defensor->nome);

    int dadoAtacante = (rand() % 6) + 1; // 1 a 6
    int dadoDefensor = (rand() % 6) + 1; // 1 a 6

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: %s conquistou %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor); // muda a cor (controle)
        defensor->tropas = atacante->tropas / 2; // transfere metade das tropas
    } else {
        printf("Resultado: %s falhou no ataque e perdeu uma tropa.\n", atacante->nome);
        if (atacante->tropas > 0) {
            atacante->tropas--; // perde 1 tropa se falhar
        }
    }
}

// Liberação da memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso.\n");
}

int main() {
    srand(time(NULL)); // Garante aleatoriedade nos dados

    int quantidade;

    printf("Informe a quantidade de territórios a cadastrar: ");
    scanf("%d", &quantidade);

    if (quantidade <= 1) {
        printf("É necessário ter ao menos 2 territórios para realizar ataques.\n");
        return 1;
    }

    // Alocação dinâmica de memória
    Territorio* mapa = (Territorio*) malloc(quantidade * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, quantidade);

    int opcao;
    do {
        exibirTerritorios(mapa, quantidade);

        printf("\nMENU DE AÇÕES:\n");
        printf("1. Realizar ataque\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idxAtacante, idxDefensor;

            printf("\nInforme o número do território ATACANTE: ");
            scanf("%d", &idxAtacante);

            printf("Informe o número do território DEFENSOR: ");
            scanf("%d", &idxDefensor);

            // Validações
            if (idxAtacante < 0 || idxAtacante >= quantidade ||
                idxDefensor < 0 || idxDefensor >= quantidade) {
                printf("Índices inválidos!\n");
                continue;
            }

            if (idxAtacante == idxDefensor) {
                printf("Um território não pode atacar a si mesmo!\n");
                continue;
            }

            if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
                printf("Não é possível atacar um território da mesma cor.\n");
                continue;
            }

            atacar(&mapa[idxAtacante], &mapa[idxDefensor]);

        } else if (opcao != 0) {
            printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}
