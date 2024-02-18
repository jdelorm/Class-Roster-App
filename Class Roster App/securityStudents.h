#pragma once
#include "degree.h"
#include "students.h"

class SecurityStudent : public Student
{
protected:
	Degree degree = SECURITY;
public:
	using Student::Student;
	Degree getDegree() override;
};