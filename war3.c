// nivel mestre

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MISSOES 5

// Struct para representar um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\nCadastro do Território %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n===== TERRITÓRIOS ATUAIS =====\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("==============================\n");
}

// Função para simular ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\n%s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado do atacante: %d | Dado do defensor: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf("Vitória de %s! Conquistou o território!\n", atacante->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("%s falhou no ataque e perdeu uma tropa.\n", atacante->nome);
        if (atacante->tropas > 0) atacante->tropas--;
    }
}

// Função para atribuir missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Função para exibir a missão do jogador
void exibirMissao(char* missao) {
    printf("\n== SUA MISSÃO ==\n%s\n================\n", missao);
}

// Função para verificar se a missão foi cumprida (simplesmente verifica se há 2 territórios da cor do jogador)
int verificarMissao(char* missao, char* corJogador, Territorio* mapa, int total) {
    if (strstr(missao, "Conquistar 2 territórios")) {
        int contador = 0;
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contador++;
            }
        }
        if (contador >= 2) return 1;
    }

    if (strstr(missao, "Eliminar territórios vermelhos")) {
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0) {
                return 0; // Ainda existe território vermelho
            }
        }
        return 1; // Nenhum território vermelho
    }

    return 0; // Missão ainda não cumprida
}

// Função para liberar a memória
void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
    printf("\nMemória liberada com sucesso.\n");
}

int main() {
    srand(time(NULL));

    // Missões disponíveis
    char* missoes[MAX_MISSOES] = {
        "Conquistar 2 territórios inimigos",
        "Eliminar todos os territórios vermelhos",
        "Manter pelo menos 3 territórios ao final do turno",
        "Conquistar um território com mais de 5 tropas",
        "Ter domínio sobre um território chamado 'Capital'"
    };

    int total;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &total);

    // Alocar território dinamicamente
    Territorio* mapa = (Territorio*) malloc(sizeof(Territorio) * total);
    if (!mapa) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    // Cadastro
    cadastrarTerritorios(mapa, total);

    // Alocação da missão do jogador
    char* missaoJogador = (char*) malloc(sizeof(char) * 100);
    if (!missaoJogador) {
        printf("Erro na alocação da missão.\n");
        free(mapa);
        return 1;
    }

    // Sorteia e exibe missão
    atribuirMissao(missaoJogador, missoes, MAX_MISSOES);
    exibirMissao(missaoJogador);

    // Jogador escolhe uma cor
    char corJogador[10];
    printf("\nDigite a cor do seu exército: ");
    scanf(" %[^\n]", corJogador);

    int opcao;
    do {
        exibirTerritorios(mapa, total);

        // Verifica missão antes de permitir nova ação
        if (verificarMissao(missaoJogador, corJogador, mapa, total)) {
            printf("\n!!! MISSÃO CUMPRIDA !!! Você venceu o jogo!\n");
            break;
        }

        printf("\nMENU:\n1. Atacar\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int atk, def;
            printf("Escolha o número do território ATACANTE: ");
            scanf("%d", &atk);
            printf("Escolha o número do território DEFENSOR: ");
            scanf("%d", &def);

            if (atk < 0 || atk >= total || def < 0 || def >= total) {
                printf("Território inválido.\n");
                continue;
            }

            if (strcmp(mapa[atk].cor, corJogador) != 0) {
                printf("Você só pode atacar a partir de seus próprios territórios.\n");
                continue;
            }

            if (strcmp(mapa[def].cor, corJogador) == 0) {
                printf("Você não pode atacar seus próprios territórios.\n");
                continue;
            }

            atacar(&mapa[atk], &mapa[def]);
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador);
    return 0;
}
