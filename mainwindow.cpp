#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , was_change(false)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет на редактирвоание ячеек таблицы
    ui->lineEdit_3->setValidator(new QRegExpValidator(QRegExp("\\d\\d\\d\\d"))); // проверка на валидность введённых данных
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("todo.db");

}

MainWindow::~MainWindow()
{
    delete ui;  
}

void MainWindow::createDB()
{
    if (!db.open())
    {
        QMessageBox::critical(this, "Error", "Error create database");
    }
    else
    {
        QSqlQuery query;
        query.exec("CREATE TABLE Computers "
                   "(id	INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,"
                   "Name TEXT,"
                   "Model TEXT,"
                   "Year TEXT)");
    }
    db.removeDatabase("todo.db");
}

void MainWindow::saveToDB()
{
    if (!db.open())
    {
        QMessageBox::critical(this, "Error", "Unable to sava data!");
    }
    else
    {
        QSqlQuery query;
        query.exec("DELETE FROM Computers"); //очищаем таблицу

        for (int i = 0; i < ui->tableWidget->rowCount() - 1; i++)
        {
            QString name = ui->tableWidget->item(i, 0)->text();
            QString model = ui->tableWidget->item(i, 1)->text();
            QString year = ui->tableWidget->item(i, 2)->text();

            query.prepare(QString("INSERT INTO Computers (Name, Model, Year) VALUES ('%1', '%2', '%3');").arg(name).arg(model).arg(year));
            query.exec();
        }
        db.removeDatabase("todo.db");
    }
    was_change = false;
}

void MainWindow::on_pushButton_clicked()
{

    if (ui->lineEdit->text().isEmpty()
            && ui->lineEdit_2->text().isEmpty()
            && ui->lineEdit_3->text().isEmpty())
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
    was_change = true;

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tableWidget->clearContents();
    qDebug() << "clear table" << endl;
    was_change = true;
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
    was_change = true;
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
    if (was_change == true)
    {
        QMessageBox::StandardButton answer = QMessageBox::question(this, "Exit", "Do you want to save the changes made to the database file?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (answer == QMessageBox::Save)
        {
            saveToDB();
            QApplication::exit();
        }
        else if (answer == QMessageBox::Discard)
        {
            QApplication::exit();
        }
    }
}

void MainWindow::connectToDB()
{
    int numRowsInDB = 1;

    if (!db.open())
    {
        QMessageBox::critical(this, "Error", "Error open database");
    }
    else
    {
        qDebug() << "Database connected" << endl;
        QSqlQuery query("SELECT * FROM Computers");

        query.last();
        numRowsInDB = query.at() + 2;

        qDebug() << numRowsInDB  << "num rows in database" << endl;
        if (numRowsInDB == 0)
        {
            ui->tableWidget->setRowCount(numRowsInDB+1);
        }
        else
        {
            ui->tableWidget->setRowCount(numRowsInDB);
        }

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
    }
    db.removeDatabase("todo.db");
}

void MainWindow::on_pushButton_6_clicked()
{
    saveToDB();
}
