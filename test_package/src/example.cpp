#include "markdown/parser/Parser.h"
using namespace md::parser;
int main() {
    auto ret = Parser::parse("# h1");
    return 0;
}
