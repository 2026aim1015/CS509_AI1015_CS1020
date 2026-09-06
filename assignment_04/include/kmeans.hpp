#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <vector>

struct KMeansParams {
    int N = 0;              // Number of data points
    int D = 0;              // Dimensionality of points
    int K = 0;              // Target clusters
    int max_iterations = 300;
    double tolerance = 1e-4;
};

struct KMeansResult {
    std::vector<int> assignments;               // Cluster ID for each point
    std::vector<std::vector<double>> centroids; // Final coordinates of centroids
    double wcss = 0.0;                          // Within-Cluster Sum of Squares
    int iterations = 0;
    bool converged = false;
};

// Lloyd's K-Means clustering algorithm
KMeansResult runKMeans(const std::vector<std::vector<double>>& points, const KMeansParams& params);

#endif // KMEANS_HPP