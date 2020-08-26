#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Spotify.h"
#include <QNetworkAccessManager>
#include <QListWidget>

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
    void on_iniciarButton_clicked();

    //void login();


    //void on_pushButton_2_clicked();

    void on_searchButton_clicked();

    void on_showResultsButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Spotify spotify;
    //QNetworkAccessManager *manager;
    //QNetworkRequest request;

};
#endif // MAINWINDOW_H
