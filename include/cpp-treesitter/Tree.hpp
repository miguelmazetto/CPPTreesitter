#pragma once
#include "Language.hpp"
#include "Node.hpp"

#include <tree_sitter/api.h>

namespace TS
{
class Tree
{
protected:
	friend class Parser;
	TSTree* pTree;

	Tree(TSTree* tree);

public:
	Tree(const Tree& tree);
	Tree(Tree&& tree);
	~Tree();
	Node GetRootNode();
	Language* GetLanguage() const;
	void Edit(InputEdit Input);
};
}	 // namespace TS