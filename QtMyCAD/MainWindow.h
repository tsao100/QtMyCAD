#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QSplitter>
#include <QMdiArea>
#include <QApplication>
#include <QTabWidget>
#include <QMdiSubWindow>
#include <QOpenGLWidget>
#include <QVBoxLayout>
#include "OpenGLWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QTextEdit* commandWindow;
    QMdiArea* mdiArea;
    QSplitter* splitter;
    OpenGLWidget* openGLWidget;
    OpenGLWidget* openGLWidget2;
};

#endif // MAINWINDOW_H
