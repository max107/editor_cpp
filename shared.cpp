#include "shared.h"

/// Settings
bool Shared::Line_Count             = true;
bool Shared::Highlight_Current_Line = true;
char Shared::Selected_Colorscheme = 0;

/// Initialize QColors used for colorschemes
QColor Shared::Background               ;
QColor Shared::Comments                 ;
QColor Shared::Foreground               ;
QColor Shared::Functions                ;
QColor Shared::HighlightLineBackground  ;
QColor Shared::HighlightLineForeground  ;
QColor Shared::Keywords                 ;
QColor Shared::Numbers                  ;
QColor Shared::OtherColor               ;
QColor Shared::Quotations               ;
QColor Shared::SelectedTextBackground   ;
QColor Shared::SelectedTextForeground   ;
QColor Shared::LineCountBackgroundColor ;
QColor Shared::LineCountForegroundColor ;

// File menu
QString Shared::File   = "&" + QObject::tr("File");
QString Shared::New    = QObject::tr("New");
QString Shared::Open   = QObject::tr("Open") + "...";
QString Shared::Save   = QObject::tr("Save");
QString Shared::SaveAs = QObject::tr("Save as") + "...";
QString Shared::Print  = QObject::tr("Print") + "...";
QString Shared::Close  = QObject::tr("Close this document");
QString Shared::Quit   = QObject::tr("Quit");

// Highlight Mode menu
QString Shared::HighlightMode = QObject::tr("Highlighting mode");
QString Shared::PlainText = QObject::tr("Plain text");
QString Shared::BashScript = "Bash";
QString Shared::C = "C/C++";
QString Shared::CSS = "CSS";
QString Shared::HTML = "HTML";
QString Shared::Java = "Java";
QString Shared::LaTeX = "LaTeX";
QString Shared::Python = "Python";
QString Shared::Vala = "Vala";
QString Shared::VBasic = "Visual Basic";

// Other strings
QString Shared::Untitled              = QObject::tr("Untitled") + " ";
QString Shared::Words                 = QObject::tr("Words");
QString Shared::Length                = QObject::tr("Length");
QString Shared::Lines                 = QObject::tr("Lines");
QString Shared::SaveChangesToDocument = "<b>" + QObject::tr("Do you want to save the changes made to document '%1'?") + "</b>";
QString Shared::YourChangesWillBeLost = QObject::tr("Your changes will be lost if you don't save them.");
QString Shared::AreYouSure            = "<b>" + QObject::tr("Are you sure you want to do this?") + "</b>";
QString Shared::YouErasedAllContent   = QObject::tr("You have erased all content on this document, saving it could be fatal!");
QString Shared::Error                 = QObject::tr("Error");
QString Shared::CannotWriteFile       = QObject::tr("Cannot write file") + " %1:\n%2";
QString Shared::CannotReadFile        = QObject::tr("Cannot read file")  + " %1:\n%2";
QString Shared::RestartApp            = QObject::tr("The language change will take effect after a restart of Textpad.");
QString Shared::HelpText              = QObject::tr("<p><h2>To use Textpad, you need to be able to:</h2></p><hr>"
                                    "<ul>"
                                    "<li>Use a mouse and/or trackpad.</li>"
                                    "<li>To read and understand a text.</li>"
                                    "<li>Know how to use a keyboard.</li>"
                                    "<li>Use common sense.</li>"
                                    "<li>Pay attention when saving files "
                                    "(don't blame me for not knowing where you put your files).</li>"
                                    "<li>Click the <i>Report bug</i> menu if you find a bug, "
                                    "this will help me make Textpad better and more stable.</li>"
                                    "</ul>"
                                    "<hr>"
                                    "<p><b>That's all!</b></p>"
                                    "<p>If you are willing to write a manual with all the features of Textpad, "
                                    "please do it and <a href = 'mailto:alex_sr97@outlook.com'>send it to my email</a> "
                                    "(please provide your name or nickname so that I can give credit for your work).</p>");

Shared::Shared()
{
}

QString Shared::CheckOS()
{
    // Get the current operating system
#ifdef Q_OS_MAC
    return "Mac";
#endif
#ifdef Q_OS_LINUX
    return "Linux";
#endif
#ifdef Q_OS_WIN32
    return "Windows";
#endif
}

