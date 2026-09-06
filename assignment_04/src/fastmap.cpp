#include "../include/fastmap.hpp"

#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;


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

    // Store coordinates for all objects.
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

        int pivotA = findFarthest(currentDistance,startObject,n );
        int pivotB = findFarthest(currentDistance,pivotA,n);

        result.pivotA[dim] = pivotA;
        result.pivotB[dim] = pivotB;

        // Distance between the two pivots.
        double pivotDistance = currentDistance[pivotA][pivotB];

        if (pivotDistance <= 0.0)
        {
            for (int i = 0; i < n; i++)
            {
                result.coordinates[i][dim] = 0.0;
            }
            continue;
        }
        for (int i = 0; i < n; i++)
        {
            double dAi = currentDistance[pivotA][i];
            double dBi = currentDistance[pivotB][i];

            double numerator = (dAi * dAi)+ (pivotDistance * pivotDistance)- (dBi * dBi);

            double coordinate =numerator / (2.0 * pivotDistance);

            result.coordinates[i][dim] = coordinate;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                double difference =result.coordinates[i][dim]- result.coordinates[j][dim];

                double remainingSquared =(currentDistance[i][j] * currentDistance[i][j])- (difference * difference);

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