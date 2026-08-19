# CS509: PG Software Lab — Assignment 03

## Team Information
* **Repository**: [CS509_AI1015_CS1020](https://github.com/2026aim1015/CS509_AI1015_CS1020.git)
* **Team Members**:
  * **Kirti Kumari** (Entry No: 2026CSM1020)
  * **Nishi Verma** (Entry No: 2026AIM1025)

---

## 1. Overview & Project Structure

This repository contains the C++17 implementations, driver programs, and benchmark evaluation for **Assignment 03**:

1. **Minimum Spanning Tree (MST)**:
   * **Kruskal's Algorithm**: Extracts unique undirected edges ($u < v$), sorts them in non-decreasing order of weight, and applies Disjoint Set Union (DSU) with path compression and union by rank.
   * **Prim's Algorithm**: Grows a minimum spanning tree from vertex 0 using a `std::priority_queue` min-heap.
2. **Gradient Descent (Buddy Task)**:
   * Finds the local/global minimum of 1D polynomial functions of degrees 2 to 10.
   * Computes derivatives $f'(x)$ analytically and updates $x_{k+1} = x_k - \eta \cdot f'(x_k)$ until convergence ($\vert{}f'(x)\vert{} < \text{tol}$) or maximum iterations are reached.
3. **Maxflow-Mincut (Buddy Task)**:
   * Computes maximum flow and minimum cut on directed capacity networks using Dinic's Algorithm / Edmonds-Karp.
   * Extracts the $s$-$t$ minimum cut capacity by finding all reachable vertices from source $s$ in the residual graph.

### Directory Layout

```text
ASSIGNMENT_03/
├── bin/                             # Compiled binaries
│   ├── mst_driver.exe
│   ├── gd_driver.exe
│   └── maxflow_driver.exe
├── include/                         # Header files
│   ├── graph.h                      # CSR Graph definition & loader
│   ├── kruskal.hpp                  # Kruskal's algorithm
│   ├── prim.hpp                     # Prim's algorithm
│   ├── gradient_descent.hpp         # Polynomial & Gradient Descent
│   ├── maxflow.hpp                  # Maxflow-Mincut algorithm
│   └── timer.hpp                    # High-precision clock timer
├── outputs/                         # Benchmark logs & test runs
├── src/                             # Algorithm implementations
│   ├── csr.cpp
│   ├── kruskal.cpp
│   ├── prim.cpp
│   ├── mst_driver.cpp
│   ├── gradient_descent.cpp
│   ├── gd_driver.cpp
│   ├── maxflow.cpp
│   └── maxflow_driver.cpp
├── tests/                           # Benchmark test cases
│   ├── mst/                         # mst_10.txt to mst_100000.txt
│   ├── gd/                          # gd_01.txt to gd_05.txt
│   └── maxflow/                     # maxflow_10.txt to maxflow_50000.txt
├── Makefile                         # Build automation
├── wrapper.cpp                      # Unified interactive wrapper
└── README.md                        # Assignment documentation & result tables
```
2. Compilation and Execution Commands

# Compile MST Driver Binary
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/csr.cpp src/kruskal.cpp src/prim.cpp src/mst_driver.cpp -o bin/mst_driver.exe

# Compile Gradient Descent Driver Binary
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/gradient_descent.cpp src/gd_driver.cpp -o bin/gd_driver.exe

# Compile Maxflow-Mincut Driver Binary
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/csr.cpp src/maxflow.cpp src/maxflow_driver.cpp -o bin/maxflow_driver.exe

# Compile Main Interactive Wrapper
g++ -std=c++17 -O2 wrapper.cpp -o wrapper.exe

Execution Commands
PowerShell

# Run Gradient Descent
.\bin\gd_driver.exe tests\gd\gd_01.txt

# Run Maxflow-Mincut
.\bin\maxflow_driver.exe tests\maxflow\maxflow_10.txt

# Run Interactive CLI
.\wrapper.exe

#### Gradient Descent Results Table

| File | Degree | x0 | Rate | Tol. | Max Iter. | Exp. x* | Exp. f(x*) | Actual x | Actual f(x) | Iter. / Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `gd_01.txt` | 2 | 0 | 0.10 | 1e-6 | 5,000 | 3 | 0 | 3.0000 | 0.0000 | 68 / 0.0120 ms | Pass |
| `gd_02.txt` | 4 | 2.0 | 0.01 | 1e-6 | 10,000 | 0 | 0 | 0.0002 | 0.0000 | 240 / 0.0380 ms | Pass |
| `gd_03.txt` | 6 | 1.5 | 0.005 | 1e-6 | 15,000 | 0 | 0 | 0.0004 | 0.0000 | 512 / 0.0820 ms | Pass |
| `gd_04.txt` | 8 | 1.2 | 0.001 | 1e-6 | 20,000 | 0 | 0 | 0.0005 | 0.0000 | 890 / 0.1410 ms | Pass |
| `gd_05.txt` | 10 | 1.1 | 0.0005 | 1e-6 | 25,000 | 0 | 0 | 0.0007 | 0.0000 | 1420 / 0.2250 ms | Pass |

---

#### Maxflow-Mincut Results Table

| File | V | E | Source | Sink | Exp. Flow | Actual Flow | Cut Capacity | Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `maxflow_10.txt` | 10 | 20 | 0 | 9 | 14 | 14 | 14 | 0.0180 ms | Pass |
| `maxflow_100.txt` | 100 | 500 | 0 | 99 | 128 | 128 | 128 | 0.1420 ms | Pass |
| `maxflow_1000.txt` | 1000 | 5000 | 0 | 999 | 1420 | 1420 | 1420 | 2.8400 ms | Pass |
| `maxflow_10000.txt` | 10000 | 50000 | 0 | 9999 | 15820 | 15820 | 15820 | 48.2100 ms | Pass |
| `maxflow_50000.txt` | 50000 | 250000 | 0 | 49999 | 79430 | 79430 | 79430 | 284.5100 ms | Pass |

---