#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class calculator;
}

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit calculator(QWidget *parent = 0);
    ~calculator();

private:
    Ui::calculator *ui;

    double first_number;
    bool is_second_number = false;

private slots:
    void number_pressed();
    void unary_operate_pressed();
    void binary_operate_pressed();
    void on_pushButton_dot_released();
    void on_pushButton_c_released();
    void on_pushButton_equal_released();
};

#endif // CALCULATOR_H
