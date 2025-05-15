#include <iostream>
#include <vector>
#include <algorithm> // for for_each
#include <numeric>   // for accumulate

int main() {
    std::vector<int> numbers;
    int num;

    std::cout << "Enter integers (enter -1 to stop): ";
    while (std::cin >> num && num != -1) {
        numbers.push_back(num);
    }

    std::cout << "Squares: ";
    std::for_each(numbers.begin(), numbers.end(), [](int x) {
        std::cout << (x * x) << " ";
        });
    std::cout << std::endl;

    int sum_of_squares = std::accumulate(numbers.begin(), numbers.end(), 0, [](int total, int x) {
        return total + (x * x);
        });

    std::cout << "Sum of squares: " << sum_of_squares << std::endl;

    return 0;
}