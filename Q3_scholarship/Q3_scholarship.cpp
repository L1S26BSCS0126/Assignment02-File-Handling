/*
 * Name       : Umber Fatimi
 * Reg No     : L1S26BSCS0126
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship List
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);
    if (!inFile.is_open())
    {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n;
    inFile >> n;
    inFile.ignore(100, '\n');

    if (n > 30)
    {
        cout << "Too many students!" << endl;
        inFile.close();
        return 0;
    }

    ofstream scholarship("scholarship.txt");

    char name[30];
    double cgpa;
    int count = 0, eligible = 0;
    double sum = 0;
    double topCgpa = -1;
    char topName[30] = "";

    for (int i = 0; i < n; i++)
    {
        if (!inFile.getline(name, 30, ','))
        {
            break;
        }
        if (!(inFile >> cgpa))
        {
            break;
        }
        inFile.ignore(100, '\n');

        cout << "[" << name << "] CGPA: " << cgpa << endl;

        if (cgpa >= 3.50)
        {
            scholarship << name << "," << cgpa << endl;
            eligible++;
        }

        sum += cgpa;
        count++;

        if (cgpa > topCgpa)
        {
            topCgpa = cgpa;
            strcpy(topName, name);
        }
    }
    inFile.close();
    scholarship.close();

    if (count < n)
    {
        cout << "Warning: only " << count << " of " << n
             << " records found." << endl;
    }

    if (count == 0)
    {
        cout << "No students found!" << endl;
        return 0;
    }

    cout << "Students: " << count << endl;
    cout << "Average CGPA: " << sum / count << endl;
    cout << "Eligible for scholarship: " << eligible << endl;
    cout << "Top student: " << topName << " (" << topCgpa << ")" << endl;
    return 0;
}