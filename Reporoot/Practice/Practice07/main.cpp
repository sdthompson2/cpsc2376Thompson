#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

class Employee {
protected:
    std::string name;
    int id;

public:
    Employee(std::string name, int id) : name(name), id(id) {}
    virtual ~Employee() {} // needed for deleting base class pointers
    virtual double calculateSalary() const = 0;
    virtual void displayInfo() const = 0;
};

class SalariedEmployee : public Employee {
private:
    double monthlySalary;

public:
    SalariedEmployee(std::string name, int id, double salary)
        : Employee(name, id), monthlySalary(salary) {}

    double calculateSalary() const override {
        return monthlySalary;
    }

    void displayInfo() const override {
        std::cout << "ID: " << id << ", Name: " << name
            << ", Type: Salaried, Monthly Salary: $"
            << std::fixed << std::setprecision(2) << calculateSalary() << "\n";
    }
};

class HourlyEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;

public:
    HourlyEmployee(std::string name, int id, double rate, int hours)
        : Employee(name, id), hourlyRate(rate), hoursWorked(hours) {}

    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }

    void displayInfo() const override {
        std::cout << "ID: " << id << ", Name: " << name
            << ", Type: Hourly, Hours Worked: " << hoursWorked
            << ", Hourly Rate: $" << std::fixed << std::setprecision(2) << hourlyRate
            << ", Salary: $" << calculateSalary() << "\n";
    }
};

class CommissionEmployee : public Employee {
private:
    double baseSalary;
    double totalSales;
    double commissionRate;

public:
    CommissionEmployee(std::string name, int id, double base, double sales, double rate)
        : Employee(name, id), baseSalary(base), totalSales(sales), commissionRate(rate) {}

    double calculateSalary() const override {
        return baseSalary + (totalSales * commissionRate);
    }

    void displayInfo() const override {
        std::cout << "ID: " << id << ", Name: " << name
            << ", Type: Commission, Base: $" << baseSalary
            << ", Sales: $" << totalSales
            << ", Rate: " << commissionRate
            << ", Salary: $" << std::fixed << std::setprecision(2) << calculateSalary() << "\n";
    }
};

int main() {
    std::ifstream infile("employees.txt");
    if (!infile) {
        std::cerr << "Error: Cannot open file 'employees.txt'\n";
        return 1;
    }

    std::vector<Employee*> employees;
    std::string type;
    int id;
    std::string name;

    while (infile >> type >> id >> name) {
        if (type == "Salaried") {
            double salary;
            infile >> salary;
            employees.push_back(new SalariedEmployee(name, id, salary));
        }
        else if (type == "Hourly") {
            double rate;
            int hours;
            infile >> rate >> hours;
            employees.push_back(new HourlyEmployee(name, id, rate, hours));
        }
        else if (type == "Commission") {
            double base, sales, rate;
            infile >> base >> sales >> rate;
            employees.push_back(new CommissionEmployee(name, id, base, sales, rate));
        }
        else {
            std::cerr << "Unknown employee type: " << type << "\n";
        }
    }

    std::cout << "\nEmployee Info:\n";
    for (const auto& emp : employees) {
        emp->displayInfo();
    }

    for (auto emp : employees) {
        delete emp;
    }

    return 0;
}
