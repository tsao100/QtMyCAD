#include "OpenGLWidget.h"
#include <GL/glu.h> // You may need to install or link GLU depending on your system

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent), 
point1Set(false), point2Set(false) {
}

OpenGLWidget::~OpenGLWidget() {
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color

    // Enable depth testing to handle overlapping 3D objects
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glLoadIdentity();
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // Simple orthogonal projection

    ////glMatrixMode(GL_MODELVIEW);
    ////glLoadIdentity();
    //// Set the camera viewpoint using gluLookAt
    //gluLookAt(
    //    0.0, 0.0, 1.0,  // Camera position (x, y, z)
    //    0.0, 0.0, 0.0,  // Look-at point (center of the scene)
    //    0.0, 0.0, 1.0   // Up direction (positive Y axis)
    //);

    // Draw primitives
    //drawPrimitives();
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    // Set up the projection matrix (Perspective or Orthographic)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Use a perspective projection
    //gluPerspective(45.0, 1.33, 0.1, 100.0);

    // Switch back to the model-view matrix
    glMatrixMode(GL_MODELVIEW);
}

void OpenGLWidget::enterEvent(QEvent* event)
{
    Q_UNUSED(event); // Avoid unused parameter warning
    setCursor(Qt::CrossCursor); // Set cursor to visible (default)
}

void OpenGLWidget::leaveEvent(QEvent* event)
{
    Q_UNUSED(event); // Avoid unused parameter warning
    setCursor(Qt::CrossCursor); // Set cursor to visible (default)
}

void OpenGLWidget::drawPrimitives()
{
    // Set up some colors
    GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat green[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    GLfloat blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };

    // Draw a red triangle
    glColor3fv(red);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.8f, -0.5f);
    glVertex2f(0.0f, 0.8f);
    glVertex2f(0.8f, -0.5f);
    glEnd();

    // Draw a green line
    glColor3fv(green);
    glBegin(GL_LINES);
    glVertex2f(-0.9f, -0.9f);
    glVertex2f(0.9f, 0.9f);
    glEnd();

    // Draw a blue point
    glColor3fv(blue);
    glPointSize(10.0f);  // Set point size
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glEnd();
}

void OpenGLWidget::setPoint1(const QPointF& pt) {
    point1 = pt;
    point1Set = true;
}

void OpenGLWidget::setPoint2(const QPointF& pt) {
    point2 = pt;
    point2Set = true;
    lines.push_back({ point1, point2 });  // Store the line
    update();  // Trigger repaint to draw the line
}

void OpenGLWidget::paintEvent(QPaintEvent* event) {
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

void OpenGLWidget::mousePressEvent(QMouseEvent* event)  {
    if (event->button() == Qt::LeftButton) {
        emit pointPicked(event->pos());  // Emit signal when a point is picked
    }
    else if (event->button() == Qt::RightButton) {
        emit repeatLineCommand();  // Right click triggers repeat of "line" command
    }
}




