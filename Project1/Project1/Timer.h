#pragma once

#include <chrono>

class Timer
{
public:
	void start()
	{
		str= sc.now();
	}

	std::chrono::duration<double> stop() 
	{
		end = sc.now();	 

		return static_cast<std::chrono::duration<double>>(end - str); 
	}

	Timer() {};

	~Timer() {};

private:
	std::chrono::steady_clock sc;

	std::chrono::time_point<std::chrono::steady_clock> str;

	std::chrono::time_point<std::chrono::steady_clock> end;
};
