#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    // Override mouse event handlers to manage cursor visibility
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    void drawPrimitives(); // Method to draw basic primitives
};

#endif // OPENGLWIDGET_H
