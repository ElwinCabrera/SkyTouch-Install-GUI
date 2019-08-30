#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "global.h"

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
    QTabWidget *tabs = nullptr;
};

#endif // OPTIONSMENU_H
