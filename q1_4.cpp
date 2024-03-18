#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

// Function to compute the distance between two points
double distance(Point a, Point b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

// Function to calculate the length of a diagonal between two vertices
double diagonalLength(Point* polygon, int i, int j) {
    return distance(polygon[i], polygon[j]);
}

// Function to find the length of the optimal triangulation using a greedy approach
double greedyTriangulation(Point* polygon, int n) {
    // Ensure the polygon has at least 3 vertices
    if (n < 3)
        return 0.0;

    // Initialize total length of triangulation
    double total_length = 0.0;

    // Greedily select diagonals in sorted order
    for (int i = 0; i < n - 2; i++) {
        total_length += diagonalLength(polygon, i, i + 2); // Connect vertices i and i+2
    }

    // Connect the last two vertices to complete the polygon
    total_length += diagonalLength(polygon, 0, n - 1);

    return total_length;
}

int main() {
    FILE *fp;
    char filename[] = "polygons.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    int num_polygons;
    fscanf(fp, "%d", &num_polygons);

    // Read polygons from the file and compute the length of the greedy triangulation
    for (int k = 0; k < num_polygons; k++) {
        int num_vertices;
        fscanf(fp, "%d", &num_vertices);

        Point* polygon = (Point*)malloc(num_vertices * sizeof(Point));
        for (int i = 0; i < num_vertices; i++) {
            fscanf(fp, "%lf %lf", &polygon[i].x, &polygon[i].y);
        }

        // Compute and print the length of the greedy triangulation for each polygon
        printf("Polygon %d: %.2lf\n", k + 1, greedyTriangulation(polygon, num_vertices));
        free(polygon);
    }

    fclose(fp);
    return 0;
}