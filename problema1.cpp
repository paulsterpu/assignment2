#include <fstream>
#include <vector>
#include <set>

int V;		//numarul de noduri

using Graph = std::vector<std::vector<std::pair<long long, long long> > >;

int k = 0;
//k este folosit pentru a verifica o anumita pozitie din apartine
bool apartine[200000];
//retine indicele nodurilor care au fost incluse pana la momentul respectiv in arborele minim
std::set<std::pair<long long, long long> > myset;
//pair-ul din set va contine :  distanta de la arborele minim la celelate noduri si indexul nodurilor respective

long long prim0(Graph& G)
{
	long long j, u, sum = 0;
		
	myset.insert((std::make_pair(0,1)));					//pornesc cu nodul cu indicele 1

	for ( j = 1; j <= V-1; j++){						//pentru restul de V-1 noduri neexplorate
		while ( myset.size() > 0 ){
			if ( apartine[(*(myset.begin())).second] == !k ){	//daca nodul extras din set a fost deja inclus in arborele minim
					myset.erase(myset.begin());		//il sterg din set si extrag altul
				}
			else {
				sum = sum + (*(myset.begin())).first;
				u = (*(myset.begin())).second;		//indicele nodului adaugat in arborele minim
				apartine[u] = !k;			//indic in apartine ca a fost verificat
				myset.erase(myset.begin());
				break;
			}
		}

		for (auto &adj : G[u]) {			//toti vecini lui u care nu au fost adaugati in arborele minim
								//sunt inserati in set ordonat in functie de distanta lor la arborele minim
			if ( apartine[adj.first] == k ){
				myset.insert((std::make_pair(adj.second,adj.first)));
			}
		}
	}

	while ( myset.size() > 0 ){			//daca va ramane in set un singur nod care nu a fost adaugat
		if ( apartine[(*(myset.begin())).second] == !k ){		//daca nodul extras din set a fost deja inclus in arborele minim
			myset.erase(myset.begin());
		}
		else {
			sum = sum + (*(myset.begin())).first;
			apartine[(*(myset.begin())).second] = !k;
			myset.erase(myset.begin());
			break;
		}
	}
	myset.clear();
	return sum;
}

long long prim(Graph& G , long long s , long long d,long long c)
{
	long long j,u,sum = c;		//initializez suma cu costul muchiei (s,d)

	//identic cu prim0 , dar intai adaug in arborele minim muchia (s,d)

	apartine[s] = !k;
	apartine[d] = !k;

	for (auto &adj : G[s]) {
		if ( apartine[adj.first] == k ){
			myset.insert((std::make_pair(adj.second,adj.first)));
		}
	}
	for (auto &adj : G[d]) {
		if ( apartine[adj.first] == k ){
			myset.insert((std::make_pair(adj.second,adj.first)));
		}
	}

	for ( j = 1; j <= V-2; j++){
		while ( myset.size() > 0 ){
			if ( apartine[(*(myset.begin())).second] == !k ){		//daca nodul extras din set a fost deja inclus in arborele minim
					myset.erase(myset.begin());
			}
			else {
				sum = sum + (*(myset.begin())).first;
				u = (*(myset.begin())).second;				//indicele nodului adaugat in arborele minim
				apartine[u] = !k;					//indic in apartine ca a fost verificat
				myset.erase(myset.begin());
				break;
			}
		}
		for (auto &adj : G[u]) {				//toti vecini lui u care nu au fost adaugati in arborele minim
			if ( apartine[adj.first] == k ){		//sunt inserati in set ordonat in functie de distanta lor la arborele minim
				myset.insert((std::make_pair(adj.second,adj.first)));

			}
		}
	}

	while ( myset.size() > 0 ){
		if ( apartine[(*(myset.begin())).second] == !k ){		//daca nodul extras din set a fost deja inclus in arborele minim
			myset.erase(myset.begin());
		}
		else {
			sum = sum + (*(myset.begin())).first;
			apartine[(*(myset.begin())).second] = !k;
			myset.erase(myset.begin());
			break;
		}
	}
	myset.clear();
	return sum;
}

int main(){

	long long num_nodes, num_edges, q, m, x, y, c;

	FILE *f,*g;

	f = fopen("kim.in","r");
	g = fopen("kim.out","w");

	fscanf(f,"%lld %lld %lld",&num_nodes,&num_edges , &q);

	long long noduri[3][num_edges+1],rez[num_edges+1];
	//rez[i] va contine suma muchiilor pentru arborele minim care va contine obligatoriu muchia cu indicele i
	//in noduri se va retine informatia despre muchia i , adica nodul sursa , nodu destinatie si costul muchiei

	V = num_nodes;
	Graph G(num_nodes + 1);

	for ( long long i = 1 ; i <= V ; i++ ){			//initializarea lui apartine
		apartine[i] = 0;
	}

	for (long long i = 1; i <= num_edges; i++) {		//citirea grafului
		fscanf(f,"%lld %lld %lld",&x,&y , &c);
		G[x].push_back(std::make_pair(y, c));
		noduri[0][i] = x;
		noduri[1][i] = y;
		noduri[2][i] = c;
		G[y].push_back(std::make_pair(x, c));
		rez[i] = -1;
	}

	fprintf(g,"%lld\n" , prim0(G));
	k = !k;

	for ( long long i = 1 ; i <= q ; i++ ){
		fscanf(f,"%lld", &m);
		if ( rez[m] == -1 ){		//daca nu s-a calculat deja arborele minim care contine muchia cu indicele m
			rez[m] = prim(G,noduri[0][m],noduri[1][m],noduri[2][m]);
			k = !k;
			fprintf(g,"%lld\n",rez[m]);
		}
		else {
			fprintf(g,"%lld\n",rez[m]);
		}
	}
fclose(f);
fclose(g);
return 0;
}
