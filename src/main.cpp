/*
 * Trabalho 1 - Zoologico
 *
 * GEN254 - Grafos - 2025/1
 *
 * Nome:      [Seu Nome]
 * Matricula: [Sua Matrícula]
 */

 #include <iostream>
 #include "Grafo.h"
 #include "Aresta.h"
 
 int main() {
     int A, R;
     std::cin >> A >> R;
 
     Grafo g(A); // Cria grafo com A vértices
 
     // Lê as R relações
     for (int i = 0; i < R; ++i) {
         int X, Y;
         char Z;
         std::cin >> X >> Y >> Z;
 
         // Se Z é 'A', os grupos se atacam, então adiciona uma aresta
         if (Z == 'A') {
             g.insere_aresta(Aresta(X, Y));
         }
         // Se Z é 'N', os grupos não se atacam, então não adiciona aresta
     }
 
     // Executa eh_bipartido_1 e imprime resultado
     std::cout << (g.eh_bipartido_1() ? "SIM" : "NAO") << std::endl;
 
     // Executa eh_bipartido_2 e imprime resultado
     std::cout << (g.eh_bipartido_2() ? "SIM" : "NAO") << std::endl;
 
     return 0;
 }