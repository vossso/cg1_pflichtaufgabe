#ifndef CGIDCOUNTER_H
#define CGIDCOUNTER_H


class CgIdCounter
{
public:
    CgIdCounter();
    int getId();

private:
    static int m_id;
};


#endif // CGIDCOUNTER_H
