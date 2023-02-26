#pragma once
#include "TreesitterStruct.hpp"

#include <tree_sitter/api.h>

#include <string>

namespace TS
{
class Language
{
	friend class Parser;
	friend class Query;
	const TSLanguage* pLanguage;

public:
	Language(const TSLanguage* Language);

	int GetFieldCount();
	std::string GetFieldName(int ID);
	int GetFieldID(std::string Name);

	int GetSymbolCount();
	int GetSymbolID(std::string SymbolName, bool isNamed);
	std::string GetSymbolName(int SymbolID);
	SymbolType GetSymbolType(int SymbolID);
	int GetLanguageVersion();
};
}	 // namespace TS