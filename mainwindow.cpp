#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtNetworkAuth>
#include <QJsonDocument>
#include <QJsonObject>
#include "clientid.h"
#include "Spotify.h"
#include "playlist.h"
#include <QInputDialog>
#include <QMessageBox>

#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , spotify()
    , playlistManager()

{
    ui->setupUi(this);
    spotify.login();


}


MainWindow::~MainWindow()
{
    delete ui;
    //delete spotify;
    //delete manager;
}

void MainWindow::refreshAuxListWidget()
{
    // Mostra as playlists já atualizadas na tela auxiliar
    ui->auxListWidget->clear();
    // Inicializa as playlists na tela auxiliar
    int i=0;
    if(playlistManager.allPlaylists.isEmpty())
    {
        QString playlistEmpty = "No playlists to show";
        ui->auxListWidget->addItem(playlistEmpty);
    }
    else
    {
        for(i=0; i<playlistManager.allPlaylists.size();i++)
        {
            QString playlistName = playlistManager.allPlaylists[i].getPlaylistName();
            ui->auxListWidget->addItem(playlistName);
        }
    }
}


void MainWindow::on_iniciarButton_clicked()
{
    //QString authtoken = spotify.getToken();
    //ui->teOutput->appendPlainText(authtoken);

    refreshAuxListWidget();
}


void MainWindow::on_searchButton_clicked()
{
    // Lê o que o user escreveu para realizar a busca
    QString searchInput;
    searchInput = ui->teOutput->toPlainText();
    //qDebug() << searchInput;
    spotify.searchTrack(searchInput);

}


void MainWindow::on_showResultsButton_clicked()
{
    // Primeiro, limpa as telas listWidget e teOutput
    ui->listWidget->clear();
    ui->teOutput->clear();
    // Vamos mostrar o resultado da pesquisa na tela listWidget
    QList<track> results = spotify.getSearch();
    //qDebug() << results.isEmpty();
    // Varrer a QList obtida com um loop para exibir suas informações
    int i=0;
    for(i=0; i<results.size();i++)
    {
        // Vamos formatar os dados uteis para exibir
        QString trackname = results[i].name;
        QString trackalbum = results[i].album;
        QString trackartist = results[i].artist;
        //qDebug() << trackname;
        QString listItem = trackname + " | " + trackartist + " | " + trackalbum;
        ui->listWidget->addItem(listItem);
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    // A track selecionada será adicionada na playlist desejada

    // Primeiro, obtemos a row clicada na tela principal listWidget
    int row = ui->listWidget->row(item);
    qDebug() << row;
    // Criamos o objeto track com as informações selecionadas
    track selectedTrack = spotify.searchResult[row];
    qDebug() << selectedTrack.name;
    // Recebe a row da playlist atualmente selecionada
    int selectedPlaylist = ui->auxListWidget->currentRow();
    playlistManager.addTrackToPlaylist(selectedTrack, selectedPlaylist);

}


void MainWindow::on_renamePlaylistButton_clicked()
{
    // Usa um InputDialog para obter o novo nome da playlist
    QString playlistName = QInputDialog::getText(this, "Rename playlist", "Enter new playlist name");
    // Recebe a row da playlist atualmente selecionada
    int selectedPlaylist = ui->auxListWidget->currentRow();
    playlistManager.renamePlaylist(playlistName, selectedPlaylist);
    refreshAuxListWidget();
}


void MainWindow::on_newPlaylistButton_clicked()
{
    // Cria uma nova playlist e exibe na tela auxiliar
    //ui->auxListWidget->clear();
    // Usa um InputDialog para obter o nome da nova playlist
    QString playlistName;
    playlistName = QInputDialog::getText(this, "New playlist", "Enter new playlist name");
    //qDebug() << playlistName;
    // Cria o novo objeto playlist com o nome
    playlist playlist;
    playlist.setPlaylistName(playlistName);
    // Insere a nova playlist no container de playlists
    playlistManager.appendPlaylist(playlist);
    //qDebug() << playlistManager.allPlaylists[0].playlistName;
    refreshAuxListWidget();
}

void MainWindow::on_auxListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->listWidget->clear();
    // Double click na playlist para exibir suas tracks na tela principal
    int row = ui->auxListWidget->row(item);
    playlist playlist = playlistManager.allPlaylists[row];
    // Varrer a QList obtida com um loop
    if(playlist.playlistTracks.isEmpty())
    {
        QString playlistEmpty = "Your playlist is empty";
        ui->listWidget->addItem(playlistEmpty);
    }
    else
    {
        int i=0;
        for(i=0; i<playlist.playlistTracks.size();i++)
        {
            QString trackname = playlist.playlistTracks[i].name;
            QString trackalbum = playlist.playlistTracks[i].album;
            QString trackartist = playlist.playlistTracks[i].artist;
            //qDebug() << trackname;
            QString listItem = trackname + " | " + trackartist + " | " + trackalbum;
            ui->listWidget->addItem(listItem);
        }
    }
}

void MainWindow::on_addTrackButton_clicked()
{
    // A track selecionada será adicionada na playlist selecionada

    // Primeiro, obtemos a row selecionada na tela principal listWidget
    int row = ui->listWidget->currentRow();
    //qDebug() << row;
    // Criamos o objeto track com as informações selecionadas
    track selectedTrack = spotify.searchResult[row];
    //qDebug() << selectedTrack.name;
    // Recebe a row da playlist atualmente selecionada
    int selectedPlaylist = ui->auxListWidget->currentRow();
    playlistManager.addTrackToPlaylist(selectedTrack, selectedPlaylist);
}

void MainWindow::on_removeTrackButton_clicked()
{
    // A track selecionada será removida da playlist atual

    // Primeiro, obtemos a row selecionada na tela principal listWidget
    int row = ui->listWidget->currentRow();
    qDebug() << row;
    // Recebe a row da playlist atualmente selecionada
    int selectedPlaylist = ui->auxListWidget->currentRow();
    // Faz a remoção
    playlistManager.removeTrackFromPlaylist(row, selectedPlaylist);
    // Vamos atualizar a tela para mostrar a playlist já atualizada
    ui->listWidget->clear();
    playlist playlist = playlistManager.allPlaylists[selectedPlaylist];
    // Varrer a QList obtida com um loop
    if(playlist.playlistTracks.isEmpty())
    {
        QString playlistEmpty = "Your playlist is empty";
        ui->listWidget->addItem(playlistEmpty);
    }
    else
    {
        int i=0;
        for(i=0; i<playlist.playlistTracks.size();i++)
        {
            QString trackname = playlist.playlistTracks[i].name;
            QString trackalbum = playlist.playlistTracks[i].album;
            QString trackartist = playlist.playlistTracks[i].artist;
            //qDebug() << trackname;
            QString listItem = trackname + " | " + trackartist + " | " + trackalbum;
            ui->listWidget->addItem(listItem);
        }
    }
}

void MainWindow::on_deletePlaylistButton_clicked()
{
    // Primeiro, vamos confirmar se realmente deseja excluir
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete playlist", "Are you sure?", QMessageBox::Yes | QMessageBox::No);
    // Se sim, deleta a playlist
    if(reply == QMessageBox::Yes)
    {
        // Recebe a row da playlist atualmente selecionada
        int selectedPlaylist = ui->auxListWidget->currentRow();
        playlistManager.deletePlaylist(selectedPlaylist);
        refreshAuxListWidget();
    }
}
