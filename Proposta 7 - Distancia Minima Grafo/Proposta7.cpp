// Implementação do algoritmo de Dijkstra
// Teste: http://br.spoj.com/problems/ENGARRAF/

#include <iostream>
#include <list>
#include <queue>
#include <vector>
#define INFINITO 10000000

using namespace std;

class Grafo
{
private:
	int V; // número de vértices

	// ponteiro para um array contendo as listas de adjacências
	list<pair<int, int> > * adj;

public:

	// construtor
	Grafo(int V)
	{
		this->V = V; // atribui o número de vértices

		/*
			cria as listas onde cada lista é uma lista de pairs
			onde cada pair é formado pelo vértice destino e o custo
		*/
		adj = new list<pair<int, int> >[V];
	}

	// adiciona uma aresta ao grafo de v1 à v2 e de v2 à v1
	void addAresta(int v1, int v2, int custo)
	{
		adj[v1].push_back(make_pair(v2, custo));
		adj[v2].push_back(make_pair(v1, custo));
	}

	// algoritmo de Dijkstra
	int dijkstra(int orig, int dest)
	{
		// vetor de distâncias
		int dist[V];

		/*
		   vetor de visitados serve para caso o vértice já tenha sido
		   expandido (visitado), não expandir mais
		*/
		int visitados[V];

		// fila de prioridades de pair (distancia, vértice)
		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > pq;

		// inicia o vetor de distâncias e visitados
		for(int i = 0; i < V; i++)
		{
			dist[i] = INFINITO;
			visitados[i] = false;
		}

		// a distância de orig para orig é 0
		dist[orig] = 0;

		// insere na fila
		pq.push(make_pair(dist[orig], orig));

		// loop do algoritmo
		while(!pq.empty())
		{
			pair<int, int> p = pq.top(); // extrai o pair do topo
			int u = p.second; // obtém o vértice do pair
			pq.pop(); // remove da fila

			// verifica se o vértice não foi expandido
			if(visitados[u] == false)
			{
				// marca como visitado
				visitados[u] = true;

				list<pair<int, int> >::iterator it;

				// percorre os vértices "v" adjacentes de "u"
				for(it = adj[u].begin(); it != adj[u].end(); it++)
				{
					// obtém o vértice adjacente e o custo da aresta
					int v = it->first;
					int custo_aresta = it->second;

					// relaxamento (u, v)
					if(dist[v] > (dist[u] + custo_aresta))
					{
						// atualiza a distância de "v" e insere na fila
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}

		// retorna a distância mínima até o destino
		return dist[dest];
	}
};

int melhororigem(vector<int> &results){
    int menor = results[0];
    int vertice = 0;
    int c = 0;
    for (auto i = results.begin(); i != results.end(); ++i){
        if (menor > *i){
            menor = *i;
            vertice = c;
        }
        c++;
    }
    results[vertice] = INFINITO;
    cout << endl;
    return vertice;
}

vector<int> somamenoresdist(Grafo g, int vertice){
    vector<int> somas;
    int soma = 0;
    for (int i = 1; i < vertice+1; i++){
        for(int j = 1; j < vertice+1; j++){
            soma = soma + g.dijkstra(i, j);
            }
        cout <<"O vértice "<<i<<" Possui soma de distância minima com os outros vértices = "<<soma<< endl;
        somas.push_back(soma);
        soma = 0;
        }
    return (somas);
}

int main(int argc, char *argv[])
{
    int v1,v2,p,vertice;
    FILE *arq;
    arq = fopen("input.txt", "r");
    
    fscanf(arq, "%d", &vertice);
	Grafo g(vertice+1);
	while (!feof(arq)){
	fscanf(arq, "%d%d%d", &v1,&v2,&p);
	g.addAresta(v1, v2, p);
	}
	fclose(arq);
    static vector<int> results = somamenoresdist(g, vertice);
    int a = melhororigem(results);
    int b = melhororigem(results);
    cout <<"Melhores Vertices são: " << a+1 << " e "<< b+1;
	return 0;
}