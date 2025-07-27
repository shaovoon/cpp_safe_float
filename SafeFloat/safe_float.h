// The MIT License (MIT)
// C++ Safe Float 0.1.0
// Copyright (C) 2025, by Wong Shao Voon (shaovoon@yahoo.com)
//
// http://opensource.org/licenses/MIT

#pragma once
#include <cfenv>
#include <stdexcept>

template<typename T>
class SafeFloat
{
public:
	SafeFloat(const T& data) : Data(data) {}
	SafeFloat(const int& data) : Data((T)data) {}

	SafeFloat& operator=(const SafeFloat& other)
	{
		Data = other.Data;
		return *this;
	}

	SafeFloat& operator+=(const SafeFloat& other)
	{
		const T a = Data;
		const T b = other.Data;
		std::feclearexcept(FE_ALL_EXCEPT);
		Data += other.Data;
		CheckExceptionThrown(a, "+=", b, Data);
		return *this;
	}

	SafeFloat& operator-=(const SafeFloat& other)
	{
		const T a = Data;
		const T b = other.Data;
		std::feclearexcept(FE_ALL_EXCEPT);
		Data -= other.Data;
		CheckExceptionThrown(a, "-=", b, Data);
		return *this;
	}

	SafeFloat& operator*=(const SafeFloat& other)
	{
		const T a = Data;
		const T b = other.Data;
		std::feclearexcept(FE_ALL_EXCEPT);
		Data *= other.Data;
		CheckExceptionThrown(a, "*=", b, Data);
		return *this;
	}

	SafeFloat& operator/=(const SafeFloat& other)
	{
		const T a = Data;
		const T b = other.Data;
		std::feclearexcept(FE_ALL_EXCEPT);
		Data /= other.Data;
		CheckExceptionThrown(a, "/=", b, Data);
		return *this;
	}

	SafeFloat& operator+(const SafeFloat& other)
	{
		const T a = Data;
		const T b = other.Data;

		std::feclearexcept(FE_ALL_EXCEPT);
		SafeFloat temp(Data + other.Data);
		CheckExceptionThrown(a, "+", b, temp.Data);
		return temp;
	}

	SafeFloat& operator-(const SafeFloat& other)
	{
		const T a = Data;
		const T b = other.Data;

		std::feclearexcept(FE_ALL_EXCEPT);
		SafeFloat temp(Data - other.Data);
		CheckExceptionThrown(a, "-", b, temp.Data);
		return temp;
	}

	SafeFloat& operator*(const SafeFloat& other)
	{
		const T a = Data;
		const T b = other.Data;

		std::feclearexcept(FE_ALL_EXCEPT);
		SafeFloat temp(Data * other.Data);
		CheckExceptionThrown(a, "*", b, temp.Data);
		return temp;
	}

	SafeFloat operator/(const SafeFloat& other)
	{
		const T a = Data;
		const T b = other.Data;

		std::feclearexcept(FE_ALL_EXCEPT);
		SafeFloat temp(Data / other.Data);
		CheckExceptionThrown(a, "/", b, temp.Data);
		return temp;
	}

	static void CheckExceptionThrown()
	{
		int res = std::fetestexcept(ExceptionToCheck);

		if (res != 0)
			std::feclearexcept(res);
		else
			return;

		const char* except = nullptr;

		if (res == FE_DIVBYZERO)
			except = "Divide by zero";
		if (res == FE_INEXACT)
			except = "Inexact result";
		if (res == FE_INVALID)
			except = "Invalid result";
		if (res == FE_OVERFLOW)
			except = "Overflow";
		if (res == FE_UNDERFLOW)
			except = "Underflow";

		throw std::runtime_error(except);
	}

	static void CheckExceptionThrown(const T& a, const char* op, const T& b, const T& result)
	{
		int res = std::fetestexcept(ExceptionToCheck);

		if (res != 0)
			std::feclearexcept(res);
		else
			return;

		const char* except = nullptr;

		if (res == FE_DIVBYZERO)
			except = "Divide by zero";
		if (res == FE_INEXACT)
			except = "Inexact result";
		if (res == FE_INVALID)
			except = "Invalid result";
		if (res == FE_OVERFLOW)
			except = "Overflow";
		if (res == FE_UNDERFLOW)
			except = "Underflow";

		char buf[200];
#ifdef _MSC_VER
		sprintf_s(buf, "%f %s %f = %f result in %s\n", a, op, b, result, except);
#else
		snprintf(buf, sizeof(buf), "%f %s %f = %f result in %s\n", a, op, b, result, except);
#endif
		throw std::runtime_error(buf);
	}
	static void SetExceptionToCheck(int ex)
	{
		ExceptionToCheck = ex;
	}
private:
	T Data;
	static inline int ExceptionToCheck = FE_ALL_EXCEPT;
};