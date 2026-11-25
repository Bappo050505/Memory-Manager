#pragma once
#include <iostream>
#include <fstream>
#include <chrono>


class Logger
{
private:
	Logger();
	Logger(Logger& L) = delete;
	std::ofstream LogFile;
	static Logger* m_instance;
public:
	~Logger();

	static Logger* Get();
	
	void logToFile(std::string string);
	void logToConsole(std::string string);

	void logToFile(std::string string, void* memloc);
	void logToConsole(std::string string , void* memloc);
	

};

#define LOG_CONSOLE(x) Logger::Get()->logToConsole(x)
#define LOG_FILE(x) Logger::Get()->logToFile(x)

#define LOG_ADDRESS_CONSOLE(x, y) Logger::Get()->logToConsole(x,y)
#define LOG_ADDRESS_FILE(x,y) Logger::Get()->logToFile(x,y)