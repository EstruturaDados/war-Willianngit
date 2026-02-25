#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[20];
    int tropas;
};

void cadastrarTerritorios(struct Territorio *territorios) {
    int i;
    printf("=== CADASTRO DE TERRITORIOS ===\n\n");
    for (i = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);
        printf("Digite o nome: ");
        scanf("%s", territorios[i].nome);
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        printf("\n");
    }
    printf("Cadastro concluido com sucesso!\n\n");
}

void exibirMapa(struct Territorio *territorios) {
    int i;
    printf("MAPA DO MUNDO\n");
    for (i = 0; i < 5; i++) {
        printf("%d. %s (Exercito: %s, Tropas: %d)\n", i+1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    printf("\n");
}

int contarExercito(struct Territorio *territorios, const char *cor) {
    int i, total = 0;
    for (i = 0; i < 5; i++) {
        if (strcmp(territorios[i].cor, cor) == 0) {
            total += territorios[i].tropas;
        }
    }
    return total;
}

void verificarMissao(struct Territorio *territorios, char *missaoCor) {
    printf("\n--- SUA MISSAO (Exercito Azul) ---\n");
    printf("Destruir o exercito %s.\n", missaoCor);
    
    int tropasInimigo = contarExercito(territorios, missaoCor);
    if (tropasInimigo == 0) {
        printf("MISSAO CUMPRIDA!\n");
        printf("Escolha nova cor para proxima missao (entre as cadastradas): ");
        scanf("%s", missaoCor);
        printf("Nova missao: Destruir exercito %s!\n", missaoCor);
    } else {
        printf("Voce ainda nao cumpriu sua missao. Continue a lutar!\n");
    }
    printf("Pressione Enter para continuar...\n");
    getchar();
    while (getchar() != '\n');
}

int atacar(struct Territorio *territorios) {
    int atac, def, dado_atac, dado_def;
    printf("\nEscolha o territorio atacante (1 a 5): ");
    scanf("%d", &atac);
    atac--;
    printf("Escolha o territorio defensor (1 a 5): ");
    scanf("%d", &def);
    def--;
    
    if (atac < 0 || atac >= 5 || def < 0 || def >= 5 || atac == def) {
        printf("Escolha invalida!\n");
        return 1;
    }
    
    dado_atac = (rand() % 6) + 1;
    dado_def = (rand() % 6) + 1;
    
    printf("\n--- RESULTADO DA BATALLA ---\n");
    printf("- ATACANTE (%s): %d    DEFESA (%s): %d\n", territorios[atac].nome, dado_atac, territorios[def].nome, dado_def);
    
    if (dado_atac >= dado_def) {
        printf("Vitoria do ATAQUE! | o defensor perde 1 tropa.\n");
        territorios[def].tropas--;
        if (territorios[def].tropas <= 0) {
            printf("CONQUISTA! o territorio %s foi dominado pelo Exercito %s!\n", territorios[def].nome, territorios[atac].cor);
            strcpy(territorios[def].cor, territorios[atac].cor);
            territorios[def].tropas = 1;
        }
    } else {
        printf("Vitoria da DEFESA! | o atacante perde 1 tropa.\n");
        territorios[atac].tropas--;
    }
    
    printf("Pressione Enter para continuar...\n");
    getchar();
    while (getchar() != '\n');
    return 1;
}

int main() {
    srand(time(NULL));
    const int N = 5;
    struct Territorio *territorios = calloc(N, sizeof(struct Territorio));
    if (!territorios) {
        printf("Erro de memoria!\n");
        return 1;
    }
    
    cadastrarTerritorios(territorios);
    
    char missaoCor[20];
    printf("Escolha a cor para sua primeira missao: ");
    scanf("%s", missaoCor);
    
    printf("\n--- SUA MISSAO (Exercito Azul) ---\n");
    printf("Destruir o exercito %s.\n\n", missaoCor);
    
    int opcao;
    while (1) {
        printf("\n--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("\n--- ATAQUE ESPECIAL ---\n");
                printf("Escolha cor alvo: ");
                char corAlvo[20];
                scanf("%s", corAlvo);
                exibirMapa(territorios);
                atacar(territorios);
                break;
            case 2:
                verificarMissao(territorios, missaoCor);
                break;
            case 0:
                printf("Encerrrando o jogo...\n");
                printf("Memoria liberada com sucesso.\n");
                free(territorios);
                return 0;
            default:
                printf("Opcao invalida!\n");
        }
    }
    
    return 0;
}
