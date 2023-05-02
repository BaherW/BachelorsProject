#include "bishop.cpp"
#include "rook.cpp"

struct MagicEntry {
    BitBoard mask;
    U64 magic;
    uint8_t index_bits;
};
