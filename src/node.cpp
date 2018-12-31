
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

		this->isRoot = true;
	}

	this->isRoot = true;

	//Define this node as the root.
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

std::list<Node*> Node::GetAllChildren()
{
	std::list<Node*> temp;
	this->ListAllChildren(temp);
	return temp;
}

std::list<Node*>& Node::GetChildren()
{
	return this->children;
}

void Node::ListAllChildren(std::list<Node*>& list)
{
	for (Node* node : this->children)
	{
		//Recursive function to open all children in all childs of this node.
		if (node != nullptr)
		{
			node->ListAllChildren(list);
		}
	}

	if(this->parent)
		list.push_back(this);

}

void Node::ListRoot(Node& node)
{
	if (this->parent->isRoot)
	{
		node = *this->parent;
	}

	if (this->parent)
	{
		this->parent->ListRoot(node);
	}
	
}

bool Node::hasChildren()
{
	if (this->children.size() != 0)
		return true;
	return false;
}

bool Node::hasRoot()
{
	return this->isRoot;
}

Node* Node::GetParent()
{
	return this->parent;
}

Node* Node::GetRoot()
{
	Node* temp = this;

	this->ListRoot(*temp);
	return temp;
}

//Void Update
void Node::Update()
{
	//For every child in this nodes children list
	for (Node* child : this->children) 
	{
		//Execute its Update function.
		child->Update();
	}
}

void Node::Cleanup(void)
{
	for (Node* child : this->children)
	{
		//Execute its Update function.
		child->Cleanup();
	}

	if (this->parent)
	{
		//Remove this node from its parent children list.
		this->parent->deletedObjects.push_back(this);
	}

	this->children.clear();
	delete this;
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
