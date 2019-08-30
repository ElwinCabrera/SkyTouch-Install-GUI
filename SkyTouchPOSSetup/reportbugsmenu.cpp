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

void ReportBugsMenu::sendInfo()
{
    if( bugDescInput->toPlainText().isEmpty()){
        messageBox("Input Fields empty","");
        return;
    }
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);
    smtp.setUser("your_email_address@gmail.com");
    smtp.setPassword("your_password");

    MimeMessage message;

    message.setSender(new EmailAddress("your_email_address@gmail.com", "Your Name"));
    message.addRecipient(new EmailAddress("recipient@host.com", "Recipient's Name"));
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
        int msgRet = messageBox("You are Currently editing, are you sure?","","Warning");
        if(msgRet == QMessageBox::Ok) this->close();
    } else {
        this->close();
    }

}
