// Error.h
// Jongwon Jang

#ifndef AID_ERROR_H
#define AID_ERROR_H
#include <iostream>

namespace aid 
{
	class Error
	{
		char* _msg;
	public:
		Error();
		explicit Error(const char* errorMessage);
		Error(const Error& em) = delete;
		Error& operator=(const Error& em) = delete;
		virtual ~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};
	std::ostream& operator<<(std::ostream& os, const Error& error);
}

#endif 

