/*
 * Trabalho 1 - Zoologico
 *
 * GEN254 - Grafos - 2025/1
 *
 * Nome:      Jeferson Pompermaier e Marco Lunardi
 * Matricula: 2221101042 e 2221101054
 */

#include "Grafo.h"
#include <vector>

using namespace std;

Grafo::Grafo(int num_vertices) : num_vertices_(num_vertices) {
    matriz_adj_.resize(num_vertices, vector<int>(num_vertices, false));
}

void Grafo::insere_aresta(Aresta e) {
    if (e.v1 >= 0 && e.v1 < num_vertices_ && e.v2 >= 0 && e.v2 < num_vertices_ && e.v1 != e.v2) {
        matriz_adj_[e.v1][e.v2] = 1;
        matriz_adj_[e.v2][e.v1] = 1;
    }
}

// Função pública que inicia a verificação se o grafo é bipartido
bool Grafo::eh_bipartido_1() {
    vector<int> atribuicao(num_vertices_, -1); // -1: vértice ainda não atribuído a nenhum conjunto
    return eh_bipartido_1_recursivo(num_vertices_ - 1, atribuicao); // Chamada recursiva a partir do último vértice
}

// Função auxiliar recursiva que tenta atribuir os vértices a dois conjuntos (0 ou 1)
bool Grafo::eh_bipartido_1_recursivo(int vertice, vector<int>& atribuicao) {
    if (vertice < 0) return true; // Caso base: todos os vértices foram atribuídos com sucesso

    bool vai_para_grupo_A = true; // Tentativa de colocar o vértice atual no grupo A (0)

    // Verifica se algum vértice adjacente já está no grupo A
    for (int u = vertice + 1; u < num_vertices_; ++u) {
        if (atribuicao[u] == 0 && matriz_adj_[vertice][u]) {
            vai_para_grupo_A = false; // Conflito encontrado, não pode ir para grupo A
            break;
        }
    }

    if (vai_para_grupo_A) {
        atribuicao[vertice] = 0; // Atribui vértice ao grupo A
        return eh_bipartido_1_recursivo(vertice - 1, atribuicao); // Continua com o próximo vértice
    }

    bool vai_para_grupo_B = true; // Tentativa de colocar o vértice atual no grupo B (1)

    // Verifica se algum vértice adjacente já está no grupo B
    for (int u = vertice + 1; u < num_vertices_; ++u) {
        if (atribuicao[u] == 1 && matriz_adj_[vertice][u]) {
            vai_para_grupo_B = false; // Conflito encontrado, não pode ir para grupo B
            break;
        }
    }

    if (vai_para_grupo_B) {
        atribuicao[vertice] = 1; // Atribui vértice ao grupo B
        return eh_bipartido_1_recursivo(vertice - 1, atribuicao); // Continua com o próximo vértice
    }

    return false; // Se não puder ir para nenhum grupo, grafo não é bipartido
}


// Verifica se o grafo é bipartido com busca em profundidade
bool Grafo::eh_bipartido_2() {
    vector<int> grupo(num_vertices_, -1); // -1: não pertence a grupo, 0: conjunto1, 1: conjunto2
    vector<int> visitados(num_vertices_, 0);

    // Verifica cada componente conexa
    for (int vertice = 0; vertice < num_vertices_; ++vertice) {
        if (!visitados[vertice]) {
            grupo[vertice] = 0; // Inicia com o grupo A
            if (!eh_bipartido_2_prof(vertice, grupo, visitados)) {
                return false; // Se qualquer componente não for bipartida, retorna falso
            }
        }
    }
    return true; // Todas as componentes são bipartidas
}

// Busca em profundidade recursiva para verificar bipartição
bool Grafo::eh_bipartido_2_prof(int vertice, vector<int>& grupo, vector<int>& visitados) {
    visitados[vertice] = 1;

    // Verifica todos os vizinhos do vértice atual
    for (int u = 0; u < num_vertices_; ++u) {
        if (matriz_adj_[vertice][u]) {
            if (!visitados[u]) {
                grupo[u] = 1 - grupo[vertice]; // Atribui grupo oposto ao atual
                if (!eh_bipartido_2_prof(u, grupo, visitados)) {
                    return false; // Se qualquer vizinho não for bipartido, retorna falso
                }
            } else if (grupo[u] == grupo[vertice]) {
                return false; // dois vértices adjacentes no mesmo grupo
            }
        }
    }
    return true;
}
