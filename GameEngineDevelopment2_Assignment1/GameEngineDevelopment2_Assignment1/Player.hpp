#pragma once
#include "Command.hpp"
#include <map>

class CommandQueue;

class Player
{
public:
	Player();
	void					handleEvent(CommandQueue& commands);
	void					handleRealtimeInput(CommandQueue& commands);
#pragma region step 1
	//static const float		PlayerSpeed;
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		MoveForward,
		MoveBackward,
		ActionCount
	};
	void					assignKey(Action action,char key);
	char	getAssignedKey(Action action) const;


private:
	void					initializeActions();
	static bool				isRealtimeAction(Action action);


private:
	std::map<char, Action>		mKeyBinding;
	std::map<Action, Command>				mActionBinding;

#pragma endregion


};


