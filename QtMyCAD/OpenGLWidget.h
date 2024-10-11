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
    void setPoint1(const QPointF& pt) {
        point1 = pt;
        point1Set = true;
    }

    // Set point 2
    void setPoint2(const QPointF& pt) {
        point2 = pt;
        point2Set = true;
        lines.push_back({ point1, point2 });  // Store the line
        update();  // Trigger repaint to draw the line
    }



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
    void paintEvent(QPaintEvent* event) override {
        QOpenGLWidget::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Set the pen color to white for visibility against the black background
        QPen pen(Qt::white);
        pen.setWidth(2);  // Set line width (optional)
        painter.setPen(pen);

        // Draw all lines stored in the vector
        for (const Line& line : lines) {
            painter.drawLine(line.start, line.end);
        }
    }

    // Capture mouse click event to pick points
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            emit pointPicked(event->pos());  // Emit signal when a point is picked
        }
        else if (event->button() == Qt::RightButton) {
            emit repeatLineCommand();  // Right click triggers repeat of "line" command
        }
    }

signals:
    void pointPicked(const QPointF& point);
    void repeatLineCommand();

private:
    QPointF point1, point2;
    bool point1Set, point2Set;

    std::vector<Line> lines;  // Vector to store lines
};

#endif // OPENGLWIDGET_H
