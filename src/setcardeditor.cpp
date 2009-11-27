
#include "setcardeditor.h"

#include "setcard.h"

// widgets
#include "setcardwidget.h"
#include <QComboBox>
#include <QSpinBox>
// layouts
#include <QHBoxLayout>
#include <QVBoxLayout>





SetCardEditor::SetCardEditor(QWidget* pParent) : QWidget(pParent)
{
    m_pSetCard = NULL;
    createGui();
}

SetCardEditor::~SetCardEditor()
{
}

void SetCardEditor::createGui()
{
    // create widgets
    wdgSetCard = new SetCardWidget;
    cmbShape = new QComboBox;
    cmbFill = new QComboBox;
    cmbColor = new QComboBox;
    cmbCount = new QComboBox;
    // create layouts
    layoutOptions = new QVBoxLayout;
    layoutOptions->addWidget(cmbShape);
    layoutOptions->addWidget(cmbFill);
    layoutOptions->addWidget(cmbColor);
    layoutOptions->addWidget(cmbCount);
    // parent layout
    layoutParent = new QHBoxLayout;
    //layoutParent->setMaring(0); // TODO find right "setMargin"-fct
    layoutParent->addWidget(wdgSetCard);
    layoutParent->addLayout(layoutOptions);
    // set layout to widget
    setLayout(layoutParent);
    // add data to combo boxes
    cmbShape->addItem("Rect", (int)SetCard::SHAPERECT);
    cmbShape->addItem("Round", (int)SetCard::SHAPEROUND);
    cmbShape->addItem("Wave", (int)SetCard::SHAPEWAVE);
    cmbFill->addItem("Empty", (int)SetCard::FILLEMPTY);
    cmbFill->addItem("Dot", (int)SetCard::FILLDOT);
    cmbFill->addItem("Solid", (int)SetCard::FILLSOLID);
    cmbColor->addItem("Red", (int)SetCard::COLORRED);
    cmbColor->addItem("Purple", (int)SetCard::COLORPURPLE);
    cmbColor->addItem("Green", (int)SetCard::COLORGREEN);
    cmbCount->addItem("1", (int)SetCard::COUNT1);
    cmbCount->addItem("2", (int)SetCard::COUNT2);
    cmbCount->addItem("3", (int)SetCard::COUNT3);
    // connect slots
    connect(cmbShape, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCard()));
    connect(cmbFill, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCard()));
    connect(cmbColor, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCard()));
    connect(cmbCount, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCard()));
}

void SetCardEditor::setSetCard(SetCard* pSetCard)
{
    m_pSetCard = pSetCard;
    wdgSetCard->setSetCard(m_pSetCard);
    updateOptions();
}


void SetCardEditor::updateCard()
{
    if(!m_pSetCard)
    {
        return;
    }
    // set data
    m_pSetCard->setShape((SetCard::Shape)cmbShape->itemData(cmbShape->currentIndex()).toInt());
    m_pSetCard->setFill((SetCard::Fill)cmbFill->itemData(cmbFill->currentIndex()).toInt());
    m_pSetCard->setColor((SetCard::Color)cmbColor->itemData(cmbColor->currentIndex()).toInt());
    m_pSetCard->setCount((SetCard::Count)cmbColor->itemData(cmbCount->currentIndex()).toInt());
    // update
    wdgSetCard->update();
}
void SetCardEditor::updateOptions()
{
    if(!m_pSetCard)
    {
        return;
    }
    // backup values first
    SetCard::Shape eShape = m_pSetCard->shape();
    SetCard::Fill eFill = m_pSetCard->fill();
    SetCard::Color eColor = m_pSetCard->color();
    SetCard::Count eCount = m_pSetCard->count();
    // THEN : set it to widgets
    // be carfeful: changing values in widgets causes updateCard()
    cmbShape->setCurrentIndex(cmbShape->findData((int)eShape));
    cmbFill->setCurrentIndex(cmbFill->findData((int)eFill));
    cmbColor->setCurrentIndex(cmbColor->findData((int)eColor));
    cmbCount->setCurrentIndex(cmbCount->findData((int)eCount));
}


