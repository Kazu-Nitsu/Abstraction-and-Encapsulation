#include <iostream>
#include <vector>
#include <limits>
#include <set>
#include <cctype>
using namespace std;

class Employee {
protected:
    string id;
    string name;
public:
    Employee(string id, string name) : id(id), name(name) {}
    virtual double calculateSalary() const = 0;
    virtual void display() const = 0;
    string getId() const { return id; }
    virtual ~Employee() {}
};

class FullTimeEmployee : public Employee {
private:
    double salary;
public:
    FullTimeEmployee(string id, string name, double salary)
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
    PartTimeEmployee(string id, string name, double hourlyWage, int hoursWorked)
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
    ContractualEmployee(string id, string name, double paymentPerProject, int projectsCompleted)
        : Employee(id, name), paymentPerProject(paymentPerProject), projectsCompleted(projectsCompleted) {}

    double calculateSalary() const override { return paymentPerProject * projectsCompleted; }

    void display() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n"
             << "Contract Payment Per Project: $" << paymentPerProject << "\n"
             << "Projects Completed: " << projectsCompleted << "\n"
             << "Total Salary: $" << calculateSalary() << "\n\n";
    }
};

set<string> existingIds;

string getUniqueId() {
    string id;
    while (true) {
        cout << "Enter Employee ID: ";
        cin >> id;
        
        bool isValid = !id.empty();
        for (char c : id) {
            if (!isalnum(c)) {
                isValid = false;
                break;
            }
        }

        if (!isValid) {
            cout << "Invalid input! Please enter an Number or Letter\n";
            continue;
        }
        
        if (existingIds.find(id) == existingIds.end()) {
            existingIds.insert(id);
            return id;
        }
        cout << "Duplicate ID! Please enter a unique ID.\n";
    }
}

double getValidDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (!(cin >> value) || value <= 0 || cin.peek() != '\n') {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        return value;
    }
}

int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value) || value <= 0 || cin.peek() != '\n') {
            cout << "Invalid input! Please enter a numbern";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        return value;
    }
}

int main() {
    vector<Employee*> employees;
    int choice;

    do {
        choice = getValidInt("\n----- Menu -----\n1 - Full-time Employee\n2 - Part-time Employee\n3 - Contractual Employee\n4 - Display Payroll Report\n5 - Exit\nEnter choice: ");

        switch (choice) {
            case 1: {
                string id = getUniqueId();
                cin.ignore();
                string name;
                cout << "Enter Employee Name: ";
                getline(cin, name);
                double salary = getValidDouble("Enter Fixed Monthly Salary: $");
                employees.push_back(new FullTimeEmployee(id, name, salary));
                break;
            }
            case 2: {
                string id = getUniqueId();
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
                string id = getUniqueId();
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

