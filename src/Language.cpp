#include <cpp-treesitter/Language.hpp>

#include <tree_sitter/api.h>

using namespace std;
using namespace TS;

Language::Language(const TSLanguage* Language) : pLanguage(Language)
{
}

uint32_t Language::GetFieldCount()
{
	return ts_language_field_count(pLanguage);
}
string Language::GetFieldName(TSFieldId ID)
{
	return ts_language_field_name_for_id(pLanguage, ID);
}
TSFieldId Language::GetFieldID(string Name)
{
	return ts_language_field_id_for_name(pLanguage, Name.data(), Name.size());
}

uint32_t Language::GetSymbolCount()
{
	return ts_language_symbol_count(pLanguage);
}

TSSymbol Language::GetSymbolID(string SymbolName, bool isNamed)
{
	return ts_language_symbol_for_name(pLanguage, SymbolName.data(), SymbolName.size(), isNamed);
}

string Language::GetSymbolName(TSSymbol SymbolID)
{
	return ts_language_symbol_name(pLanguage, SymbolID);
}

SymbolType Language::GetSymbolType(TSSymbol SymbolID)
{
	return static_cast<SymbolType>(ts_language_symbol_type(pLanguage, SymbolID));
}

uint32_t Language::GetLanguageVersion()
{
	return ts_language_version(pLanguage);
}