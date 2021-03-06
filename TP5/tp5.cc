#include <iostream>
#include <vector>

using namespace std;

const int N = 6;
const int INF = 9999; //La valeur infinie.

bool floydWarshall(int longueur[][N], int dist[][N], int chemin[][N])
{
    for (int i = 0; i < N; i++)
    {
        dist[i][i] = 0;
        chemin[i][i] = i;
        for (int j = 0; j < N; j++)
        {
            if (longueur[i][j] < INF)
            {
                dist[i][j] = longueur[i][j];
                chemin[i][j] = j;
            }
            else
            {
                dist[i][j] = INF;
                chemin[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    chemin[i][j] = chemin[i][k];
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (dist[i][i] < 0)
        {
            return false;
        }
    }
    return true;
}

bool itineraire(int depart, int arrivee, int chemin[][N])
{

    if (chemin[depart][arrivee] == -1)
        return false;

    int courant = depart;
    if (chemin[courant][arrivee] < 0)
    {
        return false;
    }

    while (chemin[courant][arrivee] != arrivee)
    {

        cout << courant << "->";
        courant = chemin[courant][arrivee];
    }
    cout << arrivee << endl;

    return true;
}
void affichage(int dist[][N], int chemin[][N])
{

    for (int depart = 0; depart < N; ++depart)
    {

        for (int arrive = 0; arrive < N; ++arrive)
        {

            if (itineraire(depart, arrive, chemin))
            {

                cout << "dist = " << dist[depart][arrive] << endl;
            }
        }
    }
}
void coompFortConnexe(int n, int fermeture[][N])
{
    bool marque[n];

    for (int i = 0; i < n; i++)
    {
        marque[i] = false;
    }

    for (int i = 0; i < n; i++)
    {
        if (!marque[i])
        {

            cout << "{" << i;
            for (int j = i + 1; j < n; j++)
            {
                if (fermeture[i][j] == 1 && fermeture[j][i] == 1)
                {
                    cout << "," << j;
                    marque[j] = true;
                }
            }
            cout << "}";
            marque[i] = true;
        }
    }
}
void fermetureTransitive(int arc[][N], int fermeture[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            fermeture[i][j] = arc[i][j];
        fermeture[i][i] = 1;
    }

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (fermeture[i][j] == 0 && fermeture[i][k] == 1 && fermeture[k][j] == 1)
                    fermeture[i][j] = 1;
}

int main()
{

    // int longueur[N][N] = {{0, 2, INF, 4, INF},   //Les longueurs des arcs.
    //                       {INF, 0, 2, INF, INF}, //longueur[i][j]=INF si l'arc ij n'existe pas
    //                       {INF, INF, 0, 2, INF},
    //                       {INF, -3, INF, 0, 2},
    //                       {2, INF, INF, INF, 0}};
    int dist[N][N]; //Le tableau des distances.
    // int chemin[N][N]; //Le tableau de la premiere etape du chemin de i a j.
    // floydWarshall(longueur, dist, chemin);
    // affichage(dist, chemin);

    int arc[N][N] = {{0, 0, 0, 1, 0, 1}, //La matrice d’adjacences du graphe oriente D.
                     {1, 0, 1, 1, 0, 0},
                     {0, 0, 0, 1, 0, 0},
                     {0, 0, 0, 0, 1, 1},
                     {0, 0, 1, 0, 0, 1},
                     {0, 0, 1, 0, 0, 0}};
    int fermeture[N][N]; // La matrice de la fermeture transitive de D.

    fermetureTransitive(arc, fermeture);
    coompFortConnexe(N, fermeture);
    return EXIT_SUCCESS;
}
