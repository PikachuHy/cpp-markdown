//
// Created by pikachu on 2021/1/31.
//

#ifndef MD_PARSER_H
#define MD_PARSER_H
#include "def.h"
#include "Token.h"
#include "Document.h"
#include <vector>
namespace md::parser {
class Node;
class MARKDOWN_PARSER_EXPORT Parser {
 public:
  Parser();
  static NodePtrList parse(String text);
  constexpr static const String lr = "\n";
};
}

#endif //MD_PARSER_H
