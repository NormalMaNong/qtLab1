#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QKeyEvent>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString op;
    QString opcode;

    QStack<QString> ops;
    QStack<QString> opcodes;

    QMap<int,QPushButton*> digitBtns;

    QString calculation(bool *ok = NULL);

    bool isEqual = false;

    int equals = 0;

    QString n2;
    QString equalOp;

private slots:

    void btnNumClicked();

    void btnTwoOperatorClicked();

    void btnOneOperatorClicked();

    void on_btnPeriod_clicked();

    void on_btnDel_clicked();

    void on_btnClean_clicked();

    void on_btnEqual_clicked();

    virtual void keyPressEvent(QKeyEvent* event);

    void on_btnCleanAll_clicked();

    void on_btnSign_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
