find_package(magic_enum REQUIRED)
add_library(MarkdownParser SHARED)
target_link_libraries(MarkdownParser PRIVATE magic_enum::magic_enum)
target_compile_definitions(MarkdownParser PRIVATE -DMarkdownParser_LIBRARY)
target_include_directories(MarkdownParser PUBLIC .)
target_sources(MarkdownParser PRIVATE
        markdown/parser/Parser.cpp
        markdown/parser/Parser.h
        markdown/parser/Document.cpp
        markdown/parser/Document.h
        markdown/parser/Token.cpp
        markdown/parser/Token.h
        markdown/parser/Visitor.cpp
        markdown/parser/Visitor.h
        )
set(PUBLIC_HEADER_FILES
        markdown/parser/def.h
        markdown/parser/Parser.h
        markdown/parser/Document.h
        markdown/parser/Token.h
        markdown/parser/Visitor.h
        )
set_target_properties(MarkdownParser PROPERTIES
        PUBLIC_HEADER "${PUBLIC_HEADER_FILES}"
        )
install(TARGETS MarkdownParser DESTINATION "."
        PUBLIC_HEADER DESTINATION include/markdown/parser
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )