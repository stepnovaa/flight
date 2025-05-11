#pragma once
#include <iostream>
#include<string>
#include<fstream>
using namespace std;

//Структура рейса 
struct Flight {
	string flightNumber;//Номер рейса 
	string destination;//Пункт назначения 
	string departureTime;//Время отправление 
	void print() const;
};

class FlightSchedule {
private:
	Flight** flights;//Массив указателей полетов
	int size;//Размер массива указателей полётов 
	int capacity;//Вместимость массива указателей полётов
	void resize(int newCapacity);//ф-я обновляет массив указателей полётов
public:
	FlightSchedule(int initCapacity = 3);
	~FlightSchedule();

	void addFlightFront(Flight* flight);

	void addFlightAt(Flight* flight, int index);

	void addFlightBack(Flight* flight);

	void removeFlight(int index);

	void printAll() const;
	
	void getScheduleInput();

	void saveToFile(const string &FlightSchedule);

	void loadFromFile(const string& FlightSchedule);

	
	
};