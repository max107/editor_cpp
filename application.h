#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include "mainwindow.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char **argv);
    MainWindow *mainWindow;
    virtual ~Application();

protected:
    bool event(QEvent *Event);

private:
    void LoadFile(const QString &Filename);

};

#endif // APPLICATION_H
