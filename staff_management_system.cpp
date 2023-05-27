#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class StaffManagement {
private:
    int employeeID;
    string name;
    string position;
    const string filename = "stafff.txt";

public:
     void menu();
    // we will use the function to display the menu
    void addEmployee();
    // we will use the function to add a new employee
    void editEmployee();
    // we will use the function to edit an existing employee
    void removeEmployee();
     // function to remove an employee
    void listEmployees();
    // function to list all employees

};

void StaffManagement::menu() {
    int choice;
    while (true) {
        cout << "\t\t\t\t\t****************************** " << endl;
        cout << "\t\t\t\t\t*                            * " << endl;
        cout << "\t\t\t\t\t*   Staff Management System  * " << endl;
        cout << "\t\t\t\t\t****************************** " << endl;
        cout << "\t\t\t 1. Add Employee" << endl;
        cout << "\t\t\t 2. Edit Employee" << endl;
        cout << "\t\t\t 3. Remove Employee" << endl;
        cout << "\t\t\t 4. List Employees" << endl;
        cout << "\t\t\t 5. Exit" << endl;
        cout << "\t\t\t\n";
        cout << "\t\t\t Please select an option: ";
        cin >> choice;

        // Perform the operations based on the user's choice
        switch (choice) {
            case 1:
                addEmployee();
                break;

            case 2:
                editEmployee();
                break;

            case 3:
                removeEmployee();
                break;

            case 4:
                listEmployees();
                break;

            case 5:
                exit(0);

            default:
                cout << "Please select from the given options" << endl;
        }
    }
}


void StaffManagement::addEmployee() {
    fstream file;
    file.open(filename, ios::app | ios::out); // we will open the file in append mode

    cout << "\n\n\t\t___ Add New Employee ___" << endl;
    cout << "Employee ID: ";
    cin >> employeeID;
    cout << "Name: ";
    cin.ignore(); // Ignore the newline character in the input buffer
    getline(cin, name);
    cout << "Position: ";
    getline(cin, position);

    file << employeeID << " " << name << " " << position << endl; // by this line we the employee data will be written to the file
    file.close();

    cout << "Employee added successfully!" << endl;
}

void StaffManagement::editEmployee() {
    fstream file;
    fstream tempFile;
    int employeeIDToUpdate;
    bool found = false;

    file.open(filename, ios::in);
    tempFile.open("tempp.txt", ios::out); // Create a temporary file for writing updated data

    cout << "\n\n\t\t___ Edit Employee ___" << endl;

    cout << "Enter the Employee ID to edit: ";

    cin >> employeeIDToUpdate;

    while (file >> employeeID >> name >> position) {
        if (employeeID == employeeIDToUpdate) {
            found = true;
            cout << "New Name: ";
            cin.ignore(); // Ignore the newline character in the input buffer
            getline(cin, name);
            cout << "New Position: ";
            getline(cin, position);
        }

        tempFile << employeeID << " " << name << " " << position << endl; // Write data to the temporary file
    }

    file.close();
    tempFile.close();

    if (!found) {
        cout << "Employee not found!" << endl;
        remove("tempp.txt"); // now we will remove the temporary file
        return;
    }

    remove(filename.c_str()); // now we will remove the original file
    rename("tempp.txt", filename.c_str()); // Rename the temporary file to the original file

    cout << "Employee details updated successfully!" << endl;
}

void StaffManagement::removeEmployee() {
    fstream file;
    fstream tempFile;
    int employeeIDToRemove;
    bool found = false;

    file.open(filename, ios::in);
    tempFile.open("tempp.txt", ios::out); // Create a temporary file for writing remaining data

    cout << "\n\n\t\t___ Remove Employee ___" << endl;
    cout << "Enter the Employee ID to remove: ";
    cin >> employeeIDToRemove;

    while (file >> employeeID >> name >> position) {
        if (employeeID != employeeIDToRemove) {
            tempFile << employeeID << " " << name << " " << position << endl; // now we will write data to the temporary file
        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    if (!found) {
        cout << "Employee not found!" << endl;
        remove("tempp.txt"); // Remove the temporary file
        return;
    }

    remove(filename.c_str()); // Remove the original file
    rename("tempp.txt", filename.c_str()); // Rename the temporary file to the original file

    cout << "Employee removed successfully!" << endl;
}

void StaffManagement::listEmployees() {
    ifstream file(filename);
    if (!file) {
        cout << "No employee records found!" << endl;
        return;
    }

    cout << "\n__________________" << endl;
    cout << "Employee ID\tName\t\t\tPosition" << endl;
    cout << "__________________" << endl;

    while (file >> employeeID >> name >> position) {
        cout << employeeID << "\t\t" << name << "\t\t" << position << endl; // Display employee data
    }

    file.close();
}

int main() {
    StaffManagement sm;
    sm.menu(); // now start the staff management system by calling the menu function
    return 0;
}

