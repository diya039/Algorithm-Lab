#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double x;
    double y;
} Point;

// Function to generate a random double between min and max
double randomDouble(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

// Function to generate a random convex polygon with n vertices
Point* generateConvexPolygon(int n) {
    Point* polygon = (Point*)malloc(n * sizeof(Point));

    // Generate random points
    for (int i = 0; i < n; i++) {
        polygon[i].x = randomDouble(-100.0, 100.0); // Adjust range as needed
        polygon[i].y = randomDouble(-100.0, 100.0); // Adjust range as needed
    }

    return polygon;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int num_polygons = 5; // Number of polygons to generate
    int max_vertices = 6; // Maximum number of vertices for each polygon

    FILE *fp;
    char filename[] = "polygons.txt";
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    fprintf(fp, "%d\n", num_polygons); // Write the number of polygons to the file

    for (int i = 0; i < num_polygons; i++) {
        int num_vertices = rand() % (max_vertices - 3 + 1) + 3; // Random number of vertices (3 to max_vertices)
        fprintf(fp, "%d\n", num_vertices); // Write the number of vertices for the current polygon

        Point* polygon = generateConvexPolygon(num_vertices);

        // Write the coordinates of each vertex to the file
        for (int j = 0; j < num_vertices; j++) {
            fprintf(fp, "%.2lf %.2lf\n", polygon[j].x, polygon[j].y);
        }

        free(polygon); // Free allocated memory
    }

    fclose(fp);
    printf("Polygon dataset generated and stored in %s\n", filename);

    return 0;
}