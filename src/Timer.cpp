#include "Timer.h"

void Timer::start() {
	last_time = std::chrono::high_resolution_clock::now();
	dt = 1.0 / 60;
	time_since_start = dt;
}

void Timer::tick() {
	auto current_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> diff = current_time - last_time;
	dt = diff.count();
	time_since_start += dt;
	last_time = current_time;
}
