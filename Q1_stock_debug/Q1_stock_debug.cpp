/*
 * Name       : Umber Fatimi
 * Reg No     : L1S26BSCS0126
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

#include <iostream>
// FIX 1: <fstream> was missing
#include <fstream>
using namespace std;

int main()
{
    ifstream inFile("stock.txt");
    // FIX 2: the Check step tested the wrong condition it should be !inFile
    if (!inFile)
    {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: ios::app to keep old data
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;
    // FIX 4: total was an int,it must be a double to hold values like 7507.47
    double total = 0;

    // FIX 5: ignore the first header line before the loop
    inFile.ignore(1000, '\n');

    while (count < 50 && inFile >> code >> qty >> price)
    {
        count++;
        total = total + qty * price;
        if (qty < 10)
        {
            // FIX 6: endl was missing
            reorder << code << " " << qty << endl;
            low++;
        }
    }
    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}