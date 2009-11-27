
#ifndef __SETCARDWIDGET_H_
#define __SETCARDWIDGET_H_

#include <QWidget>
#include <QPainterPath>

class SetCard;
class QMouseEvent;

class SetCardWidget : public QWidget
{
    Q_OBJECT
  public:
    SetCardWidget(QWidget* pParent = 0);
    ~SetCardWidget();
    // getter & setter
    void setSetCard(SetCard* pSetCard);
    // getter for card
    QColor cardColor(SetCard* pSetCard);
    QPainterPath cardShape(SetCard* pSetCard, QRect cRect);
    Qt::BrushStyle cardFill(SetCard* pSetCard);
    int cardCount(SetCard* pSetCard);
  protected:
    void drawCardBackground(QPainter* pPainter, QRect cRect);
    virtual void paintEvent(QPaintEvent* pEvent);
    virtual void mousePressEvent(QMouseEvent* pEvent);
  private:
    SetCard* m_pSetCard;
};

#endif

