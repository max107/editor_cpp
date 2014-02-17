#include "application.h"

Application::Application (int & argc, char **argv) : QApplication(argc, argv) {
    // Setup the name, version and icon of the application
    setApplicationName("Textpad Editor");
    setApplicationVersion("0.8.1");
    setWindowIcon(QIcon(":/Icons/Resources/Icons/48x48/TextpadEditor.png"));

    // Prepare a string that will be used to determine the arguments that where passed to the program
    QString Arguments;

    // Declare a new MainWindow
    mainWindow = new MainWindow;

    // Load the geometry settings
    QSettings Settings("Textpad Editor", "WindowData");
    mainWindow->setGeometry(Settings.value("Window.Geometry",  QRect(150, 150, 800, 400)).toRect());

    // Check that we actually received arguments
    if (argc != 1) {
        // Convert the received arguments to a string
        for (int i = 0; i < argc; i++)
            Arguments = argv[i];

        // Remove the "--args" argument in Mac OS X
        if (Shared::CheckOS() == "Mac")
            Arguments.replace("--args", "");

        // Do nothing if we receive this argument (mainly used in Linux)
        if (Arguments == "%U") {
            Arguments.clear();
            return;
        }

        // Open a file (or create one) with the name specified in the arguments
        else {
            mainWindow->newCleanWorkspace();
            // mainWindow->TextEdit->OpenFile(Arguments);
            return;
        }
    }

    // Setup the first MainWindow
    mainWindow->newWindow();
}

Application::~Application() {

}

void Application::LoadFile(const QString &Filename) {
    // Check that the file specified exists
    if  (!Filename.isEmpty()) {
        // Check if we need to open the file in a new window or not
        qDebug() << "filename open";
//        if (mainWindow->TextEdit->Filename.isEmpty() && !mainWindow->TextEdit->document()->isModified())
//            mainWindow->TextEdit->OpenFile(Filename);
//        else {
//            // Open the file in a new window
//            MainWindow *NewWindow = new MainWindow();
//            NewWindow->TextEdit->OpenFile(Filename);

//            // Make sure that the NewWindow connects with all the other instanced of MainWindow
//            mainWindow->CreateNewWindow(NewWindow);
//        }
    }
}

bool Application::event(QEvent *Event) {
    switch (Event->type()) {
    case QEvent::FileOpen:
        LoadFile(static_cast<QFileOpenEvent *>(Event)->file());
        return true;
        break;
    default:
        return QApplication::event(Event);
    }
}
