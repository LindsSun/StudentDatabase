#pragma once
#include <string>
#include "degree.h"
using std::string;

const string studentData[] =
{
	"A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY",
	"A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,NETWORK",
	"A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE",
	"A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY",
	"A5,Lindsey,Sunga,lsunga@wgu.edu,27,21,43,34,SOFTWARE"
};

static const unsigned int numStudents = sizeof(studentData) / sizeof(studentData[0]);
static const unsigned int dataColumns = 9;

class Roster
{
public:
	Student* classRosterArray[numStudents] = { nullptr, nullptr, nullptr, nullptr, nullptr };

	void add(
		string studentId,
		string firstName,
		string lastName,
		string email,
		int age,
		int numDays1,
		int numDays2,
		int numDays3,
		Degree degree
	);
	void remove(string studentId);
	void printAll();
	void printDaysInCourseAve(string studentId);
	void printInvalidEmails();
	void printDegProgram(Degree degree);

	~Roster();
};