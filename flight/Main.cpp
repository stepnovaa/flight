#include <iostream>
#include "Flight.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	FlightSchedule  Schedule;
	/*Schedule.addFlightFront(new Flight{ "1","Москва","12:00" });
	Schedule.addFlightBack(new Flight{ "7","Рязань","17:00" });
	Schedule.addFlightBack(new Flight{ "9","Ростов","19:00" });
	Schedule.addFlightAt(new Flight{ "3","Ярославль","14:00" }, 3);
    Schedule.saveToFile("FlightSchedule.txt");*/

    Schedule.loadFromFile("FlightSchedule.txt");
    Schedule.printAll();
   

    char choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить рейс\n";
        cout << "2. Удалить рейс\n";
        cout << "3. Показать расписание\n";
        cout << "4. Сохранить в файл\n";
        cout << "5. Загрузить из файла\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case '1': {}

        }
    } while (choice != '0');
}