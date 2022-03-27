/*
-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// World.cpp
-------------------------------------------------------------------------*/
#define NOMINMAX

#include "World.hpp"
#include "Game.hpp"
World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mSceneLayers()
	, mWorldBounds(-4.f, 4.f, 200.0f, 0.0f)
	, mSpawnPostion(0.0f,0.0f)
	, mScrollSpeed(-1.f)
{
	
}
/**
 * Updates the scene graph, calls the update function of eahc scene node
 *@param const GameTimer& gt
 * @return void
 */
void World::update(const GameTimer& gt)
{
	
      mBackground->move(0.f, 0, mScrollSpeed * gt.DeltaTime());
	
	  mPlayerAircraft->setVelocity(0.0f, 0.0f);

	  // Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	  while (!mCommandQueue.isEmpty())
		 mSceneGraph->onCommand(mCommandQueue.pop(), gt);
	
#pragma region step 5

	adaptPlayerVelocity();

	// Regular update step, adapt position (correct if outside view)
	mSceneGraph->update(gt);
	adaptPlayerPosition();

#pragma endregion
}

void World::draw()
{
	mSceneGraph->draw();
}
/**
 * builds the game scene, creates scene nodes and adds the m to the scene graph
 *@param void
 * @return void
 */
void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode(mGame));
		mSceneLayers[i] = layer.get();

		mSceneGraph->attachChild(std::move(layer));
	}
	std::unique_ptr<Aircraft> aircraft(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = aircraft.get();
	mPlayerAircraft->setPosition(0, 0.1, -2.0);
	mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	mPlayerAircraft->setVelocity(1,0.0001);
	mSceneLayers[Air]->attachChild(std::move(aircraft));
	


	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor = enemy1.get();
	raptor->setPosition(0.9, 0.2, -1.0);
	raptor->setScale(1,1, 1);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor1 = enemy2.get();
	raptor1->setPosition(-0.9, 0.2, -1.0);
	raptor1->setScale(1, 1, 1);
	
	mPlayerAircraft->attachChild(std::move(enemy2));


	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0);
	mBackground->setScale(300, 1, 300);
	mSceneGraph->attachChild(std::move(backgroundSprite));
	
	mSceneGraph->build();

}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}
#pragma region step 4

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	
	const float borderDistance = 100.f;

	XMFLOAT3 position = mPlayerAircraft->getWorldPosition();
	position.x = std::max(position.x, mWorldBounds.x);
	position.x = std::min(position.x, mWorldBounds.y);
	position.z = std::max(position.y, mWorldBounds.z);
	position.z = std::min(position.y, mWorldBounds.w);
	mPlayerAircraft->setPosition(position.x, position.y, position.z);
}

void World::adaptPlayerVelocity()
{
	XMFLOAT2 velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity.x / std::sqrt(2.f), velocity.y / std::sqrt(2.f));

	// Add scrolling velocity
//	mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}

#pragma endregion

