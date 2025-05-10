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

// Verifica se o grafo é bipartido em ordem decrescente
bool Grafo::eh_bipartido_1() {
    vector<int> atribuicao(num_vertices_, -1); // -1: não atribuído, 0: conjunto A, 1: conjunto B

    // Percorre os vértices em ordem decrescente
    for (int vertice = num_vertices_ - 1; vertice >= 0; --vertice) {

        bool vai_para_grupo_A = true;

        // Verifica se pode ir para o grupo A
        for (int u = vertice + 1; u < num_vertices_; ++u) {
            if (atribuicao[u] == 0 && matriz_adj_[vertice][u]) {
                vai_para_grupo_A = false;
                break;
            }
        }

        // Se puder ir para A, atribui e continua
        if (vai_para_grupo_A) {
            atribuicao[vertice] = 0;
            continue;
        }

        bool vai_para_grupo_B = true;

        // Caso contrário, verifica se pode ir para o grupo B
        for (int u = vertice + 1; u < num_vertices_; ++u) {
            if (atribuicao[u] == 1 && matriz_adj_[vertice][u]) {
                vai_para_grupo_B = false;
                break;
            }
        }

        // Se puder ir para B, atribui; senão, o grafo não é bipartido
        if (vai_para_grupo_B) {
            atribuicao[vertice] = 1;
        } else {
            return false; // Não pode ser colocado em nenhum conjunto
        }
    }
    return true; 
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
