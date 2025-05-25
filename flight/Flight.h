#pragma once
#include <iostream>
#include<string>
#include<fstream>
#include <vector>
using namespace std;

//��������� ����� 
struct Flight {
	string flightNumber;//����� ����� 
	string destination;//����� ���������� 
	string departureTime;//����� ����������� 
	void print() const;
};

class FlightSchedule {
private:
	Flight** flights;//������ ���������� �������
	int size;//������ ������� ���������� ������ 
	int capacity;//����������� ������� ���������� ������
	void resize(int newCapacity);//�-� ��������� ������ ���������� ������
public:
	FlightSchedule(int initCapacity = 3);
	~FlightSchedule();

	void addFlightFront(Flight* flight);

	void addFlightAt(Flight* flight, int index);

	void addFlightBack(Flight* flight);

	void removeFlight(int index);

	void printAll() const;
	
	void InputAndAddFlight();

	void saveToFile (const string &FlightSchedule) const;

	void loadFromFile(const string& FlightSchedule);

	
	
};