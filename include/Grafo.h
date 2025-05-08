/*
 * Trabalho 1 - Zoologico
 *
 * GEN254 - Grafos - 2025/1
 *
 * Nome:      Jeferson Pompermaier e Marco Lunardi
 * Matricula: 2221101042 e 
 */

 #ifndef GRAFO_H
 #define GRAFO_H
 
 #include "Aresta.h"
 #include <vector>
 
 class Grafo {
 public:
     Grafo(int num_vertices);
     ~Grafo();
     void insere_aresta(Aresta e);
     bool eh_bipartido_1();
     bool eh_bipartido_2();
 private:
     int num_vertices_;
     std::vector<std::vector<bool>> matriz_adj_;
     bool eh_bipartido_1_recursivo(int v, std::vector<int>& conjunto1, std::vector<int>& conjunto2, std::vector<bool>& removidos);
     bool eh_bipartido_2_dfs(int v, std::vector<int>& cores, std::vector<bool>& visitados);
 };
 
 #endif /* GRAFO_H */