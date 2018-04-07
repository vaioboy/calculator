#include "calculator.h"
#include "ui_calculator.h"

calculator::calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::calculator)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(number_pressed()));

    connect(ui->pushButton_sign, SIGNAL(released()), this, SLOT(unary_operate_pressed()));
    connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(unary_operate_pressed()));

    connect(ui->pushButton_add, SIGNAL(released()), this, SLOT(binary_operate_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operate_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(binary_operate_pressed()));
    connect(ui->pushButton_devide, SIGNAL(released()), this, SLOT(binary_operate_pressed()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_devide->setCheckable(true);
}

calculator::~calculator()
{
    delete ui;
}

void calculator::number_pressed()
{
    QPushButton *button = (QPushButton *)sender();
    double label_number;
    QString number_string;
    if((ui->pushButton_add->isChecked() || ui->pushButton_minus->isChecked() ||
            ui->pushButton_multiply->isChecked() || ui->pushButton_devide->isChecked()) && (!is_second_number))
    {
        label_number = button->text().toDouble();
        number_string = QString::number(label_number, 'g', 15);
        is_second_number = true;
    }
    else
    {
        if(ui->label->text().contains(".") && button->text() == "0")
        {
            number_string = ui->label->text() + "0";
        }
        else
        {
            label_number = (ui->label->text() + button->text()).toDouble();
            number_string = QString::number(label_number, 'g', 15);
        }
    }
    ui->label->setText(number_string);
}

void calculator::unary_operate_pressed()
{
    QPushButton *button = (QPushButton *)sender();
    double label_number;
    if(button->text() == "+/-")
    {
        label_number = ui->label->text().toDouble() * -1;
    }
    else
    {
        label_number = ui->label->text().toDouble() * 0.01;
    }
    QString number_string = QString::number(label_number, 'g', 15);
    ui->label->setText(number_string);
}

void calculator::on_pushButton_dot_released()
{
    QString number_string = ui->label->text();
    if((ui->pushButton_add->isChecked() || ui->pushButton_minus->isChecked() ||
            ui->pushButton_multiply->isChecked() || ui->pushButton_devide->isChecked()) && (!is_second_number))
    {
        ui->label->setText("0.");
        is_second_number = true;
    }
    else if(!number_string.contains("."))
    {
        ui->label->setText(number_string + ".");
    }
}

void calculator::on_pushButton_c_released()
{
    ui->pushButton_add->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_devide->setChecked(false);
    ui->label->setText("0");
}

void calculator::binary_operate_pressed()
{
    QPushButton *button = (QPushButton *)sender();
    first_number = ui->label->text().toDouble();
    button->setChecked(true);
}

void calculator::on_pushButton_equal_released()
{
    double label_number, second_number;
    second_number = ui->label->text().toDouble();
    QString number_string;
    if(ui->pushButton_add->isChecked())
    {
        label_number = first_number + second_number;
        number_string = QString::number(label_number);
        ui->label->setText(number_string);
        ui->pushButton_add->setChecked(false);
    }
    else if(ui->pushButton_minus->isChecked())
    {
        label_number = first_number - second_number;
        number_string = QString::number(label_number);
        ui->label->setText(number_string);
        ui->pushButton_minus->setChecked(false);
    }
    else if(ui->pushButton_multiply->isChecked())
    {
        label_number = first_number * second_number;
        number_string = QString::number(label_number);
        ui->label->setText(number_string);
        ui->pushButton_multiply->setChecked(false);
    }
    else if(ui->pushButton_devide->isChecked())
    {
        label_number = first_number / second_number;
        number_string = QString::number(label_number);
        ui->label->setText(number_string);
        ui->pushButton_devide->setChecked(false);
    }

    is_second_number = false;
}
