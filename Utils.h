#pragma once
#include <functional>

class TriggerManager
{
private:
	bool curState;
	std::function<void(bool)> triggerEvent;

public:
	TriggerManager(bool init);
	void setTrigger(std::function<void(bool)> triggerEvent);
	bool getState();
	void  changeState(bool newState);
	void checkState(bool newState);
};




