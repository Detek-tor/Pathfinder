#include "pathfinder.h"

void addConnection(t_path **current, t_path **newConnection)
{
    t_path *currentNode = *current;
    while (currentNode->nextConnect){
        currentNode->nextPath = *newConnection;
        currentNode = currentNode->nextConnect;
    }
    currentNode->nextPath = *newConnection;
}

t_path *addSinglePath(t_path **previous, int island, int distance)
{
    t_path *newNode = NULL;
    t_path *lastNode = *previous;
    t_path *result = NULL;

    if (!lastNode) return result = createPath(island, distance);

    result = createPath(lastNode->pathID, lastNode->pathDist);
    newNode = result;
    lastNode = lastNode->nextConnect;
    while (lastNode){
        newNode->nextConnect = createPath(lastNode->pathID, lastNode->pathDist);
        lastNode = lastNode->nextConnect;
        newNode = newNode->nextConnect;
    }
    newNode->nextConnect = createPath(island, distance);

    return result;
}

t_path *addPath(t_path **previous, int island, int distance)
{
    t_path *currentNode = NULL;
    t_path *result = NULL;
    t_path *newNode = NULL;
    t_path *fastNode = NULL;

    if (*previous)
        currentNode = *previous;
    result = addSinglePath(&currentNode, island, distance);
    fastNode = result;
    if (currentNode)
        currentNode = currentNode->nextPath;
    while (currentNode) {
        newNode = addSinglePath(&currentNode, island, distance);
        addConnection(&fastNode, &newNode);
        fastNode = fastNode->nextPath;
        currentNode = currentNode->nextPath;
    }
    return result;
}
