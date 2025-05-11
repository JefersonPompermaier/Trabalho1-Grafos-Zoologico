/*
 * Trabalho 1 - Zoologico
 *
 * GEN254 - Grafos - 2025/1
 *
 * Nome:      Jeferson Pompermaier e Marco Lunardi
 * Matricula: 2221101042 e 2221101054
 */

 #ifndef GRAFO_H
 #define GRAFO_H
 
 #include "Aresta.h"
 #include <vector>

 using namespace std;
 
 class Grafo {
 public:
     Grafo(int num_vertices);
     void insere_aresta(Aresta e);
     bool eh_bipartido_1();
     bool eh_bipartido_2();
 private:
     int num_vertices_;
     vector<vector<int>> matriz_adj_;
     bool eh_bipartido_2_prof(int v, vector<int>& cores, vector<int>& visitados);
     bool eh_bipartido_1_recursivo (int vertice, vector<int>& atribuicao);
 };
 
 #endif /* GRAFO_H */