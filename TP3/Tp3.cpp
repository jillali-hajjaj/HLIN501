#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <queue>
#include <stack>
using namespace std;

void voisinsRandom(int n, int m, vector<int> voisins[])
{
    int x, y;
    for (int i = 0; i < m; i++)
    {
        do
        {
            x = rand() % n;
            y = rand() % n;
        } while (x == y || find(voisins[x].begin(), voisins[x].end(), y) != voisins[x].end());
        voisins[x].push_back(y);
        voisins[y].push_back(x);
    }
}

void parcoursLargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[])
{
    int *dv = new int[n];
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
        while (!AT.empty())
        {
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
void parcoursLargeurCorrection(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[])
{
    queue<int> filetraitement;
    filetraitement.push(0);
    for (int i = 0; i < n; i++)
        pere[i] = -2;
    pere[0] = -1;
    int comptordre = 0;
    while (!filetraitement.empty())
    {
        ordre[filetraitement.front()] = comptordre;
        comptordre++;
        if (pere[filetraitement.front()] == -1)
            niveau[filetraitement.front()] = 0;
        else
            niveau[filetraitement.front()] = niveau[pere[filetraitement.front()]] + 1;
        for (int i = 0; i < voisins[filetraitement.front()].size(); i++)
        {
            if (pere[voisins[filetraitement.front()].at(i)] == -2)
            {
                pere[voisins[filetraitement.front()].at(i)] = filetraitement.front();
                filetraitement.push(voisins[filetraitement.front()].at(i));
            }
        }
        filetraitement.pop();
    }

    for (int i = 0; i < n; i++)
    {
        cout << "s:" << i << "\t" << pere[i] << "\t" << ordre[i] << "\t" << niveau[i] << endl;
    }
}

void parcoursProfondeurCorrection(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[])
{
    stack<int> piletraitement;
    piletraitement.push(0);
    for (int i = 0; i < n; i++)
        pere[i] = -2;
    pere[0] = -1;
    int comptordre = 0;
    while (!piletraitement.empty())
    {
        int sommetCourant = piletraitement.top();
        piletraitement.pop();
        ordre[sommetCourant] = comptordre;
        comptordre++;
        if (pere[sommetCourant] == -1)
            niveau[sommetCourant] = 0;
        else
            niveau[sommetCourant] = niveau[pere[sommetCourant]] + 1;
        for (int i = 0; i < voisins[sommetCourant].size(); i++)
        {
            if (pere[voisins[sommetCourant].at(i)] == -2)
            {
                pere[voisins[sommetCourant].at(i)] = sommetCourant;
                piletraitement.push(voisins[sommetCourant].at(i));
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << "s:" << i << "\t" << pere[i] << "\t" << ordre[i] << "\t" << niveau[i] << endl;
    }
}

void ecritureNiveaux(int n, int niveau[])
{
    int compteur = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (niveau[j] == niveau[i])
            {
                compteur++;
            }
        }
        cout << " il y a " << compteur << " sommets de niveau " << i << endl;
        compteur = 0;
    }
}

int main()
{
    int n; // Le nombre de sommets.
    int m; // Le nombre d'aretes.
    cout << "Entrer le nombre de sommets: ";
    cin >> n;
    cout << "Entrer le nombre d'aretes: ";
    cin >> m;
    vector<int> *voisins = new vector<int>[n]; // Les listes des voisins.

    int *pere = new int[n];  // L'arbre en largeur.
    int *ordre = new int[n]; // L'ordre de parcours.
    int *niveau = new int[n];
    ; // Le niveau du point.
    voisinsRandom(n, m, voisins);
    parcoursLargeurCorrection(n, voisins, niveau, ordre, pere);
    cout << "-----------------------------------------------------------------------------" << endl;
    parcoursProfondeurCorrection(n, voisins, niveau, ordre, pere);
    return EXIT_SUCCESS;
}
