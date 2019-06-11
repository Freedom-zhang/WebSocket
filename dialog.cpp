#include "dialog.h"

Dialog::Dialog(QObject *parent) : QObject(parent)
{
    ui.setupUi(&dialog);
    dialog.show();
    connect(ui.send, SIGNAL(clicked()), SLOT(clicked()));
}
