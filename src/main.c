#include "pathfinder.h"

static void parsing(char *fd, int ***matrixArr, char ***set) {
    char **arrarr = NULL;
    char **src = mx_strsplit(fd, '\n');

    generateDataArray(src, &arrarr);
    generateIslandSet(&(*set), &arrarr, src[0]);
    *matrixArr = createAdjacencyMatrix(*set, &arrarr);

    mx_del_strarr(&src);
    mx_del_strarr(&arrarr);
}

int main(int argc, char *argv[])
{
    int **matrixArr = NULL;
    char **set = NULL;
    char *openFile = mx_file_to_str(argv[1]);

    handleErrors(argc, openFile, argv);
    parsing(openFile, &matrixArr, &set);
    findShortestPaths(matrixArr, set);
    removeAdjacencyMatrix(&matrixArr, set);
    mx_strdel(&openFile);
    mx_del_strarr(&set);
    return 0;
}
