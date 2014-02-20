#include "projectslist.h"

ProjectsList::ProjectsList( QWidget *parent )
: QListView( parent )
{
    // Disable outline on Mac OS
    setAttribute(Qt::WA_MacShowFocusRect, false);

    QStandardItem* Items = new QStandardItem("myString");
    QStandardItemModel* ListModel = new QStandardItemModel();
    ListModel->appendRow(Items);

    setModel(ListModel);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
}
