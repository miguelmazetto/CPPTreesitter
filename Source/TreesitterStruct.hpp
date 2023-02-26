#pragma once

namespace TS
{
enum class SymbolType
{
	Regular,
	Anonymous,
	Auxiliary
};

struct Position
{
	unsigned int Line = 0;
	unsigned int Column = 0;
};

struct InputEdit
{
	Position Start;
	Position OldEnd;
	Position NewEnd;
};
}	 // namespace TS