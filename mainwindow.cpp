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

//使用右击功能
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu(this);
    QAction *action1 = new QAction(this);
    QAction *action2 = new QAction(this);
    QAction *action3 = new QAction(this);
    QAction *action4 = new QAction(this);
    QAction *action5 = new QAction(this);
    QAction *action6 = new QAction(this);

    action1->setText("另存");
    QObject::connect(action1,SIGNAL(triggered()),this,SLOT(on_savePushButton_clicked()));

    action2->setText("重新截图");
    QObject::connect(action2,SIGNAL(triggered()),this,SLOT(on_newPushButton_clicked()));
    action3->setText("复制到粘贴板");
    //QObject::connect(action3,SIGNAL(triggered()),this,SLOT(on_newPushButton_clicked()));
    action4->setText("清除粘贴板");
    action5->setText("退出");
    QObject::connect(action5,SIGNAL(triggered()),this,SLOT(close()));
    action6->setText("什么都不做，哈哈");

    menu->addAction(action1);
    menu->addSeparator();
    menu->addAction(action2);
    menu->addSeparator();
    menu->addAction(action3);
    menu->addSeparator();
    menu->addAction(action4);
    menu->addSeparator();
    menu->addAction(action5);
    menu->addSeparator();
    menu->addAction(action6);


    menu->exec(QCursor::pos());


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
    if(this->pixmap.isNull())
    {
        QMessageBox::information(this,"截图","截图失败");
        return ;
    }
    //讲截图复制到系统的剪切板
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setPixmap(this->pixmap);
    //scaled按比例缩放
    ui->preview_label->setPixmap(this->pixmap.scaled(ui->preview_label->size()));
    this->show();

}

void MainWindow::on_savePushButton_clicked()
{
    //使用了qt5的新类QStandardPaths,得到本地图片的路径
    QString filename = QFileDialog::getSaveFileName(this,"保存截图",
                            QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
    //qt4的方法
    //QString filename = QFileDialog::getSaveFileName(this,"保存截图",
    //                        QDesktopServices::storageLocation(QStandardPaths::PicturesLocation));
    if(filename.isEmpty())
    {
        //QMessageBox::information(this,"保存截图","保存出错");
        return ;
    }
    if(this->pixmap.isNull())
    {
        QMessageBox::information(this,"保存截图","你还没截图吧,亲");
        return ;
    }
    this->pixmap.save(filename);


}
