#include "texteditor.h"

TextEditor::TextEditor(QWidget *parent): QPlainTextEdit(parent) {
    connect(this, SIGNAL(textChanged()),            this, SLOT(UpdateDocumentStatus()));

    LineCountArea = new LineNumberArea(this);
    connect(this, SIGNAL(blockCountChanged(int)),   this, SLOT(UpdateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(UpdateLineNumberArea(QRect,int)));
    UpdateLineNumberAreaWidth(0);

//    connect(this, SIGNAL(cursorPositionChanged()),
//            this, SLOT(Highlight_Current_Line()));
    connect(this, SIGNAL(cursorPositionChanged()),
            this, SLOT(bracketValidate()));

    setFont(QFont("Monaco", 12));

    setTabSize(4);

    Size = 0;
    Counter = 0;
    Start = 0;
    End = 0;

    // Setup autocomplete
    minCompleterLength = 1;

    c = new QCompleter(this);
//            c->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    c->setWrapAround(false);
    c->setWidget(this);
    c->popup()->setObjectName("autocomplete");

    completerModel = new QStringListModel(getWords(), c);
    c->setModel(completerModel);

    connect(this, SIGNAL(textChanged()),
            this, SLOT(updateCompleterModel()));

    QTextOption option = document()->defaultTextOption();

    bool on = false;
    if (on) {
        option.setFlags(option.flags() | QTextOption::ShowTabsAndSpaces);
    } else {
        option.setFlags(option.flags() & ~QTextOption::ShowTabsAndSpaces);
    }
    option.setFlags(option.flags() | QTextOption::AddSpaceForLineAndParagraphSeparators);
    document()->setDefaultTextOption(option);

    setTabsAsSpaces(true);

    bracketMismatchFormat = currentCharFormat();
    bracketMismatchFormat.setBackground(QColor(255, 223, 223));

    bracketMatchFormat = currentCharFormat();
    bracketMatchFormat.setBackground(QColor(158, 209, 255));
}

void TextEditor::bracketValidate()
{
    validateAndHighlightBrackets('(', ')');
    validateAndHighlightBrackets('{', '}');
    validateAndHighlightBrackets('[', ']');
}

void TextEditor::validateAndHighlightBrackets(const QChar &openStr, const QChar &closeStr)
{
    QTextDocument * doc = document();

    if(!brackets.contains(openStr)) {
        brackets[openStr] = QTextCursor();
    }
    if(!brackets.contains(closeStr)) {
        brackets[closeStr] = QTextCursor();
    }

    QTextCursor bracketBeginCursor = brackets[openStr];
    QTextCursor bracketEndCursor = brackets[closeStr];

    if (!bracketBeginCursor.isNull() || !bracketEndCursor.isNull()) {
        bracketBeginCursor.setCharFormat(QTextCharFormat());
        bracketEndCursor.setCharFormat(QTextCharFormat());
        bracketBeginCursor = bracketEndCursor = QTextCursor();
    }

    QTextCursor cursor = textCursor();

    int position = cursor.position();

    bool forward;
    QChar begin, end;

    if (doc->characterAt(position) == openStr || doc->characterAt(position - 1) == openStr ||
        doc->characterAt(position - 1) == closeStr || doc->characterAt(position) == closeStr) {

        forward = doc->characterAt(position) == openStr || doc->characterAt(position - 1) == openStr;

        if (forward) {
            if(doc->characterAt(position) == openStr) {
                position++;
            } else {
                cursor.setPosition(position - 1);
            }
            begin = openStr;
            end = closeStr;
        } else {
            if(doc->characterAt(position) == closeStr) {
                cursor.setPosition(position + 1);
                position -= 1;
            } else {
                position -= 2;
            }
            begin = closeStr;
            end = openStr;
        }

        bracketBeginCursor = QTextCursor(cursor);
        bracketBeginCursor.movePosition(forward ? QTextCursor::NextCharacter : QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);

        QTextCharFormat format = bracketMismatchFormat;

        int braceDepth = 1;

        QChar c;
        while (!(c = doc->characterAt(position)).isNull()) {
            if (c == begin) {
                braceDepth++;
            } else if (c == end) {
                braceDepth--;

                if (!braceDepth) {
                    bracketEndCursor = QTextCursor(doc);
                    bracketEndCursor.setPosition(position);
                    bracketEndCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
                    bracketEndCursor.setCharFormat(bracketMatchFormat);

                    format = bracketMatchFormat;

                    break;
                }
            }
            forward ? position++ : position--;
        }
        bracketBeginCursor.setCharFormat(format);
    }
    brackets[openStr] = bracketBeginCursor;
    brackets[closeStr] = bracketEndCursor;
}

void TextEditor::setTabsAsSpaces(bool value)
{
    tabsAsSpaces = value;
}

void TextEditor::updateCompleterModel()
{
    completerModel->setStringList(getWords());
}

bool TextEditor::closeDocument()
{
    if (document()->isModified()) {
        if (Filename.isEmpty()) {
            int Return;
            setDocumentTitle(Shared::Untitled + QString::number(documentNumber));

            QMessageBox MessageBox;
            MessageBox.setText(Shared::SaveChangesToDocument.arg(documentTitle()));
            MessageBox.setInformativeText(Shared::YourChangesWillBeLost);
            MessageBox.setWindowTitle(" ");
            MessageBox.setIconPixmap(QPixmap(":/Icons/Resources/Icons/48x48/TextpadEditor.png"));
            MessageBox.setStandardButtons(QMessageBox::Discard | QMessageBox::Cancel | QMessageBox::Save);
            Return = MessageBox.exec();

            if (Return == QMessageBox::Cancel) {
                return false;
            } else if (Return == QMessageBox::Save) {
                return Save();
            } else {
                return true;
            }
        } else {
            int Return;
            setDocumentTitle(Shared::Untitled + QString::number(documentNumber));

            QMessageBox MessageBox;
            MessageBox.setText(Shared::SaveChangesToDocument.arg(documentTitle()));
            MessageBox.setInformativeText(Shared::YourChangesWillBeLost);
            MessageBox.setWindowTitle(" ");
            MessageBox.setIconPixmap(QPixmap(":/Icons/Resources/Icons/48x48/TextpadEditor.png"));
            MessageBox.setStandardButtons(QMessageBox::Discard | QMessageBox::Cancel | QMessageBox::Save);
            Return = MessageBox.exec();

            if (Return == QMessageBox::Cancel) {
                return false;
            } else if (Return == QMessageBox::Save) {
                return Save();
            } else {
                return true;
            }
        }
    } else {
        return true;
    }
}

bool TextEditor::MaybeSave() {
    if (document()->isModified()) {
        if (Filename.isEmpty()) {
            int Return;
            setDocumentTitle(Shared::Untitled + QString::number(documentNumber));

            QMessageBox MessageBox;
            MessageBox.setText(Shared::SaveChangesToDocument.arg(documentTitle()));
            MessageBox.setInformativeText(Shared::YourChangesWillBeLost);
            MessageBox.setWindowTitle(" ");
            MessageBox.setIconPixmap(QPixmap(":/Icons/Resources/Icons/48x48/TextpadEditor.png"));
            MessageBox.setStandardButtons(QMessageBox::Discard | QMessageBox::Cancel | QMessageBox::Save);
            Return = MessageBox.exec();

            if      (Return == QMessageBox::Cancel)  return false;
            else if (Return == QMessageBox::Save)    return Save();
        }

        else
            if (toPlainText().isEmpty()) {
                int Return;

                QMessageBox MessageBox;
                MessageBox.setText(Shared::AreYouSure);
                MessageBox.setInformativeText(Shared::YouErasedAllContent);
                MessageBox.setWindowTitle(" ");
                MessageBox.setIconPixmap(QPixmap(":/Icons/Resources/Icons/48x48/TextpadEditor.png"));
                MessageBox.setStandardButtons(QMessageBox::Discard | QMessageBox::Cancel | QMessageBox::Save);
                MessageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
                Return = MessageBox.exec();

                if (Return == QMessageBox::Cancel)
                    return false;
                if (Return == QMessageBox::Discard)
                    return true;
            }

            else
                return Save();
    }
    return true;
}

void TextEditor::OpenFile(const QString FileLocation) {
    qApp->setOverrideCursor(Qt::WaitCursor);
    if  (!FileLocation.isEmpty()) {
        QFile File(FileLocation);

        if (File.open(QFile::ReadOnly | QFile::WriteOnly | QFile::ReadWrite)) {
            QTextStream InputFile(&File);
            InputFile.setCodec("UTF-8");
            setPlainText(InputFile.readAll());

            QObject::connect(c, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));

            File.close();
            Filename = FileLocation;
            SetupFile();

            qApp->restoreOverrideCursor();
            return;
        }

        QMessageBox::warning(this, Shared::Error,
                             Shared::CannotReadFile.arg(FileLocation).arg(File.errorString()));

        qApp->restoreOverrideCursor();
        return;
    }
    qApp->restoreOverrideCursor();
}

