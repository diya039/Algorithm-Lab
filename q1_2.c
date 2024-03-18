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

// Function to calculate the perimeter of a triangle given three vertices
double trianglePerimeter(Point a, Point b, Point c) {
    return distance(a, b) + distance(b, c) + distance(c, a);
}

// Function to find the minimum of two doubles
double min(double a, double b) {
    return a < b ? a : b;
}

// Function to find the minimum of three doubles
double min3(double a, double b, double c) {
    return min(min(a, b), c);
}

// Function to compute the length of the optimal triangulation of a convex polygon
double optimalTriangulation(Point* polygon, int n) {
    // Base case: If the polygon has less than 3 vertices, it cannot be triangulated
    if (n < 3) {
        return 0.0;
    }

    // For polygons with 3 vertices, no triangulation is needed (it's already a triangle)
    if (n == 3) {
        return trianglePerimeter(polygon[0], polygon[1], polygon[2]);
    }

    double min_length = INFINITY; // Initialize with a large value

    // Try all possible triangles as the first cut
    for (int i = 1; i < n - 1; i++) {
        double length = trianglePerimeter(polygon[0], polygon[i], polygon[i + 1]) +
                        optimalTriangulation(polygon, i + 1) +
                        optimalTriangulation(polygon + i, n - i);
        min_length = min(min_length, length);
    }

    return min_length;
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

    // Read polygons from the file and compute the optimal triangulation length
    for (int k = 0; k < num_polygons; k++) {
        int num_vertices;
        fscanf(fp, "%d", &num_vertices);

        Point* polygon = (Point*)malloc(num_vertices * sizeof(Point));
        for (int i = 0; i < num_vertices; i++) {
            fscanf(fp, "%lf %lf", &polygon[i].x, &polygon[i].y);
        }

        // Compute and print the optimal triangulation length for each polygon
        printf("Polygon %d: %.2lf\n", k + 1, optimalTriangulation(polygon, num_vertices));
        free(polygon);
    }

    fclose(fp);
    return 0;
}