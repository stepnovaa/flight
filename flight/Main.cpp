#include <iostream>
#include "Flight.h"

using namespace std;
// Reaqlization 

int main() {
	setlocale(LC_ALL, "RU");
	FlightSchedule  Schedule;
	Schedule.addFlightFront(new Flight{ "1","москва","12:00" });
	Schedule.addFlightBack(new Flight{ "7","рязань","17:00" });
	Schedule.addFlightBack(new Flight{ "9","ростов","19:00" });
	Schedule.addFlightAt(new Flight{ "3","ярославль","14:00" }, 3);
    Schedule.saveToFile("FlightSchedule.txt");

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
        case '1': {
            Schedule.InputAndAddFlight();
            break;
        }
        case'2': {
            int index;
            cout << "Введите  индекс рейса для удаления: ";
            cin >> index;
            Schedule.removeFlight(index-1);
            break;
        }
        case '3': {
            Schedule.printAll();
            break;
        }
        case '4': {
            Schedule.saveToFile("FlightSchedule.txt");
            break;
        }
        case '5': {
            Schedule.loadFromFile("FlightSchedule.txt");
            break;
        }
        case'0': {
            cout << "Выход из программы:\n";
            break;
        }
        default: {
            cout << "Неверный выбор!!!\n";
        }
        }
    } while (choice != '0');
}