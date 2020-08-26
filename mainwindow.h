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

    void on_searchButton_clicked();

    void on_showResultsButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    //void on_editPlaylistTracksButton_clicked();

    void on_newPlaylistButton_clicked();

    void on_auxListWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Spotify spotify;
    playlistManager playlistManager;

};
#endif // MAINWINDOW_H
