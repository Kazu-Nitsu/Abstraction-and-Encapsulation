#include <iostream>
#include <vector>
#include <limits>
#include <set>
using namespace std;

class Employee {
protected:
    int id;
    string name;
public:
    Employee(int id, string name) : id(id), name(name) {}
    virtual double calculateSalary() const = 0;
    virtual void display() const = 0;
    int getId() const { return id; }
    virtual ~Employee() {}
};

class FullTimeEmployee : public Employee {
private:
    double salary;
public:
    FullTimeEmployee(int id, string name, double salary)
        : Employee(id, name), salary(salary) {}

    double calculateSalary() const override { return salary; }

    void display() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n"
             << "Fixed Monthly Salary: $" << salary << "\n\n";
    }
};

class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;
public:
    PartTimeEmployee(int id, string name, double hourlyWage, int hoursWorked)
        : Employee(id, name), hourlyWage(hourlyWage), hoursWorked(hoursWorked) {}

    double calculateSalary() const override { return hourlyWage * hoursWorked; }

    void display() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n"
             << "Hourly Wage: $" << hourlyWage << "\n"
             << "Hours Worked: " << hoursWorked << "\n"
             << "Total Salary: $" << calculateSalary() << "\n\n";
    }
};

class ContractualEmployee : public Employee {
private:
    double paymentPerProject;
    int projectsCompleted;
public:
    ContractualEmployee(int id, string name, double paymentPerProject, int projectsCompleted)
        : Employee(id, name), paymentPerProject(paymentPerProject), projectsCompleted(projectsCompleted) {}

    double calculateSalary() const override { return paymentPerProject * projectsCompleted; }

    void display() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n"
             << "Contract Payment Per Project: $" << paymentPerProject << "\n"
             << "Projects Completed: " << projectsCompleted << "\n"
             << "Total Salary: $" << calculateSalary() << "\n\n";
    }
};

set<int> existingIds;

int getUniqueId() {
    int id;
    while (true) {
        cout << "Enter Employee ID: ";
        if (!(cin >> id)) {
            cout << "Invalid input! Please enter a valid integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (existingIds.find(id) == existingIds.end()) {
            existingIds.insert(id);
            return id;
        }
        cout << "Duplicate ID! Please enter a unique ID.\n";
    }
}

int getValidInt(const string& prompt) {
    string input;
    int value;
    while (true) {
        cout << prompt;
        cin >> input;
        if (input.find_first_not_of("0123456789") == string::npos) {
            value = stoi(input);
            return value;
        }
        cout << "Invalid input! Please enter a valid integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double getValidDouble(const string& prompt) {
    string input;
    double value;
    while (true) {
        cout << prompt;
        cin >> input;
        bool isValid = true;
        int dotCount = 0;
        for (char c : input) {
            if (!isdigit(c)) {
                if (c == '.' && dotCount == 0) {
                    dotCount++;
                } else {
                    isValid = false;
                    break;
                }
            }
        }
        if (isValid) {
            value = stod(input);
            return value;
        }
        cout << "Invalid input! Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    vector<Employee*> employees;
    int choice;

    do {
        choice = getValidInt("\n----- Menu -----\n1 - Full-time Employee\n2 - Part-time Employee\n3 - Contractual Employee\n4 - Display Payroll Report\n5 - Exit\nEnter choice: ");

        switch (choice) {
            case 1: {
                int id = getUniqueId();
                cin.ignore();
                string name;
                cout << "Enter Employee Name: ";
                getline(cin, name);
                double salary = getValidDouble("Enter Fixed Monthly Salary: $");
                employees.push_back(new FullTimeEmployee(id, name, salary));
                break;
            }
            case 2: {
                int id = getUniqueId();
                cin.ignore();
                string name;
                cout << "Enter Employee Name: ";
                getline(cin, name);
                double hourlyWage = getValidDouble("Enter Hourly Wage: $");
                int hoursWorked = getValidInt("Enter Hours Worked: ");
                employees.push_back(new PartTimeEmployee(id, name, hourlyWage, hoursWorked));
                break;
            }
            case 3: {
                int id = getUniqueId();
                cin.ignore();
                string name;
                cout << "Enter Employee Name: ";
                getline(cin, name);
                double paymentPerProject = getValidDouble("Enter Contract Payment Per Project: $");
                int projectsCompleted = getValidInt("Enter Projects Completed: ");
                employees.push_back(new ContractualEmployee(id, name, paymentPerProject, projectsCompleted));
                break;
            }
            case 4: {
                cout << "\n------ Employee Payroll Report ------\n";
                for (const auto& emp : employees) emp->display();
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1-5.\n";
        }
    } while (choice != 5);

    for (auto emp : employees) delete emp;
    return 0;
}