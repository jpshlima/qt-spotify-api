#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Spotify.h"
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    //void login();


    //void on_pushButton_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Spotify spotify;
    //QNetworkAccessManager *manager;
    //QNetworkRequest request;

};
#endif // MAINWINDOW_H
