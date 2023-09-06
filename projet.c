#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

// Structure pour stocker les informations sur les arcs
struct Edge {
    int dest; // destination du arc
    int weight; // poids de l'arc, c'est à dire le temps en l'occurence
    int time; // temps de parcours de l'arc
};

// Structure pour stocker les informations sur les nœuds
struct Node {
    int dist; // distance actuelle depuis la source
    int prev; // nœud précédent dans le chemin le plus court
    int visited; // indique si le nœud a été visité ou non
    int totalTime; // temps total de parcours depuis la source
};

// Fonction pour initialiser les informations sur les nœuds
void initNodes(struct Node nodes[], int size, int source) {
    int i;
    //utilise une boucle for pour parcourir tous les éléments du tableau de structures Node
    for (i = 0; i < size; i++) {
        //pour chaque nœud, je définit la distance à partir de la source à l'infini (INT_MAX), le nœud précédent à -1 (aucun nœud précédent) et l'état de visite à 0 (non visité).
        nodes[i].dist = INT_MAX;
        nodes[i].prev = -1;
        nodes[i].visited = 0;
        nodes[i].totalTime = 0;

    }
    //définit la distance de la source à 0 pour le nœud source
    nodes[source].dist = 0;
}

// Fonction pour trouver le nœud non visité avec la distance minimale
int findMinNode(struct Node nodes[], int size) {
    //initialise deux variables, minNode à -1 (aucun nœud trouvé) et minDist à INT_MAX (distance maximale)
    int i, minNode = -1;
    int minDist = INT_MAX;
    //utilise une boucle for pour parcourir tous les éléments du tableau de structures Node
    for (i = 0; i < size; i++) {
        //pour chaque nœud, si le nœud n'a pas été visité et si la distance à partir de la source est inférieure à la distance minimale enregistrée, elle met à jour minDist avec la distance de ce nœud et minNode avec l'index de ce nœud
        if (!nodes[i].visited && nodes[i].dist < minDist) {
            minDist = nodes[i].dist;
            minNode = i;
        }
    }
    //retourne l'index du nœud non visité avec la distance minimale ou -1 si aucun nœud n'a été trouvé
    return minNode;
}

// Fonction pour trouver le plus court chemin entre la source et la destination
void dj(int source, int dest, struct Edge edges[][MAX_NODES], struct Node nodes[], int numNodes) {
    int i, currNode, neighbor;

    //utilise la fonction "initNodes" pour initialiser les informations sur les nœuds en utilisant le nœud source
    initNodes(nodes, numNodes, source);

    // utilise une boucle while qui continuera jusqu'à ce que tous les nœuds aient été visités ou jusqu'à ce que le nœud de destination ait été atteint
    while (1) {
        //utilise la fonction "findMinNode" pour trouver le prochain nœud à explorer en utilisant la distance minimale à partir de la source
        currNode = findMinNode(nodes, numNodes);
        if (currNode == -1 || currNode == dest)
            break;

        // Marquer le nœud actuel comme visité
        nodes[currNode].visited = 1;

        //utilisée pour mettre à jour les informations sur les nœuds en fonction des informations sur les arcs
        for (i = 0; i < numNodes; i++) {
        //vérifie si il existe un arc (lien) entre le nœud actuel ("currNode") et le nœud en cours d'examen ("i") en vérifiant si le poids de l'arc n'est pas égal à -1 (ce qui signifie qu'il existe un arc entre les deux nœuds)
            if (edges[currNode][i].weight != -1) {
            //si un arc existe, la variable neighbor est définie comme étant égale à i, ce qui signifie que neighbor est le nœud en cours d'examen
                neighbor = i;
                //vérifie si le nœud en cours d'examen (neighbor) n'a pas encore été visité et si la distance de la source (nodes[currNode].dist) plus le poids de l'arc reliant ces deux nœuds (edges[currNode][neighbor].weight) est inférieur à la distance actuelle de neighbor (nodes[neighbor].dist),
                if (!nodes[neighbor].visited && nodes[currNode].dist + edges[currNode][neighbor].weight < nodes[neighbor].dist) {
                //définit le nœud précédent de neighbor comme étant égal à currNode et le temps total de parcours depuis la source comme étant égal au temps total de parcours actuel de currNode plus le temps de parcours de l'arc reliant ces deux nœuds ("edges[currNode][neighbor].time")
                    nodes[neighbor].dist = nodes[currNode].dist + edges[currNode][neighbor].weight;
                    nodes[neighbor].prev = currNode;
                    nodes[neighbor].totalTime = nodes[currNode].totalTime + edges[currNode][neighbor].time;
                    
                }
            }
        }
     }
}

int main(){
    //déclare les variables nécessaires pour stocker les informations sur les nœuds, les arcs et les points de départ et d'arrivée
	int numNodes, numEdges, source, dest, i, j;
	struct Edge edges[MAX_NODES][MAX_NODES];
	struct Node nodes[MAX_NODES];
	// Lire les informations sur le réseau depuis un fichier texte

//utilise la fonction fopen pour ouvrir un fichier texte nommé "network.txt" en mode lecture
FILE* file = fopen("network.txt", "r");
//utilise la fonction fscanf pour lire les informations sur le réseau depuis le fichier texte. Elle lit d'abord le nombre de nœuds et le nombre d'arcs, puis elle utilise une boucle pour lire les informations sur les arcs (source, destination et poids)
fscanf(file, "%d %d", &numNodes, &numEdges);
//utilise une boucle pour initialiser tous les arcs à un poids de -1. Cela signifie qu'il n'y a pas d'arc entre ces deux nœuds
for (i = 0; i < numNodes; i++) {
    for (j = 0; j < numNodes; j++) {
        edges[i][j].weight = -1;
    }
}

for (i = 0; i < numEdges; i++) {
    int src, dest, weight, time;
    //utilise encore fscanf pour lire les informations sur les points de départ et d'arrivée
    fscanf(file, "%d %d %d", &src, &dest, &weight, &time);
    edges[src][dest].weight = weight;
    edges[src][dest].time = time;

}
fscanf(file, "%d %d", &source, &dest);
//utilise la fonction fclose pour fermer le fichier texte
fclose(file);

// Trouver le plus court chemin entre la source et la destination
dj(source, dest, edges, nodes, numNodes);

// Afficher le chemin le plus court
//vérifie si le nœud d'arrivée a un nœud précédent (-1 signifie qu'il n'y a pas de chemin possible entre les deux points)
if (nodes[dest].prev != -1) {
    int curr = dest;
    printf("Chemin le plus court : %d", dest);
    //s'il y a un chemin possible, il utilise une boucle while pour parcourir les nœuds précédents depuis l'arrivée jusqu'à la source, en utilisant l'information stockée dans la structure Node. Il affiche l'index de chaque nœud en cours de parcours.
    while (curr != source) {
        curr = nodes[curr].prev;
        printf(" <- %d", curr);
    }
    //temps du parcours
    printf("\nTemps total de parcours : %d", nodes[dest].totalTime);
    //s'il n'y a pas de chemin possible, affiche un message indiquant qu'il n'y a pas de chemin possible entre les deux points
} else {
    printf("Aucun chemin possible entre %d et %d", source, dest);
}
//retourne 0 pour indiquer la fin du programme
return 0;

}
