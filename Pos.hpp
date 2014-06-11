#ifndef MINIPOS_POS_HPP
#define MINIPOS_POS_HPP


#include <memory>

namespace MiniPos {
class Pos;
}

class MiniPos::Pos
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    Pos();
    ~Pos();
};


#endif // MINIPOS_POS_HPP
