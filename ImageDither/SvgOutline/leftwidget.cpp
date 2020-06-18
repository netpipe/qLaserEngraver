#include "leftwidget.h"
#include <QPainter>
#include <QPainterPath>
LeftWidget::LeftWidget(QWidget *parent) : QWidget(parent)
{

}
void LeftWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    int i;
    QPainterPath total;
    for(i = 0; i<m_list.size(); i++)
    {
        QPainterPath path = m_list.at(i)->shape();
        p.fillPath(path, QColor(0,0,0));

        total = total.united(path);
    }

    //draw out line
    QPen pen(Qt::green, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen);
    p.setBrush(QColor(0,0,0,0));
    p.drawPath(total.simplified());
    //p.drawRect(0,0,200,200);
}
