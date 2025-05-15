#include <iostream>
#include <vector>

void printVector(const std::vector<int>& vec) {
    for (int num : vec) std::cout << num << " ";
    std::cout << "\n";
}

void doubleVector(std::vector<int>& vec) {
    for (int& num : vec) num *= 2;
}

int sumVector(const std::vector<int>& vec) {
    int sum = 0;
    for (int num : vec) sum += num;
    return sum;
}

void printMultiples(const std::vector<int>& vec, int value) {
    for (int num : vec) if (num % value == 0) std::cout << num << " ";
    std::cout << "\n";
}

int main() {
    std::vector<int> numbers;
    int choice, num;

    while (true) {
        std::cout << "1. Add\n2. Print\n3. Double\n4. Sum\n5. Multiples\n6. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) { std::cin >> num; numbers.push_back(num); }
        else if (choice == 2) printVector(numbers);
        else if (choice == 3) doubleVector(numbers);
        else if (choice == 4) std::cout << sumVector(numbers) << "\n";
        else if (choice == 5) { std::cin >> num; printMultiples(numbers, num); }
        else if (choice == 6) break;
        else std::cout << "Invalid choice\n";
    }

    return 0;
}
