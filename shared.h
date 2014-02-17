#ifndef SHARED_H
#define SHARED_H

#include <QDebug>
#include <QString>
#include <QColor>

class Shared
{
public:
    Shared();

    /// Settings
    static bool Line_Count;
    static bool Highlight_Current_Line;
    static char  Selected_Colorscheme;

    static QString CheckOS();
    static void SetColorschemes(char _Selected_Colorscheme);

    /// Colorschemes
    static QColor Background;
    static QColor Comments;
    static QColor Foreground;
    static QColor Functions;
    static QColor HighlightLineBackground;
    static QColor HighlightLineForeground;
    static QColor Keywords;
    static QColor Numbers;
    static QColor OtherColor;
    static QColor Quotations;
    static QColor SelectedTextBackground;
    static QColor SelectedTextForeground;
    static QColor LineCountBackgroundColor;
    static QColor LineCountForegroundColor;

    /// Highlight Mode menu
    static QString HighlightMode;
    static QString PlainText;
    static QString BashScript;
    static QString C;
    static QString CSS;
    static QString HTML;
    static QString Java;
    static QString LaTeX;
    static QString Python;
    static QString Vala;
    static QString VBasic;

    /// File menu
    static QString File;
    static QString New;
    static QString Open;
    static QString Save;
    static QString SaveAs;
    static QString Print;
    static QString Close;
    static QString Quit;

    /// Other strings
    static QString Untitled;
    static QString Words;
    static QString Length;
    static QString Lines;
    static QString SaveChangesToDocument;
    static QString YourChangesWillBeLost;
    static QString AreYouSure;
    static QString YouErasedAllContent;
    static QString Error;
    static QString CannotWriteFile;
    static QString CannotReadFile;
    static QString HelpText;
    static QString RestartApp;
};

#endif // SHARED_H
