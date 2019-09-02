#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "global.h"
#include "softwareinfo.h"
class OptionsMenu : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsMenu(QWidget *parent = nullptr);
    ~OptionsMenu();
    void addTab(QWidget *widget, QString tabName);

signals:

public slots:


private:
    QVBoxLayout *mainLayout = nullptr;
    QTabWidget *tabs = nullptr;
};

#endif // OPTIONSMENU_H
