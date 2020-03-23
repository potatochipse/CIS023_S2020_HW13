// Module:	TimeClass.h
// Author:	Miguel Antonio Logarta
// Date:	March 20, 2020
// Purpose:	Header file for TimeClass
//			Store time, perform operations on time

#pragma once
class TimeClass
{
public:
	TimeClass(TCHAR szInput[][TCHAR_SIZE]);			// Overload constructor
	
	// Overload operators
	TCHAR* operator+(const TimeClass& rcOther);
	TCHAR* operator-(const TimeClass& rcOther);

	TCHAR szReturn[3][TCHAR_SIZE];					// Overload operator return value. It is a 2d array

private:
	int iDate[3];									// Array to hold the hours, minutes, and seconds
};

