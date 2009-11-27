#include "setcard.h"

#include <stdlib.h> // for rand()

SetCard::SetCard()
{
    m_bSelected = false;
    setShape(SHAPEROUND);
    setFill(FILLDOT);
    setColor(COLORRED);
    setCount(COUNT3);
}

SetCard::~SetCard()
{
}

void SetCard::setShape(SetCard::Shape eShape)
{
    m_eShape = eShape;
}

SetCard::Shape SetCard::shape() const
{
    return m_eShape;
}

void SetCard::setFill(SetCard::Fill eFill)
{
    m_eFill = eFill;
}

SetCard::Fill SetCard::fill() const
{
    return m_eFill;
}

void SetCard::setColor(SetCard::Color eColor)
{
    m_eColor = eColor;
}

SetCard::Color SetCard::color() const
{
    return m_eColor;
}

void SetCard::setCount(SetCard::Count eCount)
{
    m_eCount = eCount;
}

SetCard::Count SetCard::count() const
{
    return m_eCount;
}

bool SetCard::selected() const
{
    return m_bSelected;
}

void SetCard::setSelected(bool bSelected)
{
    m_bSelected = bSelected;
}

bool SetCard::matches(const SetCard& cCard1, const SetCard& cCard2, const SetCard& cCard3)
{
    bool bResult = true;
    // does shape match ?
    bResult = bResult && matchesInt(cCard1.shape(), cCard2.shape(), cCard3.shape());
    // does fill-type match ? ... etc ...
    bResult = bResult && matchesInt(cCard1.fill(), cCard2.fill(), cCard3.fill());
    bResult = bResult && matchesInt(cCard1.color(), cCard2.color(), cCard3.color());
    bResult = bResult && matchesInt(cCard1.count(), cCard2.count(), cCard3.count());
    return bResult;
}

// checks, if all ints are the same or different
bool SetCard::matchesInt(int n1, int n2, int n3)
{
    bool bResult = false;
    // all ints are the equal
    bResult = bResult || (n1 == n2 && n2 == n3);
    // or all ints are different
    bResult = bResult || (n1 != n2 && n2 != n3 && n3 != n1);
    return bResult;
}

void SetCard::randomize()
{
    Shape rgShapes[] = { SHAPEROUND, SHAPERECT, SHAPEWAVE };
    m_eShape = rgShapes[rand() % 3];
    Fill rgFills[] = { FILLSOLID, FILLDOT, FILLEMPTY };
    m_eFill = rgFills[rand() % 3];
    Color rgColors[] = { COLORRED, COLORPURPLE, COLORGREEN };
    m_eColor = rgColors[rand() % 3];
    Count rgCounts[] = { COUNT1, COUNT2, COUNT3 };
    m_eCount = rgCounts[rand() % 3];
}


