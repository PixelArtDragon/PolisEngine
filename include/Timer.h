#pragma once

#include <chrono>

class Timer {
public:
	float dt;
	float time_since_start;
	void start();
	void tick();
private:
	std::chrono::high_resolution_clock::time_point last_time;
};
