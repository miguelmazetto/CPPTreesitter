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

	uint32_t GetFieldCount();
	std::string GetFieldName(TSFieldId ID);
	TSFieldId GetFieldID(std::string Name);

	uint32_t GetSymbolCount();
	TSSymbol GetSymbolID(std::string SymbolName, bool isNamed);
	std::string GetSymbolName(TSSymbol SymbolID);
	SymbolType GetSymbolType(TSSymbol SymbolID);
	uint32_t GetLanguageVersion();
};
}	 // namespace TS