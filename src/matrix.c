#include "pathfinder.h"

static void updateMatrix(char **islands, char **data, int ***adjMatrix, t_information *info) {
    int **matrix = *adjMatrix;
    int k = 0;
    int i = info->size;
    int j = info->root;

    if (mx_isdigit(data[j + 1][0])) {
        while (mx_strcmp(islands[k], data[j - 1]) != 0)
            k++;
        if (!matrix[i][k] || matrix[i][k] > mx_atoi(data[j + 1]))
            matrix[i][k] = mx_atoi(data[j + 1]);
    }
    else {
        while (mx_strcmp(islands[k], data[j + 1]) != 0)
            k++;
        if (!matrix[i][k] || matrix[i][k] > mx_atoi(data[j + 2]))
            matrix[i][k] = mx_atoi(data[j + 2]);
    }
}

static void fillMatrix(char **islands, char **data, int ***adjMatrix) {
    t_information *info = malloc(sizeof(t_information));

    info->size = 0;
    while (islands[info->size]) {
        info->root = 0;
        while (data[info->root]) {
            if (mx_strcmp(islands[info->size], data[info->root]) == 0) {
                updateMatrix(islands, data, &(*adjMatrix), info);
            }
            info->root += 1;
        }
        info->size += 1;
    }
    free(info);
}

int **createAdjacencyMatrix(char **islands, char ***data) {
    int **adjMatrix = NULL;
    int i = 0;
    int k = 0;

    while (islands[i])
        i++;

    k = i;
    adjMatrix = malloc(sizeof(int*) * i);
    while (k >= 0) {
        adjMatrix[k] = malloc(sizeof(int) * i);
        k--;
    }

    fillMatrix(islands, *data, &adjMatrix);
    return adjMatrix;
}
