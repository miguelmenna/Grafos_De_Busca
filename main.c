#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CIDADES 100
#define MAX_NOME_CIDADE 50

// Estruturas de dados
typedef struct No {
    int cidade_destino;
    struct No* proximo;
} No;

typedef struct Grafo {
    int num_cidades;
    char cidades[MAX_CIDADES][MAX_NOME_CIDADE];
    No* adjacencia[MAX_CIDADES];
} Grafo;

// Função para criar o grafo
Grafo* criarGrafo() {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    g->num_cidades = 0;
    for (int i = 0; i < MAX_CIDADES; i++) {
        g->adjacencia[i] = NULL;
    }
    return g;
}

// Função para adicionar uma cidade ao grafo
void adicionarCidade(Grafo* g, const char* nome) {
    if (g->num_cidades < MAX_CIDADES) {
        strcpy(g->cidades[g->num_cidades], nome);
        g->num_cidades++;
    } else {
        printf("Limite de cidades atingido.\n");
    }
}

// Função para obter o índice de uma cidade no grafo
int obterIndiceCidade(Grafo* g, const char* nome) {
    for (int i = 0; i < g->num_cidades; i++) {
        if (strcmp(g->cidades[i], nome) == 0) {
            return i;
        }
    }
    return -1; // Cidade não encontrada
}

// Função para adicionar uma conexão entre duas cidades
void adicionarConexao(Grafo* g, const char* origem, const char* destino) {
    int origem_idx = obterIndiceCidade(g, origem);
    int destino_idx = obterIndiceCidade(g, destino);

    if (origem_idx == -1 || destino_idx == -1) {
        printf("Uma ou ambas as cidades não existem.\n");
        return;
    }

    // Adicionar conexão de origem -> destino
    No* novo_no = (No*)malloc(sizeof(No));
    novo_no->cidade_destino = destino_idx;
    novo_no->proximo = g->adjacencia[origem_idx];
    g->adjacencia[origem_idx] = novo_no;

    // Adicionar conexão de destino -> origem (grafo não dirigido)
    novo_no = (No*)malloc(sizeof(No));
    novo_no->cidade_destino = origem_idx;
    novo_no->proximo = g->adjacencia[destino_idx];
    g->adjacencia[destino_idx] = novo_no;
}

// Função para remover uma conexão entre duas cidades
void removerConexao(Grafo* g, const char* origem, const char* destino) {
    int origem_idx = obterIndiceCidade(g, origem);
    int destino_idx = obterIndiceCidade(g, destino);

    if (origem_idx == -1 || destino_idx == -1) {
        printf("Uma ou ambas as cidades não existem.\n");
        return;
    }

    // Remover a conexão de origem -> destino
    No* temp = g->adjacencia[origem_idx];
    No* anterior = NULL;
    while (temp != NULL && temp->cidade_destino != destino_idx) {
        anterior = temp;
        temp = temp->proximo;
    }
    if (temp != NULL) {
        if (anterior == NULL) {
            g->adjacencia[origem_idx] = temp->proximo;
        } else {
            anterior->proximo = temp->proximo;
        }
        free(temp);
    }

    // Remover a conexão de destino -> origem
    temp = g->adjacencia[destino_idx];
    anterior = NULL;
    while (temp != NULL && temp->cidade_destino != origem_idx) {
        anterior = temp;
        temp = temp->proximo;
    }
    if (temp != NULL) {
        if (anterior == NULL) {
            g->adjacencia[destino_idx] = temp->proximo;
        } else {
            anterior->proximo = temp->proximo;
        }
        free(temp);
    }
}

// Função para buscar todas as conexões partindo de uma cidade
void buscarConexoes(Grafo* g, const char* cidade) {
    int cidade_idx = obterIndiceCidade(g, cidade);
    if (cidade_idx == -1) {
        printf("Cidade não encontrada.\n");
        return;
    }

    No* temp = g->adjacencia[cidade_idx];
    printf("Conexões de %s:\n", cidade);
    while (temp != NULL) {
        printf("- %s\n", g->cidades[temp->cidade_destino]);
        temp = temp->proximo;
    }
}

// Função para imprimir o grafo
void imprimirGrafo(Grafo* g) {
    for (int i = 0; i < g->num_cidades; i++) {
        printf("%s -> ", g->cidades[i]);
        No* temp = g->adjacencia[i];
        while (temp != NULL) {
            printf("%s ", g->cidades[temp->cidade_destino]);
            temp = temp->proximo;
        }
        printf("\n");
    }
}

// Função DFS (Busca em Profundidade)
void dfs(Grafo* g, int cidade_idx, bool* visitado) {
    visitado[cidade_idx] = true;
    printf("%s ", g->cidades[cidade_idx]);

    No* adjacente = g->adjacencia[cidade_idx];
    while (adjacente != NULL) {
        if (!visitado[adjacente->cidade_destino]) {
            dfs(g, adjacente->cidade_destino, visitado);
        }
        adjacente = adjacente->proximo;
    }
}

// Função BFS (Busca em Largura)
void bfs(Grafo* g, int cidade_idx) {
    bool visitado[MAX_CIDADES] = { false };
    visitado[cidade_idx] = true;

    // Fila para BFS
    int fila[MAX_CIDADES], inicio = 0, fim = 0;
    fila[fim++] = cidade_idx;

    while (inicio < fim) {
        int cidade_atual = fila[inicio++];
        printf("%s ", g->cidades[cidade_atual]);

        No* adjacente = g->adjacencia[cidade_atual];
        while (adjacente != NULL) {
            if (!visitado[adjacente->cidade_destino]) {
                visitado[adjacente->cidade_destino] = true;
                fila[fim++] = adjacente->cidade_destino;
            }
            adjacente = adjacente->proximo;
        }
    }
}

