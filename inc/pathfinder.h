#ifndef PATHFINDER
#define PATHFINDER

#include "libmx.h"

typedef struct  s_path {
    int pathID;
    int pathDist;
    int index;
    struct s_path *nextConnect;
    struct s_path *nextPath;
}		        t_path;

typedef struct  s_island {
    int islandIndex;
    int islandDist;
    struct s_path *islandPath;
    struct s_island *next;
}		        t_island;

typedef struct  s_patharr{
    t_island *first;
    t_island *second;
    t_island *third;
    t_island *fourth;
}		        t_patharr;

typedef struct  s_name {
    int num;
    char *name1;
    char *name2;
    char *name3;
}		        t_name;

typedef struct  s_twoislands {
    int island1;
    int island2;
    int mainland;
}		        t_twoislands;

typedef struct  s_information {
    int size;
    int root;
}		        t_information;

t_path *createPath(int isl, int dist);
t_path *addPath(t_path **previous, int island, int distance);
t_path *copyPath(t_path **data);
t_path *addSinglePath(t_path **previous, int island, int distance);
void removePaths(t_path **head);
void addNewPathToIsland(t_island **island, t_path **islandPath, int isl, int dist);
void sortPath(t_path **disp, int sizeP);
void pathPushBack(t_path **islandPath, t_path **previous, int isl, int dist);
void findShortestPaths(int **matrix, char **set);
int isPathUnique(t_path **new, t_path **pre);
int **createAdjacencyMatrix(char **set, char ***arrarr);
void removeAdjacencyMatrix(int ***matrix, char **set);
void generateDataArray(char **src, char ***arrarr);
void generateIslandSet(char ***set, char ***arrarr, char *numOfIsland);
void addConnection(t_path **current, t_path **newConnection);
t_island *findShortestDistance(t_island **unvisited);
void removeIslandFromFront(t_island **head);
void removeIslandFromMiddle(t_island **unvisited, int index);
void concatenateStrings(char **res, char *s2);
void handleErrors(int argc, char *file, char **argv);
void printPaths(t_island **visited, int root, int size, char **set);

#endif
