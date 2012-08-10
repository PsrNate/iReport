#include "resultwindow.h"
#include <QtGui>

ResultWindow::ResultWindow(QString *report) : QDialog()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    text = new QTextEdit;
    text->setPlainText(*report);
    text->setReadOnly(true);
    mainLayout->addWidget(text);
    clipboard = new QPushButton("Copier dans le presse-papiers");
    connect(clipboard, SIGNAL(pressed()), this, SLOT(copyToClipboard()));
    mainLayout->addWidget(clipboard);
    setLayout(mainLayout);
}

void ResultWindow::copyToClipboard()
{
    QApplication::clipboard()->setText(text->toPlainText());
    QMessageBox::information(this, QString("Copie"), QString("Le rapport a été copié dans le presse-papiers ! <br /> Vous pouvez maintenant le coller dans le forum."));
}
