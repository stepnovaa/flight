#include <iostream>
#include<string>

using namespace std;

struct Flight {
	string flightNumber;
	string destination;
	string departureTime;
	void print() const {
		cout << "����� �����:" << flightNumber << ", " << "����� ����������"
			<< destination << ", " << "����� ������: " << departureTime << endl;
	}
};

class FlightSchedule {
private:
	Flight** flights;//������ ����������
	int size;
	int capacity;

	void resize(int newCapacity) {
		Flight** newArray = new Flight*[newCapacity];

		for (int i = 0; i < size;i++) newArray[i] = flights[i];

		delete[] flights;
		flights = newArray;
		capacity = newCapacity;
	}
public:
	FlightSchedule(int initCapacity = 3): size(0), capacity(initCapacity) {
		flights = new Flight * [capacity];
	}
	~FlightSchedule() {
		for (int i = 0; i < size; i++) {
			delete flights[i];//�������� ������� ��������
		}
		delete[] flights;
	}

	void addFlightFront(Flight* flight) {

		if (size == capacity) {
			resize(capacity * 2);//������ � log2(2)=1 => ������ 1 ���
		}
		for (int i = size; i > 0; --i) {
			flights[i] = flights[i - 1];
		}
		flights[0] = flight;
		size++;
	}

	void addFlightBack(Flight* flight) {
		if (size == capacity) {
			resize(capacity * 2);//������ � log2(2)=1 => ������ 1 ���
		}
		flights[size++] = flight;
	}

	void removeFlight(int index) {
		if (index < 0 || index>=size) {
			cout << "�������� ������" << endl;
			return;
		}
		delete flights[index];
		for (int i = index; i < size-1; i++) {
			flights[i] = flights[i - 1];
		}
		size--;
	}

	void printAll () const {
		if (size == 0) {
			cout << "���������� �����������" << endl;
			return;
		}
		for (int i = 0; i < size; i++) {
			flights[i]->print();
		}

	}
};