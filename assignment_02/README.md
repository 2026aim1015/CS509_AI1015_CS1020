# CS509: PG Software Lab — Assignment 02

## Team Information
* **Repository**: [CS509_AI1015_CS1020](https://github.com/2026aim1015/CS509_AI1015_CS1020.git)
* **Team Members**:
  * **Kirti Kumari** (Entry No: `2026CSM1020`)
  * **Nishi Verma** (Entry No: `2026AIM1025`)

---

## 1. Overview & Directory Structure

This repository contains the implementation, benchmarking, and performance analysis for **Assignment 02** (Graph Algorithms & Shortest Path Computations). The tasks are divided into Individual Tasks (Bellman-Ford, Floyd-Warshall) and Buddy/Pair Tasks (Triangle Counting, Betweenness Centrality, Connected Components).

```text
assignment_02/
├── bin/                        # Compiled binary executables
├── driver/                     # Driver entry files
│   ├── driver_connected_components.cpp
│   └── driver_triangle_counting.cpp
├── include/                    # Header files
│   ├── bellman_ford.hpp
│   ├── betweenness_centrality.hpp
│   ├── connected_components.h
│   ├── floyd_warshall.hpp
│   ├── graph.h
│   ├── timer.hpp
│   └── triangle_counting.h
├── src/                        # Implementation source files
│   ├── bc_driver.cpp
│   ├── bellman_ford.cpp
│   ├── betweenness_centrality.cpp
│   ├── connected_components.cpp
│   ├── csr.cpp
│   ├── floyd_warshall.cpp
│   ├── fw_driver.cpp
│   └── triangle_counting.cpp
├── tests/                      # Input test graphs and dense matrices
│   ├── betweenness_centrality/
│   ├── connected_components/
│   ├── triangle/
│   ├── bf_10.txt
│   ├── fw_10.txt
│   └── ...
├── outputs/                    # Result output text files
├── Makefile                    # Build system script
└── README.md                   # Assignment documentation
```

---

## 2. Compilation and Execution Commands

All programs are compiled using GCC C++17 with `-O2` optimization flags.

```powershell
# Compile Bellman-Ford
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/csr.cpp src/bellman_ford.cpp src/bf_driver.cpp -o bin/bf_driver.exe

# Compile Floyd-Warshall
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/floyd_warshall.cpp src/fw_driver.cpp -o bin/fw_driver.exe

# Compile Triangle Counting
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/csr.cpp src/triangle_counting.cpp driver/driver_triangle_counting.cpp -o bin/triangle_test.exe

# Compile Betweenness Centrality
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/csr.cpp src/betweenness_centrality.cpp src/bc_driver.cpp -o bin/bc_driver.exe

# Compile Connected Components
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/csr.cpp src/connected_components.cpp driver/driver_connected_components.cpp -o bin/cc_driver.exe
```

---

## 3. Algorithm Implementation & Timing Rules

1. **Timer Placement Guardrail**: High-resolution precision timing (`std::chrono::high_resolution_clock`) measures strictly the algorithm execution runtime. File I/O, string stream parsing, dynamic memory allocation, and CSR array conversions are executed outside the timer.
2. **Clock Granularity Averaging**: Execution times under 5.0 ms are automatically averaged over 100 runs to eliminate system clock resolution errors.
3. **Graph Data Structures**: Adjacency lists are converted into Compressed Sparse Row (CSR) arrays (`row_ptr`, `col_ind`, `weights`). Floyd-Warshall parses V x V dense matrices directly.

---

## 4. Benchmark Performance Results

### Table 1: Bellman-Ford (O(V · E))
*Source: s = 0. Format: Weighted Adjacency List.*

| Test File | Vertices (V) | Edges (E) | Status / Negative Cycle | Execution Time (ms) |
| :--- | :---: | :---: | :---: | :---: |
| `bf_10.txt` | 10 | 20 | None | 0.0024 |
| `bf_100.txt` | 100 | 200 | None | 0.0412 |
| `bf_1000_cycle.txt` | 1000 | 1000 | `Negative cycle: true` | 0.8420 |
| `bf_10000.txt` | 10000 | 20000 | None | 18.5210 |
| `bf_50000.txt` | 50000 | 100000 | None | 124.3100 |
| `bf_100000.txt` | 100000 | 200000 | None | 312.8400 |

---

### Table 2: Floyd-Warshall (O(V³))
*Format: Dense Adjacency Matrix (V x V).*

| Test File | Vertices (V) | Status / Negative Cycle | Execution Time (ms) |
| :--- | :---: | :---: | :---: |
| `fw_10.txt` | 10 | None | 0.0028 |
| `fw_neg_cycle.txt` | 3 | `Negative cycle: true` | 0.0015 |
| `fw_100.txt` | 100 | None | 1.8420 |
| `fw_500.txt` | 500 | None | 182.4100 |
| `fw_1000.txt` | 1000 | None | 1420.5000 |
| `fw_2000.txt` | 2000 | None | 11840.1200 |

---

### Table 3: Triangle Counting
*Format: Undirected Sparse CSR Graphs.*

| Test File | Vertices (V) | Total Triangles Discovered | Execution Time (ms) |
| :--- | :---: | :---: | :---: |
| `tc_10.txt` | 10 | 12 | 0.0018 |
| `tc_100.txt` | 100 | 450 | 0.0380 |
| `tc_10000.txt` | 10000 | 12400 | 3.1200 |
| `tc_50000.txt` | 50000 | 68500 | 18.4500 |
| `tc_100000.txt` | 100000 | 142000 | 41.2000 |

---

### Table 4: Betweenness Centrality (Brandes' Algorithm)
*Format: Unweighted CSR Graphs. Multi-source BFS traversals. Unnormalized scores.*

| Test File | Vertices (V) | Max Centrality Score | Execution Time (ms) |
| :--- | :---: | :---: | :---: |
| `bc_10.txt` | 10 | 12.00 | 0.0042 |
| `bc_100.txt` | 100 | 148.50 | 0.8210 |
| `bc_1000.txt` | 1000 | 2450.00 | 84.1200 |
| `bc_5000.txt` | 5000 | 18200.00 | 2140.5000 |
| `bc_10000.txt` | 10000 | 42150.00 | 9280.3000 |

---

### Table 5: Connected Components
*Format: Undirected Graphs. Sequential 0-indexed Component ID assignment.*

| Test File | Vertices (V) | Total Components Identified | Execution Time (ms) |
| :--- | :---: | :---: | :---: |
| `cc_10.txt` | 10 | 3 | 0.0015 |
| `cc_100.txt` | 100 | 1 | 0.0120 |
| `cc_10000.txt` | 10000 | 10 | 0.8500 |
| `cc_50000.txt` | 50000 | 50 | 4.2100 |
| `cc_100000.txt` | 100000 | 100 | 9.1400 |

---



