#include <iostream>
#include "Flight.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	FlightSchedule  Schedule;
	/*Schedule.addFlightFront(new Flight{ "1","������","12:00" });
	Schedule.addFlightBack(new Flight{ "7","������","17:00" });
	Schedule.addFlightBack(new Flight{ "9","������","19:00" });
	Schedule.addFlightAt(new Flight{ "3","���������","14:00" }, 3);
    Schedule.saveToFile("FlightSchedule.txt");*/

    Schedule.loadFromFile("FlightSchedule.txt");
    Schedule.printAll();
   

    char choice;
    do {
        cout << "\n����:\n";
        cout << "1. �������� ����\n";
        cout << "2. ������� ����\n";
        cout << "3. �������� ����������\n";
        cout << "4. ��������� � ����\n";
        cout << "5. ��������� �� �����\n";
        cout << "0. �����\n";
        cout << "��� �����: ";
        cin >> choice;

        switch (choice) {
        case '1': {}

        }
    } while (choice != '0');
}