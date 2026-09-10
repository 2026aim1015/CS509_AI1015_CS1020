# Assignment 04 — K-Means Clustering and FastMap

## Objective

The objective of this assignment is to implement and test:

* K-Means Clustering
* FastMap Dimensionality Reduction

Both algorithms are implemented in C++ and tested on datasets of different sizes. Execution time and algorithm-specific results are recorded.

## Project Structure

```text
assignment_04/
│
├── include/
│   ├── fastmap.hpp
│   ├── kmeans.hpp
│   └── timer.hpp
│
├── src/
│   ├── fastmap.cpp
│   └── kmeans.cpp
│
├── driver/
│   ├── fastmap_driver.cpp
│   └── kmeans_driver.cpp
│
├── tests/
│   ├── fastmap/
│   │   ├── fm_01.txt
│   │   ├── fm_02.txt
│   │   ├── fm_03.txt
│   │   └── fm_04.txt
│   │
│   └── kmeans/
│       ├── km_01.txt
│       ├── km_02.txt
│       ├── km_03.txt
│       └── km_04.txt
│
└── outputs/
    ├── fastmap/
    └── kmeans/
```

## Algorithms

### K-Means

K-Means divides the given data points into `K` clusters.

Steps:

1. Initialize the centroids.
2. Assign each point to its nearest centroid.
3. Recalculate the centroids.
4. Repeat until convergence.
5. Calculate WCSS for the final clusters.

### FastMap

FastMap reduces the dimensionality of a dataset while trying to preserve the distances between objects.

Steps:

1. Select two pivot objects.
2. Calculate distances from the pivots.
3. Project objects onto the current dimension.
4. Remove the contribution of the current dimension.
5. Repeat for the required number of dimensions.

## Test Cases

### K-Means

| Test File   |  Points | Dimensions |  K |
| ----------- | ------: | ---------: | -: |
| `km_01.txt` |     100 |          2 |  3 |
| `km_02.txt` |   1,000 |          2 |  5 |
| `km_03.txt` |  10,000 |          5 |  8 |
| `km_04.txt` | 100,000 |          5 | 10 |

### FastMap

| Test File   | Objects | Target Dimensions |
| ----------- | ------: | ----------------: |
| `fm_01.txt` |      10 |                 2 |
| `fm_02.txt` |     100 |                 2 |
| `fm_03.txt` |   1,000 |                 3 |
| `fm_04.txt` |  10,000 |                 3 |

## Results

### K-Means Results

| Test        | Iterations |           WCSS | Converged | Time (ms) |
| ----------- | ---------: | -------------: | --------- | --------: |
| `km_01.txt` |          2 |     411.758021 | Yes       |    0.9990 |
| `km_02.txt` |          2 |  10,000.000000 | Yes       |    0.0000 |
| `km_03.txt` |          2 |  80,000.000000 | Yes       |    5.6360 |
| `km_04.txt` |          2 | 312,500.000000 | Yes       |   14.4570 |

### FastMap Results

| Test        | Objects | Target Dimensions |     Time (ms) |
| ----------- | ------: | ----------------: | ------------: |
| `fm_01.txt` |      10 |                 2 |      0.000000 |
| `fm_02.txt` |     100 |                 2 |      0.000000 |
| `fm_03.txt` |   1,000 |                 3 |    267.147000 |
| `fm_04.txt` |  10,000 |                 3 | 16,149.099000 |

## Observations

* All K-Means test cases converged in 2 iterations.
* K-Means execution time increased with larger datasets.
* FastMap produced the required reduced dimensions for all test cases.
* FastMap took considerably more time for the larger datasets.
* The `fm_04.txt` test case had the highest execution time.

## Complexity

### K-Means

For `N` points, `K` clusters, `D` dimensions and `I` iterations:

```text
O(N × K × D × I)
```

### FastMap

The running time depends mainly on the number of objects, distance calculations, pivot selection and target dimensions.

## Conclusion

K-Means and FastMap were implemented successfully in C++. Both algorithms were tested using datasets of different sizes, and their execution results were recorded. K-Means converged for all test cases, while FastMap successfully generated the requested lower-dimensional representation.
