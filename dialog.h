#ifndef DIALOG_H
#define DIALOG_H

#include <QObject>
#include "./ui_dialog.h"

class Dialog : public QObject
{
    Q_OBJECT

public:
    explicit Dialog(QObject *parent = 0);
    void displayMessage(const QString &message)
    {
        ui.output->appendPlainText(message);
    }
signals:
    void sendText(const QString &text);

public slots:
    void receiveText(const QString &text)
    {
        displayMessage(tr("Received message: %1").arg(text));
    }

private slots:
    void clicked()
    {
        const QString text = ui.input->text();        
        if (text.isEmpty()) {
            return;
        }
        emit sendText(text);
        displayMessage(tr("Sent message: %1").arg(text));
        ui.input->clear();
    }
private:
    QDialog dialog;
    Ui::Dialog ui;
};

#endif // DIALOG_H
