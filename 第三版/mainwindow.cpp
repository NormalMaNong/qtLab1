#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QdeBug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnMultiple,SIGNAL(clicked()),this,SLOT(btnTwoOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnTwoOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnTwoOperatorClicked()));
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnTwoOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton*>(sender())->text();
    if(digit == "0" && op == "0")
        digit = "";
    if(digit != "0" && op == "0")
        op = "";
    op = op + digit;
    ui->display->setText(op);
}

void MainWindow::on_btnPeriod_clicked()
{
    if(!op.contains("."))
         op=op + qobject_cast<QPushButton*>(sender())->text();
    ui->display->setText(op);
}


void MainWindow::on_btnDel_clicked()
{
    op = op.left(op.length() - 1);
    ui->display->setText(op );
}


void MainWindow::on_btnClean_clicked()
{
    op.clear();
    ui->display->setText(op );
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;
    if(ops.size() == 2 && opcodes.size() > 0){
        double num1 = ops.front().toDouble();
        ops.pop_front();
        double num2 = ops.front().toDouble();
        ops.pop_front();

        QString o = opcodes.front();
        opcodes.pop_front();

        if(o == "+"){
            result = num1 + num2;
        }
        else if(o == "-"){
            result = num1 - num2;
        }
        else if(o == "×"){
            result = num1 * num2;
        }
        else if(o == "/"){
            result = num1 / num2;
        }
        QString s =QString::number(result);
        ops.push_back(s);
    }
    else
        ui->statusbar->showMessage(QString("op is %1,opcodes is %2").arg(ops.size()).arg(opcodes.size()));
    qDebug() << result;
    return QString::number(result);
}

void MainWindow::btnTwoOperatorClicked()
{
    opcode = qobject_cast<QPushButton*>(sender())->text();
    if(op != ""){
        ops.push_back(op);
        op = "";
        opcodes.push_back(opcode);
    }
    QString result=calculation();
    ui->display->setText(result);

}

void MainWindow::on_btnEqual_clicked()
{
    if(op != ""){
        ops.push_back(op);
        op = "";
    }

    QString result=calculation();
    ui->display->setText(result);
}

