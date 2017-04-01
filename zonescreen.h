#ifndef ZONESCREEN_H
#define ZONESCREEN_H

#include <QWidget>

namespace Ui {
class ZoneScreen;
}

class ZoneScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneScreen(QWidget *parent = 0);
    ~ZoneScreen();

private:
    Ui::ZoneScreen *ui;
};

#endif // ZONESCREEN_H
