#include <stdio.h>
#include <string.h>

// Definição da struct
struct Territorio {
    char nome[30];
    char cor[20];
    int tropas;
};

int main() {

    struct Territorio territorios[5];
    int i;

    printf("=== SISTEMA DE CADASTRO DE TERRITORIOS ===\n\n");

    // Cadastro dos territórios
    for (i = 0; i < 5; i++) {

        printf("Cadastro do territorio %d\n", i + 1);

        printf("Digite o nome: ");
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Mensagem de sucesso
    printf("Cadastro inicial concluido com sucesso!\n\n");

    // Título
    printf("================================================================\n");
    printf("        MAPA DO MUNDO - ESTADO ATUAL - github.com/Willianngit\n");
    printf("=================================================================\n\n");

    // Exibição 
    for (i = 0; i < 5; i++) {

        printf("TERRITORIO %d:\n", i + 1);
        printf(" - Nome: %s\n", territorios[i].nome);
        printf(" - Dominado por: Exercito %s\n", territorios[i].cor);
        printf(" - Tropas: %d\n", territorios[i].tropas);

        printf("\n");
    }

    return 0;
}