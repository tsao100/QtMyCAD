#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QDockWidget>
#include <QSplitter>
#include <QMdiArea>
#include <QMouseEvent>
#include <QApplication>
#include <QTabWidget>
#include <QTabBar.h>
#include <QMdiSubWindow>
#include <QOpenGLWidget>
#include <QVBoxLayout>
#include "OpenGLWidget.h"
#include <QShortcut>
#include <QString>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    // Create the dockable window
    void createDockableWindow();

protected:
    // Override key press event to handle space bar press
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void handleCommandInput();

    void handlePointPicked(const QPointF& point);

    // Slot to handle repeating the line command
    void repeatLineCommand();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QDockWidget* dockableWindow;
    QSplitter* CMDsplitter;
    QTextEdit* commandTextEdit;
    QTextEdit* logsTextEdit;

    QPlainTextEdit* commandWindow;
    QMdiArea* mdiArea;
    QSplitter* splitter;
    OpenGLWidget* openGLWidget;
    OpenGLWidget* openGLWidget2;

    bool isLineCommand = false;
    bool waitForPoint1 = false;
};

#endif // MAINWINDOW_H
