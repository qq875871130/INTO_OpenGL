#pragma once
#include <functional>

class TriggerManager
{
private:
	bool cur_state;
	std::function<void(bool)> trigger_event;

public:
	TriggerManager(bool init);
	void SetTrigger(std::function<void(bool)> triggerEvent);
	bool GetState();
	void  ChangeState(bool newState);
	void CheckState(bool newState);
};




