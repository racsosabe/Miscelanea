#include<stdio.h>
#include<stdlib.h>
#include "parse.h"
#include "vector.h"


struct Graph {
    int e;
    int n;
    struct Vector to;
    struct Vector sz;
    struct Vector nxt;
    struct Vector last;
};

void set(struct Graph *G, int n) {
    init(&G -> to);
    init(&G -> sz);
    init(&G -> nxt);
    init(&G -> last);
    G -> e = 0;
    G -> n = n;
    int i;
    for(i = 0; i < n; i++) {
        push_back(&G -> last, -1);
        push_back(&G -> sz, 0);
    }
}

void add_edge(struct Graph *G, int u, int v) {
    push_back(&G -> to, v);
    push_back(&G -> nxt, G -> last.a[u]);
    G -> last.a[u] = G -> e;
    G -> e++;
}

void read_data(FILE *in, struct Graph *G) {
    int n;
    fscanf(in, "%d", &n);
    set(G, n);
    int i;
    for(i = 1; i < n; i++) {
        int u, v;
        fscanf(in, "%d %d", &u, &v);
        u--; v--;
        add_edge(G, u, v);
        add_edge(G, v, u);
    }
}

int get_digits(int n) {
    return n < 10 ? 1 : 1 + get_digits(n / 10);
}

void DFS(struct Graph *G, int u, int p) {
    int e;
    G -> sz.a[u] = 1;
    for(e = G -> last.a[u]; ~e; e = G -> nxt.a[e]) {
        int v = G -> to.a[e];
        if(v == p) continue;
        DFS(G, v, u);
        G -> sz.a[u] += G -> sz.a[v];
    }
}

int check_centroid(struct Graph *G, int u) {
    int e;
    for(e = G -> last.a[u]; ~e; e = G -> nxt.a[e]) {
        int v = G -> to.a[e];
        if(2 * G -> sz.a[v] > G -> n) return -1;
    }
    return 1;
}

int check(FILE *in, struct Graph *G) {
    int x = read_int(in);
    if(x < 1 || G -> n < x) return -1; // Node given is out of range
    x--;
    int i;
    for(i = 0; i < G -> n; i++) G -> sz.a[i] = 0;
    DFS(G, x, -1);
    return check_centroid(G, x);
}

int main(int argc, char* argv[]) {
    if(argc < 4) {
        printf("Error. Please execute this code with the following format:\n");
        printf("\t./a.out (input file) (output file) (answer file) \n");
        return 3;
    }
    FILE *inf = fopen(argv[1], "r");
    FILE *ouf = fopen(argv[2], "r");
    FILE *ans = fopen(argv[3], "r");
    struct Graph G;
    read_data(inf, &G);
    int jans = check(ans, &G);
    int pans = check(ouf, &G);
    if(jans == -1) {
        printf("Failed. Jury has an invalid answer.\n");
        return 3;
    }
    if(pans == -1) {
        printf("Wrong answer. Participant has an invalid answer.\n");
        return 1;
    }
    printf("Accepted.\n");
    return 0;
}