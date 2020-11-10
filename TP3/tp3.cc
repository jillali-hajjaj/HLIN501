#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include "../TP2/affichage.cc"
using namespace std;

void voisinsRandom(int n, int m, vector<int>voisins[], coord point[n])
{
  int x,y;
  for(int i = 0 ; i < n ; ++i)
  {

    int x= rand()%n ;
    int y= rand()%n ;


    point[i].abs = x;
    point[i].ord = y;
    
    cout << point[i].abs << " ";
    cout << point[i].ord << endl;
  }
  for(int i=0;i<m;i++)
  {
    do
    {
      x=rand()%n;
      y=rand()%n;
    }
    while(x==y || find(voisins[x].begin(),voisins[x].end(),y)!=voisins[x].end());
    voisins[x].push_back(y);
    voisins[y].push_back(x);
  }
  
}


void parcoursLargeur(int n, vector<int> voisins[], int niveau[],int ordre[], int pere[]){
    int dv[n];
    int r = 0;
    vector<int> AT;
    int temps = 0;
    for (int i = 0; i < n; ++i)
    {
      dv[i] = 0;
      dv[r] = 1;
      ordre[r] = 1; 
      pere[r] = r;
      niveau[r] = 0;
      temps = 2;
      AT.push_back(r);
      while(!AT.empty()){
        int v = AT.at(0);
        AT.erase(AT.begin());
        for (int j = 0; j < voisins[v].size(); ++j)
        {
          if (dv[j] == 0)
          {
            dv[j] = 1;
            AT.push_back(j);
            ordre[j] = temps;
            temps++;
            pere[j] = v;
            niveau[j] = niveau[v] + 1;
          }
        }
      }
    }
}


void affichage(int n,int m ,int pere[]){
  int arbre[n-1][2];

  for (int i = 0; i < m-1 ; ++i)
  {
    // arbre[i][pere[i]] = 1;
    cout << "arete : " << i << "  "<< pere[i] <<endl;
  }
}


int main()
{
  int n;                                    // Le nombre de sommets.
  int m;                                    // Le nombre d'aretes.
  cout << "Entrer le nombre de sommets: ";
  cin >> n;
  cout << "Entrer le nombre d'aretes: ";
  cin >> m;
  vector<int> voisins[n];                   // Les listes des voisins. 
  coord point[n];
  int pere[n];                              // L'arbre en largeur.
  int ordre[n];                             // L'ordre de parcours.
  int niveau[n];                            // Le niveau du point.
  voisinsRandom(n,m, voisins,point);
  parcoursLargeur(n,voisins,niveau,ordre,pere);
  affichage(n,m,pere);

  return EXIT_SUCCESS;
}
