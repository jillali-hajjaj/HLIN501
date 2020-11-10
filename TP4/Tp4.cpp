#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <time.h>
#include <math.h>
#include <stdio.h>

using namespace std;

const int N = 1400;
const int M = (N * (N - 1)) / 2;

typedef struct coord
{
    int abs;
    int ord;
} coord;

void pointRandom(int n, coord point[])
{

    srand(time(NULL));
    for (int i = 0; i < n; ++i)
    {

        int x = rand() % 612;
        int y = rand() % 792;

        point[i].abs = x;
        point[i].ord = y;

        cout << point[i].abs << " ";
        cout << point[i].ord << endl;
    }
}
void voisins(int n, int dmax, coord point[], vector<int> voisin[], int &m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int distance = sqrt(pow(point[j].abs - point[i].abs, 2) + pow(point[j].ord - point[i].ord, 2));
            if (distance <= dmax)
            {
                voisin[i].push_back(j);
                voisin[j].push_back(i);
                m++;
            }
        }
    }
}
void voisins2arete(int n, vector<int> voisins[], int arete[][2])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arete[i][0] = voisins[i].front();
            arete[i][1] = voisins[j].front();
        }
    }
}

void affichageGraphique(int n, int m, coord point[], int arete[][2], string name)
{
    ofstream output;
    output.open("Exemple.ps", ios::out);
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
    for (int i = 0; i < n - 1; i++)
    {
        output << point[arete[i][0]].abs << " " << point[arete[i][0]].ord
               << " moveto" << endl;
        output << point[arete[i][1]].abs << " " << point[arete[i][1]].ord
               << " lineto" << endl;
        output << "stroke" << endl;
        output << endl;
    }
    output << "showpage";
    output << endl;
}

bool existe(int n, int dis[], bool traite[], int &x);
void dijkstra(int n, vector<int> voisin[], coord point[], int pere[]);
int construireArbre(int n, int arbre[][2], int pere[]);

int main()
{
    int n; // Le nombre de points.
    cout << "Entrer le nombre de points: ";
    cin >> n;
    int dmax = 50;                            // La distance jusqu'a laquelle on relie deux points.
    coord point[300];                         // Les coordonnees des points.
    vector<int> *voisin = new vector<int>[n]; // Les listes de voisins.

    int *arbre = new int[2]; // Les aretes de l'arbre de Dijkstra.
    for (int i = 0; i < n; ++i)
        arbre[i] = new int[2];

    int *pere = new int[n]; // La relation de filiation de l'arbre de Dijkstra.
    int m;                  // Le nombre d'aretes
    pointRandom(n, point);
    voisins(n, dmax, point, voisin, m);
    int **arete = new int *[m]; // Les aretes du graphe
    for (int i = 0; i < m; ++i)
        arete[i] = new int[m];

    voisins2arete(n, voisin, arete);
    return EXIT_SUCCESS;
}
