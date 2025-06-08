#include <iostream>
using namespace std;

class Cyrux {
public:
    int day, month, year;

    Cyrux(int d = 1, int m = 1, int y = 1900) : day(d), month(m), year(y) {}

    void input() {
        // Validate day (1-31)
        do {
            cout << "Enter day (1-31): ";
            cin >> day;
            if (day < 1 || day > 31) {
                cout << "Invalid day! Please enter a valid 2-digit day.\n";
            }
        } while (day < 1 || day > 31);

        // Validate month (1-12)
        do {
            cout << "Enter month (1-12): ";
            cin >> month;
            if (month < 1 || month > 12) {
                cout << "Invalid month! Please enter a valid 2-digit month.\n";
            }
        } while (month < 1 || month > 12);

        // Validate year (1000-9999)
        do {
            cout << "Enter year (4 digits): ";
            cin >> year;
            if (year < 1000 || year > 9999) {
                cout << "Invalid year! Please enter a valid 4-digit year.\n";
            }
        } while (year < 1000 || year > 9999);
    }
};

class Virus {
private:
    Cyrux birth;
    Cyrux current;

public:
    void setBirthDate() {
        cout << "Enter your date of birth:\n";
        birth.input();
    }

    void setCurrentDate() {
        cout << "\nEnter the current date:\n";
        current.input();
    }

    int calculateAge() {
        int age = (current.year - birth.year);

        // Adjust age if current date is before birthday in the current year
        if ((current.month < birth.month) || 
            (current.month == birth.month && current.day < birth.day)) {
            age--;
        }

        return age;
    }
};

int main() {
    Virus virus;

    virus.setBirthDate();
    virus.setCurrentDate();

    int age = virus.calculateAge();

    cout << "\nYour age is: " << age << " years.\n" << endl;

    return 0;
}