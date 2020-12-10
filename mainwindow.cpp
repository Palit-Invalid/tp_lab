#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , row(1)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    if (ui->lineEdit->text().isEmpty()
            and ui->lineEdit_2->text().isEmpty()
            and ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Fields are ampty");
        qDebug() << "Error, fields are empty" << endl;
    }
    else
    {
        QTableWidgetItem* name = new QTableWidgetItem();
        name->setText(ui->lineEdit->text());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,name);

        QTableWidgetItem* model = new QTableWidgetItem();
        model->setText(ui->lineEdit_2->text());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,model);

        QTableWidgetItem* date = new QTableWidgetItem();
        date->setText(ui->lineEdit_3->text());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,date);

        qDebug() << ui->lineEdit->text() << " " << ui->lineEdit_2->text() << " " << ui->lineEdit_3->text() << "insert to" << ui->tableWidget->rowCount() << "row" << endl;

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tableWidget->clearContents();
    qDebug() << "clear table" << endl;
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "remove" << ui->tableWidget->currentRow() << endl;
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::aboutQt(this, "AboutQt");
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton answer = QMessageBox::question(this, "Exit", "Do you realy want to close programm?", QMessageBox::Yes | QMessageBox::No);

    if (answer == QMessageBox::Yes)
    {
        QApplication::exit();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::StandardButton answer = QMessageBox::question(this, "Exit", "Do you realy want to close programm?", QMessageBox::Yes | QMessageBox::No);

    if (answer == QMessageBox::Yes)
    {
        QApplication::exit();
    }
}
