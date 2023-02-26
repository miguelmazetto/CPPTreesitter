#pragma once
#include "TreesitterStruct.hpp"

#include <tree_sitter/api.h>

#include <string>

namespace TS
{
class Node
{
	friend class Query;
	friend class Tree;
	friend class NodeCursor;
	friend class QueryCursor;

	TSNode node;
	Node(TSNode TNode);

public:
	void Edit(InputEdit Input);
	Position GetStartPos();
	Position GetEndPos();

	Node GetParentNode();

	int GetChildCount();
	Node GetChild(int ID);
	Node GetNextSibling();
	Node GetPreviousSibling();

	int GetNamedChildCount();
	Node GetNamedChild(int ID);
	Node GetNextNamedSibling();
	Node GetPreviousNamedSibling();

	Node GetChildByFieldID(int FieldID);
	Node GetChildByFieldName(std::string FieldName);
	// Returns empty string, if no field is found.
	std::string GetFieldNameForChild(int ID);

	// Node type name (Example: parameter_list, primitive_type, function_declarator)
	std::string GetTypeName();
	int GetSymbolID();
	bool isNull();
	bool isNamed();

	bool isExtra();

	bool isMissing();
	// Check if a syntax node has been edited
	bool hasChanges();
	// String node tree
	std::string toString();

	inline bool operator==(const Node& iNode)
	{
		return ts_node_eq(node, iNode.node);
	}
	inline bool operator!=(const Node& iNode)
	{
		return !ts_node_eq(node, iNode.node);
	}

	// For loop
	inline Node begin()
	{
		return ts_node_child(node, 0);
	}
	inline Node end()
	{
		return ts_node_child(node, ts_node_child_count(node));
	}
	inline Node& operator++()
	{
		node = ts_node_next_sibling(node);
		return *this;
	}
	inline Node operator++(int)
	{
		return ts_node_next_sibling(node);
	}
	inline Node& operator*()
	{
		return *this;
	}
};

class NodeCursor
{
	TSTreeCursor pCursor;

public:
	NodeCursor(Node node);
	NodeCursor(const NodeCursor& node);
	~NodeCursor();

	// Move cursor
	// Methods return true if the cursor successfully moved
	bool GotoFirstChild();
	bool GotoNextSibling();
	bool GotoParent();

	Node GetCurrentNode();
	std::string GetCurrentFieldName();
	int GetCurrentFieldID();
	void Reset(Node NewNode);
};
}	 // namespace TS