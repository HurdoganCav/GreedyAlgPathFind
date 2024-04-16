#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct City {
    double x, y;
    bool visited;
};

double distance(const City& city1, const City& city2) {
    return sqrt(pow(city1.x - city2.x, 2) + pow(city1.y - city2.y, 2));
}

// Açgözlü algoritma
void greedyTSP(vector<City>& cities) {
    int n = cities.size();
    cities[0].visited = true;
    double total_cost = 0;

    cout << "Optimal maliyet deðeri: ";

    int current_city = 0;
    cout << "0";

    for (int i = 0; i < n - 1; ++i) {
        double min_distance = numeric_limits<double>::max();
        int nearest_city;

        for (int j = 0; j < n; ++j) {
            if (!cities[j].visited) {
                double dist = distance(cities[current_city], cities[j]);
                if (dist < min_distance) {
                    min_distance = dist;
                    nearest_city = j;
                }
            }
        }

        cities[nearest_city].visited = true;
        total_cost += min_distance;
        cout << " -> " << nearest_city;
        current_city = nearest_city;
    }

    total_cost += distance(cities[current_city], cities[0]);
    cout << " -> 0\n";

    cout << "Toplam maliyet: " << total_cost << endl;
}

int main() {
    vector<string> files = { "tsp_51_1.txt", "tsp_100_2.txt", "tsp_783_1.txt", "tsp_4461_1.txt", "tsp_85900_1.txt" };

    for (const auto& filename : files) {
        // Ensure the path is correctly formatted with a raw string literal for clarity
        string filePath = R"(C:\Users\Hurdogan\Desktop\AAT\Algoritma\Data\)" + filename;

        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Dosya açýlamadý: " << filename << endl;
            continue;
        }

        int n;
        file >> n;
        vector<City> cities(n);
        for (int i = 0; i < n; ++i) {
            file >> cities[i].x >> cities[i].y;
            cities[i].visited = false;
        }
        file.close();

        cout << "Dosya: " << filename << endl;

        auto start = high_resolution_clock::now();

        greedyTSP(cities);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        cout << "Geçen süre: " << duration.count() << " milisaniye" << endl;

        cout << endl;
    }

    return 0;
}