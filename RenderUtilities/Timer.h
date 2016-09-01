#pragma once

class Time
{
	float currentTime;
	float previousTime;
	float deltaTime;
public:
	bool init();
	bool update();
	bool term();

	float getDeltaTime() const; // Fixed to start of frame
	float getTotalTime() const; // Fixed to start of frame
	float getrealTime() const; // Return the real passage of time
};