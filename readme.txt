Oudghiri Mehdi L2A 20001692

Pour compiler mon projet il suffit de faire dans le terminal: make puis pour l'éxécuter: ./projet.



Le code est un programme C qui utilise l’algorithme de Dijkstra pour trouver le chemin le plus court entre un noeud source et un noeud de destination dans un graphique. Les fonctions et aspects clés du code sont :

struct Edge : Structure qui stocke des informations sur les bords du graphique. Il contient trois membres : dest, qui est la destination du bord; poids, qui est le poids du bord; et le temps, qui est le temps qu’il faut pour traverser le bord.

struct Node : Structure qui stocke des informations sur les nœuds dans le graphique. Il contient quatre membres : dist, qui est la distance actuelle de la source; prev, qui est le noeud précédent dans le chemin le plus court; visité, qui indique si le noeud a été visité ou non; et totalTime le temps total qu’il faut pour traverser le chemin à partir de la source

initNodes(struct Node nodes[], int size, int source) : Fonction qui initialise les informations sur les nœuds, en définissant leur distance de la source à l’infini, leur nœud précédent à -1, et leur état visité à 0.

findMinNode(struct Node nodes[], int size) : Fonction qui trouve le noeud non visité avec la distance minimale par rapport à la source.

dj(int source, int dest, struct Edge edges[][MAX_NODES], struct Node nodes[], int numNodes) : Fonction qui utilise l’algorithme de Dijkstra pour trouver le chemin le plus court entre la source et le noeud de destination. Il utilise les tableaux de bords et de nœuds, et le nombre de nœuds dans le graphique.

MAX_NODES : constante correspondant au nombre maximum de nœuds dans le graphique


currNode = findMinNode(nodes, numNodes) : une ligne de code qui utilise la fonction findMinNode pour trouver le prochain noeud à explorer en utilisant la distance minimale par rapport à la source

currNode == -1 || currNode == dest : Une condition qui arrête la boucle si plus de noeud est trouvé ou lorsque le noeud de destination est atteint

nodes[i]. dist = INT_MAX; : ligne de code qui initialise la distance de la source à l’infini pour chaque nœud

nodes[i]. prev = -1; : Une ligne de code qui initialise le noeud précédent pour chaque noeud à -1

noeuds[i]. visités = 0; : une ligne de code qui initialise l’état visité pour chaque noeud à 0

noeuds[i]. totalTime = 0; : ligne de code qui initialise le temps total du chemin pour chaque noeud à 0