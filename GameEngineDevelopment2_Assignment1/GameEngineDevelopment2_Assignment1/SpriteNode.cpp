/*
-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// SpriteNode.cpp
// Builds a sprite render item
-------------------------------------------------------------------------*/
#include "SpriteNode.hpp"
#include "Game.hpp"
SpriteNode::SpriteNode(Game* game):Entity(game)
{
}

void SpriteNode::drawCurrent() const
{
	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}
/**
 * Builds a sprite render item and adds it to the mAllRenderItems in the game class
 * 
 * @return void
 */
void SpriteNode::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform,XMMatrixScaling(100,100,100));
	renderer->ObjCBIndex = gameInstance->getRenderItems().size();
	renderer->Mat = gameInstance->getMaterilas()["Desert"].get();
	renderer->Geo = gameInstance->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	gameInstance->getRenderItems().push_back(std::move(render));
}
