#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include "EditDialog.h"


EditDialog::EditDialog(QWidget *parent) : QDialog(parent) {
    QFormLayout *lay = new QFormLayout(this);

    QLabel *l1 = new QLabel(QString("Label"), this);
    labelField = new QLineEdit(this);
    lay->addRow(l1, labelField);

    QLabel *l2 = new QLabel(QString("Value"), this);
    valueField = new QLineEdit(this);
    lay->addRow(l2, valueField);

    QDialogButtonBox *bb = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal, this);
    lay->addWidget(bb);

    connect(bb, &QDialogButtonBox::accepted, this, &EditDialog::accept);
    connect(bb, &QDialogButtonBox::rejected, this, &EditDialog::reject);

    setLayout(lay);
    setWindowTitle("Edit");
}

QString EditDialog::getLabel() {
    return labelField->text();
}

QString EditDialog::getValue() {
    return valueField->text();
}
