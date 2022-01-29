//
// Created by pikachu on 2021/1/31.
//

#include "Document.h"
#include "Parser.h"
#include <utility>
#include <string>
#include "magic_enum.hpp"
using namespace std::literals;
namespace md::parser {
std::ostream &operator<<(std::ostream &os, const NodeType &type) {
  os << magic_enum::enum_name(type);
  return os;
}
Header::Header(int level) : m_level(level) { m_type = NodeType::header; }

Document::Document(String str) {
  Parser parser;
  m_nodes = parser.parse(std::move(str));
}

void Document::accept(VisitorNode *visitor) {
  for (auto it : m_nodes) {
    it->accept(visitor);
  }
}
NodePtrList Document::children() { return m_nodes; }
}