void Shared::SetColorschemes(char Selected_Colorscheme) {
    switch (Selected_Colorscheme)
    {
    case 1:
        // Default
        Background.setRgb               (254, 254, 254);
        Comments.setRgb                 ( 29, 112,   0);
        Foreground.setRgb               ( 41,  40,  39);
        Functions.setRgb                ( 38,   0, 114);
        HighlightLineBackground.setRgb  (232, 242, 254);
        Keywords.setRgb                 (108,   0,   0);
        Numbers.setRgb                  ( 38,   0, 114);
        OtherColor.setRgb               (109, 109, 109);
        Quotations.setRgb               (192,  94,   0);
        SelectedTextBackground.setRgb   (210, 220, 248);
        SelectedTextForeground.setRgb   ( 41,  40,  39);
        LineCountBackgroundColor.setRgb (240, 240, 240);
        LineCountForegroundColor.setRgb (140, 140, 140);
        break;
    case 2:
        // Cobalt
        Background.setRgb               (  0,  27,  51);
        Comments.setRgb                 (  0, 136, 255);
        Foreground.setRgb               (255, 255, 255);
        Functions.setRgb                (255, 157,   6);
        HighlightLineBackground.setRgb  (  0,  59, 112);
        Keywords.setRgb                 (255, 157,   6);
        Numbers.setRgb                  (255,   0,  68);
        OtherColor.setRgb               (255,   0,  68);
        Quotations.setRgb               ( 58, 217,   0);
        SelectedTextBackground.setRgb   (  0, 136, 255);
        SelectedTextForeground.setRgb   (255, 255, 255);
        LineCountBackgroundColor.setRgb (  0,  20,  44);
        LineCountForegroundColor.setRgb (  0, 101, 191);
        break;
    case 3:
        // Grayscale
        Background.setRgb               (255, 255, 255);
        Comments.setRgb                 (150, 150, 150);
        Foreground.setRgb               ( 45,  45,  45);
        Functions.setRgb                ( 45,  45,  45);
        HighlightLineBackground.setRgb  (232, 232, 232);
        Keywords.setRgb                 ( 45,  45,  45);
        Numbers.setRgb                  (145, 145, 145);
        OtherColor.setRgb               (145, 145, 145);
        Quotations.setRgb               (145, 145, 145);
        SelectedTextBackground.setRgb   (210, 210, 210);
        SelectedTextForeground.setRgb   ( 45,  45,  45);
        LineCountBackgroundColor.setRgb (245, 245, 245);
        LineCountForegroundColor.setRgb (140, 140, 140);
        break;
    case 4:
        // Kate
        Background.setRgb               (255, 255, 255);
        Comments.setRgb                 (128, 128, 128);
        Foreground.setRgb               (  0,   0,   0);
        Functions.setRgb                (  0,  87, 174);
        HighlightLineBackground.setRgb  (238, 246, 255);
        Keywords.setRgb                 (  0,  87, 174);
        Numbers.setRgb                  (176, 126,   0);
        OtherColor.setRgb               (  0,  87, 174);
        Quotations.setRgb               (221,   0,   0);
        SelectedTextBackground.setRgb   ( 67, 172, 232);
        SelectedTextForeground.setRgb   (255, 255, 255);
        LineCountBackgroundColor.setRgb (255, 255, 255);
        // LineCountBackgroundColor.setRgb (235, 235, 235);
        LineCountForegroundColor.setRgb (105, 105, 105);
        break;
    case 5:
        // Oblivion
        Background.setRgb               ( 46,  52,  54);
        Comments.setRgb                 (136, 138, 133);
        Foreground.setRgb               (211, 215, 207);
        Functions.setRgb                (206,  92,   0);
        HighlightLineBackground.setRgb  ( 85,  87,  83);
        Keywords.setRgb                 (138, 226,  52);
        Numbers.setRgb                  (237, 212,   0);
        OtherColor.setRgb               (206,  92,   0);
        Quotations.setRgb               (237, 212,   0);
        SelectedTextBackground.setRgb   (136, 138, 133);
        SelectedTextForeground.setRgb   (238, 238, 236);
        LineCountBackgroundColor.setRgb ( 40,  42,  44);
        LineCountForegroundColor.setRgb (111, 115, 107);
        break;
    case 6:
        // Tango
        Background.setRgb               (255, 255, 255);
        Comments.setRgb                 ( 32,  74, 135);
        Foreground.setRgb               (109, 109, 111);
        Functions.setRgb                (164,   0,   0);
        HighlightLineBackground.setRgb  (238, 238, 236);
        Keywords.setRgb                 (164,   0,   0);
        Numbers.setRgb                  (173, 127, 168);
        OtherColor.setRgb               ( 78, 154,   6);
        Quotations.setRgb               (173, 127, 168);
        SelectedTextBackground.setRgb   ( 67, 172, 232);
        SelectedTextForeground.setRgb   (255, 255, 255);
        LineCountBackgroundColor.setRgb (240, 240, 240);
        LineCountForegroundColor.setRgb (140, 140, 140);
        break;
    }
}
