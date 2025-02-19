#include <iostream>
#include <sglib.h>

void printHello(int size)
{
	for (int i = 0; i < size; i++)
		std::cout << TEXT("HelloWorld") << "\n";
}

void printHelloEndl(int size)
{
	for (int i = 0; i < size; i++)
		std::cout << TEXT("HelloWorld") << std::endl;
}

int main()
{
	sglib::Logger::SetLogPrefix(TEXT("HelloWorld"));
	std::cout << TEXT("HelloWorld\n");
	SG_LOG_INFO(TEXT("HelloWorld"));
	SG_LOG_ERROR(TEXT("HelloWorld"));
	SG_LOG_CRITICAL(TEXT("HelloWorld"));
	SG_LOG_LOG(TEXT("HelloWorld"));
	SG_LOG_WARN(TEXT("HelloWorld"));

	SG_LOG_INFO(TEXT("loop 100 print hello"));
	sglib::timer::InvokeWithTimer({}, std::bind(printHello, 100));
	SG_LOG_INFO(TEXT("loop 100 print hello endl"));
	sglib::timer::InvokeWithTimer({}, std::bind(printHelloEndl, 100));

	SG_LOG_INFO(TEXT("loop 1000 print hello"));
	sglib::timer::InvokeWithTimer({}, std::bind(printHello, 1000));

	SG_LOG_INFO(TEXT("loop 1000 print hello endl"));
	sglib::timer::InvokeWithTimer({}, std::bind(printHello, 1000));
}