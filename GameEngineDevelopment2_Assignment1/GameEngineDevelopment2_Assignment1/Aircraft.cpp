/**-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// Aircraft.cpp, builds an aircraft render item
-------------------------------------------------------------------------*/
#include "Aircraft.hpp"
#include "Game.hpp"

/// <summary>
   /// Aircraft constructor, sets the sprite based on the type of the aircraft
 /// </summary>
Aircraft::Aircraft(Type type, Game* game):Entity(game), mType(type)
{
	switch (type)
	{
	case (Eagle):
		mSprite = "Eagle";
		break;
	case (Raptor):
		mSprite = "Raptor";
		break;
	default:
		mSprite = "Eagle";
			break;
	}

}

void Aircraft::drawCurrent() const
{
	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;

	
}
/**
 * Builds an aircraft render item and adds it to the mAllRenderItems in the game class
 *
 * @return void
 */
void Aircraft::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = gameInstance->getRenderItems().size();
	renderer->Mat = gameInstance->getMaterilas()[mSprite].get();
	renderer->Geo = gameInstance->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	//mAircraftRitem = render.get();
	
	gameInstance ->getRenderItems().push_back(std::move(render));

}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case Eagle:
		return Category::PlayerAircraft;

	default:
		return Category::EnemyAircraft;
	}
}

