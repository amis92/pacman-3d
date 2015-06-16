#pragma once
#include <exception>

static const auto OutOfBoundsError = 0x0001;

class PacmanException : std::exception
{
public:
	explicit PacmanException(int errorCode)
	{
		ErrorCode = errorCode;
	}

	int ErrorCode;
};
