#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

class ItemTracker {
private:
    map<string, int> itemFrequency;

public:
    void LoadData(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string item;
        while (file >> item) {
            itemFrequency[item]++;
        }

        file.close();
    }

    int GetItemFrequency(const string& item) {
        if (itemFrequency.find(item) != itemFrequency.end()) {
            return itemFrequency[item];
        }
        return 0; // Return 0 if the item is not found
    }

    void PrintAllFrequencies() {
        cout << "Item Frequencies:" << endl;
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    void PrintHistogram() {
        cout << "Item Histogram:" << endl;
        for (const auto& pair : itemFrequency) {
            cout << setw(15) << left << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    void SaveDataToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (const auto& pair : itemFrequency) {
            file << pair.first << " " << pair.second << endl;
        }

        file.close();
    }
};

void DisplayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Look up item frequency" << endl;
    cout << "2. Display all item frequencies" << endl;
    cout << "3. Display histogram of item frequencies" << endl;
    cout << "4. Exit" << endl;
}

int main() {
    ItemTracker tracker;
    tracker.LoadData("CS210_Project_Three_Input_File.txt");
    tracker.SaveDataToFile("frequency.dat");

    int choice;
    do {
        DisplayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string item;
                cout << "Enter the item to look for: ";
                cin >> item;
                int frequency = tracker.GetItemFrequency(item);
                cout << "Frequency of " << item << ": " << frequency << endl;
                break;
            }
            case 2:
                tracker.PrintAllFrequencies();
                break;
            case 3:
                tracker.PrintHistogram();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