// Função para liberar memória do grafo
void liberarGrafo(Grafo* g) {
    for (int i = 0; i < g->num_cidades; i++) {
        No* temp = g->adjacencia[i];
        while (temp != NULL) {
            No* aux = temp;
            temp = temp->proximo;
            free(aux);
        }
    }
    free(g);
}

// Função para mostrar o menu
void mostrarMenu() {
    printf("\n------ MENU ------\n");
    printf("1. Adicionar cidade\n");
    printf("2. Adicionar conexão\n");
    printf("3. Remover conexão\n");
    printf("4. Buscar conexões de uma cidade\n");
    printf("5. Imprimir o grafo\n");
    printf("6. Buscar cidades com DFS\n");
    printf("7. Buscar cidades com BFS\n");
    printf("8. Sair\n");
}

int main() {
    Grafo* g = criarGrafo();
    int opcao;
    char cidade_origem[MAX_NOME_CIDADE], cidade_destino[MAX_NOME_CIDADE];
    char nome_cidade[MAX_NOME_CIDADE];

    // Inserir cidades e conexões pré-definidas
    printf("Adicionando cidades iniciais...\n");
    adicionarCidade(g, "São Paulo");
    adicionarCidade(g, "Rio de Janeiro");
    adicionarCidade(g, "Belo Horizonte");
    adicionarCidade(g, "Salvador");

    printf("Adicionando conexões iniciais...\n");
    adicionarConexao(g, "São Paulo", "Rio de Janeiro");
    adicionarConexao(g, "São Paulo", "Belo Horizonte");
    adicionarConexao(g, "Belo Horizonte", "Salvador");

    // Imprimir o grafo inicial
    printf("\nGrafo inicial:\n");
    imprimirGrafo(g);

    while (1) {
        mostrarMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Para consumir o '\n' após o scanf

        switch (opcao) {
            case 1:
                // Adicionar cidade
                printf("Digite o nome da cidade: ");
                fgets(nome_cidade, MAX_NOME_CIDADE, stdin);
                nome_cidade[strcspn(nome_cidade, "\n")] = '\0';  // Remover o '\n' do final
                adicionarCidade(g, nome_cidade);
                printf("Cidade %s adicionada com sucesso!\n", nome_cidade);
                break;

            case 2:
                // Adicionar conexão
                printf("Digite a cidade de origem: ");
                fgets(cidade_origem, MAX_NOME_CIDADE, stdin);
                cidade_origem[strcspn(cidade_origem, "\n")] = '\0';

                printf("Digite a cidade de destino: ");
                fgets(cidade_destino, MAX_NOME_CIDADE, stdin);
                cidade_destino[strcspn(cidade_destino, "\n")] = '\0';

                adicionarConexao(g, cidade_origem, cidade_destino);
                printf("Conexão adicionada entre %s e %s.\n", cidade_origem, cidade_destino);
                break;

            case 3:
                // Remover conexão
                printf("Digite a cidade de origem: ");
                fgets(cidade_origem, MAX_NOME_CIDADE, stdin);
                cidade_origem[strcspn(cidade_origem, "\n")] = '\0';

                printf("Digite a cidade de destino: ");
                fgets(cidade_destino, MAX_NOME_CIDADE, stdin);
                cidade_destino[strcspn(cidade_destino, "\n")] = '\0';

                removerConexao(g, cidade_origem, cidade_destino);
                printf("Conexão removida entre %s e %s.\n", cidade_origem, cidade_destino);
                break;

            case 4:
                // Buscar conexões
                printf("Digite o nome da cidade para buscar as conexões: ");
                fgets(cidade_origem, MAX_NOME_CIDADE, stdin);
                cidade_origem[strcspn(cidade_origem, "\n")] = '\0';

                buscarConexoes(g, cidade_origem);
                break;

            case 5:
                // Imprimir o grafo
                imprimirGrafo(g);
                break;

            case 6:
                // Buscar cidades com DFS
                printf("Digite o nome da cidade para iniciar a busca DFS: ");
                fgets(cidade_origem, MAX_NOME_CIDADE, stdin);
                cidade_origem[strcspn(cidade_origem, "\n")] = '\0';

                int cidade_idx = obterIndiceCidade(g, cidade_origem);
                if (cidade_idx != -1) {
                    bool visitado[MAX_CIDADES] = { false };
                    printf("DFS a partir de %s: ", cidade_origem);
                    dfs(g, cidade_idx, visitado);
                    printf("\n");
                } else {
                    printf("Cidade não encontrada.\n");
                }
                break;

            case 7:
                // Buscar cidades com BFS
                printf("Digite o nome da cidade para iniciar a busca BFS: ");
                fgets(cidade_origem, MAX_NOME_CIDADE, stdin);
                cidade_origem[strcspn(cidade_origem, "\n")] = '\0';

                cidade_idx = obterIndiceCidade(g, cidade_origem);
                if (cidade_idx != -1) {
                    printf("BFS a partir de %s: ", cidade_origem);
                    bfs(g, cidade_idx);
                    printf("\n");
                } else {
                    printf("Cidade não encontrada.\n");
                }
                break;

            case 8:
                // Sair
                printf("Saindo do programa...\n");
                liberarGrafo(g); // Libera memória do grafo
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }

    return 0; // Fechar a função main corretamente
}