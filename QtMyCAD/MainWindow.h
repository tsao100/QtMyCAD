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
    void keyPressEvent(QKeyEvent* event) override {
        if (event->key() == Qt::Key_Space) {
            repeatLineCommand();  // Space bar triggers repeat of "line" command
        }
    }

private slots:
    void handleCommandInput() {
        QString command = commandTextEdit->toPlainText().trimmed();

        if (command == "line") {
            logsTextEdit->append("line command received. Point 1:");
            commandTextEdit->clear();
            isLineCommand = true;
            waitForPoint1 = true;
        }
    }

    void handlePointPicked(const QPointF& point) {
        if (isLineCommand) {
            if (waitForPoint1) {
                openGLWidget->setPoint1(point);
                logsTextEdit->append(QString("Point 1: (%1, %2)").arg(point.x()).arg(point.y()));
                logsTextEdit->append("Point 2:");
                waitForPoint1 = false;
            }
            else {
                openGLWidget->setPoint2(point);
                logsTextEdit->append(QString("Point 2: (%1, %2)").arg(point.x()).arg(point.y()));
                logsTextEdit->append("Line drawn.");
                commandTextEdit->clear();  // Ready for new commands
                isLineCommand = false;
            }
        }
    }

    // Slot to handle repeating the line command
    void repeatLineCommand() {
        logsTextEdit->append("Repeating line command. Point 1:");
        isLineCommand = true;
        waitForPoint1 = true;
    }

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton && isLineCommand) {
            if (waitForPoint1) {
                // Map the global click position to the OpenGL widget
                QPointF point1 = openGLWidget->mapFromGlobal(event->globalPos());
                openGLWidget->setPoint1(point1);
                logsTextEdit->append(QString("Point 1: (%1, %2)").arg(point1.x()).arg(point1.y()));
                logsTextEdit->append("Point 2:");
                waitForPoint1 = false;  // Now wait for point 2
            }
            else {
                QPointF point2 = openGLWidget->mapFromGlobal(event->globalPos());
                openGLWidget->setPoint2(point2);
                logsTextEdit->append(QString("Point 2: (%1, %2)").arg(point2.x()).arg(point2.y()));
                logsTextEdit->append("Line drawn.");
                commandTextEdit->clear();  // Ready for new commands
                isLineCommand = false;  // Reset for next command
            }
        }
    }

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
