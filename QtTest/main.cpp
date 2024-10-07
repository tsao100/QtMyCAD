#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QComboBox>

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        // Create a toolbar
        QToolBar* toolbar = addToolBar("Main Toolbar");

        // Create a combobox
        QComboBox* comboBox = new QComboBox();
        comboBox->addItem("Option 1");
        comboBox->addItem("Option 2");
        comboBox->addItem("Option 3");

        // Add the combobox to the toolbar
        toolbar->addWidget(comboBox);

        // Set the window title
        setWindowTitle("ComboBox in Toolbar Example");
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Create and show the main window
    MainWindow mainWindow;
    mainWindow.resize(400, 300);  // Set initial window size
    mainWindow.show();

    return app.exec();
}
