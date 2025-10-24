#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QdeBug>
#include <math.h>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    digitBtns = {{Qt::Key_0,ui->btnNum0},
                 {Qt::Key_1,ui->btnNum1},
                 {Qt::Key_2,ui->btnNum2},
                 {Qt::Key_3,ui->btnNum3},
                 {Qt::Key_4,ui->btnNum4},
                 {Qt::Key_5,ui->btnNum5},
                 {Qt::Key_6,ui->btnNum6},
                 {Qt::Key_7,ui->btnNum7},
                 {Qt::Key_8,ui->btnNum8},
                 {Qt::Key_9,ui->btnNum9},
                };

    foreach (auto btn, digitBtns) {
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    }

    // connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnMultiple,SIGNAL(clicked()),this,SLOT(btnTwoOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnTwoOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnTwoOperatorClicked()));
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnTwoOperatorClicked()));

    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnOneOperatorClicked()));
    connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnOneOperatorClicked()));
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnOneOperatorClicked()));
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnOneOperatorClicked()));
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
    ui->display->setText(op);
}

void MainWindow::on_btnCleanAll_clicked()
{
    ops.clear();
    opcodes.clear();
    op.clear();
    opcode.clear();
    isEqual = false;
    equals = 0;
    ui->display->setText(op);
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
        else if(o == "÷"){
            result = num1 / num2;
        }
        QString s =QString::number(result);
        ops.push_back(s);
        ui->statusbar->showMessage(QString(" Calculation Done,ops is %1,opcodes is %2").arg(ops.size()).arg(opcodes.size()));
    }
    else
        ui->statusbar->showMessage(QString("ops is %1,opcodes is %2").arg(ops.size()).arg(opcodes.size()));
    return QString::number(result);
}

void MainWindow::btnTwoOperatorClicked()
{
    equals = 0;
    opcode = qobject_cast<QPushButton*>(sender())->text();
    if(op != ""){
        if(!isEqual)
            ops.push_back(op);
        op = "";
        opcodes.push_back(opcode);
    }
    QString result=calculation();
    ui->display->setText(result);

}

void MainWindow::btnOneOperatorClicked()
{
    if(op != ""){
        double result = op.toDouble();
        op = "";
        QString o = qobject_cast<QPushButton*>(sender())->text();
        if(o == "%"){
            result = result / 100.0;
        }
        else if(o == "1/x"){
            result = 1 / result;
        }
        else if(o == "x²"){
            result = result * result;
        }
        else if(o == "√"){
            result =sqrt(result);
        }
        op = QString::number(result);
        ui->display->setText(QString::number(result));
    }
}

void MainWindow::on_btnSign_clicked()
{
    if(op != ""){
        if(op == "0" || op == "0.")
            return;
        else if(op.indexOf("-") < 0)
            op = "-" + op;
        else
            op = op.mid(1);
    }
    ui->display->setText(op);
}


void MainWindow::on_btnEqual_clicked()
{
    isEqual = true;
    if(op != ""){
        if(equals < 1)
            ops.push_back(op);
        op = "";
    }
    equals++;
    if(equals > 1){
        //用于连等运算
        ops.push_back(n2);
        opcodes.push_back(equalOp);
    }
    else{
        //用于连等运算存储
        n2 = ops.front();
        equalOp = opcode;
    }
    QString result = calculation();
    ui->display->setText(result);
    op = result;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach(auto btnKey, digitBtns.keys())
    {
        if(event->key() == btnKey)
            digitBtns[btnKey]->animateClick();
    }
}





