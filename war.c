#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRINGNAME 30
#define MAX_STRINGCOR 10


 // DEFINIÇÃO DA STRUCT TERRITORIO
 
typedef struct {
    char nome[MAX_STRINGNAME];
    char cor[MAX_STRINGCOR];
    int tropas;
} Territorio;

// DECLARAÇÃO DAS FUNÇÕES (PROTÓTIPOS)
void limparBuffer();
void cadastrarTerritorios(Territorio* territorios, int total);
void listarTerritorios(Territorio* territorios, int total);
void atacar(Territorio* atacante, Territorio* defensor);
void realizarAtaque(Territorio* territorios, int total);
void liberarMemoria(Territorio* territorios);

int main() {
    // Inicialização do gerador de números aleatórios
    srand(time(NULL));
    
    Territorio* territorios = NULL;
    int totalTerritorios = 0;
    int opcao;
    
    printf("=== SISTEMA DE BATALHA DE TERRITORIOS ===\n");
    
    // Solicita o número de territórios para alocação dinâmica
    printf("Digite o numero total de territorios: ");
    scanf("%d", &totalTerritorios);
    limparBuffer();
    
    if (totalTerritorios <= 0) {
        printf("Numero de territorios deve ser maior que zero!\n");
        return 1;
    }
    
    // ALOCAÇÃO DINÂMICA DE MEMÓRIA
    territorios = (Territorio*)calloc(totalTerritorios, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }
    
    printf("Memoria alocada para %d territorios!\n", totalTerritorios);
    
    // Menu principal
    do {
        printf("\n==================================\n");
        printf("1. Cadastrar territorios\n");
        printf("2. Listar territorios\n");
        printf("3. Realizar ataque\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                cadastrarTerritorios(territorios, totalTerritorios);
                break;
                
            case 2:
                listarTerritorios(territorios, totalTerritorios);
                break;
                
            case 3:
                realizarAtaque(territorios, totalTerritorios);
                break;
                
            case 0:
                printf("Saindo do programa...\n");
                break;
                
            default:
                printf(" Opcao invalida!\n");
                break;
        }
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
        
    } while (opcao != 0);
    
    // LIBERAÇÃO DA MEMÓRIA ALOCADA DINAMICAMENTE
    liberarMemoria(territorios);
    
    return 0;
}


//limparBuffer
 
void limparBuffer() {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


 // FUNÇÃO: cadastrarTerritorios
 
void cadastrarTerritorios(Territorio* territorios, int total) {
    printf("\n=== CADASTRO DE %d TERRITORIOS ===\n", total);
    
    for(int i = 0; i < total; i++) {
        printf("\n--- Territorio %d ---\n", i + 1);
        
        printf("Digite o nome do territorio: ");
        scanf("%29s", territorios[i].nome);
        
        printf("Digite a cor do exercito: ");
        scanf("%9s", territorios[i].cor);
        
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        limparBuffer();
    }
}


 // FUNÇÃO: listarTerritorios
 
void listarTerritorios(Territorio* territorios, int total) {
    printf("\n=== LISTA DE TERRITORIOS ===\n");
    
    if (total == 0) {
        printf("Nao existem territorios cadastrados!\n");
        return;
    }
    
    for(int i = 0; i < total; i++) {
        printf("\n--- Territorio %d ---\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }
    printf("===============================================\n");
}


 // FUNÇÃO: atacar
 
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== SIMULACAO DE ATAQUE ===\n");
    printf("Atacante: %s (%s) com %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) com %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
    
    // Simulação de dados de batalha (1-6 para cada lado)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("\n Dado do atacante: %d\n", dadoAtacante);
    printf(" Dado do defensor: %d\n", dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("\n  VITORIA DO ATACANTE!\n");
        
        // Defensor muda de dono (cor)
        printf("O territorio %s agora pertence ao exercito %s!\n", defensor->nome, atacante->cor);
        strcpy(defensor->cor, atacante->cor);
        
        // Transferência de tropas (metade do defensor para o atacante)
        int tropasConquistadas = defensor->tropas / 2;
        atacante->tropas += tropasConquistadas;
        defensor->tropas = defensor->tropas / 2; // Metade restante
        
        printf("Tropas conquistadas: %d\n", tropasConquistadas);
        
    } else if (dadoAtacante < dadoDefensor) {
        // Defensor vence
        printf("\n  VITORIA DO DEFENSOR!\n");
        
        // Atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("O atacante perdeu 1 tropa!\n");
        } else {
            printf("O atacante nao pode perder mais tropas!\n");
        }
        
    } else {
        // Empate
        printf("\n EMPATE! Nenhum territorio mudou de dono.\n");
    }
    
    printf("\n--- SITUACAO POS-BATALHA ---\n");
    printf("Atacante (%s): %d tropas\n", atacante->nome, atacante->tropas);
    printf("Defensor (%s): %d tropas - Cor: %s\n", defensor->nome, defensor->tropas, defensor->cor);
}


 //FUNÇÃO: realizarAtaque
 
void realizarAtaque(Territorio* territorios, int total) {
    if (total < 2) {
        printf(" E necessario pelo menos 2 territorios para realizar um ataque!\n");
        return;
    }
    
    int idxAtacante, idxDefensor;
    
    printf("\n=== SELECAO DE ATAQUE ===\n");
    
    // Lista territórios disponíveis para ataque
    printf("Territorios disponiveis:\n");
    for(int i = 0; i < total; i++) {
        printf("%d. %s (%s) - %d tropas\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    
    // Seleção do atacante
    printf("\nSelecione o territorio ATACANTE (1-%d): ", total);
    scanf("%d", &idxAtacante);
    limparBuffer();
    
    if (idxAtacante < 1 || idxAtacante > total) {
        printf(" Territorio invalido!\n");
        return;
    }
    idxAtacante--; // Ajusta para índice do array
    
    // Seleção do defensor
    printf("Selecione o territorio DEFENSOR (1-%d): ", total);
    scanf("%d", &idxDefensor);
    limparBuffer();
    
    if (idxDefensor < 1 || idxDefensor > total) {
        printf(" Territorio invalido!\n");
        return;
    }
    idxDefensor--; // Ajusta para índice do array
    
    // Validações
    if (idxAtacante == idxDefensor) {
        printf(" Um territorio nao pode atacar a si mesmo!\n");
        return;
    }
    
    if (strcmp(territorios[idxAtacante].cor, territorios[idxDefensor].cor) == 0) {
        printf(" Nao pode atacar um territorio da mesma cor!\n");
        return;
    }
    
    if (territorios[idxAtacante].tropas <= 1) {
        printf(" Territorio atacante precisa de pelo menos 2 tropas!\n");
        return;
    }
    
    // Realiza o ataque usando ponteiros
    atacar(&territorios[idxAtacante], &territorios[idxDefensor]);
}


 //liberarMemoria

void liberarMemoria(Territorio* territorios) {
    if (territorios != NULL) {
        free(territorios);
        printf("✅ Memoria liberada com sucesso!\n");
    }
}