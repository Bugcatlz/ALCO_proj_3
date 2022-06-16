#ifndef REGISTER_H
#define REGISTER_H
#include <vector>
#include <map>
#include <string>

using namespace std;

class Register
{
public:
	Register()
		:myValue()
	{}

	Register(int n)
		:myValue(n)
	{}

	int& operator=(int value)
	{
		myValue = value;
		return myValue;
	}

	void operator=(Register r)
	{
		myValue = r.myValue;
	}

	int& operator+(int value)
	{
		int v = myValue + value;
		return v;
	}

	int& operator+(Register r)
	{
		int v = myValue + r.myValue;
		return v;
	}

	int& operator*(Register r)
	{
		int v = myValue * r.myValue;
		return v;
	}

	int& operator/(Register r)
	{
		int v = myValue / r.myValue;
		return v;
	}

	int getValue()
	{
		return myValue;
	}

	void setName(string s)
	{
		renaming = s;
	}

	bool getState()
	{
		return renaming.size()==0;
	}

	void setValue(int n)
	{
		myValue = n;
	}

	string& getName()
	{
		return renaming;
	}

private:
	int myValue;
	string renaming;
};

#endif