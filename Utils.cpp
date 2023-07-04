#include "Utils.h"

TriggerManager::TriggerManager(bool init)
{
	this->curState = init;
}

void TriggerManager::setTrigger(std::function<void(bool)> triggerEvent)
{
	this->triggerEvent = triggerEvent;
}

bool TriggerManager::getState()
{
	return curState;
}

void TriggerManager::changeState(bool newState)
{
	checkState(newState);
	curState = newState;
}

void  TriggerManager::checkState(bool newState) {
	if (newState != curState)
	{
		triggerEvent(curState);
	}
}

