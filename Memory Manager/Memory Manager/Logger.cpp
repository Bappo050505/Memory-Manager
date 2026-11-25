#include "Logger.h"

Logger* Logger::m_instance = nullptr;
Logger::Logger() 
{
	LogFile.open("log.txt", std::ios::out);
	LogFile.close();
}

Logger::~Logger()
{
	if (m_instance != nullptr)
	{
		
		delete m_instance;
		m_instance = nullptr;
	}
}

Logger* Logger::Get()
{
	if (m_instance != nullptr)
	{
		return m_instance;
	}
	else
	{
		m_instance = new Logger;
		return m_instance;
	}
}

void Logger::logToFile(std::string string)
{
	LogFile.open("log.txt", std::ios::app);
	LogFile << string;
	LogFile.close();
	
}


void Logger::logToConsole(std::string string)
{
	std::cout << string;
}

void Logger::logToFile(std::string string, void* memloc)
{
	LogFile.open("log.txt", std::ios::app);
	LogFile << string << memloc;
	LogFile.close();
}

void Logger::logToConsole(std::string string, void* memloc)
{
	std::cout << string << memloc;
}

