/* Your code here! */
#include "dsets.h"
#include <vector>
#include <iostream>

void DisjointSets::addelements(int num) {
    for(int i = 0; i < num; i++) {
        up.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    int s = up.size();
    if(elem >= s) return 0;
    if(up[elem] < 0) return elem;
    else return find(up[elem]);
}

void DisjointSets::setunion(int a, int b) {
    while(up[a] > 0) a = up[a];
    while(up[b] > 0) b = up[b];
    int update_size = up[a] + up[b];

    if(up[a] < up[b]) {
        up[b] = a;
        up[a] = update_size;
    } else {
        up[a] = b;
        up[b] = update_size;
    }
}

int DisjointSets::size(int elem) {
    while(up[elem] > 0) elem = up[elem];
    int ret = up[elem] * -1;
    return ret;
}
