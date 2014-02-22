#include "../highlighter.h"

void Highlighter::setLaTeX() {
    // Keywords
    KeywordPatterns << "\\\\section"           << "\\\\item"              << "\\\\subsection" << "\\\\subsubsection"
                    << "\\\\chapter"           << "\\\\begin"             << "\\\\end"        << "\\\\usepackage" <<"\\\\document"
                    << "\\\\cite"              << "\\\\upcite"            << "\\\\ref"        << "\\\\label"      <<"\\\\caption"
                    << "\\\\hline"             << "\\\\cline"             << "\\\\toprule"    << "\\\\bottomrule" <<"\\\\\\\\"
                    << "\\{flalign\\}"         << "\\&"                   << "\\\\;"
                    << "\\{subarray\\}"        << "\\{equation\\}"        << "\\{cases\\}"    << "\\{array\\}"
                    << "\\\\bibliographystyle" << "\\\\title"             << "\\\\footnote"   << "\\\\includegraphics"
                    << "\\\\centering"         << "\\\\vspace"            << "\\\\scriptsize"
                    << "\\\\bibitem"           << "\\{thebibliography\\}" << "\\{abstract\\}";

    // Comments
    CommentEndExpressionString = "\\";
    CommentStartExpressionString = "\\";
    FunctionsString = "\\b[A-Za-z0-9_]+ (?=\\ ()";
    SingleLineComment = "\%[^\n]*";
}
