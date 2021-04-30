#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QString>

class EditDialog : public QDialog {
    Q_OBJECT
public:
    explicit EditDialog(QWidget *parent = nullptr);

    QString getLabel();
    QString getValue();

private:
    QLineEdit *labelField;
    QLineEdit *valueField;

signals:

};

#endif // EDITDIALOG_H
