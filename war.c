//nivel novato

#include <stdio.h>
#include <string.h>

// Definindo a struct Territorio
// Essa estrutura vai guardar os dados de cada território
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

int main() {
    // Criando um vetor com capacidade para 5 territórios
    Territorio territorios[5];

    // Variável auxiliar para controlar o loop
    int i;

    printf("==== Cadastro de Territórios ====\n");

    // Loop para cadastrar os 5 territórios
    for (i = 0; i < 5; i++) {
        printf("\nCadastro do território %d:\n", i + 1);

        // Lendo o nome do território
        printf("Nome do território: ");
        scanf(" %[^\n]", territorios[i].nome); // lê até a quebra de linha

        // Lendo a cor do exército
        printf("Cor do exército: ");
        scanf(" %[^\n]", territorios[i].cor); // lê até a quebra de linha

        // Lendo a quantidade de tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibindo os dados cadastrados
    printf("\n==== Territórios Registrados ====\n");

    for (i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
