//
// Created by pikachu on 2021/1/31.
//

#ifndef MD_DOCUMENT_H
#define MD_DOCUMENT_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>

#include "Token.h"
#include "Visitor.h"
#include "def.h"

namespace md::parser {
enum class NodeType {
  none,
  header,
  paragraph,
  text,
  image,
  link,
  code_block,
  inline_code,
  latex_block,
  inline_latex,
  checkbox,
  checkbox_item,
  ul,
  ul_item,
  ol,
  ol_item,
  hr,
  quote_block,
  italic,
  bold,
  italic_bold,
  strickout,
  table
};
MARKDOWN_PARSER_EXPORT std::ostream& operator<<(std::ostream& os, const NodeType& type);
class MARKDOWN_PARSER_EXPORT Node {
 public:
  explicit Node(NodeType type = NodeType::none) : m_type(type) {}

  virtual void accept(VisitorNode *) = 0;

  NodeType type() { return m_type; }

 protected:
  NodeType m_type;
};

template <typename T>
struct Visitable : public Node {
  void accept(VisitorNode *v) override {
    auto p = dynamic_cast<Visitor<T> *>(v);
    if (p) {
      p->visit(static_cast<T *>(this));
    }
  }
};

using NodePtrList = std::vector<Node *>;

class MARKDOWN_PARSER_EXPORT Container : public Node {
 public:
  Container() = default;

  std::vector<Node *> &children() { return m_children; }

  void appendChild(Node *child) { m_children.push_back(child); }

  [[nodiscard]] auto size() const { return m_children.size(); }
  [[nodiscard]] auto childAt(std::size_t index) { return m_children.at(index); }
 protected:
  std::vector<Node *> m_children;
};

template <typename T>
struct ContainerVisitable : public Container {
  void accept(VisitorNode *v) override {
    if (auto p = dynamic_cast<Visitor<T> *>(v); p) {
      p->visit(static_cast<T *>(this));
    }
  }
};

class MARKDOWN_PARSER_EXPORT Header : public ContainerVisitable<Header> {
 public:
  explicit Header(int level);

  int level() { return m_level; }

 private:
  int m_level;
};

class MARKDOWN_PARSER_EXPORT Paragraph : public ContainerVisitable<Paragraph> {
 public:
  Paragraph() { m_type = NodeType::paragraph; }
};

class MARKDOWN_PARSER_EXPORT CheckboxItem
    : public ContainerVisitable<CheckboxItem> {
 public:
  CheckboxItem() { m_type = NodeType::checkbox_item; }

  [[nodiscard]] bool isChecked() const { return m_checked; }

  void setChecked(bool flag) { m_checked = flag; }

 private:
  bool m_checked{};
};

class MARKDOWN_PARSER_EXPORT CheckboxList
    : public ContainerVisitable<CheckboxList> {
 public:
  CheckboxList() { m_type = NodeType::checkbox; }
};

class MARKDOWN_PARSER_EXPORT UnorderedList
    : public ContainerVisitable<UnorderedList> {
 public:
  UnorderedList() { m_type = NodeType::ul; }
};

class MARKDOWN_PARSER_EXPORT UnorderedListItem
    : public ContainerVisitable<UnorderedListItem> {
 public:
  UnorderedListItem() { m_type = NodeType::ul_item; }
};

class MARKDOWN_PARSER_EXPORT OrderedList
    : public ContainerVisitable<OrderedList> {
 public:
  OrderedList() { m_type = NodeType::ol; }
};

class MARKDOWN_PARSER_EXPORT OrderedListItem
    : public ContainerVisitable<OrderedListItem> {
 public:
  OrderedListItem() { m_type = NodeType::ol_item; }
};

class MARKDOWN_PARSER_EXPORT QuoteBlock
    : public ContainerVisitable<QuoteBlock> {
 public:
  QuoteBlock() { m_type = NodeType::quote_block; }
};

class MARKDOWN_PARSER_EXPORT Text : public Visitable<Text> {
 public:
  explicit Text(StringList str) : m_str(std::move(str)) { m_type = NodeType::text; }

  StringList str() { return m_str; }

