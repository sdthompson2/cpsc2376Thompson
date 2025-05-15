#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const string FILE_NAME = "account_balance.txt";
const double INITIAL_BALANCE = 100.00;

// Function to read balance from file
double readBalance() {
    ifstream inFile(FILE_NAME);
    double balance = INITIAL_BALANCE;

    if (inFile) {  // File exists, read balance
        inFile >> balance;
    }
    else {  // File does not exist, create it with initial balance
        ofstream outFile(FILE_NAME);
        outFile << fixed << setprecision(2) << INITIAL_BALANCE;
    }

    return balance;
}

// Function to update balance in file
void updateBalance(double balance) {
    ofstream outFile(FILE_NAME);
    if (!outFile) {
        cout << "Error: Unable to update balance file!" << endl;
        return;
    }
    outFile << fixed << setprecision(2) << balance;
}

// Function to display menu
void displayMenu() {
    cout << "\n--- Bank Account Menu ---\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    double balance = readBalance();
    int choice;

    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {  // Check for invalid input
            cin.clear();  // Clear error flag
            cin.ignore(10000, '\n');  // Ignore invalid input
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Your balance: $" << fixed << setprecision(2) << balance << endl;
            break;

        case 2: {
            double deposit;
            cout << "Enter deposit amount: $";
            cin >> deposit;

            if (cin.fail() || deposit <= 0) {
                cout << "Invalid amount. Deposit must be positive.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else {
                balance += deposit;
                updateBalance(balance);
                cout << "Deposit successful. New balance: $" << balance << endl;
            }
            break;
        }

        case 3: {
            double withdraw;
            cout << "Enter withdrawal amount: $";
            cin >> withdraw;

            if (cin.fail() || withdraw <= 0) {
                cout << "Invalid amount. Withdrawal must be positive.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else if (withdraw > balance) {
                cout << "Insufficient funds. Your balance is: $" << balance << endl;
            }
            else {
                balance -= withdraw;
                updateBalance(balance);
                cout << "Withdrawal successful! New balance: $" << balance << endl;
            }
            break;
        }

        case 4:
            cout << "Exiting program. Thank you.\n";
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }

    } while (choice != 4);

    return 0;
}