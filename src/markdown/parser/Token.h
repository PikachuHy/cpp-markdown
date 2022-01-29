//
// Created by pikachu on 2021/1/31.
//

#ifndef MD_TOKEN_H
#define MD_TOKEN_H
#include "def.h"
#include <string_view>
#include <unordered_map>
namespace md::parser {
enum class TokenType {
  none,
  sharp,              // #
  space,              //
  left_parenthesis,   // (
  right_parenthesis,  // )
  left_bracket,       // [
  right_bracket,      // ]
  exclamation,        // !
  gt,                 // >
  quotation_en,       // "
  star,               // *
  tilde,              // ~
  text,
  backquote,  // `
  dollar
};
class MARKDOWN_PARSER_EXPORT Token {
 public:
  explicit Token(TokenType type = TokenType::none);

  explicit Token(String str, TokenType type = TokenType::none);

  bool operator==(const Token &rhs) const;

  bool operator!=(const Token &rhs) const;

  TokenType type() const { return m_type; }
  String str() const { return m_str; }

 protected:
  TokenType m_type;
  String m_str;
};
using TokenList = std::vector<Token>;
extern std::unordered_map<char, Token> spMap;
inline bool isSharp(Token token) { return token.type() == TokenType::sharp; }
inline bool isSpace(Token token) { return token.type() == TokenType::space; }
inline bool isLeftParenthesis(Token token) {
  return token.type() == TokenType::left_parenthesis;
}
inline bool isRightParenthesis(Token token) {
  return token.type() == TokenType::right_parenthesis;
}
inline bool isLeftBracket(Token token) {
  return token.type() == TokenType::left_bracket;
}
inline bool isRightBracket(Token token) {
  return token.type() == TokenType::right_bracket;
}
inline bool isExclamation(Token token) {
  return token.type() == TokenType::exclamation;
}
inline bool isGt(Token token) { return token.type() == TokenType::gt; }
inline bool isQuotationEn(Token token) {
  return token.type() == TokenType::quotation_en;
}
inline bool isStar(Token token) { return token.type() == TokenType::star; }
inline bool isTilde(Token token) { return token.type() == TokenType::tilde; }
inline bool isText(Token token) { return token.type() == TokenType::text; }
inline bool isBackquote(Token token) {
  return token.type() == TokenType::backquote;
}
inline bool isDollar(Token token) { return token.type() == TokenType::dollar; }
}
#endif //MD_TOKEN_H
