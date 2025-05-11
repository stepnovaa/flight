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

void  FlightSchedule::getScheduleInput() {
	string number, dest, departure;
	int position;
	cout << "\nВведите номер рейса"; getline(cin, number);
	cout << "\nВведите пункт назначения"; getline(cin, dest);
	cout << "\nВведите время отправления"; getline(cin, departure);
	cout << "Куда добавить рейс?\n"
		<< "0- начало\n"
		<< size << "- в конец"
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

void FlightSchedule::saveToFile(const string& FlightSchedule) {
	ofstream inFile(FlightSchedule);
	if (!inFile) {
		cout << "Не удалось открыть файл для записи: " << FlightSchedule << endl;
		return;
	}
	for (int i = 0; i < size; ++i) {
		inFile << flights[i]->flightNumber << endl;
		inFile << flights[i]->destination << endl;
		inFile << flights[i]->departureTime << endl;
	}
	inFile.close();
	cout << "Данные записаны в файл: " << FlightSchedule << endl;
}

void FlightSchedule::loadFromFile(const string& FlightSchedule){

	ifstream outFile(FlightSchedule);
	if (!outFile) {
		cout << "Не удалось открыть файл для чтения: " << FlightSchedule << endl;
		return;
	}

	//size = 0;
	int count=0;
	string line;
	getline(outFile, line);
	try {
		count = stoi(line);//ф-я преобразования строки в int
	}
	catch (...) {
		cout << "Ошибка чтения количества рейсов"<<endl;
		return;
	}
	

	for (int i = 0; i < size; i++) {
		delete flights[i];
	}
	size = 0;
	string number, dest, departure;
	while (getline(outFile, number) && getline(outFile, dest) && getline(outFile, departure)) {
		addFlightBack(new Flight{ number, dest, departure });
	}
	//for(int i=0;i<count;i++) {
	//	getline(outFile,number);
	//	getline(outFile,dest);
	//	getline(outFile,departure);
	//	addFlightBack(new Flight{number, dest, departure});
	//}
	outFile.close();
	cout << "Прочитано " << count << " рейса из файла." << endl;
}

	
