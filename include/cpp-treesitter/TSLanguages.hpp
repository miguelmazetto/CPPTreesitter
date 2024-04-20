#pragma once
#include "Language.hpp"

extern "C"
{
	TSLanguage* tree_sitter_cpp();
}

namespace TS
{
[[nodiscard]] static TS::Language* LanguageCpp()
{
	return new TS::Language(tree_sitter_cpp());
};
}	 // namespace TS