#include <cpp-treesitter/Query.hpp>

#include <tree_sitter/api.h>

using namespace std;
using namespace TS;

QueryCursor::QueryCursor()
{
	pQCursor = ts_query_cursor_new();
}

QueryCursor::QueryCursor(QueryCursor&& Cursor)
{
	pQCursor = Cursor.pQCursor;
	Cursor.pQCursor = nullptr;
}

QueryCursor::~QueryCursor()
{
	if (pQCursor)
		ts_query_cursor_delete(pQCursor);
}

bool QueryCursor::NextCapture(unsigned int& Index)
{
	return ts_query_cursor_next_capture(pQCursor, &QMatch, &Index);
}
void QueryCursor::RemoveMatch(int ID)
{
	ts_query_cursor_remove_match(pQCursor, ID);
}

bool QueryCursor::NextMatch()
{
	return ts_query_cursor_next_match(pQCursor, &QMatch);
}

Node QueryCursor::GetCaptureNode(int Index)
{
	return Node(QMatch.captures[Index].node);
}

int QueryCursor::GetCaptureCount()
{
	return QMatch.capture_count;
}

// Query =====

Query::Query(Query&& query)
{
	TSQuery* pQuery = query.pQuery;
	uint32_t ErrorOffset = query.ErrorOffset;
	TSQueryError QueryError = query.QueryError;
	query.pQuery = nullptr;
}

Query::Query(Language* Language, string Query)
{
	pQuery = ts_query_new(Language->pLanguage, Query.data(), Query.length(), &ErrorOffset, &QueryError);
}

Query::~Query()
{
	ts_query_delete(pQuery);
}

QueryCursor Query::Exec(Node QNode)
{
	QueryCursor QCursor;
	ts_query_cursor_exec(QCursor.pQCursor, pQuery, QNode.node);
	return QCursor;
}

string Query::GetStringValueForID(int ID)
{
	uint32_t length;
	auto* str = ts_query_string_value_for_id(pQuery, ID, &length);
	return string(str, length);
}
string Query::GetCaptureNameForID(int ID)
{
	uint32_t length;
	auto* str = ts_query_capture_name_for_id(pQuery, ID, &length);
	return string(str, length);
}
int Query::GetStringCount()
{
	return ts_query_string_count(pQuery);
}
int Query::GetPatternCount()
{
	return ts_query_pattern_count(pQuery);
}
int Query::GetCaptureCount()
{
	return ts_query_capture_count(pQuery);
}
void Query::DisableCapture(string Name)
{
	ts_query_disable_capture(pQuery, Name.data(), Name.size());
}
void Query::DisablePattern(int PatternID)
{
	ts_query_disable_pattern(pQuery, PatternID);
}