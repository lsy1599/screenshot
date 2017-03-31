#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QString>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newPushButton_clicked();

    //截图的槽
    void screenShotSlot();

    void on_savePushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QPixmap pixmap;
};

#endif // MAINWINDOW_H
