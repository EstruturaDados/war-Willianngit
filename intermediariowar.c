#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// definir struct
struct Territorio {
    char nome[30];
    char cor[20];
    int tropas;
};

// cadastro dos territorios
void cadastrarTerritorios(struct Territorio *territorios, int n) {
    int i;
    printf("=== SISTEMA DE CADASTRO DE TERRITORIOS ===\n\n");
    for (i = 0; i < n; i++) {
        printf("Cadastro do territorio %d\n", i + 1);
        printf("Digite o nome: ");
        scanf("%s", territorios[i].nome);
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        printf("\n");
    }
    printf("Cadastro inicial concluido com sucesso!\n\n");
}

void exibirMapa(struct Territorio *territorios, int n) {
    int i;
    printf("================================================================\n");
    printf("         MAPA DO MUNDO - ESTADO ATUAL - github.com/Willianngit\n");
    printf("================================================================\n\n");
    for (i = 0; i < n; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    printf("\n");
}

int atacar(struct Territorio *territorios, int n) {
    int atac, def, dado_atac, dado_def;
    printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", n);
    scanf("%d", &atac);
    if (atac == 0) return 0;
    atac--;
    printf("Escolha o territorio defensor (1 a %d): ", n);
    scanf("%d", &def);
    def--;
    if (atac < 0 || atac >= n || def < 0 || def >= n || atac == def) {
        printf("Escolha invalida!\n");
        printf("Pressione Enter para continuar...\n");
        getchar();
        while (getchar() != '\n');
        return 1;
    }
    dado_atac = (rand() % 6) + 1;
    dado_def = (rand() % 6) + 1;
    printf("\n--- RESULTADO DA BATALLA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", territorios[atac].nome, dado_atac);
    printf("O defensor %s rolou um dado e tirou: %d\n", territorios[def].nome, dado_def);
    if (dado_atac >= dado_def) {  // Empate favorece atacante
        printf("VITORIA DO ATAQUE! o defensor perde 1 tropa.\n");
        territorios[def].tropas--;
        if (territorios[def].tropas <= 0) {
            printf("CONQUISTA! o territorio %s foi dominado pelo Exercito %s!\n", territorios[def].nome, territorios[atac].cor);
            strcpy(territorios[def].cor, territorios[atac].cor);
            territorios[def].tropas = 1;
        }
    } else {
        printf("VITORIA DO DEFENSOR! o atacante perde 1 tropa.\n");
        territorios[atac].tropas--;
    }
    printf("Pressione Enter para continuar para o proximo turno...\n");
    getchar();
    while (getchar() != '\n');
    printf("\n");
    return 1;
}

int main() {
    srand(time(NULL));
    int n = 5;
    struct Territorio *territorios = calloc(n, sizeof(struct Territorio));
    if (territorios == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }
    cadastrarTerritorios(territorios, n);
    exibirMapa(territorios, n);
    printf("--- FASE DE ATAQUE --\n");
    while (1) {
        exibirMapa(territorios, n);
        if (!atacar(territorios, n)) break;
        printf("--- FASE DE ATAQUE --\n");
    }
    // encerrar e liberar memoria
    printf("Jogo encerrado e memoria liberada.\nAte a proxima!\n");
    free(territorios);
    return 0;
}
