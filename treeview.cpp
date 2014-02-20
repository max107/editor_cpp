#include "treeview.h"

TreeView::TreeView( QWidget *parent )
: QTreeView( parent )
{
    // Disable outline on Mac OS
    setAttribute(Qt::WA_MacShowFocusRect, false);

    setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction* newFile = new QAction("New file", this);
    connect(newFile, SIGNAL(triggered()), this, SLOT(newFile()));
    addAction(newFile);

    QAction* newFolder = new QAction("New folder", this);
    connect(newFolder, SIGNAL(triggered()), this, SLOT(newFolder()));
    addAction(newFolder);

    QAction* deleteItem = new QAction("Delete", this);
    connect(deleteItem, SIGNAL(triggered()), this, SLOT(deleteFileOrFolder()));
    addAction(deleteItem);

    QAction* copyPath = new QAction("Copy path", this);
    connect(copyPath, SIGNAL(triggered()), this, SLOT(copyPathToClipboard()));
    addAction(copyPath);

    model = new QDirModel(this);
    model->setReadOnly(false);
    // Setup sort criteria
    // directory first, ignore case,
    // and sort by name
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    model->setFilter(QDir::Dirs | QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot);
    setModel(model);

    setHeaderHidden(true);

    // Fix double click event
    // setSelectionMode( QAbstractItemView::SingleSelection );
    setExpandsOnDoubleClick(true);
    setEditTriggers(QAbstractItemView::EditKeyPressed);
    // setEditTriggers(QAbstractItemView::NoEditTriggers);

//    connect(this, SIGNAL(activated(QModelIndex)),
//            this, SLOT(toggle(const QModelIndex &)));
}

void TreeView::copyPathToClipboard()
{
    QModelIndex index = currentIndex();
    if (!index.isValid()) {
        return;
    }

    QClipboard *cb = qApp->clipboard();
    cb->setText(model->fileInfo(index).absoluteFilePath());
}

void TreeView::setPath(const QString &path)
{
    // model->setRootPath(QDir::currentPath());
    // Set initial selection
    QModelIndex index = model->index(path);

    // Set initial view of directory
    // for the selected drive as expanded
    expand(index);

    // Make it scroll to the selected
    // scrollTo(index);

    // Highlight the selected
    setCurrentIndex(index);

    // Resizing the column - first column
    resizeColumnToContents(0);

    setRootIndex(index);
}

void TreeView::newFile()
{
    // Make directory
    QModelIndex index = currentIndex();
    if(!index.isValid()) {
        return;
    }

    QString name  = QInputDialog::getText(this, "Name", "Enter a file name");

    if(name.isEmpty()) {
        return;
    }

    QFileInfo info = model->fileInfo(index);

    QDir dir;
    // If current item in tree is a file
    if(!info.isDir()) {
        // Get parent directory from file
        dir = info.dir();
    } else {
        // Else get current absolute dir path
        dir = QDir(info.absoluteFilePath());
    }

    // Merge dir path with entered user path and cd into dir
    QFileInfo newFile = QFileInfo(QDir::cleanPath(dir.path() + QDir::separator() + name));

    // if path not exists
    if(!newFile.exists()) {
        QFile File(newFile.absoluteFilePath());
        if (File.open(QIODevice::WriteOnly | QIODevice::Text)) {
            File.close();

            // refresh tree
            model->refresh();
        }
    }
}

void TreeView::deleteFileOrFolder()
{
    // Delete directory

    // Get the current selection
    QModelIndex index = currentIndex();
    if(!index.isValid()) {
        return;
    }

    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "title", "Delete?", QMessageBox::Yes|QMessageBox::No).exec())
    {
        QFileInfo info = model->fileInfo(index);
        if(info.isDir()) {
            // directory
            QDir dir(info.absoluteFilePath());
            dir.removeRecursively();
            model->refresh();

            // Remove single directory
            // model->rmdir(index);
        } else {
            // file
            model->remove(index);
        }
    }
}

void TreeView::newFolder()
{
    // Make directory
    QModelIndex index = currentIndex();
    if(!index.isValid()) {
        return;
    }

    QString name  = QInputDialog::getText(this, "Name", "Enter a directory name");

    if(name.isEmpty()) {
        return;
    }

    // For single folder. test1/test2/test3 not supported
    // model->mkdir(index, name);

    // For mkpath like logic. test1/test2/test3 supported
    QFileInfo info = model->fileInfo(index);

    QDir dir;
    // If current item in tree is a file
    if(!info.isDir()) {
        // Get parent directory from file
        dir = info.dir();
    } else {
        // Else get current absolute dir path
        dir = QDir(info.absoluteFilePath());
    }

    // Merge dir path with entered user path and cd into dir
    QDir newDir = QDir(QDir::cleanPath(dir.path() + QDir::separator() + name));

    // if path not exists
    if(!newDir.exists()) {
        // create current dir|dirs
        newDir.mkpath(QString('.'));

        // refresh tree
        model->refresh();
    }
}
