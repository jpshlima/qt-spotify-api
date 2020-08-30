#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Spotify.h"
#include <QNetworkAccessManager>
#include <QListWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refreshAuxListWidget();
    void showTracksOnScreen(QList<track>);


private slots:
    void on_iniciarButton_clicked();

    void on_searchButton_clicked();

    void on_showResultsButton_clicked();

    void on_renamePlaylistButton_clicked();

    void on_newPlaylistButton_clicked();

    void on_auxListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_addTrackButton_clicked();

    void on_removeTrackButton_clicked();

    void on_deletePlaylistButton_clicked();

    void on_savePlaylistButton_clicked();

    void on_playButton_clicked();

    void on_previewTrackButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void on_resumeButton_clicked();


private:
    Ui::MainWindow *ui;
    Spotify spotify;
    playlistManager playlistManager;
    QMediaPlayer* player;
    QMediaPlaylist* mediaPlaylist;

};
#endif // MAINWINDOW_H
