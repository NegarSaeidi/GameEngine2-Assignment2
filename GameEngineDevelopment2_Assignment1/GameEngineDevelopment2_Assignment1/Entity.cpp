/*
-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// Entity.cpp, adjusts the velocity of the entity
-------------------------------------------------------------------------*/
#include "Entity.hpp"

Entity::Entity(Game* game):SceneNode(game), mVelocity(0, 0,0)
{
	
}
/**
 * sets the velocity of the entity
 *@param XMFLOAT2 velocity
 * @return void
 */
void Entity::setVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy, float vz)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
	mVelocity.z = vz;
}
/**
 * returns the velocity of the entity
 *@param void
 * @return XMFLOAT2
 */
XMFLOAT3 Entity::getVelocity() const
{
	return mVelocity;
}
void Entity::accelerate(XMFLOAT3 velocity)
{
	mVelocity.x += velocity.x;
	mVelocity.y += velocity.y;
	mVelocity.z += velocity.z;
}
void Entity::accelerate(float vx, float vy, float vz)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
	mVelocity.z += vz;
}
/**
 * updates the current entity
 *@param const GameTimer& gt
 * @return void
 */
void Entity::updateCurrent(const GameTimer& gt)
{

	float xMovement = mVelocity.x * gt.DeltaTime();
	float yMovement = mVelocity.y * gt.DeltaTime();
	float zMovement = mVelocity.z * gt.DeltaTime();
	move(xMovement, yMovement,zMovement);

	
}
