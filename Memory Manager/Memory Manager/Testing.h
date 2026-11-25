#pragma once
#include <iostream>
#include <chrono>
#include "MemoryManager.h"
#include "Logger.h"

class Dog
{
private:	
public:
	std::string m_breed;
	int m_age;
	int m_speed;
	std::string m_name;
	Dog(std::string name, std::string breed, int age, int speed)
	{
		m_name = name;
		m_breed = breed;
		m_age = age;
		m_speed = speed;
	}
	void info()
	{
		std::cout << "Name:" << m_name << "\n";
		std::cout << "Breed:" << m_breed << "\n";
		std::cout << "Age:" << m_age << "\n";
		std::cout << "Speed:" << m_speed << " km/h\n";
	}
	void bark()
	{
		std::cout << "Dog named:" << m_name << " says WOOF";
	}


};

class Testing
{
private:
	std::chrono::time_point<std::chrono::steady_clock> StartTime;
	std::chrono::time_point<std::chrono::steady_clock> EndTime;
	
	MemoryManager* mem;
	const int stressTestAmount = 1000000;
public:
	void TestBase();
	void TestIncorrect();
	void StressTest();
	void TestComplex();

};



