#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers;
    int num;

    std::cout << "Enter integers (enter -1 to stop): ";
    while (std::cin >> num && num != -1) {
        numbers.push_back(num);
    }

    std::cout << "Numbers entered: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    int even_sum = 0;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it % 2 == 0)
            even_sum += *it;
    }
    std::cout << "Sum of even numbers: " << even_sum << std::endl;

    return 0;
}