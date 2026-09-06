#include "kmeans.hpp"
#include <cmath>
#include <limits>

static double computeEuclideanDistanceSq(const std::vector<double>& a, const std::vector<double>& b, int D) {
    double dist_sq = 0.0;
    for (int d = 0; d < D; ++d) {
        double diff = a[d] - b[d];
        dist_sq += diff * diff;
    }
    return dist_sq;
}

KMeansResult runKMeans(const std::vector<std::vector<double>>& points, const KMeansParams& params) {
    KMeansResult result;
    int N = params.N;
    int D = params.D;
    int K = params.K;

    result.assignments.assign(N, 0);
    result.centroids.assign(K, std::vector<double>(D, 0.0));

    // Section 2.3: Initializing with the first K input points in input order
    for (int k = 0; k < K; ++k) {
        result.centroids[k] = points[k];
    }

    std::vector<std::vector<double>> new_centroids(K, std::vector<double>(D, 0.0));
    std::vector<int> cluster_counts(K, 0);

    for (int iter = 1; iter <= params.max_iterations; ++iter) {
        result.iterations = iter;

        // 1. Assignment step: assign each point to nearest centroid
        for (int i = 0; i < N; ++i) {
            double min_dist_sq = std::numeric_limits<double>::max();
            int best_cluster = 0;

            for (int k = 0; k < K; ++k) {
                double dist_sq = computeEuclideanDistanceSq(points[i], result.centroids[k], D);
                if (dist_sq < min_dist_sq) {
                    min_dist_sq = dist_sq;
                    best_cluster = k;
                }
            }
            result.assignments[i] = best_cluster;
        }

        // 2. Update step: recompute centroid as mean of assigned points
        for (int k = 0; k < K; ++k) {
            std::fill(new_centroids[k].begin(), new_centroids[k].end(), 0.0);
            cluster_counts[k] = 0;
        }

        for (int i = 0; i < N; ++i) {
            int c = result.assignments[i];
            cluster_counts[c]++;
            for (int d = 0; d < D; ++d) {
                new_centroids[c][d] += points[i][d];
            }
        }

        double max_shift = 0.0;
        for (int k = 0; k < K; ++k) {
            if (cluster_counts[k] > 0) {
                for (int d = 0; d < D; ++d) {
                    new_centroids[k][d] /= cluster_counts[k];
                }
            } else {
                // Section 2.3: Keep previous centroid unchanged if cluster becomes empty
                new_centroids[k] = result.centroids[k];
            }

            // Check Euclidean shift of centroid
            double shift = std::sqrt(computeEuclideanDistanceSq(result.centroids[k], new_centroids[k], D));
            if (shift > max_shift) {
                max_shift = shift;
            }
        }

        result.centroids = new_centroids;

        // Convergence check against tolerance
        if (max_shift <= params.tolerance) {
            result.converged = true;
            break;
        }
    }

    // Compute Within-Cluster Sum of Squares (WCSS)
    result.wcss = 0.0;
    for (int i = 0; i < N; ++i) {
        int c = result.assignments[i];
        result.wcss += computeEuclideanDistanceSq(points[i], result.centroids[c], D);
    }

    return result;
}