#include "pathfinder.h"

static void extractData(char *line, char **island1, char **island2, char **distance) {
    int i = 0;
    char *str = line;

    while (str[i] != '-')
    {
        i++;
    }
    *island1 = mx_strndup(str, i);
    str += i + 1;
    i = 0;
    while (str[i] != ',')
    {
        i++;
    }
    *island2 = mx_strndup(str, i);
    str += i + 1;
    i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    *distance = mx_strndup(str, i);
}

static void populateArray(char ***data, char **lines, int lineIndex) {
    char **dataArray = *data;
    char *firstIsland = NULL;
    char *secondIsland = NULL;
    char *dist = NULL;
    int lineNumber = lineIndex;

    int dataIndex = 0;
    while (lines[lineIndex]) {
        extractData(lines[lineIndex], &firstIsland, &secondIsland, &dist);
        if (mx_strcmp(firstIsland, secondIsland) == 0 && mx_atoi(dist) != 0) {
            lineNumber++;
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(lineNumber));
            mx_printerr(" is not valid\n");
            exit(0);
        }

        dataArray[dataIndex++] = mx_strdup(firstIsland);
        mx_strdel(&firstIsland);

        dataArray[dataIndex++] = mx_strdup(secondIsland);
        mx_strdel(&secondIsland);

        dataArray[dataIndex++] = mx_strdup(dist);
        mx_strdel(&dist);

        for (int i = 0; i < dataIndex - 3; i += 3) {
            if (mx_strcmp(dataArray[dataIndex - 3], dataArray[i]) == 0 && mx_strcmp(dataArray[dataIndex - 2], dataArray[i + 1]) == 0)
            {
                mx_printerr("error: duplicate bridges\n");
                exit(0);
            }
            if (mx_strcmp(dataArray[dataIndex - 2], dataArray[i]) == 0 && mx_strcmp(dataArray[dataIndex - 3], dataArray[i + 1]) == 0)
            {
                mx_printerr("error: duplicate bridges\n");
                exit(0);
            }
        }

        lineIndex++;
    }
}

void generateDataArray(char **lines, char ***dataArray) {
    int lineIndex = 1;

    while (lines[lineIndex]) {
        lineIndex++;
    }
    *dataArray = (char **)malloc((lineIndex * 3 + 1) * sizeof(char *));
    populateArray(&(*dataArray), lines, 1);
}

static int checkFlag(char *element, char **set) {
    int index = 0;
    int flag = 0;

    while (set[index]) {
        if (mx_strcmp(element, set[index]) == 0) {
            flag++;
            break;
        }
        index++;
    }
    return flag;
}

static void updateSet(char ***islandSet, char ***dataArray) {
    char **dataArr = *dataArray;
    char **set = *islandSet;
    int index = 0;

    for (int flag = 0; *dataArr; flag = 0) {
        if (mx_isdigit(**dataArr))
            dataArr++;
        if (*dataArr) {
            flag = checkFlag(*dataArr, set);
            if (flag != 0) {
                dataArr++;
                continue;
            }
            if (flag == 0) {
                set[index] = mx_strdup(*dataArr);
                set[index + 1] = NULL;
                index++;
            }
            dataArr++;
        }
    }
}

static int countUniqueIslands(char **dataArray, char *numIslands) {
    int count = 0;
    int index = 0;

    if (dataArray && *dataArray) {
        if (dataArray[0])
            count++;
        for (int i = 1; dataArray[i] != NULL; i++) {
            if (mx_isdigit(dataArray[i][0]))
                i++;
            if (dataArray[i] == NULL)
                break;
            for (index = i - 1; index >= 0; index--) {
                if (mx_strcmp(dataArray[i], dataArray[index]) == 0)
                    break;
                if (index == 0)
                    count++;
            }
        }
    }
    if (count == 0 || count != mx_atoi(numIslands) || count == 1) {
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }
    return count;
}

void generateIslandSet(char ***islandSet, char ***dataArray, char *numIslands) {
    int count = countUniqueIslands(*dataArray, numIslands);
    *islandSet = (char **)malloc((count + 1) * sizeof(char *));
    **islandSet = NULL;
    updateSet(&(*islandSet), &(*dataArray));
}
