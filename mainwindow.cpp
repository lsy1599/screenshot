#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newPushButton_clicked()
{
    if(ui->delayRadioButton->isChecked())
    {
        qDebug() << "选中了";
        timer = new QTimer();
        QObject::connect(this->timer,SIGNAL(timeout()),this,SLOT(screenShotSlot()));
        this->hide();
        timer->start(ui->delaySpinBox->text().toInt()*1000);
    }
    else
    {
        qDebug() << "没有选中";
        qApp->beep();
    }
}

void MainWindow::screenShotSlot()
{

    qDebug() << "时间到了";
    this->timer->stop();
    delete this->timer;
    this->pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    //scaled按比例缩放
    ui->preview_label->setPixmap(this->pixmap.scaled(ui->preview_label->size()));
    this->show();

}

void MainWindow::on_savePushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,"保存截图",QDesktopServices::storageLocation(QStandardPaths::PicturesLocation));
    if(filename.isEmpty())
    {
        QMessageBox::information(this,"保存截图","保存出错");
        return ;
    }

    QFile *file=new QFile();
    bool ok = file->open(filename);
    if(ok)
    {

    }
    else
    {
        delete file;
        return ;
    }
    delete file;
    return ;
}
