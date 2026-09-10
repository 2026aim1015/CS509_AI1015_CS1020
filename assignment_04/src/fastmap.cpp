#include "../include/fastmap.hpp"

#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

// Find the object that is farthest from the given object.
static int findFarthest(const vector<vector<double>>& distance,int object,int n)
{
    int farthest = object;
    double maxDistance = -1.0;

    for (int i = 0; i < n; i++)
    {
        if (distance[object][i] > maxDistance)
        {
            maxDistance = distance[object][i];
            farthest = i;
        }
    }

    return farthest;
}

FastMapResult fastMap(const vector<vector<double>>& distance, int n, int k)
{
    FastMapResult result;

    result.n = n;
    result.k = k;

    // Initialize coordinates for all objects.
    result.coordinates.assign( n, vector<double>(k, 0.0));

    // Store pivots for every dimension.
    result.pivotA.resize(k);
    result.pivotB.resize(k);

    // Working distance matrix.
    // It is progressively deflated after every dimension.
    vector<vector<double>> currentDistance = distance;

    for (int dim = 0; dim < k; dim++)
    {
        int startObject = 0;
        // Select the first pivot as the farthest object from the start object.
        int pivotA = findFarthest(currentDistance,startObject,n );
        // Select the second pivot as the farthest object from pivot A.
        int pivotB = findFarthest(currentDistance,pivotA,n);

        result.pivotA[dim] = pivotA;
        result.pivotB[dim] = pivotB;

        // If the pivots have zero distance, all coordinates in this dimension are set to zero.
        double pivotDistance = currentDistance[pivotA][pivotB];

        if (pivotDistance <= 0.0)
        {
            for (int i = 0; i < n; i++)
            {
                result.coordinates[i][dim] = 0.0;
            }
            continue;
        }
        // Calculate the coordinate of every object along this dimension.
        for (int i = 0; i < n; i++)
        {
            double dAi = currentDistance[pivotA][i];
            double dBi = currentDistance[pivotB][i];
            // FastMap coordinate calculation using the distances from the two selected pivots.
            double numerator = (dAi * dAi)+ (pivotDistance * pivotDistance)- (dBi * dBi);

            double coordinate =numerator / (2.0 * pivotDistance);

            result.coordinates[i][dim] = coordinate;
        }
        // Remove the distance represented by the current dimension.
        // The remaining distance is used for the next dimension.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                double difference =result.coordinates[i][dim]- result.coordinates[j][dim];

                double remainingSquared =(currentDistance[i][j] * currentDistance[i][j])- (difference * difference);
                // Avoid taking sqrt of a small negative value caused by floating-point errors.
                if (remainingSquared < 0.0)
                {
                    remainingSquared = 0.0;
                }
                currentDistance[i][j] = sqrt(remainingSquared);
            }
        }
    }
    return result;
}