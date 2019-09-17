// Error.cpp
// Jongwon Jang

#include<cstring>
#include<iostream>
#include"Error.h"

using namespace std;

namespace aid
{
	Error::Error()
	{
		_msg = nullptr;
	}

	Error::Error(const char* errorMessage)
	{
		if (errorMessage == nullptr || errorMessage[0] == '\0')
			_msg = nullptr;
		else 
		{
			_msg = new char[strlen(errorMessage) + 1];
			strcpy(_msg, errorMessage);
			_msg[strlen(errorMessage)] = '\0';
		}
	}
	 
	Error::~Error() 
	{
		delete[] _msg;	
	}

	void Error::clear()
	{
		delete[] _msg;
		_msg = nullptr;
	}

	bool Error::isClear() const 
	{
		return _msg == nullptr;
	}

	void Error::message(const char* str) 
	{
		clear();
		if (str == nullptr || str[0] == '\0')
			_msg = nullptr;
		else 
		{
			_msg = new char[strlen(str) + 1];
			strcpy(_msg, str);
			_msg[strlen(str)] = '\0';
		}
	}

	const char* Error::message() const
	{		
			return _msg;
	}

	ostream& operator<<(ostream& os, const Error& error)
	{
		if (!error.isClear()) 
		{
			os << error.message();
		}
		return os;
	}

};



