#include "mainwindow.h"
#include "ui.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupMenu();
    loadSettings();

    statusBar()->showMessage(tr("Ready"), 2000);

    SetColorschemes(4);

    connect(ui->tree, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(treeOpenFile(const QModelIndex&)));

    connect(ui->tree, SIGNAL(activated(const QModelIndex&)),
            this, SLOT(treeOpenFile(const QModelIndex&)));

    connect(ui->tabs, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeTab(int)));
}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::writeSettings()
{
    QSettings settings("IDE settings", "Settings");

    // Window Settings
    settings.setValue("Window.Geometry",  geometry());

    int size = settings.beginReadArray("results");
    settings.endArray();
    settings.beginWriteArray("results");
    settings.setArrayIndex(size);
    settings.setValue("result", "qwerty");
    settings.setValue("result1", "qwerty");
    settings.setValue("result2", "qwerty");
    settings.endArray();

    int sizeSettings = settings.beginReadArray("results");
    for(int i=0; i<sizeSettings; ++i)
    {
        settings.setArrayIndex(i);
        qDebug() << settings.value("result").toString();
    }

    settings.beginGroup("projects");
    const QStringList keys = settings.allKeys();
    foreach (const QString &key, keys) {
        QString value = settings.value(key).toString();
        qDebug() << key << value;
    }
    settings.endGroup();

    qDebug() << qApp->applicationDirPath();
}

void MainWindow::loadSettings()
{
    QSettings settings("IDE settings", "Settings");
    setGeometry(settings.value("Window.Geometry",  QRect(150, 150, 800, 400)).toRect());
}

void MainWindow::openDocument()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));

    newWorkspace(fileName);
}

void MainWindow::saveDocument()
{
    currentEditor()->Save();
}

TextEditor* MainWindow::currentEditor()
{
    QWidget* tabItem = ui->tabs->widget(ui->tabs->currentIndex());
    return (TextEditor*)tabItem;
}

void MainWindow::newDocument()
{
    newCleanWorkspace();
}

void MainWindow::newWindow()
{
    MainWindow *window = new MainWindow();
    window->show();
}

void MainWindow::UpdateHighlightingMode(int FileType) {
    SyntaxHighlighter->setLanguage(FileType);

//    switch (FileType) {
//        case 1:  Widgets->PlainText->setChecked  (true); break;
//        case 2:  Widgets->BashScript->setChecked (true); break;
//        case 3:  Widgets->C->setChecked          (true); break;
//        case 4:  Widgets->CSS->setChecked        (true); break;
//        case 5:  Widgets->HTML->setChecked       (true); break;
//        case 6:  Widgets->Java->setChecked       (true); break;
//        case 7:  Widgets->LaTeX->setChecked      (true); break;
//        case 8:  Widgets->Python->setChecked     (true); break;
//        case 9:  Widgets->Vala->setChecked       (true); break;
//        case 10: Widgets->VBasic->setChecked     (true); break;
//    }
}

void MainWindow::setupMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"));

    QAction *newWindowAction = fileMenu->addAction(tr("&New window"));
    newWindowAction->setShortcut(tr("Ctrl+N"));
    connect(newWindowAction, SIGNAL(triggered()), this, SLOT(newWindow()));

    QAction *newAction = fileMenu->addAction(tr("&New"));
    newAction->setShortcut(tr("Ctrl+T"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newDocument()));

    fileMenu->addSeparator();

    QAction *openAction = fileMenu->addAction(tr("&Open"));
    openAction->setShortcut(tr("Ctrl+O"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openDocument()));

    QAction *saveAction = fileMenu->addAction(tr("&Save"));
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveDocument()));

    fileMenu->addSeparator();

    QAction *closeAction = fileMenu->addAction(tr("&Close"));
    closeAction->setShortcut(tr("Ctrl+W"));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(closeActiveTab()));

    QMenu *settingsMenu = new QMenu(tr("&Settings"));

    QAction *reloadThemeAction = settingsMenu->addAction(tr("&Reload theme"));
    reloadThemeAction->setShortcut(tr("Ctrl+R"));
    connect(reloadThemeAction, SIGNAL(triggered()), this, SLOT(reloadStyles()));

    QAction *saveSettings = settingsMenu->addAction(tr("S&ave settings"));
    connect(saveSettings, SIGNAL(triggered()), this, SLOT(writeSettings()));

    QMenu *languageMenu = new QMenu(tr("&Languages"));

    QAction *PlainText  = new QAction(Shared::PlainText,  this);
    QAction *BashScript = new QAction(Shared::BashScript, this);
    QAction *C          = new QAction(Shared::C,          this);
    QAction *CSS        = new QAction(Shared::CSS,        this);
    QAction *HTML       = new QAction(Shared::HTML,       this);
    QAction *Java       = new QAction(Shared::Java,       this);
    QAction *LaTeX      = new QAction(Shared::LaTeX,      this);
    QAction *Python     = new QAction(Shared::Python,     this);
    QAction *Vala       = new QAction(Shared::Vala,       this);
    QAction *VBasic     = new QAction(Shared::VBasic,     this);


    BashScript->setCheckable (true);
    C->setCheckable          (true);
    CSS->setCheckable        (true);
    HTML->setCheckable       (true);
    Java->setCheckable       (true);
    LaTeX->setCheckable      (true);
    Python->setCheckable     (true);
    Vala->setCheckable       (true);
    VBasic->setCheckable     (true);

    QSignalMapper *HighlightSignalMapper = new QSignalMapper(this);
    QObject::connect(PlainText,  SIGNAL(triggered()), HighlightSignalMapper, SLOT(map()));
    QObject::connect(BashScript, SIGNAL(triggered()), HighlightSignalMapper, SLOT(map()));
    QObject::connect(C,          SIGNAL(triggered()), HighlightSignalMapper, SLOT(map()));
    QObject::connect(CSS,        SIGNAL(triggered()), HighlightSignalMapper, SLOT(map()));
    QObject::connect(HTML,       SIGNAL(triggered()), HighlightSignalMapper, SLOT(map()));
    QObject::connect(Java,       SIGNAL(triggered()), HighlightSignalMapper, SLOT(map()));
    QObject::connect(LaTeX,      SIGNAL(triggered()), HighlightSignalMapper, SLOT(map()));
    QObject::connect(Python,     SIGNAL(triggered()), HighlightSignalMapper, SLOT(map()));
    QObject::connect(Vala,       SIGNAL(triggered()), HighlightSignalMapper, SLOT(map()));
    QObject::connect(VBasic,     SIGNAL(triggered()), HighlightSignalMapper, SLOT(map()));

    HighlightSignalMapper->setMapping(PlainText,  1);
    HighlightSignalMapper->setMapping(BashScript, 2);
    HighlightSignalMapper->setMapping(C,          3);
    HighlightSignalMapper->setMapping(CSS,        4);
    HighlightSignalMapper->setMapping(HTML,       5);
    HighlightSignalMapper->setMapping(Java,       6);
    HighlightSignalMapper->setMapping(LaTeX,      7);
    HighlightSignalMapper->setMapping(Python,     8);
    HighlightSignalMapper->setMapping(Vala,       9);
    HighlightSignalMapper->setMapping(VBasic,    10);

