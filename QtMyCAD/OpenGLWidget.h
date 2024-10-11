#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QPainter>
#include <QMouseEvent>

// Define a structure to hold a line (start and end points)
struct Line {
    QPointF start;
    QPointF end;
};

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();
    // Set point 1
    void setPoint1(const QPointF& pt);

    // Set point 2
    void setPoint2(const QPointF& pt);



protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    // Override mouse event handlers to manage cursor visibility
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    void drawPrimitives(); // Method to draw basic primitives

protected:
    void paintEvent(QPaintEvent* event) override;

    // Capture mouse click event to pick points
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void pointPicked(const QPointF& point);
    void repeatLineCommand();

private:
    QPointF point1, point2;
    bool point1Set, point2Set;

    std::vector<Line> lines;  // Vector to store lines
};

#endif // OPENGLWIDGET_H
