#ifndef CUSTOMINPUTDIALOG_H
#define CUSTOMINPUTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QLabel>
#include <QPushButton>
#include <QVariant>


class CustomInputDialog : public QDialog {
    Q_OBJECT
public:
    class InputData{
    public:
        double min,max;
        QString name;
    };

    CustomInputDialog(int min=0,int max=0,QString nome="",QWidget *parent = nullptr);
    ~CustomInputDialog();
    InputData getValues() const;
private:
    void setupUI();

    QLineEdit *minEdit,*maxEdit,*nameEdit; //contengono i valori prima che vengano ritornati
};

#endif // CUSTOMINPUTDIALOG_H
