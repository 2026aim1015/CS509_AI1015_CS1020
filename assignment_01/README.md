# CS509_AI1015_CS1020

## Team Members

| Entry Number | Name |
|---------------|------|
| 2026CSM1020 | Kirti Kumari |
| 2026AIM1015 | Nishi Verma |

## Repository Structure
CS509_AI1015_CS1020/
├── assignment_01/
│ ├── driver/
│ │ ├── bfs_driver.cpp # CLI driver for BFS: reads graph file + source vertex
│ │ ├── dfs_driver.cpp # CLI driver for DFS
│ │ └── sssp_driver.cpp # CLI driver for SSSP (weighted shortest paths)
│ │
│ ├── src/
│ │ ├── graph.h # CSRGraph struct + shared declarations
│ │ ├── csr.cpp # loadCSRGraph(): parses input file into CSR format
│ │ ├── bfs.cpp # BFS traversal + distance computation
│ │ ├── dfs.cpp # DFS traversal
│ │ ├── sssp.cpp # Dijkstra-based SSSP
│ │ ├── sssp_csr.h
│ │ └── sssp_csr.cpp
│ │
│ ├── tests/
│ │ ├── bfs_test_01.txt … bfs_test_03.txt
│ │ ├── dfs_test_01.txt … dfs_test_03.txt
│ │ └── sssp_test_01.txt, sssp_test_02.txt
│ │
│ └── outputs/
│ ├── bfs_output_01.txt, bfs_output_02.txt
│ ├── dfs_output_01.txt … dfs_output_03.txt
│ └── sssp_output_01.txt, sssp_output.txt
│
├── common_wrapper/ # shared utilities used across assignments
└── README.md

## Input Format

Graphs are provided as an unweighted (BFS/DFS) or weighted (SSSP) adjacency list:

V E
u0 degree neighbor1 neighbor2 ...
u1 degree neighbor1 neighbor2 ...
...
SOURCE s


- `V` — number of vertices, `E` — number of edges (each undirected edge counted once)
- Each line lists a vertex, its degree, then that many neighbor IDs
- A vertex with no neighbors is written as `u 0`
- `SOURCE s` gives the starting vertex for the traversal
- Unreachable vertices are reported with a distance of `-1`

## Building

Each driver is compiled together with the algorithm source and `csr.cpp`, which all three depend on for graph loading:

```bash
# BFS
g++ -std=c++17 -O2 driver/bfs_driver.cpp src/bfs.cpp src/csr.cpp -I src -o bfs_driver.exe

# DFS
g++ -std=c++17 -O2 driver/dfs_driver.cpp src/dfs.cpp src/csr.cpp -I src -o dfs_driver.exe

# SSSP
g++ -std=c++17 -O2 driver/sssp_driver.cpp src/sssp.cpp src/sssp_csr.cpp -I src -o sssp_driver.exe
```

## Running

```bash
./bfs_driver.exe tests/bfs_test_01.txt 0 > outputs/bfs_output_01.txt
./dfs_driver.exe tests/dfs_test_01.txt 0 > outputs/dfs_output_01.txt
./sssp_driver.exe tests/sssp_test_01.txt 0 > outputs/sssp_output_01.txt
```

Source vertex defaults to 0 if omitted.

## Test Results

| Algorithm | Test Case | Vertices | Edges | Source | Execution Time |
|-----------|-----------|----------|-------|--------|-----------------|
| BFS | bfs_test_01.txt | 40 | 100 | 0 | 0 ms |
| BFS | bfs_test_02.txt | 20 | 25 | 0 | 0 ms |
| BFS | bfs_test_03.txt | 1000 | 1799 | 0 | 0 ms |
| DFS | dfs_test_01.txt | 5 | 6 | 0 | 0 ms |
| DFS | dfs_test_02.txt | 50 | 70 | 0 | 28.003 ms |
| DFS | dfs_test_03.txt | 1000 | 1799 | 0 | 143.51 ms |
| SSSP | sssp_test_01.txt | 5 | 6 | 0 | 0 ms |
| SSSP | sssp_test_02.txt | 6 | 9 | 0 | 0 ms |
| SSSP | sssp_output.txt | 1000 | 9945 | 0 | 1.99 ms |

## Notes

- The CSR loader (`loadCSRGraph` in `src/csr.cpp`) is shared across all three algorithms — a bug fix there affects BFS, DFS, and SSSP builds alike.
- DFS execution time scales noticeably with graph size in these results (0 ms at 5 vertices → 143.51 ms at 1000 vertices), which is expected given the recursive traversal overhead versus BFS's queue-based approach.
- Larger test graphs (1000 vertices) are generated to guarantee full connectivity via a random spanning tree, with additional random edges layered on top.