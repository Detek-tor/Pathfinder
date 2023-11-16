#include "pathfinder.h"

static void initializeState1(t_island **unvisited, t_island **current, t_island **visited, t_information *info) {
    *unvisited = NULL;
    *visited = NULL;

    for (int i = 0; i < info->size; i++)
        addNewPathToIsland(&(*unvisited), NULL, i, 0);

    *current = *unvisited;

    while ((*current)->islandIndex != info->root)
        *current = (*current)->next;

    (*current)->islandPath = createPath(info->root, 0);
    addNewPathToIsland(&(*visited), &(*current)->islandPath, (*current)->islandIndex, (*current)->islandDist);
    removeIslandFromMiddle(&(*unvisited), info->root);
    *current = *visited;
}

static void processState2(t_island **unvisited, t_island **current, int **adjMatrix, t_twoislands **matrixData) {
    t_island *unvisitedIsland = *unvisited;
    int sum = 0;

    while (unvisitedIsland != NULL) {
        (*matrixData)->island1 = (*current)->islandIndex;
        (*matrixData)->island2 = unvisitedIsland->islandIndex;
        (*matrixData)->mainland = adjMatrix[(*matrixData)->island1][(*matrixData)->island2];

        if ((*matrixData)->mainland != 0 && unvisitedIsland->islandDist == 0) {
            unvisitedIsland->islandDist = (*current)->islandDist + (*matrixData)->mainland;

            sum += unvisitedIsland->islandDist;
            if (sum < 0) {
                mx_printerr("error: sum of bridge lengths is too large\n");
                exit(0);
            }

            unvisitedIsland->islandPath = addPath(&(*current)->islandPath, (*matrixData)->island2, (*matrixData)->mainland);
        } else if ((*matrixData)->mainland != 0) {
            if ((*current)->islandDist + (*matrixData)->mainland == unvisitedIsland->islandDist)
                pathPushBack(&unvisitedIsland->islandPath, &(*current)->islandPath, (*matrixData)->island2, (*matrixData)->mainland);

            if ((*current)->islandDist + (*matrixData)->mainland < unvisitedIsland->islandDist) {
                unvisitedIsland->islandDist = (*current)->islandDist + (*matrixData)->mainland;
                removePaths(&unvisitedIsland->islandPath);
                unvisitedIsland->islandPath = addPath(&(*current)->islandPath, (*matrixData)->island2, (*matrixData)->mainland);
            }
        }
        unvisitedIsland = unvisitedIsland->next;
    }
}

static void finalizeState3(t_patharr **list, int **adjMatrix, char **islands) {
    (*list)->fourth = findShortestDistance(&(*list)->first);
    addNewPathToIsland(&(*list)->second, &(*list)->fourth->islandPath, (*list)->fourth->islandIndex, (*list)->fourth->islandDist);
    removeIslandFromMiddle(&(*list)->first, (*list)->fourth->islandIndex);
    (*list)->third = (*list)->third->next;

    if ((*list)->third->islandPath == NULL) {
        removeAdjacencyMatrix(&adjMatrix, islands);
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }
}

static void executeAlgorithm(int **adjMatrix, char **islands, t_information *info) {
    t_patharr *list = malloc(sizeof(t_patharr));
    list->first = NULL;
    list->second = NULL;
    list->third = NULL;
    list->fourth = NULL;

    t_twoislands *matrixData = NULL;

    initializeState1(&list->first, &list->third, &list->second, info);

    while (list->first && list->first != NULL) {
        matrixData = malloc(sizeof(t_twoislands));
        processState2(&list->first, &list->third, adjMatrix, &matrixData);
        free(matrixData);
        matrixData = NULL;
        finalizeState3(&list, adjMatrix, islands);
    }

    printPaths(&list->second, info->root + 1, info->size, islands);

    while (list->second != NULL) {
        removePaths(&list->second->islandPath);
        removeIslandFromFront(&list->second);
    }

    free(list);
    list = NULL;
}

void findShortestPaths(int **adjMatrix, char **islands) {
    int size = 0;
    int i = 0;
    t_information *info = malloc(sizeof(t_information));

    while (islands[size])
        size++;

    info->size = size;

    while (i < size - 1) {
        info->root = i;
        executeAlgorithm(adjMatrix, islands, info);
        i++;
    }

    free(info);
    info = NULL;
}

static t_path *cloneSinglePath(t_path **source) {
    t_path *newNode = NULL;
    t_path *lastNode = *source;
    t_path *result = NULL;

    result = createPath(lastNode->pathID, lastNode->pathDist);
    newNode = result;
    lastNode = lastNode->nextConnect;

    while (lastNode) {
        newNode->nextConnect = createPath(lastNode->pathID, lastNode->pathDist);
        lastNode = lastNode->nextConnect;
        newNode = newNode->nextConnect;
    }

    return result;
}

t_path *copyPath(t_path **data) {
    t_path *currentNode = NULL;
    t_path *result = NULL;
    t_path *newNode = NULL;
    t_path *fastNode = NULL;

    if (*data)
        currentNode = *data;

    result = cloneSinglePath(&currentNode);
    fastNode = result;
    currentNode = currentNode->nextPath;

    while (currentNode) {
        newNode = cloneSinglePath(&currentNode);
        addConnection(&fastNode, &newNode);
        fastNode = fastNode->nextPath;
        currentNode = currentNode->nextPath;
    }

    return result;
}

t_path *createPath(int island, int distance) {
    t_path *node = (t_path *)malloc(1 * sizeof(t_path));

    node->pathID = island;
    node->pathDist = distance;
    node->nextConnect = NULL;
    node->nextPath = NULL;
    return node;
}

void pathPushBack(t_path **islandPath, t_path **previous, int island, int distance) {
    t_path *lastNode = *islandPath;
    t_path *currentNode = *previous;
    t_path *newNode = NULL;

    while (lastNode->nextPath != NULL)
        lastNode = lastNode->nextPath;

    while (currentNode) {
        newNode = addPath(&currentNode, island, distance);

        if (isPathUnique(&newNode, &(*islandPath)) == 1) {
            addConnection(&lastNode, &newNode);
            lastNode = lastNode->nextPath;
        }

        currentNode = currentNode->nextPath;
    }
}
