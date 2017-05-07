#include "Stoper.h"

Stoper::Stoper()
	: m_start(std::chrono::system_clock::time_point::min()),
	  m_end(std::chrono::system_clock::time_point::min()),
	  running (false)
{}

void Stoper::Clear()
{
	// czyszczenie stopera:
	m_start = std::chrono::system_clock::time_point::min();
	m_end = std::chrono::system_clock::time_point::min();
	running = false;
}

void Stoper::Start()
{
	m_start = std::chrono::system_clock::now();
	running = true;
}

void Stoper::Stop()
{
	if(running)	m_end = std::chrono::system_clock::now();
	running = false;
}

unsigned int Stoper::GetMs()
{
	std::chrono::system_clock::duration diff;
	if (running)
		diff = std::chrono::system_clock::now() - m_start;
	else
		diff = m_end - m_start;
	return (unsigned)(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
}

std::string Stoper::GetDuration()
{
	std::chrono::system_clock::duration diff;
	std::stringstream ss;
	unsigned int ms;
	unsigned int sek;
	unsigned int min;
	unsigned int hour;
	if (running)
		diff = std::chrono::system_clock::now() - m_start;
	else
		diff = m_end - m_start;
	ms = (unsigned)(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
	sek = ms / 1000;
	ms = ms % 1000;
	min = sek / 60;
	sek = sek % 60;
	hour = min / 60;
	min = min % 60;
	ss << "Elapsed time (H:M:S.MS): " << hour << ":" << min << ":" << sek << "." << ms;
	return ss.str();
}

