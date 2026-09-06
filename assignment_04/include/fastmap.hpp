#ifndef FASTMAP_H
#define FASTMAP_H

#include <vector>

struct FastMapResult
{
    int n;
    int k;

    std::vector<std::vector<double>> coordinates;
    std::vector<int> pivotA;
    std::vector<int> pivotB;
};

FastMapResult fastMap(
    const std::vector<std::vector<double>>& distance,
    int n,
    int k
);

#endif