#include <cpp-treesitter/Tree.hpp>

#include <tree_sitter/api.h>

using namespace TS;

Tree::Tree(TSTree* tree) : pTree(tree)
{
}
Tree::Tree(const Tree& tree)
{
	pTree = ts_tree_copy(tree.pTree);
}
Tree::Tree(Tree&& tree)
{
	pTree = tree.pTree;
	tree.pTree = nullptr;
}
Tree::~Tree()
{
	ts_tree_delete(pTree);
}

Node Tree::GetRootNode()
{
	return Node(ts_tree_root_node(pTree));
}

Language* Tree::GetLanguage() const
{
	auto Lang = ts_tree_language(pTree);
	if (Lang)
		return new Language(Lang);
	else
		return nullptr;
}

void Tree::Edit(InputEdit Input)
{
	TSInputEdit tsInputEdit;
	tsInputEdit.start_point = {Input.Start.Line, Input.Start.Column};
	tsInputEdit.old_end_point = {Input.OldEnd.Line, Input.OldEnd.Column};
	tsInputEdit.new_end_point = {Input.NewEnd.Line, Input.NewEnd.Column};
	ts_tree_edit(pTree, &tsInputEdit);
}