#ifndef REPORTBUGSMENU_H
#define REPORTBUGSMENU_H

#include "global.h"
#include "softwareinfo.h"
#include "SmtpClient/SmtpMime"

class ReportBugsMenu : public QWidget
{
    Q_OBJECT
public:
    explicit ReportBugsMenu(QWidget *parent = nullptr);
    ~ReportBugsMenu();
    bool isSent() {return sent;}

signals:

public slots:
    void sendInfo();
    void closeThis();

private:
    bool sent = false;
    QVBoxLayout *mainLayout = nullptr;
    QLineEdit *emailInput = nullptr;
    QTextEdit *bugDescInput = nullptr;
};

#endif // REPORTBUGSMENU_H
