/*
-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// SceneNode.cpp
-------------------------------------------------------------------------*/
#include "SceneNode.hpp"
#include "Command.hpp"
SceneNode::SceneNode(Game* game) :
	mChildren(),
	mParent(nullptr),
	gameInstance(game)
{
	mWorldPosition = XMFLOAT3(0, 0, 0);
	mWorldScale = XMFLOAT3(1, 1, 1);
	mWorlRotation = XMFLOAT3(0, 0, 0);
}
/**
 * add a child to this node
 *@param Ptr child
 * @return void
 */
void SceneNode::attachChild(Ptr child)
{

	child->mParent = this;
	mChildren.push_back(std::move(child));
}
/**
 * detaches a child from this node
 *@param const SceneNode& node
 * @return SceneNode::Ptr
 */
SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}
/**
 * calls the update function of this node and its children
 *@param const GameTimer& gt
 * @return void
 */
void SceneNode::update(const GameTimer& gt)
{
	updateCurrent(gt);
	updateChildren(gt);
}
/**
 * calls the draw function of this node and its children
 *@param void
 * @return void
 */
void SceneNode::draw() const
{
	
	
	drawCurrent();
	drawChildren();
}
/**
 * calls the build function of this node and its children
 *@param void
 * @return void
 */
void SceneNode::build()
{
	buildCurrent();
	buildChildren();
}
/**
 * returns the world position of this node
 *@param void
 * @return XMFLOAT3
 */
XMFLOAT3 SceneNode::getWorldPosition() const
{
	return mWorldPosition;
}
/**
 * sets the world position of this node
 *@param float x, float y, float z
 * @return void
 */
void SceneNode::setPosition(float x, float y, float z)
{
	mWorldPosition.x = x;
	mWorldPosition.y = y;
	mWorldPosition.z = z;
}
/**
 * returns the world rotation of this node
 *@param void
 * @return XMFLOAT3
 */
XMFLOAT3 SceneNode::getWorldRotation() const
{
	return mWorlRotation;
}
/**
 * sets the world rotation of this node
 *@param float x, float y, float z
 * @return void
 */
void SceneNode::setWorldRotation(float x, float y, float z)
{
	mWorlRotation.x = x;
	mWorlRotation.y = y;
	mWorlRotation.z = z;

}
/**
 * returns the world scale of this node
 *@param void
 * @return XMFLOAT3
 */
XMFLOAT3 SceneNode::getWorldScale() const
{
	return mWorldScale;
}
/**
 * sets the scale of this node
 *@param float x, float y, float z
 * @return void
 */
void SceneNode::setScale(float x, float y, float z)
{
	mWorldScale.x = x;
	mWorldScale.y = y;
	mWorldScale.z = z;
}
/**
 * returns the world tranform of this node
 *@param void
 * @return XMFLOAT4X4
 */
XMFLOAT4X4 SceneNode::getWorldTransform() const
{
	
	XMFLOAT4X4 transform = MathHelper::Identity4x4();
	XMMATRIX T = XMLoadFloat4x4(&transform);
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		XMMATRIX Tp = XMLoadFloat4x4(&node->getTransform());
		T = Tp * T;
		
	}

	XMStoreFloat4x4(&transform, T);


	return transform;
}
/**
 * returns the local tranform of this node
 *@param void
 * @return XMFLOAT4X4
 */
XMFLOAT4X4 SceneNode::getTransform() const
{
	XMFLOAT4X4 transform = MathHelper::Identity4x4();
	XMMATRIX T=XMMatrixScaling(mWorldScale.x,mWorldScale.y,mWorldScale.z)
		* XMMatrixTranslation(mWorldPosition.x,mWorldPosition.y,mWorldPosition.z)
		* XMMatrixRotationRollPitchYaw(mWorlRotation.x, mWorlRotation.y,mWorlRotation.z);
	XMStoreFloat4x4(&transform, T);

	
	return transform;

}
void SceneNode::onCommand(const Command& command, const GameTimer& gt)
{
	// Command current node, if category matches
	if (command.category & getCategory())
		command.action(*this, gt);

	// Command children
	for (Ptr& child : mChildren)
		child->onCommand(command, gt);
}
unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}
/**
 * updates the position of this node
 *@param float x, float y, float z
 * @return void
 */
void SceneNode::move(float x, float y, float z)
{
	mWorldPosition.x += x;
    mWorldPosition.y += y;
	mWorldPosition.z += z;
}

void SceneNode::updateCurrent(const GameTimer& gt)
{
	
}
/**
 * calls the update function of this node's children
 *@param const GameTimer& gt
 * @return void
 */
void SceneNode::updateChildren(const GameTimer& gt)
{
	for (Ptr& child : mChildren)
	{
		child->update(gt);
	}
}

void SceneNode::drawCurrent() const
{

}
/**
 * calls the draw function of this node's children
 *@param const GameTimer& gt
 * @return void
 */
void SceneNode::drawChildren() const
{
	for (const Ptr& child : mChildren)
	{
		child->draw();

	}
}

void SceneNode::buildCurrent()
{
}
/**
 * calls the build function of this node's children
 *@param const GameTimer& gt
 * @return void
 */
void SceneNode::buildChildren()
{
	for (const Ptr& child : mChildren)
	{
		child->build();
		
	}
}
