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
    ui->lineEdit_3->setValidator(new QRegExpValidator(QRegExp("\\d\\d\\d\\d")));
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("todo.db");
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

    if (ui->tableWidget->currentRow() != ui->tableWidget->rowCount() - 1)
    {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        qDebug() << "remove" << ui->tableWidget->currentRow() << "line" << endl;
    }
    else
    {
        qDebug() << "can't delete last row" << endl;
    }
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

void MainWindow::on_pushButton_5_clicked()
{
    numRowsInDB = 1;

    if (!db.open())
    {
        QMessageBox::critical(this, "Error", "Error open database");
    }
    else
    {
        QMessageBox::information(this, "Complete", "Database connected!");
    }

    QSqlQuery query("SELECT * FROM Computers");

     query.last();
     numRowsInDB = query.at() + 2;
     ui->tableWidget->setRowCount(numRowsInDB);
     qDebug() << numRowsInDB - 1 << "num rows in database" << endl;


     query.exec("SELECT * FROM Computers");

     int i = 0;
     while (query.next())
     {
         QTableWidgetItem* name = new QTableWidgetItem();
         name->setText(query.value(1).toString());
         ui->tableWidget->setItem(i,0,name);

         QTableWidgetItem* model = new QTableWidgetItem();
         model->setText(query.value(2).toString());
         ui->tableWidget->setItem(i,1,model);

         QTableWidgetItem* year = new QTableWidgetItem();
         year->setText(query.value(3).toString());
         ui->tableWidget->setItem(i,2,year);

         i++;
     }
     db.removeDatabase("todo.db");

}

void MainWindow::on_pushButton_6_clicked()
{

    if (!db.open())
    {
        QMessageBox::critical(this, "Error", "Error open database");
    }
    else
    {
        for (int i = 0; i < ui->tableWidget->rowCount() - 1; i++)
        {
            QString name = ui->tableWidget->item(i, 0)->text();
            QString model = ui->tableWidget->item(i, 1)->text();
            QString year = ui->tableWidget->item(i, 2)->text();
            QSqlQuery query;
            query.prepare(QString("INSERT INTO Computers (Name, Model, Year) VALUES ('%1', '%2', '%3');").arg(name).arg(model).arg(year));

        }
        QMessageBox::information(this, "Complete", "Saving completed");
    }

}
