/*
 * Name       : Umber Fatimi
 * Reg No     : L1S26BSCS0126
 * Assignment : 02 - File Handling
 * Question   : Q5 - Expense Tracker
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    int choice;

    do {
        cout << "===== Expense Tracker =====" << endl;
        cout << "1. Add an expense" << endl;
        cout << "2. Show all expenses" << endl;
        cout << "3. Show total of a category" << endl;
        cout << "4. Clear all expenses" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            char category[20];
            int amount;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!" << endl;
            }
            else {
                // ios::app keeps the old lines and adds the new one at the end
                ofstream outFile("expenses.txt", ios::app);
                outFile << category << " " << amount << endl;
                outFile.close();
                cout << "Expense saved." << endl;
            }
        }
        else if (choice == 2) {
            // open the file again so the latest data is always seen
            ifstream inFile("expenses.txt");
            char category[20];
            char largestCategory[20] = "";
            int amount;
            int count = 0, total = 0, largest = -1;

            if (inFile) {
                while (count < 100 && inFile >> category >> amount) {
                    count++;
                    cout << count << ". " << category << " " << amount << endl;
                    total += amount;
                    // strictly greater, so on a tie the first one stays
                    if (amount > largest) {
                        largest = amount;
                        strcpy(largestCategory, category);
                    }
                }
                inFile.close();
            }

            if (count == 0) {
                cout << "No expenses yet." << endl;
            }
            else {
                cout << "Total spent: " << total << endl;
                cout << "Largest expense: " << largestCategory
                     << " (" << largest << ")" << endl;
            }
        }
        else if (choice == 3) {
            char wanted[20];
            cout << "Enter category: ";
            cin >> wanted;

            ifstream inFile("expenses.txt");
            char category[20];
            int amount;
            int count = 0, total = 0;

            if (inFile) {
                while (inFile >> category >> amount) {
                    if (strcmp(category, wanted) == 0) {
                        count++;
                        total += amount;
                    }
                }
                inFile.close();
            }

            if (count == 0) {
                cout << "No expenses found for " << wanted << endl;
            }
            else {
                cout << "Expenses in " << wanted << ": " << count << endl;
                cout << "Total for " << wanted << ": " << total << endl;
            }
        }
        else if (choice == 4) {
            // a plain ofstream erases the old contents
            ofstream outFile("expenses.txt");
            outFile.close();
            cout << "All expenses cleared." << endl;
        }
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}