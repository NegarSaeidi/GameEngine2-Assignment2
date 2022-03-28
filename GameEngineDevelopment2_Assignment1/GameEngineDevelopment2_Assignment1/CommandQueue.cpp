/**-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// CommandQueue.cpp, this class transports commands to the world and the scene graph
-------------------------------------------------------------------------*/
#include "CommandQueue.hpp"
#include "SceneNode.hpp"

/**
 * pushes the new command to the queue
 *@param const Command&
 * @return void
 */
void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}
/**
 * returns the last command from the queue
 *@param none
 * @return Command
 */
Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();
	return command;
}
/**
 * checks to see if the queue is empty
 *@param const none
 * @return bool
 */
bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}


