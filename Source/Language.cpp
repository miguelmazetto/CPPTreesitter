#include "Language.hpp"

#include <tree_sitter/api.h>

using namespace std;
using namespace TS;

Language::Language(const TSLanguage* Language) : pLanguage(Language)
{
}

int Language::GetFieldCount()
{
	return ts_language_field_count(pLanguage);
}
string Language::GetFieldName(int ID)
{
	return ts_language_field_name_for_id(pLanguage, ID);
}
int Language::GetFieldID(string Name)
{
	return ts_language_field_id_for_name(pLanguage, Name.data(), Name.size());
}

int Language::GetSymbolCount()
{
	return ts_language_symbol_count(pLanguage);
}

int Language::GetSymbolID(string SymbolName, bool isNamed)
{
	return ts_language_symbol_for_name(pLanguage, SymbolName.data(), SymbolName.size(), isNamed);
}

string Language::GetSymbolName(int SymbolID)
{
	return ts_language_symbol_name(pLanguage, SymbolID);
}

SymbolType Language::GetSymbolType(int SymbolID)
{
	return static_cast<SymbolType>(ts_language_symbol_type(pLanguage, SymbolID));
}

int Language::GetLanguageVersion()
{
	return ts_language_version(pLanguage);
}