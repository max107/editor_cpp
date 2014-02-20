#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QAction>
#include <QDirModel>
#include <QTreeView>
#include <QWidget>
#include <QTreeWidgetItem>

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView( QWidget *parent = 0 );
    void setPath(const QString &path);
    QDirModel *model;

signals:

public slots:

    void newFolder();
    void deleteFileOrFolder();
    void newFile();
    void copyPathToClipboard();
};

#endif // TREEVIEW_H
