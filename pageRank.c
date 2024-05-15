#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define N 5 // Number of nodes in the graph
#define DAMPING_FACTOR 0.85
#define MAX_ITERATIONS 100
#define EPSILON 1e-6 // Convergence criterion

// Function to calculate absolute difference between two values
double abs_diff(double a, double b) {
    return fabs(a - b);
}

// Function to calculate PageRank scores
void calculate_pagerank(double adj_matrix[N][N], double *pagerank) {
    double new_pagerank[N];
    int i, j, k;
    double in_degree[N];

    // Calculate in-degree for each node
    for (i = 0; i < N; i++) {
        in_degree[i] = 0;
        for (j = 0; j < N; j++) {
            in_degree[i] += adj_matrix[j][i];
        }
    }

    // Initialize PageRank scores
    for (i = 0; i < N; i++) {
        pagerank[i] = 1.0 / N;
    }

    // Perform iterations
    for (k = 0; k < MAX_ITERATIONS; k++) {

        // Calculate new PageRank scores
        for (i = 0; i < N; i++) {
            new_pagerank[i] = 0.0;
            for (j = 0; j < N; j++) {
                if (adj_matrix[j][i] == 1) {
                    new_pagerank[i] += pagerank[j] / in_degree[j];
                }
            }
            new_pagerank[i] *= DAMPING_FACTOR;
        }

        // Apply damping factor and teleportation
        for (i = 0; i < N; i++) {
            new_pagerank[i] += (1.0 - DAMPING_FACTOR) / N;
        }

        // Check for convergence
        bool converged = true;
        for (i = 0; i < N; i++) {
            if (abs_diff(new_pagerank[i], pagerank[i]) > EPSILON) {
                converged = false;
                break;
            }
        }

        // If converged, break the loop
        if (converged) {
            break;
        }

        // Update PageRank scores
        for (i = 0; i < N; i++) {
            pagerank[i] = new_pagerank[i];
        }
    }
}

int main() {
    // Adjacency matrix representation of the graph
    double adj_matrix[N][N] = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}
    };

    // Initialize PageRank scores
    double pagerank[N];

    // Calculate PageRank scores
    calculate_pagerank(adj_matrix, pagerank);

    // Print PageRank scores
    printf("PageRank Scores:\n");
    for (int i = 0; i < N; i++) {
        printf("Node %d: %.4f\n", i, pagerank[i]);
    }

    return 0;
}
