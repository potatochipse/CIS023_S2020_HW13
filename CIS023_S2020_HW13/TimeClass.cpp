// Module:	TimeClass.h
// Author:	Miguel Antonio Logarta
// Date:	March 20, 2020
// Purpose:	Implementation file for Timeclass
//			Store time, perform operations on time

#include "CIS023_S2020_HW13.h"

TimeClass::TimeClass(TCHAR szInput[][TCHAR_SIZE])
{
	// Convert input to ints
	for (int i = 0; i < 3; i++)
	{
		iDate[i] = TCHARtoInt(szInput[i]);
	}

	// Correct any errors the user has made. Blank inputs are automatically 0
	if (iDate[0] > 12 || iDate[0] == 0)			// Set any hour greater than 12 to 12
		iDate[0] = 12;
	if (iDate[1] > 59)							// Any minute greater than 59 set to 0
		iDate[1] = 0;
	if (iDate[2] > 59)							// Any second greater than 59 set to 0
		iDate[2] = 0;

	int iInput{ 0 };

}

TCHAR* TimeClass::operator+(const TimeClass& rcOther)
{
	int iSum{ 0 };
	int iCarryOver{ 0 };

	// Add the seconds
	iSum = iDate[2] + rcOther.iDate[2];

	// Carry over
	if (iSum > 59)					// If the total seconds are above 60
	{
		iSum = iSum % 60;
		iCarryOver = 1;
	}

	InttoTCHAR(iSum, szReturn[2]);	// Put the result in the array

	// Add the minutes
	iSum = iDate[1] + rcOther.iDate[1] + iCarryOver;
	iCarryOver = 0;
	if (iSum > 59)
	{
		iSum = iSum % 60;
		iCarryOver = 1;
	}

	InttoTCHAR(iSum, szReturn[1]);

	// Add the hours
	iSum = iDate[0] + rcOther.iDate[0] + iCarryOver;
	iCarryOver = 0;
	if (iSum > 11)
	{
		iSum = iSum % 12;
	}

	InttoTCHAR(iSum, szReturn[0]);

	return *szReturn;
}

TCHAR* TimeClass::operator-(const TimeClass& rcOther)
{
	int iDifference{ 0 };
	int iBorrow{ 0 };

	// Subtract the seconds
	iDifference = iDate[2] - rcOther.iDate[2];

	// Borrow if the difference is negative
	if (iDifference < 0)
	{
		iDifference = 60 + iDifference;
		iBorrow = -1;
	}

	InttoTCHAR(iDifference, szReturn[2]);

	// Subtract the minutes
	iDifference = iDate[1] - rcOther.iDate[1] + iBorrow;
	iBorrow = 0;				// Reset borrow

	// Borrow if the difference is negative
	if (iDifference < 0)
	{
		iDifference = 60 + iDifference;
		iBorrow = -1;
	}

	InttoTCHAR(iDifference, szReturn[1]);

	// Subtract the hours
	iDifference = iDate[0] - rcOther.iDate[0] + iBorrow;
	
	// Reset hours to 12 if negative
	if (iDifference < 0)
	{
		iDifference = 12 + iDifference;
	}

	InttoTCHAR(iDifference, szReturn[0]);

	return *szReturn;
}