  void setStr(StringList str) { m_str = std::move(str); }

 private:
  StringList m_str;
};

class MARKDOWN_PARSER_EXPORT ItalicText : public Visitable<ItalicText> {
 public:
  explicit ItalicText(String str) : m_str(str) { m_type = NodeType::italic; }

  String str() { return m_str; }

  void setStr(String str) { m_str = str; }

 private:
  String m_str;
};

class MARKDOWN_PARSER_EXPORT BoldText : public Visitable<BoldText> {
 public:
  explicit BoldText(String str) : m_str(str) { m_type = NodeType::bold; }

  String str() { return m_str; }

  void setStr(String str) { m_str = str; }

 private:
  String m_str;
};

class MARKDOWN_PARSER_EXPORT ItalicBoldText
    : public Visitable<ItalicBoldText> {
 public:
  explicit ItalicBoldText(String str) : m_str(str) { m_type = NodeType::italic_bold; }

  String str() { return m_str; }

  void setStr(String str) { m_str = str; }

 private:
  String m_str;
};

class MARKDOWN_PARSER_EXPORT StrickoutText : public Visitable<StrickoutText> {
 public:
  explicit StrickoutText(String str) : m_str(str) { m_type = NodeType::strickout; }

  String str() { return m_str; }

  void setStr(String str) { m_str = str; }

 private:
  String m_str;
};

class MARKDOWN_PARSER_EXPORT Image : public Visitable<Image> {
 public:
  Image(Text *alt, Text *src) : m_alt(alt), m_src(src) {
    m_type = NodeType::image;
  }

  Text *alt() { return m_alt; }

  Text *src() { return m_src; }

 private:
  Text *m_alt;
  Text *m_src;
};

class MARKDOWN_PARSER_EXPORT Link : public Visitable<Link> {
 public:
  Link(Text *content, Text *href) : m_content(content), m_href(href) {
    m_type = NodeType::link;
  }

  Text *content() { return m_content; }

  Text *href() { return m_href; }

 private:
  Text *m_content;
  Text *m_href;
};

class MARKDOWN_PARSER_EXPORT CodeBlock : public Visitable<CodeBlock> {
 public:
  CodeBlock(Text *name, Text *code) : m_name(name), m_code(code) {
    m_type = NodeType::code_block;
  }

  Text *name() { return m_name; }

  Text *code() { return m_code; }

 private:
  Text *m_name;
  Text *m_code;
};

class MARKDOWN_PARSER_EXPORT LatexBlock : public Visitable<LatexBlock> {
 public:
  explicit LatexBlock(Text *code) : m_code(code) {
    m_type = NodeType::latex_block;
  }

  Text *code() { return m_code; }

 private:
  Text *m_code;
};

class MARKDOWN_PARSER_EXPORT Hr : public Visitable<Hr> {
 public:
  Hr() { m_type = NodeType::hr; }
};

class MARKDOWN_PARSER_EXPORT InlineCode : public Visitable<InlineCode> {
 public:
  explicit InlineCode(Text *code) : m_code(code) { m_type = NodeType::inline_code; }

  Text *code() { return m_code; }

 private:
  Text *m_code;
};

class MARKDOWN_PARSER_EXPORT InlineLatex : public Visitable<InlineLatex> {
 public:
  explicit InlineLatex(Text *code) : m_code(code) {
    m_type = NodeType::inline_latex;
  }

  Text *code() { return m_code; }

 private:
  Text *m_code;
};

class MARKDOWN_PARSER_EXPORT Table : public Visitable<Table> {
 public:
  Table() { m_type = NodeType::table; }

  void appendRow(const StringList &row) { m_content.push_back(row); }

  void setHeader(const StringList &header) { m_header = header; }

  StringList &header() { return m_header; }

  std::vector<StringList> &content() { return m_content; }

 private:
  StringList m_header;
  std::vector<StringList> m_content;
};

class MARKDOWN_PARSER_EXPORT Document {
 public:
  explicit Document(String str);

  void accept(VisitorNode *visitor);

  NodePtrList children();

 protected:
  NodePtrList m_nodes;
};
}  // namespace md::parser

#endif  // MD_DOCUMENT_H
