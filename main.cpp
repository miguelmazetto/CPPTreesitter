#include "Source/Parser.hpp"
#include "Source/Query.hpp"
#include "Source/TSLanguages.hpp"
#include "Source/Treesitter.hpp"

#include <tree_sitter/api.h>

#include <fstream>
#include <iostream>

extern "C" {
TSLanguage *tree_sitter_cpp();
}

using namespace std;

string ReadFile(string FilePatch) {
  fstream file;
  file.open(FilePatch, ios::in);
  string text;

  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      line.append("\n");
      text.append(line);
    }
    return text;
  }

  cout << "Error" << endl;
  return "";
}

int main() {
  string SourceCode = ReadFile("../code.cpp");
  auto LanguageCpp = TS::LanguageCpp();

  TS::Parser Parser(LanguageCpp);
  auto Tree = Parser.Parse(SourceCode);
  auto RootNode = Tree->GetRootNode();

  string highlight_query =
      ReadFile("../ThirdParty/tree-sitter-cpp/queries/highlights.scm");

  auto query = TS::Query(LanguageCpp, highlight_query);
  auto cursorq = query.Exec(RootNode);

  unsigned int index;
  while (cursorq.NextMatch()) {
    cout << "Match: " << endl;
    while (cursorq.NextCapture(index)) {
      cout << "Count: " << cursorq.GetCaptureCount() << endl;
      cout << "Count: " << cursorq.GetCaptureNode(index).toString() << endl;
    }
  }
}