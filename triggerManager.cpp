#include "triggerManager.h"

triggerManager::triggerManager(bool init)
{
	this->curState = init;
}

void triggerManager::setTrigger(std::function<void(bool)> triggerEvent)
{
	this->triggerEvent = triggerEvent;
}

bool triggerManager::getState()
{
	return curState;
}

void triggerManager::changeState(bool newState)
{
	checkState(newState);
	curState = newState;
}

void  triggerManager::checkState(bool newState) {
	if (newState != curState)
	{
		triggerEvent(curState);
	}
}
