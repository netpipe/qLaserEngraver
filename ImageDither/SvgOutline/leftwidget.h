#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QList>
#include <QGraphicsItem>
class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = nullptr);
public:

    void paintEvent(QPaintEvent *event);
public:
    QList<QGraphicsItem *> m_list;
signals:

};

#endif // LEFTWIDGET_H
