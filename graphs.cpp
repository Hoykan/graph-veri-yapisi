#include <iostream>
#include <vector>
#include <map>
using namespace std;
class Graph
{
private:
	map<int, vector<int>> adjlist;
public:
	// yeni bir dugum eklemek icin kullanilan metod
	void addVertex(int vertex)
	{
		// Parametre olarak gelen vertex varsa islem yapma yoksa ekle
		if (adjlist.find(vertex) == adjlist.end())
		{
			vector<int> neighbors; // yeni bir komsu dugum listesi
			adjlist[vertex] = neighbors; // dugumu komsu dugum listesiyle(vector) iliskilendirmesi
		}
	}
	// yeni bir edge(kenar) ekleme
	void addEdge(int from, int to)
	{
		// verilen dugumler arasina edge ekle
		// ilk olarak dugum ekliyoruz,eger henuz dugumler eklenmemisse
		addVertex(from);
		addVertex(to);
		// edge her iki dugumede(vertexe) eklenir 
		adjlist[from].push_back(to);
		adjlist[to].push_back(from);
	}
	void printGraph()
	{
		int nunVertices = adjlist.size();
		for (int i = 0; i < nunVertices; i++)
		{
			int vertex = i;
			auto it = adjlist.begin();
			advance(it, vertex);

			vector<int>& neighbors = adjlist[it->first];//direkt it->second yazilabilir 
			cout << "Adjacent to Vertex " << vertex << ": ";
			for (int j = 0; j < neighbors.size(); j++)
			{
				cout << neighbors[j]<<" ";
			}
			cout << endl;
		}
	}
	void removeVertex(int vertex) // bir dugumu(vertex)silmek icin kullanilir
	{
		if (adjlist.find(vertex) != adjlist.end()) // silinmek istenen vertex graph icinde mevcut mu onun kontorlu yapilir
		{
			//dugumu listeden cikar
			adjlist.erase(vertex);

			// bagli vertexlerdeki ilgili edgeleri de sil
			for (map<int, vector<int>>::iterator it = adjlist.begin(); it != adjlist.end(); it++)
			{
				int key = it->first; //dugum anahtari-key
				vector<int>& neighbors = it->second; // dugumun komsulari-value
				
				// vector icinde silinen vertex bulunursa onu kaldir
				vector<int>::iterator vecIt = neighbors.begin();
				while (vecIt != neighbors.end())
				{
					if (*vecIt == vertex)
					{
						vecIt = neighbors.erase(vecIt);
					}
					else {
						vecIt++;
					}
				}
			}
		
		}

	}
	void removeEdge(int from,int to) //bir kenari (edge) silmek icin kullanilir
	{
		if (adjlist.find(from) != adjlist.end() && adjlist.find(to) != adjlist.end())
		{
			vector<int>& fromNeighbors = adjlist[from];
			vector<int>& toNeighbors = adjlist[to];
			for (int i = 0; i < fromNeighbors.size(); i++)
			{
				if (fromNeighbors[i] == to)
				{
					fromNeighbors.erase(fromNeighbors.begin() + i); // i. elemani siler
					break; // ilk eslesmeyi kaldirip donguden cik
				}

			}
			for (int i = 0; i < toNeighbors.size(); i++)
			{
				if (toNeighbors[i] == to)
				{
					toNeighbors.erase(toNeighbors.begin() + i);// i. elemani siler
					break;// ilk eslesmeyi kaldirip donguden cik
				}
			}
		}
	}
};
int main() {
	Graph g;
	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);
	g.addVertex(5);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(2,4);
	g.addEdge(2, 5);
	g.addEdge(3, 5);
	g.addEdge(4, 5);
	cout << "Baslangic graph:\n";
	g.printGraph();
	cout << endl << "-----Remove vertex metodu deneme-----" << endl;
	g.removeVertex(1);
	g.printGraph();
	cout << endl << "-----Remove edge metodu deneme-----" << endl;
	g.removeEdge(2, 5);
	g.printGraph();
	cout << endl << "-----Tum metodlari deneme-----" << endl;
	g.addVertex(8);
	g.addEdge(8, 2);
	g.addEdge(8, 4);
	g.printGraph();
	return 0;
}