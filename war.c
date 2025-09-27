// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================

#include <stdio.h>
#include <string.h>

#define TOTAL_TERRITORIOS 5

// Struct para armazenar os dados de um território
struct Territorio {
    char nome[50];
    char cor[30];
    int tropas;
};

int main() {
    struct Territorio territorios[TOTAL_TERRITORIOS];
    
    printf("=== Cadastro dos Territórios ===\n");

    // Loop para cadastrar 5 territórios
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        
        // Limpar o buffer antes de usar fgets (caso venha do scanf anterior)
        getchar(); 

        printf("Nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remover '\n'

        printf("Cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibir os dados
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Número de Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}

