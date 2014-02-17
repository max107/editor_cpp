#ifndef LINENUMBERS_H
#define LINENUMBERS_H

#include <QWidget>
#include "texteditor.h"

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

#endif // LINENUMBERS_H