//    QActionGroup *HighlightGroup = new QActionGroup(this);
//    HighlightGroup->addAction(PlainText);
//    HighlightGroup->addAction(BashScript);
//    HighlightGroup->addAction(C);
//    HighlightGroup->addAction(CSS);
//    HighlightGroup->addAction(HTML);
//    HighlightGroup->addAction(Java);
//    HighlightGroup->addAction(LaTeX);
//    HighlightGroup->addAction(Python);
//    HighlightGroup->addAction(Vala);
//    HighlightGroup->addAction(VBasic);

    languageMenu->addAction(PlainText);
    languageMenu->addAction(BashScript);
    languageMenu->addAction(C);
    languageMenu->addAction(CSS);
    languageMenu->addAction(HTML);
    languageMenu->addAction(Java);
    languageMenu->addAction(LaTeX);
    languageMenu->addAction(Python);
    languageMenu->addAction(Vala);
    languageMenu->addAction(VBasic);

    // languageMenu->addActions(HighlightGroup);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(settingsMenu);
    menuBar()->addMenu(languageMenu);
}

void MainWindow::reloadStyles()
{
    ui->setupStyle();
}

void MainWindow::treeOpenFile(const QModelIndex& index)
{
    QFileInfo info = ui->tree->model->fileInfo(index);
    QString path = info.filePath();
    QDir dir = QDir(path);
    if (info.isFile()) {
        dir.cdUp();
    };

    currentDir = dir.absolutePath();

    if (info.isFile()) {
        newWorkspace(path);
    }
}

void MainWindow::newCleanWorkspace()
{
    QString name = "Unknown";

    TextEditor *textEdit = new TextEditor;
    textEdit->setProperty("fileName", name);
    int index = ui->tabs->addTab(textEdit, name);
    ui->tabs->setCurrentIndex(index);
}

void *MainWindow::newWorkspace(const QString& fileName)
{
    for(int i = 0; i < ui->tabs->count(); i++) {
        if(fileName == ui->tabs->widget(i)->property("fileName").toString()) {
            ui->tabs->setCurrentIndex(i);
            return 0;
        }
    }

    TextEditor *textEdit = new TextEditor;
    textEdit->OpenFile(fileName);
    SyntaxHighlighter = new Highlighter(textEdit->document());

    UpdateHighlightingMode(textEdit->HighlightByExtension());
    textEdit->setProperty("fileName", fileName);
    int index = ui->tabs->addTab(textEdit, QFileInfo(fileName).fileName());
    ui->tabs->setCurrentIndex(index);
}

void MainWindow::SetColorschemes(int Colorscheme) {
    Shared::Selected_Colorscheme = Colorscheme;
    Shared::SetColorschemes(Shared::Selected_Colorscheme);
}

void MainWindow::closeTab(const int& index)
{
    if (index == -1) {
        return;
    }

    QWidget* tabItem = ui->tabs->widget(index);
    TextEditor* editor = NULL;
    editor = (TextEditor*)tabItem;
    if (editor->closeDocument()) {
        // Removes the tab at position index from this stack of widgets.
        // The page widget itself is not deleted.
        ui->tabs->removeTab(index);

        delete(tabItem);
        tabItem = NULL;
    }
}

void MainWindow::closeActiveTab()
{
    int index = ui->tabs->currentIndex();
    closeTab(index);
}
