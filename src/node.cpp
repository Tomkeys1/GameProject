
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "scene/node.h"
#include "typedefs/utils.h"

//Node Constructor. Set parent to null pointer and isRoot to false.
Node::Node() :
	isRoot(false),
	parent(nullptr)
{
}

//Void SetParent
void Node::SetParent(Node* parent)
{
	//if this node is the root.
	if (isRoot)
	{
		LOG("It is forbidden to give root a parent");
		return;
	}

	//Set this node to the parent of the inputed node.
	this->parent = parent;
}

//Void DeleteParents
void Node::DeleteParents()
{
	//If this node has no parent.
	if (!this->parent)
	{
		//Recursive function to delete all children.
		this->DeleteChildren();
		return;
	}

	//Recursive function to do the same for the parent nodes.
	this->parent->DeleteParents();
}

//Void DeleteChildren
void Node::DeleteChildren()
{
	//for all nodes in this nodes children list.
	for (Node* node : this->children)
	{
		//Recursive function to open all children in all childs of this node.
		node->DeleteChildren();
	}

	//Delete this child. Because all children execute this function, all children with all child objects are deleted.
	delete this;
}

//Void MakeRoot
void Node::MakeRoot(void)
{
	//if this node has a parent.
	if (this->parent)
	{
		//Remove this node from its parent children list.
		this->parent->children.remove(this);

		//Delete all Parents with its child objects.
		this->DeleteParents();

		//Set this nodes parent to null pointer.
		this->parent = nullptr;
	}

	//Define this node as the root.
	this->isRoot = true;
}

//Void AddChild
void Node::AddChild(Node* node)
{
	//If the inputed node is a node.
	if (node)
	{
		//Add the inputed node into this nodes children list.
		this->children.push_back(node);

		//If the inputed node isnt the root
		if (!node->isRoot)
			//Set the inputed nodes parent to this.
			node->parent = this;
	}
}

//Void Update
void Node::Update(void)
{
	//For every child in this nodes children list
	for (Node* child : this->children) 
	{
		//Execute its Update function.
		child->Update();
	}
}

//Void += operator
void Node::operator+=(Node* child)
{
	//Add the inputed node into this nodes children list.
	this->children.push_back(child);
}

//Void += operator
void Node::operator-=(Node* child)
{
	//Remove the inputed node from this nodes children list.
	this->children.remove(child);
}

//Compare two nodes if they are equal or not.
bool Node::operator==(Node* other)
{
	//Return true if the bytes between this node and the inputed node are the size of the class Node.
	return memcmp(this, other, sizeof(Node)) == 0;
}
