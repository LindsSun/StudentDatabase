#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "student.h"
#include "networkStudent.h"
#include "securityStudent.h"
#include "softwareStudent.h"
#include "roster.h"

int main()
{
	std::cout << "C867 *** SCRIPTING AND PROGAMMING APPLICATIONS *** BY LINDSEY SUNGA" << std::endl;

	Degree degree;
	Roster courseRoster;

	string output, col[dataColumns];

	for (int i = 0; i < numStudents; ++i){

		std::istringstream input(studentData[i]);
		
		for (int j = 0; j < dataColumns; ++j) {
			std::getline(input, output, ',');
			col[j] = output;
		}
		
		if (col[8][2] == 'T') {
			degree = NETWORK;
		}
		else if (col[8][2] == 'C') {
			degree = SECURITY;
		}
		else if (col[8][2] == 'F') {
			degree = SOFTWARE;
		}

		courseRoster.add(col[0], col[1], col[2], col[3], std::stoi(col[4]), std::stoi(col[5]), std::stoi(col[6]), std::stoi(col[7]), degree);
	}

	std::cout << "ROSTER:" << std::endl;
	courseRoster.printAll();

	std::cout << "INVALID EMAILS:" << std::endl;
	courseRoster.printInvalidEmails();


	std::cout << "AVERAGE DAYS IN COURSE:" << std::endl;
	for (int i = 0; i < numStudents; ++i) {
		courseRoster.printDaysInCourseAve(courseRoster.classRosterArray[i]->getStudentId());
	}


	std::cout << "STUDENTS IN SOFTWARE PROGRAM:" << std::endl;
	courseRoster.printDegProgram(SOFTWARE);

	courseRoster.remove("A3");
	courseRoster.remove("A3");
	std::cout << std::endl;

	std::cout << "Roster:" << std::endl;
	courseRoster.printAll();
	std::cout << std::endl;

	courseRoster.~Roster();

	system("pause");
	return 0;
}

void Roster::add(string studentId, string firstName, string lastName, string email, int age, int daysInCourse1, int daysInCourse2, int daysInCourse3, Degree degree) {
	int daysInCourse[] = { daysInCourse1, daysInCourse2, daysInCourse3 };
	
	Student* student = nullptr;

	if (degree == NETWORK) {
		student = new NetworkStudent(studentId, firstName, lastName, email, age, daysInCourse, degree);
	}
	else if (degree == SECURITY) {
		student = new SecurityStudent(studentId, firstName, lastName, email, age, daysInCourse, degree);
	}
	else if (degree == SOFTWARE) {
		student = new softwareStudent(studentId, firstName, lastName, email, age, daysInCourse, degree);
	}


	for (int i = 0; i < numStudents; ++i) {
		if (classRosterArray[i] == nullptr) {
			classRosterArray[i] = student;
			break;
		}
	}
};

void Roster::remove(string studentId) 
{
	for (int i = 0; i < numStudents; ++i) {
		if (classRosterArray[i] == nullptr) {
			std::cout << "INVALID: Student with ID not found" << std::endl;
			break;
		}
		else if (studentId == classRosterArray[i]->getStudentId()) {
			classRosterArray[i] = nullptr;
			std::cout << "Student removed" << std::endl;
		}
	}
};

void Roster::printAll() 
{
	for (int i = 0; i < numStudents; ++i) 
	{
		if (classRosterArray[i] != nullptr) 
{
			classRosterArray[i]->print();
		}
	}
};

void Roster::printDaysInCourseAve(string studentId) 
{
	for (int i = 0; i < numStudents; ++i) {
		if (studentId == classRosterArray[i]->getStudentId()) {
			int* days = classRosterArray[i]->getDaysInCourse();
			std::cout << studentId << "\t";		
			std::cout << std::setprecision(3) << (((float)days[0] + (float)days[1] + (float)days[2]) / 3) << std::endl;
		}
	}
};

void Roster::printInvalidEmails() 
{
	bool valid = false;
	for (int i = 0; i < numStudents; ++i) {
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

void Roster::printDegProgram(Degree degree) {
	for (int i = 0; i < numStudents; ++i) {
		Student* student = classRosterArray[i];
		if (student->getDegree() == degree) {
			student->print();
		}
	}
};


Roster::~Roster() {

};