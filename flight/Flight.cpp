#include "Flight.h"
#include <iostream>

//���������� ������ ��������� 
void Flight::print()const{
	cout << "����� �����:" << flightNumber << ", " << " ����� ����������: "
			<< destination << ", " << "����� ������: " << departureTime << endl;
}
//���������� ������� ������ FlightSchedule
//����������� ������ FlightSchedule
FlightSchedule::FlightSchedule(int initCapacity) : size(0), capacity(initCapacity) {
	flights = new Flight * [capacity];
}

//���������� ������ FlightSchedule
FlightSchedule::~FlightSchedule(){
	for (int i = 0; i < size; i++) {
		delete flights[i];//�������� ������� ��������
	}
	delete[] flights;
}

//���������� ������ resize ������ FlightSchedule
void FlightSchedule::resize(int newCapacity) {

	Flight** newArray = new Flight * [newCapacity];

	for (int i = 0; i < size; i++) newArray[i] = flights[i];

	delete[] flights;
	flights = newArray;
	capacity = newCapacity;
}

//���������� ������ addFlightFront ������ FlightSchedule
void FlightSchedule::addFlightFront(Flight* flight) {

	if (size == capacity) {
		resize(capacity * 2);//������ � log2(2)=1 => ������ 1 ���
	}
	for (int i = size; i > 0; --i) {
		flights[i] = flights[i - 1];
	}
	flights[0] = flight;
	size++;
}

void FlightSchedule::addFlightAt(Flight* flight, int index) {
	if (index<0 || index>size) {
		cout << "������������ ������\n";
		delete flight;
		return;
	}
	if (size == capacity)resize(capacity * 2);
	for (int i = size; i < index; i--) {
		flights[i] = flights[i - 1];
	}
	flights[index] = flight; //� ������ � �������� ��������� ������ 
	size++;
}

//���������� ������ addFlightBack ������ FlightSchedule
void FlightSchedule::addFlightBack(Flight* flight) {
	if (size == capacity) {
		resize(capacity * 2);//������ � log2(2)=1 => ������ 1 ���
	}
	flights[size++] = flight;
}

//���������� ������ removeFlight ������ FlightSchedule
void FlightSchedule::removeFlight(int index) {
	if (index < 0 || index >= size) {
		cout << "�������� ������" << endl;
		return;
	}
	delete flights[index];
	for (int i = index; i < size - 1; i++) {
		flights[i] = flights[i + 1];
	}
	size--;
}

//���������� ������ printAll ������ FlightSchedule
void FlightSchedule::printAll() const {
	if (size == 0) {
		cout << "���������� �����������" << endl;
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
	cout << "\n������� ����� �����"; getline(cin, number);
	cout << "\n������� ����� ����������"; getline(cin, dest);
	cout << "\n������� ����� �����������"; getline(cin, departure);
	cout << "���� �������� ����?\n"
		<< "0- ������\n"
		<< size << "- � �����"
		<< "������� ������� �� 0 �� " << size << ": "; cin >> position;

	if (position<0 || position>size) {
		cout << "�������� �������, ���� ����� �������� � �����" << endl;
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
		cout << "�� ������� ������� ���� ��� ������: " << FlightSchedule << endl;
		return;
	}
	for (int i = 0; i < size; ++i) {
		inFile << flights[i]->flightNumber << endl;
		inFile << flights[i]->destination << endl;
		inFile << flights[i]->departureTime << endl;
	}
	inFile.close();
	cout << "������ �������� � ����: " << FlightSchedule << endl;
}

void FlightSchedule::loadFromFile(const string& FlightSchedule){

	ifstream outFile(FlightSchedule);
	if (!outFile) {
		cout << "�� ������� ������� ���� ��� ������: " << FlightSchedule << endl;
		return;
	}

	//size = 0;
	int count=0;
	string line;
	getline(outFile, line);
	try {
		count = stoi(line);//�-� �������������� ������ � int
	}
	catch (...) {
		cout << "������ ������ ���������� ������"<<endl;
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
	cout << "��������� " << count << " ����� �� �����." << endl;
}

	
