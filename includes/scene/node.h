
#pragma once
//EXTERNAL INCLUDES
#include <list>
//INTERNAL INCLUDES

//Class Node
class Node 
{
//Declare public virtual functions.
public:
	Node();

	virtual void Update(void);
	virtual void Cleanup(void);

	virtual void SetParent(Node* parent);
	virtual void DeleteParents();
	virtual void DeleteChildren();

	virtual void MakeRoot(void);

	virtual void AddChild(Node* node);
	virtual std::list<Node*> GetAllChildren();
	virtual void ListAllChildren(std::list<Node*>& list);

	virtual bool hasChildren();
	virtual bool hasRoot();

	virtual Node* GetParent();
	virtual Node* GetRoot();
	virtual void ListRoot(Node& node);

	virtual void operator+=(Node* child);
	virtual void operator-=(Node* child);
	virtual bool operator==(Node* other);

//Declare private variables.
private:
	bool isRoot;

	Node* parent;
	std::list<Node*> children;
	std::list<Node*> deletedObjects;
};
