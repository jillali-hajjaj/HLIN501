#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

typedef struct coord
{
    int abs;
    int ord;
} coord;

void pointRandom(int n, coord point[])
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        point[i].abs = rand() % 613;
        point[i].ord = rand() % 793;

        cout << i << " : " << point[i].abs << " " << point[i].ord << endl;
    }
}

int carre(int n)
{
    return n * n;
}

float distance(coord p1, coord p2)
{
    return sqrt(carre(p2.abs - p1.abs) + carre(p2.ord - p1.ord));
}

void voisins(int n, int dmax, coord point[], vector<int> voisin[], int &m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && distance(point[i], point[j]) <= dmax)
            {
                m++;
                voisin[i].push_back(j);
                //cout << "voisin de " << i << " : " << j << endl;
            }
        }
        //cout << "------------" << endl;
    }
}

void voisins2arete(int n, vector<int> voisins[], int arete[][2])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    { //point i
        for (int j = 0; j < voisins[i].size(); j++)
        { //pour tous les voisins de i
            arete[count][0] = i;
            arete[count][1] = voisins[i].at(j);
            count++;
            //cout << " Arête créée entre " << i << " et " << voisins[i].at(j) << endl;
        }
    }
}

void affichageGraphique(int n, int m, coord point[], int arete[][2], string name)
// Cree le fichier Exemple.ps qui affiche
// les points et l'arbre de Kruskal.     (int n,int m,coord point[],int arete[][2],string name)
{
    ofstream output;
    output.open(name, ios::out);
    output << "%!PS-Adobe-3.0" << endl;
    output << "%%BoundingBox: 0 0 612 792" << endl;
    output << endl;
    for (int i = 0; i < n; i++)
    {
        output << point[i].abs << " " << point[i].ord << " 3 0 360 arc" << endl;
        output << "0 setgray" << endl;
        output << "fill" << endl;
        output << "stroke" << endl;
        output << endl;
    }

    output << endl;

    cout << "m : " << m << endl;

    for (int i = 0; i < m; i++)
    {
        output << point[arete[i][0]].abs << " " << point[arete[i][0]].ord << " moveto" << endl;
        output << point[arete[i][1]].abs << " " << point[arete[i][1]].ord << " lineto" << endl;
        output << "stroke" << endl;
        output << endl;
    }
    output << "showpage";
    output << endl;
}

bool existe(int n, int dis[], bool traite[], int &x)
{
    int distanceMin = -1;
    for (int i = 0; i < n; i++)
    {
        if (traite[i] == 0 && (dis[i] < distanceMin || distanceMin < 0))
        {
            distanceMin = dis[i];
            x = i;
        }
    }
    if (distanceMin > -1)
    {
        traite[x] = true;
        return true;
    }
    return false;
}

void dijkstra(int n, vector<int> voisin[], coord point[], int pere[])
{
    int dis[n];
    bool traite[n];

    for (int i = 1; i < n; i++)
    {
        dis[i] = /*distance(point[0], point[i]);*/ INT32_MAX;
        traite[i] = false;
    }
    pere[0] = 0;
    dis[0] = 0;
    traite[0] = false;

    int x = -1;
    while (existe(n, dis, traite, x))
    {
        for (int i = 0; i < voisin[x].size(); i++)
        {
            if (!traite[voisin[x].at(i)] && dis[voisin[x].at(i)] > dis[x] + distance(point[x], point[voisin[x].at(i)]))
            {

                dis[voisin[x].at(i)] = dis[x] + distance(point[x], point[voisin[x].at(i)]);
                pere[voisin[x].at(i)] = x;
            }
        }
    }
}

int construireArbre(int n, int arbre[][2], int pere[])
{
    int aretes = 0;
    for (int i = 0; i < n; i++)
    {
        arbre[i][0] = i;
        arbre[i][1] = pere[i];
        aretes++;
    }

    return aretes;
}

int main()
{
    int n; // Le nombre de points.
    cout << "Entrer le nombre de points: ";
    //cin >> n;

    int N = 1400;
    int M = (N * (N - 1)) / 2;

    n = N;

    int dmax = 50;         // La distance jusqu'a laquelle on relie deux points.
    coord point[N];        // Les coordonnees des points.
    vector<int> voisin[N]; // Les listes de voisins.
    int arbre[N - 1][2];   // Les aretes de l'arbre de Dijkstra.
    int pere[N];           // La relation de filiation de l'arbre de Dijkstra.
    int m;                 // Le nombre d'aretes
    int arete[M][2];       // Les aretes du graphe

    pointRandom(n, point);
    voisins(n, dmax, point, voisin, m);
    voisins2arete(n, voisin, arete);
    affichageGraphique(n, m, point, arete, "afffichage.ps");
    dijkstra(n, voisin, point, pere);

    int aretes = construireArbre(n, arbre, pere);
    affichageGraphique(n, aretes, point, arbre, "arbre.ps");

    return EXIT_SUCCESS;
}