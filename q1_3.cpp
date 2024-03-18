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

// Function to compute the length of the optimal triangulation of a convex polygon using dynamic programming
double optimalTriangulationDP(Point* polygon, int n) {
    // Create a table to store the lengths of optimal triangulations
    double dp[n][n];

    // Initialize the table with zeros
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0.0;
        }
    }

    // Fill the table diagonally
    for (int gap = 2; gap < n; gap++) {
        for (int i = 0; i < n - gap; i++) {
            int j = i + gap;
            dp[i][j] = INFINITY; // Initialize with a large value

            for (int k = i + 1; k < j; k++) {
                double length = dp[i][k] + dp[k][j] + trianglePerimeter(polygon[i], polygon[k], polygon[j]);
                dp[i][j] = min(dp[i][j], length);
            }
        }
    }

    // The optimal triangulation length is stored in dp[0][n-1]
    return dp[0][n - 1];
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
        printf("Polygon %d: %.2lf\n", k + 1, optimalTriangulationDP(polygon, num_vertices));
        free(polygon);
    }

    fclose(fp);
    return 0;




    
}