#include "Parser.hpp"

#include "Language.hpp"

#include <tree_sitter/api.h>

using namespace std;
using namespace TS;

Parser::Parser(Language* language)
{
	pParser = ts_parser_new();
	if (!language)
		return;
	ts_parser_set_language(pParser, language->pLanguage);
}
Parser::Parser(const Parser& parser)
{
	pParser = ts_parser_new();
	ts_parser_set_language(pParser, parser.GetLanguage()->pLanguage);
}
Parser::Parser(Parser&& parser)
{
	pParser = parser.pParser;
	parser.pParser = nullptr;
}
Parser::~Parser()
{
	ts_parser_delete(pParser);
}

void Parser::SetLanguage(Language* language)
{
	if (!language)
		return;
	ts_parser_set_language(pParser, language->pLanguage);
}

Language* Parser::GetLanguage() const
{
	auto Lang = ts_parser_language(pParser);
	if (Lang)
		return new Language(Lang);
	else
		return nullptr;
}

Tree* Parser::Parse(string SourceCode)
{
	if (SourceCode.empty())
		return nullptr;
	return new Tree(ts_parser_parse_string(pParser, nullptr, SourceCode.data(), SourceCode.size()));
}
Tree* Parser::Parse(string SourceCode, Tree* OldTree)
{
	if (SourceCode.empty() || !OldTree)
		return nullptr;
	return new Tree(ts_parser_parse_string(pParser, OldTree->pTree, SourceCode.data(), SourceCode.size()));
}