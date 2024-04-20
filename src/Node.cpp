#include <cpp-treesitter/Node.hpp>

#include <tree_sitter/api.h>

using namespace std;
using namespace TS;

Node::Node(TSNode TNode) : node(TNode)
{
}

string Node::GetTypeName()
{
	return string(ts_node_type(node));
}

TSSymbol Node::GetSymbolID()
{
	return ts_node_symbol(node);
}

Position Node::GetStartPos()
{
	TSPoint point = ts_node_start_point(node);
	return {point.row, point.column};
}
Position Node::GetEndPos()
{
	TSPoint point = ts_node_end_point(node);
	return {point.row, point.column};
}

bool Node::isNull()
{
	return ts_node_is_null(node);
}

bool Node::isNamed()
{
	return ts_node_is_named(node);
}

bool Node::isExtra()
{
	return ts_node_is_extra(node);
}

bool Node::isMissing()
{
	return ts_node_is_missing(node);
}

bool Node::hasChanges()
{
	return ts_node_has_changes(node);
}

string Node::toString()
{
	char* Text = ts_node_string(node);
	string NodeText(Text);
	free(Text);
	return NodeText;
}

void Node::Edit(InputEdit Input)
{
	TSInputEdit tsInputEdit;
	tsInputEdit.start_point = {Input.Start.Line, Input.Start.Column};
	tsInputEdit.old_end_point = {Input.OldEnd.Line, Input.OldEnd.Column};
	tsInputEdit.new_end_point = {Input.NewEnd.Line, Input.NewEnd.Column};
	ts_node_edit(&node, &tsInputEdit);
}

Node Node::GetParentNode()
{
	return Node(ts_node_parent(node));
}
uint32_t Node::GetChildCount()
{
	return ts_node_child_count(node);
}
Node Node::GetChild(uint32_t ID)
{
	return Node(ts_node_child(node, ID));
}
Node Node::GetNextSibling()
{
	return Node(ts_node_next_sibling(node));
}
Node Node::GetPreviousSibling()
{
	return Node(ts_node_prev_sibling(node));
}

// Named
uint32_t Node::GetNamedChildCount()
{
	return ts_node_named_child_count(node);
}
Node Node::GetNamedChild(uint32_t ID)
{
	return Node(ts_node_named_child(node, ID));
}
Node Node::GetNextNamedSibling()
{
	return Node(ts_node_next_named_sibling(node));
}
Node Node::GetPreviousNamedSibling()
{
	return Node(ts_node_prev_named_sibling(node));
}

Node Node::GetChildByFieldID(TSFieldId FieldID)
{
	return Node(ts_node_child_by_field_id(node, FieldID));
}
Node Node::GetChildByFieldName(string FieldName)
{
	return Node(ts_node_child_by_field_name(node, FieldName.data(), FieldName.size()));
}

string Node::GetFieldNameForChild(uint32_t ID)
{
	auto name = ts_node_field_name_for_child(node, ID);
	return name ? name : string();
}

// =============================================================

NodeCursor::NodeCursor(Node node)
{
	pCursor = ts_tree_cursor_new(node.node);
}
NodeCursor::NodeCursor(const NodeCursor& node)
{
	pCursor = ts_tree_cursor_copy(&node.pCursor);
}
NodeCursor::~NodeCursor()
{
	ts_tree_cursor_delete(&pCursor);
}
void NodeCursor::Reset(Node NewNode)
{
	ts_tree_cursor_reset(&pCursor, NewNode.node);
}
bool NodeCursor::GotoFirstChild()
{
	return ts_tree_cursor_goto_first_child(&pCursor);
}
bool NodeCursor::GotoNextSibling()
{
	return ts_tree_cursor_goto_next_sibling(&pCursor);
}
bool NodeCursor::GotoParent()
{
	return ts_tree_cursor_goto_parent(&pCursor);
}

Node NodeCursor::GetCurrentNode()
{
	return Node(ts_tree_cursor_current_node(&pCursor));
}
string NodeCursor::GetCurrentFieldName()
{
	return ts_tree_cursor_current_field_name(&pCursor);
}
TSFieldId NodeCursor::GetCurrentFieldID()
{
	return ts_tree_cursor_current_field_id(&pCursor);
}