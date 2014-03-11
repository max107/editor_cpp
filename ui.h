#ifndef UI_H
#define UI_H

#include <QTreeWidgetItem>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSplitter>

QT_BEGIN_NAMESPACE

class UiMainWindow
{
public:
    QWidget *central;
    QVBoxLayout *layout;

    QMenuBar *menuBar;
    QStatusBar *statusBar;

    QTreeView *tree;
    QFileSystemModel *treeModel;

    QTabWidget *tabs;
    QTabWidget *sidebarTabs;
    QSplitter *split;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty()) {
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        }
        //specify a new font.
        // QFont newFont("Lucida Grande", 12, QFont::Normal, false);
        //set font of application
        // QApplication::setFont(newFont);
        MainWindow->setMinimumSize(350, 200);

        MainWindow->resize(720, 460);
        // MainWindow->setStyleSheet(QStringLiteral(""));

        setupMenuBar(MainWindow);
        setupStatusBar(MainWindow);
        setupSidebarTabs(MainWindow);
        setupTabs(MainWindow);
        setupTree("/Volumes/mac/Users/max/test/");

        split = new QSplitter;
        split->addWidget(sidebarTabs);
        split->addWidget(tabs);
        split->setStretchFactor(0, 0);
        split->setStretchFactor(1, 1);
        split->setStretchFactor(2, 0);
        split->setObjectName("split");
        split->setAccessibleName("split");

        // TODO plugins
        addSidebarTab(tree, "/Volumes/mac/Users/max/Desktop/upload2.png",
                      QApplication::translate("Tree", "Tree", 0));

        central = new QWidget;
        layout = new QVBoxLayout;
        layout->addWidget(split);
        // Remove margins
        layout->setContentsMargins(0,0,0,0);
        central->setLayout(layout);
        MainWindow->setCentralWidget(central);

        // setupDarkTheme();
        setupStyle();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void addSidebarTab(QWidget *widget, const QString & iconPath, const QString & name)
    {
        sidebarTabs->addTab(widget, rotateIcon(iconPath), name);
    }

    QIcon rotateIcon(const QString & iconSrc)
    {
        QIcon *icon = new QIcon(iconSrc);
        QSize sz;
        for (int var = 0; var < icon->availableSizes().count(); ++var) {
            if (icon->availableSizes().at(var).width() > sz.width()) {
                sz = icon->availableSizes().at(var);
            }
        }
        QPixmap pix = icon->pixmap(sz);
        QTransform trans;
        trans.rotate(+90);
        pix = pix.transformed(trans);

        return QIcon(pix);
    }

    void setupTree(const QString &path)
    {
        treeModel = new QFileSystemModel;
        // model->setRootPath(QDir::currentPath());
        treeModel->setRootPath(path);
        tree = new QTreeView;
        tree->setObjectName("tree");
        tree->setAccessibleName("tree");
        // Disable outline
        tree->setAttribute(Qt::WA_MacShowFocusRect, false);

        tree->setModel(treeModel);
        tree->setRootIndex(treeModel->index(path));

        tree->header()->hide();
        tree->hideColumn(1);
        tree->hideColumn(2);
        tree->hideColumn(3);
    }

    void setupSidebarTabs(QMainWindow *MainWindow)
    {
        sidebarTabs = new QTabWidget;
        sidebarTabs->setObjectName("sidebarTabs");
        sidebarTabs->setAccessibleName("sidebarTabs");
        sidebarTabs->setTabPosition(QTabWidget::West);
    }

    void setupTabs(QMainWindow *MainWindow)
    {
        tabs = new QTabWidget;
        tabs->setObjectName("tabs");
        tabs->setAccessibleName("tabs");
        tabs->setTabsClosable(true);
    }

    void setupMenuBar(QMainWindow *MainWindow)
    {
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 718, 22));
        MainWindow->setMenuBar(menuBar);
    }

    void setupStatusBar(QMainWindow *MainWindow)
    {
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setAccessibleName("statusBar");
        MainWindow->setStatusBar(statusBar);
    }

    void setupStyle()
    {
        QFile styleFile("d:\\projects\\editor_cpp\\data\\style.css");
        // QFile styleFile("/Volumes/mac/Users/max/test/data/style.css");
        if (styleFile.open(QIODevice::ReadOnly)) {
            QByteArray bytes = styleFile.readAll();
            // QApplication *app = (QApplication*)QApplication::instance();
            qApp->setStyleSheet(bytes);
        } else {
            qDebug() << "File not found or not readable";
        }
    }

    void setupDarkTheme()
    {
        qApp->setStyle(QStyleFactory::create("fusion"));
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(53,53,53));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(15,15,15));
        palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(53,53,53));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);

        palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
        palette.setColor(QPalette::HighlightedText, Qt::black);
        qApp->setPalette(palette);
    }

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public UiMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H
