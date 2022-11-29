
#include "link.h"
#include "board.h"

// ----------------------------------------------------------------------------
// Parent Link class
// ----------------------------------------------------------------------------

Link::Link(int strength_, Board& board_) : strength{strength_}, board{board_} {}

// ----------------------------------------------------------------------------
// Data class
// ----------------------------------------------------------------------------

Data::Data(int strength_, Board& board_) : Link(strength_, board_) {}
void Data::move() { return; }

// ----------------------------------------------------------------------------
// Virus class
// ----------------------------------------------------------------------------

Virus::Virus(int strength_, Board& board_) : Link(strength_, board_) {}
void Virus::move() { return; }


