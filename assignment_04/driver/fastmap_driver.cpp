#include "../include/fastmap.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <cmath>

using namespace std;
// Check whether the input distance matrix is valid.
bool validateDistanceMatrix(const vector<vector<double>>& distance,int n,int k)
{

    if (k <= 0 || k >= n)
    {
        cerr << "Error: Invalid target dimension K." << endl;
        return false;
    }
    if ((int)distance.size() != n)
    {
        cerr << "Error: Invalid matrix size." << endl;
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        // Every row should contain n values.
        if ((int)distance[i].size() != n)
        {
            cerr << "Error: Distance matrix is not square." << endl;
            return false;
        }
        // Distance from an object to itself should be zero.
        if (fabs(distance[i][i]) > 1e-9)
        {
            cerr << "Error: Diagonal distance must be zero." << endl;
            return false;
        }

        for (int j = 0; j < n; j++)
        {
            if (distance[i][j] < 0.0)
            {
                cerr << "Error: Negative distance found."<< endl;
                return false;
            }
             // Distance from i to j should be the same as j to i.
            if (fabs(distance[i][j] - distance[j][i]) > 1e-9)
            {
                cerr << "Error: Distance matrix is not symmetric."<< endl;
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char* argv[])
{

    if (argc != 2)
    {
        cerr << "Usage: fastmap.exe <input_file>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream infile(filename);

    if (!infile.is_open())
    {
        cerr << "Error: Cannot open input file: "<< filename << endl;
        return 1;
    }

    int n;
    int k;
    // Read the number of objects and target dimensions.
    infile >> n >> k;

    if (!infile)
    {
        cerr << "Error: Invalid input format." << endl;
        return 1;
    }

    if (n <= 0)
    {
        cerr << "Error: Invalid number of objects." << endl;
        return 1;
    }

    vector<vector<double>> distance(n,vector<double>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            infile >> distance[i][j];

            if (!infile)
            {
                cerr << "Error: Invalid distance matrix."<< endl;
                return 1;
            }
        }
    }

    infile.close();
    // Check the matrix before running FastMap.
    if (!validateDistanceMatrix(distance, n, k))
    {
        return 1;
    }


    auto start =chrono::high_resolution_clock::now();
    FastMapResult result =fastMap(distance, n, k);
    auto end =chrono::high_resolution_clock::now();


    // Calculate execution time
    double executionTime =chrono::duration<double, milli>(end - start).count();
    cout << fixed << setprecision(6);
    cout << "Algorithm: FastMap" << endl;
    cout << "Target dimensions: " << k << endl;
    cout << "Pivots per dimension:" << endl;

    for (int dim = 0; dim < k; dim++)
    {
        cout << "Dim " << dim + 1 << ": "<< result.pivotA[dim]<< " "<< result.pivotB[dim]<< endl;
    }
     // Print the final coordinates of all objects.
    cout << "Object coordinates:" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << i << ":";

        for (int dim = 0; dim < k; dim++)
        {
            cout << " "<< result.coordinates[i][dim];
        }

        cout << endl;
    }

    cout << "Execution time: "<< executionTime<< " ms" << endl;
    return 0;
}