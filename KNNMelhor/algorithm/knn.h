#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
    float distance;
    char label;
} Point;

typedef struct {
    char label;
    int length;
    Point * points;
} Group;

void on_error() {
    printf("Invalid input file.\n");
    exit(1);
}

int parse_number_of_groups() {
    int n;
    if (scanf(" n_groups=%d ", &n) != 1) on_error();

    return n;
}

Point parse_point() {
    float x, y;
    if (scanf(" (%f ,%f) ", &x, &y) != 2)  on_error();

    Point point;
    point.x = x;
    point.y = y;

    return point;
}

Group parse_next_group() {
    char label; 
    int length;

    if (scanf(" label=%c ", &label) != 1) on_error();
    if (scanf(" length=%d ", &length) != 1) on_error();

    Group group;
    group.label = label;
    group.length = length;
    group.points = (Point *) malloc(sizeof(Point) * length);

    for (int i = 0; i < length; i++) {
        group.points[i] = parse_point();
        group.points[i].label = label; 
    }

    return group;
}

int parse_k() {
    int k;
    if (scanf(" k=%d ", &k) != 1) on_error();

    return k;
}

float euclidean_distance_no_sqrt (Point a, Point b) {
    return ((b.x - a.x) * ((b.x - a.x))) + ((b.y - a.y) * (b.y - a.y));
}

int compare_for_sort(const void *a, const void *b) {
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;

    if((*pa).distance - (*pb).distance > 0)
        return 1;
    return -1;

}

int compare_for_sort_label(const void *a, const void *b){
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;

    return (*pa).label - (*pb).label;
}