#include "pathfinder.h"

void removeIslandFromMiddle(t_island **unvisited, int index) {
    t_island *temp = NULL;
    t_island *previous = NULL;

    if (!unvisited || !(*unvisited))
        return;

    if ((*unvisited)->islandIndex == index) {
        removePaths(&((*unvisited)->islandPath));
        removeIslandFromFront(&(*unvisited));
    }
    else {
        temp = *unvisited;
        previous = temp;

        while (temp != NULL && temp->islandIndex != index) {
            previous = temp;
            temp = temp->next;
        }

        if (temp && temp->islandIndex == index) {
            if (temp->next)
                previous->next = temp->next;
            else
                previous->next = NULL;

            removePaths(&temp->islandPath);
            free(temp);
            temp = NULL;
        }
    }
}

void removeIslandFromFront(t_island **head) {
    t_island *nextIsland = NULL;

    if (!head || !(*head))
        return;

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    else {
        nextIsland = (*head)->next;
        free(*head);
        *head = nextIsland;
    }
}
