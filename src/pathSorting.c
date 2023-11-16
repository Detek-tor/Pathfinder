#include "pathfinder.h"

static int comparePaths(t_path *first, t_path *second) {
    while (first && second) {
        if (first->pathID > second->pathID)
            return 1;
        if (first->pathID < second->pathID)
            return 0;
        first = first->nextConnect;
        second = second->nextConnect;
    }
    if (first && !second)
        return 1;
    return 0;
}

static void swapPaths(t_path **display, t_path **bond, t_path **fast) {
    t_path *temp = (*fast)->nextPath;
    t_path *cur = *display;

    while(cur->nextPath != *fast)
        cur = cur->nextPath;
    addConnection(&cur, &(*bond));
    cur = *display;
    if (*display == *bond)
        *display = *fast;
    else {
        while (cur && cur->nextPath != *bond)
            cur = cur->nextPath;
        addConnection(&cur, &(*fast));
    }
    addConnection(&(*fast), &(*bond)->nextPath);
    addConnection(&(*bond), &temp);
}

static void swapIfNext(t_path **display, t_path **bond, t_path **fast) {
    t_path *temp = (*fast)->nextPath;
    t_path *cur = *display;

    if ((*bond)->nextPath == *fast) {
            addConnection(&(*fast), &(*bond));
            addConnection(&(*bond), &temp);
        if (*display == *bond)
            *display = *fast;
        else {
            while (cur && cur->nextPath != *bond)
                cur = cur->nextPath;
            addConnection(&cur, &(*fast));
        }
    }
    else
        swapPaths(&(*display), &(*bond), &(*fast));
}

void sortPath(t_path **display, int sizeP) {
    t_path *bond = *display;
    t_path *fast = (*display)->nextPath;

    for (int i = 0; i < sizeP; i++) {
        bond = *display;
        fast = bond->nextPath;
        for (; bond->index != i; bond = bond->nextPath)
            fast = bond->nextPath;
        while (fast) {
            if (comparePaths(bond, fast) == 1) {
                swapIfNext(&(*display), &bond, &fast);
                for (bond = *display; bond->index != i; bond = bond->nextPath)
                    fast = bond->nextPath;
            }
            else
                fast = fast->nextPath;
        }
    }
}
