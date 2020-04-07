#pragma once
#include "degree.h"
#include "student.h"

class softwareStudent : public Student{

public:

	using Student::Student;
	Degree getDegree() override;

protected:

	Degree degree = SOFTWARE;

};