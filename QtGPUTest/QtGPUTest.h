#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGPUTest.h"

class QtGPUTest : public QMainWindow
{
    Q_OBJECT

public:
    QtGPUTest(QWidget *parent = nullptr);
    ~QtGPUTest();

private:
    Ui::QtGPUTestClass ui;
};
