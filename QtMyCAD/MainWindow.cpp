#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    // Create the main vertical splitter
    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal, this);

    // Create the horizontal splitter for Property window and MDI Area
    QSplitter* verticalSplitter = new QSplitter(Qt::Vertical, mainSplitter);

    // Property Window in the west (left) position
    QTextEdit* propertyWindow = new QTextEdit(this);
    propertyWindow->setPlaceholderText("Property Window");

    commandWindow = new QTextEdit(this);
    commandWindow->setPlaceholderText("Command Window");

    mdiArea = new QMdiArea(this);

    // Configure MDI Area to use tabs for subwindows
    mdiArea->setViewMode(QMdiArea::TabbedView);   // Enable tabbed view
    auto tab = mdiArea->findChild<QTabBar*>();
    if (tab) {
        tab->setTabsClosable(true);
        // The tabs might be very wide
        tab->setExpanding(false);
    }
    mdiArea->setTabsClosable(true);               // Add close buttons to tabs
    mdiArea->setTabsMovable(true);                // Allow reordering of tabs
    mdiArea->setTabShape(QTabWidget::Triangular);    // Set rounded tabs, could also be 'QTabWidget::Triangular'
    mdiArea->setTabPosition(QTabWidget::South);
    openGLWidget = new OpenGLWidget();
    openGLWidget2 = new OpenGLWidget();

    mdiArea->setWindowTitle("OpenGL Windows");
    mdiArea->addSubWindow(openGLWidget);
    mdiArea->addSubWindow(openGLWidget2);

    openGLWidget->setWindowTitle("1");
    openGLWidget2->setWindowTitle("2");

    mainSplitter->addWidget(propertyWindow);
    mainSplitter->addWidget(verticalSplitter);
    // Add the horizontal splitter and command window to the main splitter
    verticalSplitter->addWidget(mdiArea);
    verticalSplitter->addWidget(commandWindow);

    setCentralWidget(mainSplitter);

    setWindowTitle("QtMyCAD");
    resize(800, 600);
}

MainWindow::~MainWindow() {
}
