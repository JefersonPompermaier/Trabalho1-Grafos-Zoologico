/*
 * Trabalho 1 - Zoologico
 *
 * GEN254 - Grafos - 2025/1
 *
 * Nome:      Jeferson Pompermaier e Marco Lunardi
 * Matricula: 2221101042 e 2221101054
 */

 #include <iostream>
 #include "Grafo.h"
 #include "Aresta.h"

 using namespace std;
 
 int main() {
     int num_vertices, relacoes;
     cin >> num_vertices >> relacoes;
 
     Grafo g(num_vertices); // Cria grafo com A vértices
 
     // Lê as R relações
     for (int i = 0; i < relacoes; ++i) {
         int v1, v2;
         char relacao;
         cin >> v1 >> v2 >> relacao;
 
         // Se Z é 'A', os grupos se atacam, então adiciona uma aresta
         if (relacao == 'A') {
             g.insere_aresta(Aresta(v1, v2));
         }
         // Se Z é 'N', os grupos não se atacam, então não adiciona aresta
     }
 
     // Executa eh_bipartido_1 e imprime resultado
     if(g.eh_bipartido_1()){
        cout << "SIM\n";
     }else{
        cout << "NAO\n";
     }
 
     // Executa eh_bipartido_2 e imprime resultado
     if(g.eh_bipartido_2()){
        cout << "SIM\n";
     }else{
        cout << "NAO\n";
     }
 
     return 0;
 }