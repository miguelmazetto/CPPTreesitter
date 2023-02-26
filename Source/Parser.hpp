#pragma once
#include "Language.hpp"
#include "Tree.hpp"

#include <tree_sitter/api.h>

#include <string>

namespace TS
{
class Parser
{
	TSParser* pParser;

public:
	Parser() = default;
	Parser(Language* language);
	Parser(const Parser& parser);
	Parser(Parser&& parser);
	~Parser();

	void SetLanguage(Language* language);
	Language* GetLanguage() const;

	Tree* Parse(std::string SourceCode);
	Tree* Parse(std::string SourceCode, Tree* OldTree);
};
}	 // namespace TS