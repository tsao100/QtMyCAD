#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TIM.h"

class TIM : public QMainWindow
{
    Q_OBJECT

public:
    TIM(QWidget *parent = nullptr);
    ~TIM();

private:
    Ui::TIMClass ui;
};
