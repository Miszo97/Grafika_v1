#pragma once
#include <chrono>
#include <string>
#include <sstream>

class Stoper
{
	std::chrono::system_clock::time_point m_start;
	std::chrono::system_clock::time_point m_end;
	bool running;
public:
	Stoper();
	~Stoper() {};

	void Clear();
	void Start();
	void Stop();
	bool IsStarted() { return running; };
	unsigned int GetMs();
	std::string GetDuration();


};


