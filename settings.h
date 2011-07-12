#ifndef SETTINGS_H
#define SETTINGS_H

#include <QTabWidget>

namespace Ui {
    class settings;
}

class settings : public QTabWidget
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

private:
    Ui::settings *ui;
};

#endif // SETTINGS_H