void TextEditor::SetupFile()
{
    document()->setModified(false);
    HighlightByExtension();

    setDocumentTitle(QFileInfo(Filename).fileName());
    // requestUpdateTitle();
}

bool TextEditor::Save() {
    if (Filename.isEmpty()) {
        return SaveAs();
    } else if (!Filename.isEmpty()) {
        return SaveFile(Filename);
    }
    return false;
}

bool TextEditor::SaveAs() {
    return SaveFile(QFileDialog::getSaveFileName(this, Shared::SaveAs, QDir::homePath()));
}

bool TextEditor::SaveFile(const QString FileLocation) {
    if  (!FileLocation.isEmpty()) {
        QFile File(FileLocation);
        if (File.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qApp->setOverrideCursor(Qt::WaitCursor);
            File.write(document()->toPlainText().toUtf8());
            File.close();
            Filename = File.fileName();
            SetupFile();
            qApp->restoreOverrideCursor();
            return true;
        }

        QMessageBox::warning(this, Shared::Error,
                             Shared::CannotWriteFile.arg(FileLocation).arg(File.errorString()));
    }
    return false;
}

void TextEditor::setTabSize(const int tabStop)
{
    QFontMetrics metrics(font());
    tabStopCount = tabStop;
    setTabStopWidth(tabStop * metrics.width(' '));
}

