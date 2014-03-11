#include "../highlighter.h"

void Highlighter::setCSS() {
    // Keywords
    {
        KeywordPatterns.clear();

        // Load the file that contains all the keywords of this language
        QFile File(":/resources/syntax/keywords/css");
        File.open(QIODevice::ReadOnly);
        QTextStream TextStream(&File);

        // Read each line of the file and append it to the KeywordPatterns list
        while (!TextStream.atEnd()) {
            QString Line = "\\b";
            Line.append(TextStream.readLine());
            Line.append("\\b");
            KeywordPatterns.append(Line);
        }

        File.close();
    }

    // Comments
    CommentEndExpressionString = "\\*/";
    CommentStartExpressionString = "/\\*";
    SingleLineComment = "\\";

    // There are no functions in CSS
    FunctionsString = "\\";
}
