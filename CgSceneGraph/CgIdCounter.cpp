#include "CgIdCounter.h"


int CgIdCounter::m_id{0};

CgIdCounter::CgIdCounter()
{
    m_id++;

}

int CgIdCounter::getId(){
    return m_id;
}
