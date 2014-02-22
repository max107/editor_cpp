#include "../highlighter.h"

void Highlighter::setBash() {
    // Keywords
    KeywordPatterns << "\\bsudo\\b" << "\\bthen\\b"  << "\\bcd\\b"    << "\\bif\\b"
                    << "\\bfi\\b"   << "\\bwhile\\b" << "\\bwait\\b"  << "\\bexit\\b"
                    << "\\bfor\\b"  << "\\bdo\\b";

    // There are no multiline comments in bash
    CommentEndExpressionString   = "\\";
    CommentStartExpressionString = "\\";

    // Functions
    FunctionsString              = "\\b[A-Za-z0-9_]+ (?=\\ ()\\b";

    // Comments
    SingleLineComment            = "#[^\n]*";
}
