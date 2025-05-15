#include <iostream>
#include <vector>
#include <numeric> // for std::accumulate

int main() {
    std::vector<int> numbers;
    int num;

    std::cout << "Enter integers (enter -1 to stop): ";
    while (std::cin >> num && num != -1) {
        numbers.push_back(num);
    }

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Product: " << product << std::endl;

    return 0;
}