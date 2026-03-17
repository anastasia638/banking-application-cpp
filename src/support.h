#ifndef SUPPORT_H
#define SUPPORT_H

#include <QDialog>

namespace Ui {
class support;
}

class support : public QDialog
{
    Q_OBJECT

public:
    explicit support(QWidget *parent = nullptr);
    ~support();

private:
    Ui::support *ui;
};

#endif // SUPPORT_H
