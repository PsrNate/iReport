#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QtGui>

class ResultWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ResultWindow(QString*);
    
signals:
    
public slots:
    void copyToClipboard();
private:
    QTextEdit *text;
    QPushButton *clipboard;
};

#endif // RESULTWINDOW_H
