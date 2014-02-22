#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QStyleFactory>
#include <QPalette>

#include <QFileDialog>
#include <QFileSystemModel>
#include <QPluginLoader>
#include <QPixmap>
#include <QToolBar>
#include <QtCore>
#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QShortcut>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTextEdit>
#include <QTreeView>
#include <QTabWidget>
#include <QMessageBox>

#include "shared.h"
#include "editor/texteditor.h"
#include "editor/highlighter.h"
#include "ui.h"

using namespace std;

class TextEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString currentDir;
    void *newWorkspace(const QString &fileName);
    void newCleanWorkspace();
    TextEditor *currentEditor();
    Highlighter *SyntaxHighlighter;
public slots:
    void newWindow();
    void saveDocument();
    void UpdateHighlightingMode(int FileType);
    void SetColorschemes(int Colorscheme);
    void reloadStyles();
    void rightSidebar(bool checked);
private slots:
    void loadSettings();
    void writeSettings();

    void treeOpenFile(const QModelIndex &index);
    void openDocument();
    void newDocument();

    void closeTab(const int &index);
    void closeActiveTab();
private:
    Ui::MainWindow *ui;

    void setupMenu();
};

#endif // MAINWINDOW_H
