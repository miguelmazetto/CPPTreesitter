#pragma once
#include "Language.hpp"
#include "Node.hpp"

#include <tree_sitter/api.h>

#include <string>

namespace TS
{
class QueryCursor
{
	friend class Query;
	TSQueryCursor* pQCursor;
	TSQueryMatch QMatch;

public:
	TSQueryMatch GetQMatch()
	{
		return QMatch;
	};
	QueryCursor(const QueryCursor&) = delete;
	QueryCursor();
	QueryCursor(QueryCursor&& Cursor);
	~QueryCursor();

	bool NextCapture(unsigned int& Index);

	bool NextMatch();
	void RemoveMatch(int ID);
	Node GetCaptureNode(int Index);
	int GetCaptureCount();
};

class Query
{
protected:
	TSQuery* pQuery;
	uint32_t ErrorOffset;
	TSQueryError QueryError;

public:
	Query(const Query&) = delete;
	Query(Query&& query);
	Query(Language* Language, std::string Query);
	~Query();

	QueryCursor Exec(Node QNode);

	int GetStringCount();
	std::string GetStringValueForID(int ID);
	int GetCaptureCount();
	std::string GetCaptureNameForID(int ID);
	int GetPatternCount();
	void DisableCapture(std::string Name);
	void DisablePattern(int PatternID);
};
}	 // namespace TS