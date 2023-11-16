#include "pathfinder.h"

static void removeAllPaths(t_path **islandPath) {
    t_path *temp = NULL;

    if (!islandPath || !(*islandPath))
        return;
    while ((*islandPath)->nextConnect) {
        temp = (*islandPath)->nextConnect;
        free(*islandPath);
        *islandPath = temp;
    }
    if (!(*islandPath)->nextConnect && !(*islandPath)->nextPath) {
        free(*islandPath);
        *islandPath = NULL;
        return;
    }
}

static void removeNextPath(t_path **islandPath) {
    t_path *temp = NULL;

    if (!islandPath || !(*islandPath))
        return;
    if ((*islandPath)->nextPath == NULL) {
        free(*islandPath);
        *islandPath = NULL;
        return;
    }
    else {
        temp = (*islandPath)->nextPath;
        free(*islandPath);
        *islandPath = temp;
    }
}

void removePaths(t_path **islandPath) {
    if (!islandPath || !(*islandPath))
        return;
    while (*islandPath) {
        removeAllPaths(&(*islandPath));
        removeNextPath(&(*islandPath));
    }
}

void removeAdjacencyMatrix(int ***matrix, char **islandSet) {
    int **adjMatrix = *matrix;
    int i = 0;

    while (islandSet[i])
        i++;
    while (i >= 0) {
        free(*adjMatrix);
        adjMatrix++;
        i--;
    }
    free(*matrix);
    *matrix = NULL;
}
