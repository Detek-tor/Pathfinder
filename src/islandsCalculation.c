#include "pathfinder.h"

void concatenateStrings(char **result, char *string2) {
    char *newString = mx_strnew(mx_strlen(*result) + mx_strlen(string2));
    int i = 0;
    int str2Index = -1;
    char *string1 = *result;

    while (string1[++str2Index]) {
        newString[i] = string1[str2Index];
        i++;
    }

    str2Index = -1;
    while (string2[++str2Index]) {
        newString[i] = string2[str2Index];
        i++;
    }

    mx_strdel(&(*result));
    *result = newString;
}

void addNewPathToIsland(t_island **island, t_path **islandPath, int isl, int dist) {
    t_island *newIsland = (t_island *)malloc(1 * sizeof(t_island));
    newIsland->islandIndex = isl;
    newIsland->islandDist = dist;
    newIsland->islandPath = NULL;
    newIsland->next = NULL;

    t_island *lastIsland = *island;

    if (islandPath && *islandPath)
        newIsland->islandPath = copyPath(&(*islandPath));

    if (*island == NULL) {
        *island = newIsland;
        return;
    }

    while (lastIsland->next != NULL)
        lastIsland = lastIsland->next;

    lastIsland->next = newIsland;
    return;
}

t_island *findShortestDistance(t_island **unvisited) {
    t_island *headIsland = NULL;
    t_island *shortestDistanceIsland = NULL;

    if (unvisited || *unvisited) {
        headIsland = *unvisited;
        shortestDistanceIsland = *unvisited;

        while (headIsland) {
            if (headIsland->islandDist != 0) {
                if (shortestDistanceIsland->islandDist > headIsland->islandDist || !shortestDistanceIsland->islandDist)
                    shortestDistanceIsland = headIsland;
            }
            headIsland = headIsland->next;
        }
    }
    return shortestDistanceIsland;
}
