#ifndef PROJECTSLIST_H
#define PROJECTSLIST_H

#include <QStandardItem>
#include <QStandardItemModel>
#include <QListView>

class ProjectsList : public QListView
{
    Q_OBJECT
public:
    ProjectsList ( QWidget *parent = 0 );

signals:

public slots:

};

#endif // PROJECTSLIST_H
