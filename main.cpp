#include "application.h"

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}

int main(int argc, char *argv[]) {
    Application Textpad(argc, argv);

    // Decide if there is another instance of Textpad already running
    QSharedMemory SharedMemory("Textpad Editor (textpad-editor)");

    // There isn't another instance of Textpad runnning
    if (SharedMemory.create(1) && SharedMemory.error() != QSharedMemory::AlreadyExists)
        return Textpad.exec();

    // There is already an instance of Textpad running
    else
    {
        if (SharedMemory.attach())
            return Textpad.exec();

        else {
            // Something wicked happened and QSharedMemory could not attach the process...
            Textpad.mainWindow->hide();
            QMessageBox MessageBox;
            MessageBox.setWindowTitle("Warning");
            MessageBox.setText("<b>There is another instance of Textpad already running</b>");
            MessageBox.setInformativeText("We tried to do some magic, but we failed,"
                                          "would you like to open a new instance?");
            MessageBox.setStandardButtons(QMessageBox::Open | QMessageBox::Close);
            MessageBox.setIcon(QMessageBox::Warning);
            int Return = MessageBox.exec();

            if (Return == QMessageBox::Open) {
                Textpad.mainWindow->show();
                return Textpad.exec();
            }
        }
    }

    return 0;
}
