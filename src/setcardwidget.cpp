
#include "setcardwidget.h"
#include "setcard.h"

// for rendering card
#include <QPen>
#include <QPainter>
#include <QMouseEvent>

SetCardWidget::SetCardWidget(QWidget* pParent) : QWidget(pParent)
{
    m_pSetCard = NULL;
}

SetCardWidget::~SetCardWidget()
{
}

void SetCardWidget::setSetCard(SetCard* pSetCard)
{
    m_pSetCard = pSetCard;
}

QColor SetCardWidget::cardColor(SetCard* pSetCard)
{
    QColor cColor;
    if(!pSetCard)
    {
        return cColor;
    }
    switch (pSetCard->color())
    {
        case SetCard::COLORRED:    cColor = QColor("#cc0000"); break;
        case SetCard::COLORPURPLE: cColor = QColor("#5c3566"); break;
        case SetCard::COLORGREEN:  cColor = QColor("#4e9a06"); break;
    }
    return cColor;
}

QPainterPath SetCardWidget::cardShape(SetCard* pSetCard, QRect cRect)
{
    QPainterPath cPath;
    if(!pSetCard)
    {
        return cPath;
    }
    switch (pSetCard->shape())
    {
        case SetCard::SHAPEROUND: cPath.addEllipse(QRectF(cRect)); break;
        case SetCard::SHAPERECT:  cPath.addRect(QRectF(cRect)); break;
        case SetCard::SHAPEWAVE:
            // convert Rect do float-rect (QRectF)
            QRectF cRectF(cRect);
            cPath.moveTo(cRect.x(), cRect.y());
            cPath.cubicTo(cRectF.bottomLeft(), cRectF.topRight(), cRectF.bottomRight());
            break;
    }
    return cPath;
}

Qt::BrushStyle SetCardWidget::cardFill(SetCard* pSetCard)
{
    Qt::BrushStyle eStyle = Qt::VerPattern;
    if(!pSetCard)
    {
        return eStyle;
    }
    switch (pSetCard->fill())
    {
        case SetCard::FILLEMPTY: eStyle = Qt::NoBrush; break;
        case SetCard::FILLDOT:   eStyle = Qt::Dense6Pattern; break;
        case SetCard::FILLSOLID: eStyle = Qt::SolidPattern; break;
    }
    return eStyle;
}
int SetCardWidget::cardCount(SetCard* pSetCard)
{
    int n = 0;
    if(!pSetCard)
    {
        return n;
    }
    switch (pSetCard->count())
    {
        case SetCard::COUNT1: n = 1; break;
        case SetCard::COUNT2: n = 2; break;
        case SetCard::COUNT3: n = 3; break;
    }
    return n;
}

void SetCardWidget::drawCardBackground(QPainter* pPainter, QRect cRect)
{
    if(!pPainter || !m_pSetCard)
    {
        return;
    }
    QPen cCardBorder ("#2e3436");
    cCardBorder.setWidth(2);
    QColor cBgColor;
    if (m_pSetCard->selected())
    {
        cBgColor = QColor("#fce94f");
    }
    else
    {
        cBgColor = QColor("#ffffff");
    }
    pPainter->setBrush(QBrush(cBgColor));
    pPainter->setPen(cCardBorder);
    pPainter->drawRoundedRect(cRect, 20.0, 18.0);
}


void SetCardWidget::paintEvent(QPaintEvent* pEvent)
{
    if (!pEvent)
    {
        return;
    }
    // init painter
    QPainter cPainter (this);
    cPainter.setRenderHint(QPainter::Antialiasing, true);
    // set pen-color by card-color
    QColor cColor = cardColor(m_pSetCard);
    QPen cPen (cColor);
    cPen.setWidth(2);
    QBrush cBrush (cColor, cardFill(m_pSetCard));
    QRect cCardRect(0, 0, width(), height()); // rect on the entire widget
    //qDebug("height = %d, width = %d", height(), width());
    int nMargin = 15; // margin in pixel
    int nCardMarginX = 0.08982 * width(); // margin within card from right/left border
    int nCardMarginY = 0.14186 * height(); // margin within card from top/bottom border
    int nPadding = 0.04672 * height(); // distance between two symbols on a card
    cCardRect.adjust(nMargin, nMargin, -nMargin, -nMargin);
    drawCardBackground(&cPainter, cCardRect);
    cCardRect.adjust(nCardMarginX, nCardMarginY, -nCardMarginX, -nCardMarginY);
    int nSymbolCount = cardCount(m_pSetCard); // number of symbols on card
    int nSymbolHeight = (cCardRect.height()
                        - (2*nPadding)) // substract padding
                        / 3; // space for 3 items
    int nUsedSymbolHeight = nSymbolHeight * nSymbolCount + nPadding * (nSymbolCount-1);
    // Y-coord of most top symbol
    int nSymbolY = cCardRect.y();
    // center vertically
    nSymbolY += (cCardRect.height() - nUsedSymbolHeight) / 2;
    // set painter colors just before painting
    cPainter.setBrush(cBrush);
    cPainter.setPen(cPen);
    // do it for each symbol
    for (int i = 0; i < nSymbolCount; ++i)
    {
        QPainterPath cPath = cardShape(m_pSetCard, QRect(cCardRect.x(), nSymbolY,
                                                         cCardRect.width(), nSymbolHeight));
        cPainter.drawPath(cPath);
        // go down by paddng
        nSymbolY += nPadding;
        // and by height of a symbol
        nSymbolY += nSymbolHeight;
    }
}

void SetCardWidget::mousePressEvent(QMouseEvent* pEvent)
{
    if (!pEvent)
    {
        return;
    }
    if (pEvent->button() == Qt::LeftButton && m_pSetCard)
    {
        m_pSetCard->setSelected(!m_pSetCard->selected());
        update();
    }
}
