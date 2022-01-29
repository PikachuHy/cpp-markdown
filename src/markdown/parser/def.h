//
// Created by pikachu on 1/29/2022.
//

#ifndef MARKDOWNPARSER_DEF_H
#define MARKDOWNPARSER_DEF_H
#include <string_view>
#include <vector>
#ifdef MarkdownParser_LIBRARY
#define MARKDOWN_PARSER_EXPORT __declspec(dllexport)
#else
#define MARKDOWN_PARSER_EXPORT __declspec(dllimport)
#endif
namespace md::parser {
    using String = std::string_view;
    using StringList = std::vector<std::string_view>;
}
#endif //MARKDOWNPARSER_DEF_H
