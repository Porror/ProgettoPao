#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QInputDialog>
#include <QDebug>

#include <QtWidgets>


class MyWidget : public QWidget {
    Q_OBJECT
public:
    MyWidget(QWidget *parent = nullptr);
private slots:
    void onItemDoubleClicked(QListWidgetItem *item);
private:
    QListWidget *listWidget;
};

#endif // MYWIDGET_H
