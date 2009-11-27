
#include "setgametable.h"
#include "setcardeditor.h"
#include "setcard.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
// widgets
#include <QSpinBox>
#include <QPushButton>

SetGameTable::SetGameTable(QWidget* pParent) : QWidget(pParent)
{
    m_nCount = 0;
    createGui();
    setCount(12);
    // init widgets
    spinCount->setValue(count());
}

SetGameTable::~SetGameTable()
{
    setCount(0);
}

void SetGameTable::createGui()
{
    // create widgets
    spinCount = new QSpinBox;
    spinCount->setSuffix(" Cards");
    spinCount->setRange(0, 21);
    spinCount->setSingleStep(3);
    btnRandomize = new QPushButton;
    btnRandomize->setText("Randomize");
    btnFindMatches = new QPushButton;
    btnFindMatches->setText("Find Matches");
    // create toolbar
    layoutToolBar = new QHBoxLayout;
    layoutToolBar->addWidget(spinCount);
    layoutToolBar->addWidget(btnRandomize);
    layoutToolBar->addWidget(btnFindMatches);
    layoutTable = new QGridLayout;
    // set parent layout
    layoutParent = new QVBoxLayout;
    layoutParent->addLayout(layoutToolBar);
    layoutParent->addLayout(layoutTable);
    setLayout(layoutParent);
    // connect slots
    connect(spinCount, SIGNAL(valueChanged(int)), this, SLOT(setCount(int)));
    connect(btnRandomize, SIGNAL(clicked()), this, SLOT(randomize()));
    connect(btnFindMatches, SIGNAL(clicked()), this, SLOT(findMatches()));
}

int SetGameTable::count() const
{
    return m_nCount;
}
void SetGameTable::setCount(int nCount)
{
    if (nCount == m_nCount)
    {
        // nothing to do
        return;
    }
    if (nCount < 0)
    {
        nCount = 0;
    }
    //qDebug("Setting Count %d -> %d", m_nCount, nCount);
    int nRows = 3;
    SetCard* pNewCard;
    SetCardEditor* wdgNewEditor;
    // add new items
    for (int i = m_nCount; i < nCount; ++i)
    {
        pNewCard = new SetCard;
        pNewCard->randomize();
        // maybe: do some random thins here for new card
        m_vCards.append(pNewCard); // add card to vector
        wdgNewEditor = new SetCardEditor; // create new editor
        wdgNewEditor->setSetCard(pNewCard); // edit new card in editor
        m_vEditors.append(wdgNewEditor); // add editor to vector
        // add new editor to layout
        layoutTable->addWidget(wdgNewEditor, i % nRows, i / nRows);
    }
    SetCard* pCurrentCard;
    SetCardEditor* wdgCurrentEditor;
    // remove items, if there are to much
    for (int i = nCount; i < m_nCount; ++i)
    {
        // remove editor
        wdgCurrentEditor = m_vEditors[i];
        if (wdgCurrentEditor)
        {
            m_vEditors[i] = NULL;
            layoutTable->removeWidget(wdgCurrentEditor);
            delete wdgCurrentEditor;
        }
        // remove Card
        pCurrentCard = m_vCards[i];
        if (pCurrentCard)
        {
            m_vCards[i] = NULL;
            //qDebug("deleting Card %x", pCurrentCard);
            delete pCurrentCard;
        }
    }
    // set new size
    m_vCards.resize(nCount);
    m_vEditors.resize(nCount);
    // set size to member
    m_nCount = nCount;
}

void SetGameTable::randomize()
{
    // mix cards 
    SetCard* pCard;
    SetCardEditor* pEditor;
    for (int i = 0; i < m_nCount; ++i)
    {
        pCard = m_vCards[i];
        pEditor = m_vEditors[i];
        if (pCard)
        {
            pCard->randomize();
            pCard->setSelected(false);
            if (pEditor)
            {
                pEditor->update();
                pEditor->updateOptions();
            }
        }
    }
}

void SetGameTable::findMatches()
{
    SetCard *pCard1, *pCard2, *pCard3;
    bool bMatchFound = false;
    for (int c1 = 0; c1 < m_nCount; ++c1)
    {
        pCard1 = m_vCards[c1];
        if (!pCard1) continue;
        for (int c2 = 0; c2 < m_nCount; ++c2)
        {
            if (c1 == c2)
            {
                continue;
            }
            pCard2 = m_vCards[c2];
            if (!pCard2) continue;
            for (int c3 = 0; c3 < m_nCount; ++c3)
            {
                if (c1 == c3 || c2 == c3)
                {
                    continue;
                }
                //qDebug("checking (%d,%d,%d)", c1, c2, c3);
                pCard3 = m_vCards[c3];
                if (!pCard3) continue;
                if (SetCard::matches(*pCard1, *pCard2, *pCard3))
                {
                    pCard1->setSelected(true);
                    pCard2->setSelected(true);
                    pCard3->setSelected(true);
                    // update editors
                    SetCardEditor* pEditor = NULL;
                    if (pEditor = m_vEditors[c1]) pEditor->update();
                    if (pEditor = m_vEditors[c2]) pEditor->update();
                    if (pEditor = m_vEditors[c3]) pEditor->update();
                    bMatchFound = true;
                    break;
                }
            }
            if (bMatchFound)
            {
                break;
            }
        }
        if (bMatchFound)
        {
            break;
        }
    }
}

