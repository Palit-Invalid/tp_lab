#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define DB_NAME "todo.db"

#include <QMainWindow>
#include <QValidator>
#include <QtSql>
#include <QFile>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createDB();

    void connectToDB();

    void saveToDB();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;

    bool was_change;

};
#endif // MAINWINDOW_H
