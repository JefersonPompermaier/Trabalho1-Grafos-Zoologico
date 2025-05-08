/*
 * Trabalho 1 - Zoologico
 *
 * GEN254 - Grafos - 2025/1
 *
 * Nome:      Jeferson Pompermaier e Marco Lunardi
 * Matricula: 2221101042 e 
 */

 #include "Grafo.h"
 #include <vector>
 
 Grafo::Grafo(int num_vertices) : num_vertices_(num_vertices) {
     matriz_adj_.resize(num_vertices, std::vector<bool>(num_vertices, false));
 }
 
 Grafo::~Grafo() {
     // Não é necessário liberar memória manualmente, pois std::vector gerencia isso
 }
 
 void Grafo::insere_aresta(Aresta e) {
     if (e.v1 >= 0 && e.v1 < num_vertices_ && e.v2 >= 0 && e.v2 < num_vertices_ && e.v1 != e.v2) {
         matriz_adj_[e.v1][e.v2] = true;
         matriz_adj_[e.v2][e.v1] = true; // Grafo não-direcionado
     }
 }
 
 bool Grafo::eh_bipartido_1() {
     std::vector<int> assignment(num_vertices_, -1); // -1: não atribuído, 0: conjunto A, 1: conjunto B
     for (int v = num_vertices_ - 1; v >= 0; --v) {
         bool can_place_in_A = true;
         for (int u = v + 1; u < num_vertices_; ++u) {
             if (assignment[u] == 0 && matriz_adj_[v][u]) {
                 can_place_in_A = false;
                 break;
             }
         }
         if (can_place_in_A) {
             assignment[v] = 0;
             continue;
         }
         bool can_place_in_B = true;
         for (int u = v + 1; u < num_vertices_; ++u) {
             if (assignment[u] == 1 && matriz_adj_[v][u]) {
                 can_place_in_B = false;
                 break;
             }
         }
         if (can_place_in_B) {
             assignment[v] = 1;
         } else {
             return false; // Não pode ser colocado em nenhum conjunto
         }
     }
     return true;
 }
 
 bool Grafo::eh_bipartido_2() {
     std::vector<int> cores(num_vertices_, -1); // -1: não colorido, 0: conjunto1, 1: conjunto2
     std::vector<bool> visitados(num_vertices_, false);
 
     // Verifica cada componente conexa
     for (int v = 0; v < num_vertices_; ++v) {
         if (!visitados[v]) {
             cores[v] = 0; // Inicia com a cor 0
             if (!eh_bipartido_2_dfs(v, cores, visitados)) {
                 return false;
             }
         }
     }
     return true;
 }
 
 bool Grafo::eh_bipartido_2_dfs(int v, std::vector<int>& cores, std::vector<bool>& visitados) {
     visitados[v] = true;
 
     // Verifica todos os vizinhos
     for (int u = 0; u < num_vertices_; ++u) {
         if (matriz_adj_[v][u]) {
             if (!visitados[u]) {
                 // Atribui a cor oposta ao vértice atual
                 cores[u] = 1 - cores[v];
                 if (!eh_bipartido_2_dfs(u, cores, visitados)) {
                     return false;
                 }
             } else if (cores[u] == cores[v]) {
                 // Se o vizinho já foi visitado e tem a mesma cor, não é bipartido
                 return false;
             }
         }
     }
     return true;
 }