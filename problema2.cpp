#include <fstream>
#include <vector>

using Graph = std::vector<std::vector<long long> >;

long long V, cicluri = 0, conexe = 0;
//numarul de noduri , numarul de cicluri si numarul de componente conexe pentru un graf
int k;
//k setat pe 1 cand a fost gasit un ciclu intr-o componenta conexa

void explorare( long long v , bool *vizitat , Graph& G , long long *parinte , long long p){

	//p reprezinta parintele lui v din recursivitatea anterioara

	vizitat[v] = true;			//marchez nodul curent ca fiind vizitat

	for (auto &adj : G[v]) {		//pentru toti vecinii nodului curent
		if ( vizitat[adj] == false ){		//daca vecinul nu a mai fost vizitat ii retin parintele si reintru in recursivitate
			parinte[adj] = v;
			explorare(adj,vizitat,G,parinte,v);
		}
		else if ( parinte[adj] != -1 && adj != p) {	//daca vecinul a mai fost vizitat si nu este cel din care s-a intrat in recursivitate
			k = 1;					//atunci am gasit un ciclu
		}
	}
}

long long DFS(Graph& G,bool *vizitat,long long *parinte){

	for ( long long i = 1 ; i <= V ; i++ ){
		if ( vizitat[i] == false ){
			conexe +=1;		//numarul componentelor conexe creste odata cu fiecare intrare in recursivitate
			explorare(i,vizitat,G,parinte,-1);
			if ( k == 1 ){		//daca a fost gasit un ciclu pentru componenta conexa curenta
				cicluri += 1;
				k = 0;
			}
		}
	}

return conexe-cicluri;

}

int main(){

	FILE *f,*g;

	f = fopen("portal.in","r");
	g = fopen("portal.out","w");

	long long num_nodes, num_edges, x, y;

	fscanf(f,"%lld %lld",&num_nodes,&num_edges);
	V = num_nodes;
	Graph G(num_nodes + 1);

	bool vizitat[V];		//retine pentru fiecare nod daca a fost vizitat
	long long parinte[V];		//retine parintele fiecarui nod

	for ( long long i = 1 ; i <= V ; i++ ){
		vizitat[i] = false;
		parinte[i] = -1;
	}

	for (long long i = 1; i <= num_edges; i++) {		//citire graf
	    fscanf(f,"%lld %lld",&x,&y);
	    G[x].push_back(y);
	    G[y].push_back(x);
	}

	fprintf(g,"%lld",DFS(G,vizitat,parinte));		//afisare rezultat
	fclose(f);
	fclose(g);

return 0;
}
