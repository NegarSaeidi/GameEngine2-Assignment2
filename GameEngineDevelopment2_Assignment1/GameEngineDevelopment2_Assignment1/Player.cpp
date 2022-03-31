/**-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// Player.cpp, handles player input. previously this was done in Game class
-------------------------------------------------------------------------*/
#pragma region step 2
#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Aircraft.hpp"
#include "../../Common/MathHelper.h"
#include "../../Common/d3dApp.h"
#include <map>
#include <string>
#include <algorithm>
#include <stdio.h>

using namespace DirectX;
struct AircraftMover
{
	AircraftMover(float vx, float vy, float vz)
		: velocity(vx,vy,vz)
	{
	}

	void operator() (Aircraft& aircraft, const GameTimer&) const
	{
		aircraft.accelerate(velocity);
	}

	XMFLOAT3 velocity;
};

Player::Player()
{
	// Set initial key bindings
	mKeyBinding[VK_LEFT] = MoveLeft;
	mKeyBinding[VK_RIGHT] = MoveRight;
	mKeyBinding[VK_UP] = MoveUp;
	mKeyBinding[VK_DOWN] = MoveDown;


	mKeyBinding['A'] = MoveLeft;
	mKeyBinding['D'] = MoveRight;
	mKeyBinding['R'] = MoveUp;
	mKeyBinding['F'] = MoveDown;
	mKeyBinding['W'] = MoveForward;
	mKeyBinding['S'] = MoveBackward;




	// Set initial action bindings
	initializeActions();

	

	// Assign all categories to player's aircraft
	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}
/**
 * handles key release and press events
 *@param const Command&
 * @return void
 */
void Player::handleEvent( CommandQueue& commands)
{

	for (auto pair : mKeyBinding)
	{
		if ((GetAsyncKeyState(pair.first) & 0x8000)&&!isRealtimeAction(pair.second))
		{
			// Check if pressed key appears in key binding, trigger command if so
					commands.push(mActionBinding[pair.second]);
				
			
		}
	}
}
/**
 * handles holding a key down event (real time input)
 *@param const Command&
 * @return void
 */
void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for (auto pair : mKeyBinding)
	{
		if (GetAsyncKeyState(pair.first) & 0x8000 && isRealtimeAction(pair.second))
		{
			
			commands.push(mActionBinding[pair.second]); 
		}
	}
}
/**
 * Adds new keybindings
 *@param Action action, char key
 * @return void
 */
void Player::assignKey(Action action, char key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}
/**
 * returns the assigned key based on the relative action
 *@param Action action
 * @return char
 */
char Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return 0x00;
}
/**
 * Assign appropriate behaviour for each key 
 *@param none
 * @return void
 */
void Player::initializeActions()
{
	const float playerSpeed = 10.f;

	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f,0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f,0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed,0.f));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed,0.f));
	mActionBinding[MoveForward].action = derivedAction<Aircraft>(AircraftMover(0.f, .0f, playerSpeed));
	mActionBinding[MoveBackward].action = derivedAction<Aircraft>(AircraftMover(0.f, .0f, -playerSpeed));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
	case MoveForward:
	case MoveBackward:
		return true;

	default:
		return false;
	}
}

#pragma endregion
