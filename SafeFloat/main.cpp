// SafeFloat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "safe_float.h"
#include "unittest.h"

void DivideByZero()
{
	SafeFloat<float> num = 1000.f;
	SafeFloat<float> div = 0.0f;

	CHECK_EXP_THROW(SafeFloat<float> res = num / div, std::runtime_error);
}

void Inexact()
{
	SafeFloat<float> num = 0.1f;
	SafeFloat<float> div = 10.0f;

	CHECK_EXP_THROW(SafeFloat<float> res = num / div, std::runtime_error);
}

int main()
{
	UnitTest::Add("FloatExceptionTest", "DivideByZero", DivideByZero);
	UnitTest::Add("FloatExceptionTest", "Inexact", Inexact);

	// RunAllTests() return number of errors
	return UnitTest::RunAllTests();
}

/*
int main()
{
	SafeFloat<float>::SetExceptionToCheck(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW);
    SafeFloat<float> num = 1000.f;
	SafeFloat<float> div = 0.0f;

    try
    {
		SafeFloat<float> res = num / div;
    }
    catch (const std::runtime_error& e)
    {
		std::cout << "Runtime exception: " << e.what() <<"\n";
    }
    catch (const std::exception& e)
    {
		std::cout << "Std exception: " << e.what() << "\n";
    }

	num = 0.1f;
	div = 10.0f;

	try
	{
		SafeFloat<float> res = num / div;
	}
	catch (const std::runtime_error& e)
	{
		std::cout << "Runtime exception: " << e.what() << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "Std exception: " << e.what() << "\n";
	}

    std::cout << "Done!\n";
}
*/