#include "Flight.h"
#include <iostream>

//Реализация метода структуры 
void Flight::print()const{
	cout << "Номер рейса:" << flightNumber << ", " << " Пункт назначения: "
			<< destination << ", " << "Время отлета: " << departureTime << endl;
}
//Реализация методов класса FlightSchedule
//Конструктор класса FlightSchedule
FlightSchedule::FlightSchedule(int initCapacity) : size(0), capacity(initCapacity) {
	flights = new Flight * [capacity];
}

//Деструктор класса FlightSchedule
FlightSchedule::~FlightSchedule(){
	for (int i = 0; i < size; i++) {
		delete flights[i];//удаление каждого элемента
	}
	delete[] flights;
}

//Реализация метода resize класса FlightSchedule
void FlightSchedule::resize(int newCapacity) {

	Flight** newArray = new Flight * [newCapacity];

	for (int i = 0; i < size; i++) newArray[i] = flights[i];

	delete[] flights;
	flights = newArray;
	capacity = newCapacity;
}

//Реализация метода addFlightFront класса FlightSchedule
void FlightSchedule::addFlightFront(Flight* flight) {

	if (size == capacity) {
		resize(capacity * 2);//пример с log2(2)=1 => размер 1 итд
	}
	for (int i = size; i > 0; --i) {
		flights[i] = flights[i - 1];
	}
	flights[0] = flight;
	size++;
}

void FlightSchedule::addFlightAt(Flight* flight, int index) {
	if (index<0 || index>size) {
		cout << "Недопустимый индекс\n";
		delete flight;
		return;
	}
	if (size == capacity)resize(capacity * 2);
	for (int i = size; i < index; i--) {
		flights[i] = flights[i - 1];
	}
	flights[index] = flight; //В массив с полетами вставляем объект 
	size++;
}

//Реализация метода addFlightBack класса FlightSchedule
void FlightSchedule::addFlightBack(Flight* flight) {
	if (size == capacity) {
		resize(capacity * 2);//пример с log2(2)=1 => размер 1 итд
	}
	flights[size++] = flight;
}

//Реализация метода removeFlight класса FlightSchedule
void FlightSchedule::removeFlight(int index) {
	if (index < 0 || index >= size) {
		cout << "Неверный индекс" << endl;
		return;
	}
	delete flights[index];
	for (int i = index; i < size - 1; i++) {
		flights[i] = flights[i + 1];
	}
	size--;
}

//Реализация метода printAll класса FlightSchedule
void FlightSchedule::printAll() const {
	if (size == 0) {
		cout << "Расписание отсутствует" << endl;
		return;
	}
	for (int i = 0; i < size; ++i) {
		if (flights[i]) {
			cout << i + 1 << ". ";
			flights[i]->print();

		}
	
	}

}

void  FlightSchedule::InputAndAddFlight() {
	string number, dest, departure;
	int position;
	cout << "\nВведите номер рейса: ";cin>>number;
	cout << "\nВведите пункт назначения: ";cin>>dest;
	cout << "\nВведите время отправления: ";cin>> departure;
	cout << "Куда добавить рейс?\n"
		<< "0- начало\n"
		<< size << "- в конец\n"
		<< "Введите позицию от 0 до " << size << ": "; cin >> position;

	if (position<0 || position>size) {
		cout << "Неверная позиция, рейс будет добавлен в конец" << endl;
		addFlightBack(new Flight{ number, dest, departure });
	}
	/*else if(position==0){
		addFlightFront(new Flight{ number, dest, departure });
	}*/
	else {
		addFlightAt(new Flight{ number, dest, departure }, position);
	}
}

void FlightSchedule::saveToFile(const string& FlightSchedule) const {
	ofstream inFile(FlightSchedule, ios::binary );
	if (!inFile) {
		cout << "Не удалось открыть файл для записи: " << FlightSchedule << endl;
		return;
	}

	inFile.write(reinterpret_cast <const char*>(&size), sizeof(size));
	for (int i = 0; i < size; ++i) {
		int len;

		len = flights[i]->flightNumber.size();
		inFile.write(reinterpret_cast <const char*>(&len),sizeof(len));
		inFile.write(flights[i]->flightNumber.c_str(), len);

		len = flights[i]->destination.size();
		inFile.write(reinterpret_cast <const char*>(&len), sizeof(len));
		inFile.write(flights[i]->destination.c_str(), len);

		len = flights[i]->departureTime.size();
		inFile.write(reinterpret_cast <const char*>(&len), sizeof(len));
		inFile.write(flights[i]->departureTime.c_str(), len);
	}
	inFile.close();
	cout << "Данные записаны в файл: " << FlightSchedule << endl;
}

void FlightSchedule::loadFromFile(const string& FlightSchedule){

	ifstream outFile(FlightSchedule, ios::binary);
	if (!outFile) {
		cout << "Не удалось открыть файл для чтения: " << FlightSchedule << endl;
		return;
	}
	int count=0;
	outFile.read(reinterpret_cast <char*>(&count), sizeof(count));
	
	for (int i = 0; i < size; i++) {
		delete flights[i];
	}
	size = 0;

	for (int i = 0; i < count; i++) {
		int len;
		string num, dest, dep;
		char* buffer;

		outFile.read(reinterpret_cast <char*>(&len), sizeof(len));
		buffer = new char[len];
		outFile.read(buffer, len);
		num.assign(buffer, len);
		delete[] buffer;

		outFile.read(reinterpret_cast <char*>(&len), sizeof(len));
		buffer = new char[len];
		outFile.read(buffer, len);
		dest.assign(buffer, len);
		delete[] buffer;

		outFile.read(reinterpret_cast <char*>(&len), sizeof(len));
		buffer = new char[len];
		outFile.read(buffer, len);
		dep.assign(buffer, len);
		delete[] buffer;
	}

	outFile.close();
	cout << "Прочитано " << count << " рейса из файла." << endl;
}

	
