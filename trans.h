#ifndef TRANS_H
#define TRANS_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QButtonGroup>
#include <QGroupBox>
class Trans : public QWidget
{
    Q_OBJECT
public:
    explicit Trans(QWidget *parent = nullptr);
    void setWid();
    void empty();

    QLabel *label[3];
    QSpinBox *translate_x,*translate_y,*angle;
    QRadioButton *sym_x,*sym_y;
    QGridLayout *gridlay[4];
    QButtonGroup *btnbox;
    QGroupBox *box[4];
signals:

public slots:
};

#endif // TRANS_H
