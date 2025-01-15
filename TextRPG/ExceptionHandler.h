#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <iostream>
#include <string>
using namespace std;

enum class ErrorCode
{
	Unknown = 0,
	NullItemKey,
};

class ExceptionHandler
{
public:
	// ���� �ڵ�� �޽����� �Է¹޴´�.
	ExceptionHandler(enum class ErrorCode errorCode, string message);

	enum class ErrorCode GetErrorCode() const;
	string GetErrorMessage() const;

private:
	enum class ErrorCode errorCode;
	string message;
};

#endif // !EXCEPTIONHANDLER_H
