#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "students.h"
#include "networkStudents.h"
#include "securityStudents.h"
#include "softwareStudents.h"
#include "roster.h"

int main() {
	std::cout << "SCRIPTING AND PROGRAMMING APPLICATIONS - C867" << std::endl;
	std::cout << "Written in C++ by John DeLorme, ID: #000893378\n" << std::endl;

	Roster classRoster;
	Degree degree;

	string output, col[DATA_COLUMNS];

	for (int i = 0; i < NUMBER_OF_STUDENTS; ++i)
	{
		std::istringstream input(studentData[i]);
		for (int j = 0; j < DATA_COLUMNS; ++j) {
			std::getline(input, output, ',');
			col[j] = output;
		}

		switch (col[8][2]) {
		case 'T':
			degree = NETWORK;
			break;
		case 'C':
			degree = SECURITY;
			break;
		case 'F':
			degree = SOFTWARE;
			break;
		}

		classRoster.add(col[0], col[1], col[2], col[3], std::stoi(col[4]), std::stoi(col[5]), std::stoi(col[6]), std::stoi(col[7]), degree);
	}

	std::cout << "Roster:" << std::endl;
	classRoster.printAll();
	std::cout << std::endl;

	std::cout << "Invalid emails:" << std::endl;
	classRoster.printInvalidEmails();
	std::cout << std::endl;

	std::cout << "Average days in course by student ID:" << std::endl;
	for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
		classRoster.printAverageDaysInCourse(classRoster.classRosterArray[i]->getStudentId());
	}
	std::cout << std::endl;

	std::cout << "Students in degree program SOFTWARE:" << std::endl;
	classRoster.printByDegreeProgram(SOFTWARE);
	std::cout << std::endl;

	classRoster.remove("A3");
	classRoster.remove("A3");
	std::cout << std::endl;

	std::cout << "Roster:" << std::endl;
	classRoster.printAll();
	std::cout << std::endl;

	classRoster.~Roster();

	system("PAUSE");
	return 0;
}

void Roster::add(string studentId, string firstName, string lastName, string email, int age, int daysInCourse1, int daysInCourse2, int daysInCourse3, Degree degree) {
	int daysInCourse[] = { daysInCourse1, daysInCourse2, daysInCourse3 };
	Student* student = nullptr;

	switch (degree) {
	case NETWORK:
		student = new NetworkStudent(studentId, firstName, lastName, email, age, daysInCourse, degree);
		break;
	case SECURITY:
		student = new SecurityStudent(studentId, firstName, lastName, email, age, daysInCourse, degree);
		break;
	case SOFTWARE:
		student = new SoftwareStudent(studentId, firstName, lastName, email, age, daysInCourse, degree);
		break;
	}

	for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
		if (classRosterArray[i] == nullptr) {
			classRosterArray[i] = student;
			break;
		}
	}
};

void Roster::remove(string studentId) {
	std::cout << "Removing student with ID " << studentId << "... " << std::flush;
	for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
		if (classRosterArray[i] == nullptr) {
			std::cout << "ERROR: Student with this ID not found" << std::endl;
			break;
		}
		else if (studentId == classRosterArray[i]->getStudentId()) {
			classRosterArray[i] = nullptr;
			std::cout << "Student removed" << std::endl;
		}
	}
};

void Roster::printAll() {
	for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
		if (classRosterArray[i] != nullptr) {
			classRosterArray[i]->print();
		}
	}
};

void Roster::printAverageDaysInCourse(string studentId) {
	for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
		if (studentId == classRosterArray[i]->getStudentId()) {
			int* days = classRosterArray[i]->getDaysInCourse();
			std::cout << studentId << "\t";		// Not sure how precise you want the average of days here, so I guessed
			std::cout << std::setprecision(3) << (((float)days[0] + (float)days[1] + (float)days[2]) / 3) << std::endl;
		}
	}
};

void Roster::printInvalidEmails() {
	bool valid = false;
	for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
		if (classRosterArray[i] == nullptr) {
			continue;
		}
		valid = false;
		string email = classRosterArray[i]->getEmail();
		size_t emailLength = email.size();
		size_t j = 0;
		while (email[j] != ' ' && email[j] != '@' && j < emailLength) {
			++j;
			if (email[j] == '@' && j < emailLength) {
				++j;
				while (email[j] != ' ' && email[j] != '@' && email[j] != '.' && j < emailLength) {
					++j;
					if (email[j] == '.' && j < emailLength) {
						++j;
						while (email[j] != ' ' && email[j] != '@' && email[j] != '.' && j < emailLength) {
							++j;
							if (j == emailLength) {
								valid = true;
							}
						}
					}
				}
			}
		}
		if (valid == false) {
			std::cout << email << std::endl;
		}
	}
};

void Roster::printByDegreeProgram(Degree degree) {
	for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
		Student* student = classRosterArray[i];
		if (student->getDegree() == degree) {
			student->print();
		}
	}
};

Roster::~Roster() {

};