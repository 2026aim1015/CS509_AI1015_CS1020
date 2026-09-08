#include <iostream>
#include <fstream>
#include <iomanip>

void generate_km(const std::string& filename, int N, int D, int K, double scale, int mod_mult) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Cannot open " << filename << "\n";
        return;
    }

    out << N << " " << D << " " << K << "\n";
    out << std::fixed << std::setprecision(2);

    for (int i = 0; i < N; ++i) {
        int c = i % K;
        for (int d = 0; d < D; ++d) {
            double val = (c * scale) + ((i * (d + mod_mult)) % 20) * 0.25 + 1.0;
            out << val << (d == D - 1 ? "" : " ");
        }
        out << "\n";
    }

    out << "MAX_ITERATIONS 300\n";
    out << "TOLERANCE 0.0001\n";
    out.close();
    std::cout << "Generated " << filename << " successfully (" << N << " points).\n";
}

int main() {
    generate_km("tests/kmeans/km_03.txt", 10000, 5, 8, 15.0, 3);
    generate_km("tests/kmeans/km_04.txt", 100000, 5, 10, 25.0, 2);
    return 0;
}
