#include "Utils.h"

#pragma region TriggerManager
TriggerManager::TriggerManager(bool init)
{
	this->cur_state = init;
}

void TriggerManager::SetTrigger(std::function<void(bool)> triggerEvent)
{
	this->trigger_event = triggerEvent;
}

bool TriggerManager::GetState()
{
	return cur_state;
}

void TriggerManager::ChangeState(bool newState)
{
	CheckState(newState);
	cur_state = newState;
}

void  TriggerManager::CheckState(bool newState) {
	if (newState != cur_state)
	{
		trigger_event(cur_state);
	}
}
#pragma endregion


