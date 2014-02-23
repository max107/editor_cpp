#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "math.h"

#include <iostream>
#include <string>
#include <algorithm>

#include <QDebug>
#include <QApplication>

#include <QVector>
#include <QMap>
#include <QScrollBar>
#include <QAbstractItemView>
#include <QStringListModel>
#include <QCompleter>
#include <QTextBlock>
#include <QPainter>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QPlainTextEdit>

#include "shared.h"

class TextEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = 0);
    QString Filename;
    int documentNumber;

    int       Start;
    int       End;
    long long Size;
    long long Counter;

    QMap<QChar, QTextCursor> brackets;

    QTextCharFormat bracketMismatchFormat;
    QTextCharFormat bracketMatchFormat;

    int tabStopCount;
    bool tabsAsSpaces;
    void setTabsAsSpaces(bool value);

    // Extra widgets
    QWidget     *LineCountArea;

    // Public line count functions
    int  LineNumberAreaWidth();
    void LineNumberAreaPaintEvent(QPaintEvent *event);
    void setTabSize(const int tabStop = 4);

    // Autocomplete
    int minCompleterLength;
    QStringList getWords();
    void autoIndentNewLine();
    int getIndentPosition(QString &str);
    QString rstrip(const QString &str);
    void insertSmartTab();
    void goToLine(int lineNumber);
    void smartText(QKeyEvent *e);
    void validateAndHighlightBrackets(const QChar &openStr, const QChar &closeStr);
public slots:
    // Saving functions
    bool MaybeSave();
    bool Save();
    bool SaveAs();
    bool SaveFile(const QString FileLocation);

    // File functions
    void OpenFile(const QString FileLocation);
    void SetupFile();
    bool closeDocument();
    void UpdateDocumentStatus();

    // Syntax highlighter functions
    int HighlightByExtension();
    void Highlight_Current_Line();

    // Line count functions
    void UpdateLineNumberArea(const QRect &, int);
    void UpdateLineNumberAreaWidth(int NewBlockCount);

    // Other functions
    int CountWords();
    QString CalculateSize();

    void updateCompleterModel();
    void bracketValidate();
signals:
    void requestUpdateTitle();

protected:
    // Used for line count
    void resizeEvent(QResizeEvent *event);

    // Used for multiline identation
    void keyPressEvent(QKeyEvent *e);
    void focusInEvent(QFocusEvent *e);

private:
    // Autocompletion
    QCompleter *c;
    QStringListModel *completerModel;
    QString textUnderCursor() const;

private slots:
    void insertCompletion(const QString &completion);
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(TextEditor *editor) : QWidget(editor)
    {
        TextEdit = editor;
    }

    QSize sizeHint() const
    {
        return QSize(TextEdit->LineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
        TextEdit->LineNumberAreaPaintEvent(event);
    }

private:
    TextEditor *TextEdit;
};

#endif
