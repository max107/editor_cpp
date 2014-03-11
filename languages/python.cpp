#include "../highlighter.h"

void Highlighter::setPython() {
    // Keywords
    {
        KeywordPatterns.clear();

        // Load the file that contains all the keywords of this language
        QFile File("::/resources/syntax/keywords/python");
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


    // There are no multiline comments in Python
    CommentEndExpressionString = "\\";
    CommentStartExpressionString = "\\";

    // Functions
    FunctionsString = "\\b[A-Za-z0-9_]+ (?=\\ ()\\b";

    // Comments
    SingleLineComment = "#[^\n]*";
}
