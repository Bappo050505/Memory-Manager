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
	

};

#define LOG_CONSOLE(x) Logger::Get()->logToConsole(x)
#define LOG_FILE(x) Logger::Get()->logToFile(x)