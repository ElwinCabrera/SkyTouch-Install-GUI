#include "reportbugsmenu.h"

ReportBugsMenu::ReportBugsMenu(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout;

    //QLabel *emailLabel = new QLabel(tr("Enter Email:"));
    //emailInput = new QLineEdit;
    //emailInput->setPlaceholderText("Email");

    bugDescInput = new QTextEdit;
    bugDescInput->setPlaceholderText(tr("Enter Bug Description Here..."));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    //mainLayout->addWidget(emailLabel);
    //mainLayout->addWidget(emailInput);
    mainLayout->addWidget(bugDescInput);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &ReportBugsMenu::sendInfo);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ReportBugsMenu::closeThis);

}

ReportBugsMenu::~ReportBugsMenu()
{
    qDebug() << "ReportBugsMenu Destructor";
    if(mainLayout) clearLayotAndWidgets(mainLayout);

}

void ReportBugsMenu::sendInfo()
{
    if( bugDescInput->toPlainText().isEmpty()){
        messageBox("Input Fields empty","");
        return;
    }
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);
    smtp.setUser("my email");
    smtp.setPassword("my password");

    MimeMessage message;

    message.setSender(new EmailAddress("my email", "Elwin"));
    message.addRecipient(new EmailAddress("their email", "Skytouch"));
    message.setSubject("Bug Report - SkyTouch");

    MimeText text;
    text.setText(bugDescInput->toPlainText());

    message.addPart(&text);

    smtp.connectToHost();
    smtp.login();
    smtp.sendMail(message);
    smtp.quit();

    sent = true;

    messageBox("Bug Report Sent","Thank you for the input.");
    this->close();
}

void ReportBugsMenu::closeThis()
{
    if(!bugDescInput->toPlainText().isEmpty()){
        int msgRet = messageBox("Discard Editing?","You are currently editing, are you sure you want to discard?","Warning");
        if(msgRet == QMessageBox::Ok) this->close();
    } else {
        this->close();
    }

}