int TextEditor::CountWords() {
    // This is a very precise way of counting words, but it can consume lot of CPU and RAM on large files
    if (toPlainText().length() > 10000) {
        return toPlainText().split(QRegExp("(\\s|\\n|\\r)+"), QString::SkipEmptyParts).count();
    }

    // This method is not very precise, but it does not consume too much CPU and RAM
    {
        QString text = toPlainText();
        if (text.length() < Size) {
            Size = 0;
            Counter = 0;
            Start = 0;
            End = 0;
        }

        if (text.length() - Size == 1) {
            if (text.length() == 1) {
                if(!text.at(0).isSpace()) {
                    Counter++;
                }
            }

            if (text.length() > 2) {
                Start = text.length() - 1;
                End = text.length();

                if (text.at(Start - 1).isSpace() && !text.at(End - 1).isSpace()) {
                    Counter++;
                }
            }
        } else if (text.length() - Size > 1) {
            Counter = 0;
            if (!text.at(0).isSpace()) {
                Counter++;
            }

            for (int i = 1; i < text.length(); i++) {
                if(!text.at(i).isSpace() && text.at(i-1).isSpace()) {
                    Counter++;
                }
            }
        }

        Size = text.length();
        return Counter;
    }
}

QString TextEditor::CalculateSize() {
    float Length = toPlainText().length();
    QString UnitString;

    if  ((Length >= 0) & (Length < 1024)) {
        UnitString = " bytes";
    } else if  ((Length > 1024) & (Length < 1048576)) {
        Length /= 1024;
        UnitString = " KB";
    } else if  ((Length > 1048576)) {
        Length /= 1048576;
        UnitString = " MB";
    }

    float RoundedLength = floorf(Length * 100 + 0.5) / 100;

    return QString::number(RoundedLength) + UnitString;
}

void TextEditor::UpdateDocumentStatus() {
    QString LengthString    = Shared::Length + ": " + CalculateSize();
    QString LineCountString = Shared::Lines  + ": " + QString::number(document()->blockCount());
    QString WordCountString = Shared::Words  + ": " + QString::number(CountWords());
}

QString TextEditor::rstrip(const QString& str) {
    int n = str.size() - 1;
    for (; n >= 0; --n) {
        if (!str.at(n).isSpace()) {
            return str.left(n + 1);
        }
    }
    return "";
}

int TextEditor::getIndentPosition(QString & str)
{
    QString tab = QString('\t');

    int indent = 0;
    QString trimmed = rstrip(str);
    if(trimmed.size() == 0) {
        indent = str.size();
    } else {
        for (int i = 0; str.size() - 1 >= i; i++) {
            bool isTab = str.at(i) == tab;
            if (!str.at(i).isSpace()) {
                break;
            }
            if(isTab) {
                indent += tabStopCount;
            } else {
                indent++;
            }
        }
    }
    return indent;
}

void TextEditor::autoIndentNewLine()
{
    QTextCursor cursor = textCursor();
    QString text = cursor.block().text();
    int indent = getIndentPosition(text);

    QString tab;
    if (tabsAsSpaces) {
        tab = QString(' ');
    } else {
        tab = QString('\t');
    }

    cursor.beginEditBlock();
    cursor.insertBlock();
    for (; indent > 0; --indent) {
        cursor.insertText(tab);
    }
    cursor.endEditBlock();
}

void TextEditor::insertSmartTab()
{
    QString tab;
    if (tabsAsSpaces) {
        tab = QString(' ');
    } else {
        tab = QString('\t');
    }

    QTextCursor cursor = textCursor();
    cursor.beginEditBlock();
    int indent = tabStopCount;
    for (; indent > 0; --indent) {
        cursor.insertText(tab);
    }
    cursor.endEditBlock();
}

