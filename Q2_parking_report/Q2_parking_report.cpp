/*
 * Name       : Umber Fatimi
 * Reg No     : L1S26BSCS0126
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    ifstream inFile("parking.txt");
    if (!inFile)
    {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;
    inFile >> d >> slash >> m >> slash >> y;
    inFile.ignore(100, '\n'); // rest of line 1
    inFile.ignore(100, '\n'); // header line

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;

    ofstream receipts("receipts.txt");
    receipts << "Receipts for " << d << "/" << m << "/" << y << endl;

    char plate[15], type;
    int h1, m1, h2, m2;
    char colon;

    int count = 0, cars = 0, bikes = 0, total = 0;
    int longestMin = -1;
    char longestPlate[15] = "";

    while (count < 30 &&
           inFile >> plate >> type >> h1 >> colon >> m1 >> h2 >> colon >> m2)
    {
        int minutes = (h2 * 60 + m2) - (h1 * 60 + m1);

        int hoursCharged = (minutes + 59) / 60;
        if (hoursCharged == 0)
        {
            hoursCharged = 1;
        }

        int fee;
        const char *name;
        if (type == 'C')
        {
            fee = hoursCharged * 100;
            name = "Car";
            cars++;
        }
        else
        {
            fee = hoursCharged * 40;
            name = "Bike";
            bikes++;
        }

        cout << plate << " " << name << " "
             << minutes / 60 << " h " << minutes % 60 << " min Fee: "
             << fee << endl;
        receipts << plate << " " << fee << endl;

        total += fee;
        count++;

        if (minutes > longestMin)
        {
            longestMin = minutes;
            strcpy(longestPlate, plate);
        }
    }
    inFile.close();
    receipts.close();

    if (count == 0)
    {
        cout << "No vehicles found!" << endl;
        return 0;
    }

    cout << "Vehicles: " << count << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << total << endl;
    cout << "Longest stay: " << longestPlate << " ("
         << longestMin / 60 << " h " << longestMin % 60 << " min)" << endl;
    return 0;
}