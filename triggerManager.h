#pragma once
#include <functional>

class triggerManager
{
private:
	bool curState;
	std::function<void(bool)> triggerEvent;

public:
	triggerManager(bool init);
	void setTrigger(std::function<void(bool)> triggerEvent);
	bool getState();
	void  changeState(bool newState);
	void checkState(bool newState);
};