void TextEditor::goToLine(int lineNumber)
{
    QTextCursor cursor(document()->findBlockByLineNumber(lineNumber - 1));
    cursor.select(QTextCursor::LineUnderCursor);
    setTextCursor(cursor);
    cursor.clearSelection();

    /*
    QTextBlock text_block = central_widget_TextDocument->findBlockByLineNumber(line_number - 1);
    QTextCursor text_cursor = central_widget_TextEdit->textCursor ();
    text_cursor.setPosition (text_block.position());
    central_widget_TextEdit->setFocus();
    text_cursor.select(QTextCursor::LineUnderCursor);
    central_widget_TextEdit->setTextCursor(text_cursor);
    */
}

bool TextEditor::NextCharacterIs(QTextCursor & cursor, const QString & str)
{
    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    return cursor.selectedText() == str;
}

void TextEditor::smartText(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Tab) {
        e->accept();
        insertSmartTab();
        return;
    }

    // Smart indent
    if (e->key() == Qt::Key_Return) {
        e->accept();
        autoIndentNewLine();
        return;
    }

    QTextCursor cursor = textCursor();
    int position = cursor.position();

    if(e->key() == Qt::Key_ParenRight && NextCharacterIs(cursor, ")")) {
        cursor.setPosition(position + 1);
        setTextCursor(cursor);
        return;
    }

    if (e->key() == Qt::Key_ParenLeft) {
        cursor.insertText(")");
        cursor.setPosition(position);
        setTextCursor(cursor);
    }

    if(e->key() == Qt::Key_BracketRight && NextCharacterIs(cursor, "]")) {
        cursor.setPosition(position + 1);
        setTextCursor(cursor);
        return;
    }

    if (e->key() == Qt::Key_BracketLeft) {
        cursor.insertText("]");
        cursor.setPosition(position);
        setTextCursor(cursor);
    }

    if(e->key() == Qt::Key_BraceRight && NextCharacterIs(cursor, "}")) {
        cursor.setPosition(position + 1);
        setTextCursor(cursor);
        return;
    }

    if (e->key() == Qt::Key_BraceLeft) {
        cursor.insertText("}");
        cursor.setPosition(position);
        setTextCursor(cursor);
    }

    if(e->key() == Qt::Key_QuoteDbl && NextCharacterIs(cursor, "\"")) {
        cursor.setPosition(position + 1);
        setTextCursor(cursor);
        return;
    }

    if (e->key() == Qt::Key_QuoteDbl) {
        cursor.insertText("\"");
        cursor.setPosition(position);
        setTextCursor(cursor);
    }

    if(e->key() == Qt::Key_Apostrophe && NextCharacterIs(cursor, "'")) {
        cursor.setPosition(position + 1);
        setTextCursor(cursor);
        return;
    }

    if (e->key() == Qt::Key_Apostrophe) {
        cursor.insertText("'");
        cursor.setPosition(position);
        setTextCursor(cursor);
    }

    QPlainTextEdit::keyPressEvent(e);
}

void TextEditor::keyPressEvent(QKeyEvent *e) {
    if (c && c->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
    if (!c || !isShortcut) { // do not process the shortcut when we have a completer
        smartText(e);
    }

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!c || (ctrlOrShift && e->text().isEmpty())) {
        return;
    }

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();
    if (!isShortcut && (hasModifier || e->text().isEmpty() || completionPrefix.length() < minCompleterLength
                      || eow.contains(e->text().right(1)))) {
        c->popup()->hide();
        return;
    }

    if (completionPrefix != c->completionPrefix()) {
        c->setCompletionPrefix(completionPrefix);
        c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0) + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr); // popup it up!

//    QString DocumentTitle = documentTitle();



    // QPlainTextEdit::keyPressEvent(e);

    // setDocumentTitle(DocumentTitle);
}

std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

QStringList TextEditor::getWords()
{
    QString text = toPlainText();

    char chars[] = "#.,!()[]'<>:/{}_|=+;`";
    for (unsigned int i = 0; i < strlen(chars); ++i) {
        text = text.replace(chars[i], " ");
    }

    QStringList words = text.split(QRegExp("(\\s|\\n|\\r)+"), QString::SkipEmptyParts).toSet().toList();

    foreach (QString str, words) {
        if(str == textUnderCursor()) {
            words.removeAt(words.indexOf(str));
        }
    }

    return words;
}

void TextEditor::insertCompletion(const QString& completion)
{
    if (c->widget() != this) {
        return;
    }

    QTextCursor tc = textCursor();
    int extra = completion.length() - c->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

QString TextEditor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}


void TextEditor::focusInEvent(QFocusEvent *e)
{
    if (c) {
        c->setWidget(this);
    }
    QPlainTextEdit::focusInEvent(e);
}
