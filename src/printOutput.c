#include "pathfinder.h"

static void printSeparatorLine(t_name **pathInfo) {
    char *separator = mx_strdup("========================================");

    mx_printstr(separator);
    mx_printchar('\n');
    mx_printstr((*pathInfo)->name1);
    mx_printstr((*pathInfo)->name2);
    mx_printstr((*pathInfo)->name3);
    mx_printstr(separator);
    mx_printchar('\n');
    mx_strdel(&(*pathInfo)->name1);
    mx_strdel(&(*pathInfo)->name2);
    mx_strdel(&(*pathInfo)->name3);
    mx_strdel(&separator);
    free(*pathInfo);
    *pathInfo = NULL;
}

static t_name *createPathInfo(t_path *link, char **islands) {
    t_name *pathInfo = malloc(1 * sizeof(t_name));
    int i = 0;

    pathInfo->name1 = mx_strdup("islandPath: ");
    concatenateStrings(&pathInfo->name1, islands[link->pathID]);

    pathInfo->name2 = mx_strdup("Route: ");
    concatenateStrings(&pathInfo->name2, islands[link->pathID]);

    pathInfo->name3 = mx_strdup("Distance: ");
    for (; link; link = link->nextConnect)
        i++;
    pathInfo->num = i;

    return pathInfo;
}

static void addNextLink(t_name **pathInfo, t_path *link, char *distanceTo, char **islands) {
    char *distance = mx_itoa(link->pathDist);

    concatenateStrings(&(*pathInfo)->name2, " -> ");
    concatenateStrings(&(*pathInfo)->name2, islands[link->pathID]);

    if (mx_strlen((*pathInfo)->name3) != 10)
        concatenateStrings(&(*pathInfo)->name3, " + ");
    concatenateStrings(&(*pathInfo)->name3, distance);

    mx_strdel(&distance);

    if (link->nextConnect == NULL) {
        concatenateStrings(&(*pathInfo)->name1, " -> ");
        concatenateStrings(&(*pathInfo)->name1, islands[link->pathID]);

        if ((*pathInfo)->num != 2) {
            concatenateStrings(&(*pathInfo)->name3, " = ");
            concatenateStrings(&(*pathInfo)->name3, distanceTo);
        }

        concatenateStrings(&(*pathInfo)->name2, "\n");
        concatenateStrings(&(*pathInfo)->name1, "\n");
        concatenateStrings(&(*pathInfo)->name3, "\n");
    }
}

static void displayPath(t_path **islandPath, int distanceTo, char **islands) {
    t_path *link = *islandPath;
    t_name *pathInfo = NULL;
    char *distance = mx_itoa(distanceTo);

    while (link) {
        pathInfo = createPathInfo(link, islands);
        link = link->nextConnect;

        while (link->nextConnect) {
            addNextLink(&pathInfo, link, distance, islands);
            link = link->nextConnect;
        }

        addNextLink(&pathInfo, link, distance, islands);
        printSeparatorLine(&pathInfo);
        link = link->nextPath;
    }

    mx_strdel(&distance);
}

void printPaths(t_island **visited, int start, int end, char **islands) {
    t_island *current = NULL;
    int endIdx;

    for (; start < end; start++) {
        current = *visited;

        while (current->islandIndex != start)
            current = current->next;

        t_path *islandPath = current->islandPath;
        t_path *link = NULL;
        int i = 0;

        for (; islandPath; islandPath = islandPath->nextPath) {
            link = islandPath;
            while (link) {
                link->index = i;
                link = link->nextConnect;
            }
            i++;
        }

        endIdx = i;
        sortPath(&current->islandPath, endIdx);
        displayPath(&current->islandPath, current->islandDist, islands);
    }
}
