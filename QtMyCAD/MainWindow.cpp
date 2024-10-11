#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    // Create the main vertical splitter
    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal, this);

    // Create the horizontal splitter for Property window and MDI Area
    QSplitter* verticalSplitter = new QSplitter(Qt::Vertical, mainSplitter);

    // Property Window in the west (left) position
    QPlainTextEdit* propertyWindow = new QPlainTextEdit(this);
    propertyWindow->setPlaceholderText("Property Window");

    commandWindow = new QPlainTextEdit(this);
    //commandWindow->setPlaceholderText("Command Window");
    commandWindow->setReadOnly(true);
    commandWindow->setUndoRedoEnabled(false);
    commandWindow->appendPlainText("command:"); // Ready for new commands

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

    // Create the dockable window
    createDockableWindow();
    connect(commandTextEdit, &QTextEdit::textChanged, this, &MainWindow::handleCommandInput);
    connect(openGLWidget, &OpenGLWidget::pointPicked, this, &MainWindow::handlePointPicked);
    connect(openGLWidget2, &OpenGLWidget::pointPicked, this, &MainWindow::handlePointPicked);
    connect(openGLWidget, &OpenGLWidget::repeatLineCommand, this, &MainWindow::repeatLineCommand);
}

MainWindow::~MainWindow() {
}

void MainWindow::createDockableWindow()
{
    // Create a dock widget
    dockableWindow = new QDockWidget(tr("Command and Logs"), this);
    dockableWindow->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // Create a splitter to split the command and logs vertically
    CMDsplitter = new QSplitter(Qt::Vertical, dockableWindow);

    // Add tabs: Command and Logs
    commandTextEdit = new QTextEdit();
    commandTextEdit->setPlaceholderText("Enter command here...");

    logsTextEdit = new QTextEdit();
    logsTextEdit->setReadOnly(true);
    logsTextEdit->setPlainText("Logs will appear here...");

    // Add the command and logs windows to the splitter
    CMDsplitter->addWidget(logsTextEdit);
    CMDsplitter->addWidget(commandTextEdit);

    // Set the QTabWidget as the main widget for the dock
    dockableWindow->setWidget(CMDsplitter);

    // Add the dock widget to the main window at the bottom
    addDockWidget(Qt::BottomDockWidgetArea, dockableWindow);

}
