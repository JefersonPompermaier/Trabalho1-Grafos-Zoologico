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

bool Grafo::eh_bipartido_1() {
    vector<int> atribuicao(num_vertices_, -1); 
    return eh_bipartido_1_recursivo(num_vertices_ - 1, atribuicao); 
}


bool Grafo::eh_bipartido_1_recursivo(int vertice, vector<int>& atribuicao) {
    if (vertice < 0) return true;

    bool vai_para_grupo_A = true; 

    for (int u = vertice + 1; u < num_vertices_; ++u) {
        if (atribuicao[u] == 0 && matriz_adj_[vertice][u]) {
            vai_para_grupo_A = false; 
            break;
        }
    }

    if (vai_para_grupo_A) {
        atribuicao[vertice] = 0; 
        return eh_bipartido_1_recursivo(vertice - 1, atribuicao); 
    }

    bool vai_para_grupo_B = true; 

    for (int u = vertice + 1; u < num_vertices_; ++u) {
        if (atribuicao[u] == 1 && matriz_adj_[vertice][u]) {
            vai_para_grupo_B = false; 
            break;
        }
    }

    if (vai_para_grupo_B) {
        atribuicao[vertice] = 1; 
        return eh_bipartido_1_recursivo(vertice - 1, atribuicao); 
    }

    return false; 
}


bool Grafo::eh_bipartido_2() {
    vector<int> grupo(num_vertices_, -1); 
    vector<int> visitados(num_vertices_, 0);

    for (int vertice = 0; vertice < num_vertices_; ++vertice) {
        if (!visitados[vertice]) {
            grupo[vertice] = 0; 
            if (!eh_bipartido_2_prof(vertice, grupo, visitados)) {
                return false; 
            }
        }
    }
    return true; 
}

bool Grafo::eh_bipartido_2_prof(int vertice, vector<int>& grupo, vector<int>& visitados) {
    visitados[vertice] = 1;

    for (int u = 0; u < num_vertices_; ++u) {
        if (matriz_adj_[vertice][u]) {
            if (!visitados[u]) {
                grupo[u] = 1 - grupo[vertice]; 
                if (!eh_bipartido_2_prof(u, grupo, visitados)) {
                    return false;
                }
            } else if (grupo[u] == grupo[vertice]) {
                return false; 
            }
        }
    }
    return true;
}
