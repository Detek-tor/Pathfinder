#include "pathfinder.h"

static void comparePaths(t_path **newPath, t_path **curPath, int *flag)
{
    if (*newPath && *curPath) {
        if ((*newPath)->pathID != (*curPath)->pathID)
            *flag = 1;
        if ((*newPath)->pathDist != (*curPath)->pathDist)
            *flag = 1;
    }
    if (!(*newPath) || !(*curPath))
        *flag = 1;
}

static void moveOnPath(t_path **oldPath, t_path **islandPath, t_path **newPath)
{
    *islandPath = *newPath;
    *oldPath = (*oldPath)->nextPath;
}

int isPathUnique(t_path **newPath, t_path **currentPath)
{
    t_path *islandPath = *newPath;
    t_path *oldPath = *currentPath;
    int flag = -1;

    while (oldPath) {
        if (oldPath->nextConnect == NULL || !islandPath)
        {
            comparePaths(&islandPath, &oldPath, &flag);
            moveOnPath(&oldPath, &islandPath, &(*newPath));
            if (flag == -1)
                return -1;
            if (oldPath)
                flag = -1;
            continue;
        }
        comparePaths(&islandPath, &oldPath, &flag);
        islandPath = islandPath->nextConnect;
        oldPath = oldPath->nextConnect;
    }
    return flag;
}
