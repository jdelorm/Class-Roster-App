#pragma once
#include "degree.h"
#include "students.h"

class NetworkStudent : public Student
{
protected:
	Degree degree = NETWORK;
public:
	using Student::Student;
	Degree getDegree() override;
};