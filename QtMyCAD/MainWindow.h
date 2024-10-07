#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QDockWidget>
#include <QSplitter>
#include <QMdiArea>
#include <QApplication>
#include <QTabWidget>
#include <QTabBar.h>
#include <QMdiSubWindow>
#include <QOpenGLWidget>
#include <QVBoxLayout>
#include "OpenGLWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    // Create the dockable window
    void createDockableWindow();

private:
    QDockWidget* dockableWindow;
    QSplitter* CMDsplitter;

    QPlainTextEdit* commandWindow;
    QMdiArea* mdiArea;
    QSplitter* splitter;
    OpenGLWidget* openGLWidget;
    OpenGLWidget* openGLWidget2;
};

#endif // MAINWINDOW_H
