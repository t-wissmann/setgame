
#ifndef __SETCARD_H_
#define __SETCARD_H_

class SetCard {
  public:
    // some enumerations
    enum Shape {
        SHAPEROUND,
        SHAPERECT,
        SHAPEWAVE
    };
    enum Fill {
        FILLEMPTY,
        FILLDOT,
        FILLSOLID
    };
    enum Color {
        COLORRED,
        COLORPURPLE,
        COLORGREEN
    };
    enum Count {
        COUNT1,
        COUNT2,
        COUNT3
    };
    // functions
    SetCard();
    ~SetCard();
    // getter & setter
    Shape shape() const;
    void setShape(Shape eShape);
    Fill fill() const;
    void setFill(Fill eFill);
    Color color() const;
    void setColor(Color eColor);
    Count count() const;
    void setCount(Count eCount);
    bool selected() const;
    void setSelected(bool bSelected);
    // static functions
    static bool matches(const SetCard& cCard1, const SetCard& cCard2,
                        const SetCard& cCard3);
    static bool matchesInt(int n1, int n2, int n3);
    void randomize();
  private:
    Shape m_eShape;
    Fill m_eFill;
    Color m_eColor;
    Count m_eCount;
    bool m_bSelected;
};

#endif

