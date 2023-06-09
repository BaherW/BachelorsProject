#include "../headers/eval.h"

const int opening_phase_score = 5900;
const int endgame_phase_score = 500;

const int piece_value[2][12]{
    {89, 308, 319, 488, 888, 20001, -92, -307, -323, -492, -888, -20002},
    {96, 319, 331, 497, 853, 19998, -102, -318, -334, -501, -845, -20000}};


// piece-square tables
const int pst[2][6][64] = {
    // opening phase scores
    {
      // pawn
      {
           0,   0,   0,   0,   0,   0,   0,   0,   
          -4,  68,  61,  47,  47,  49,  45,  -1,   
           6,  16,  25,  33,  24,  24,  14,  -6,   
           0,  -1,   9,  28,  20,   8,  -1,  11,   
           6,   4,   6,  14,  14,  -5,   6,  -6,   
          -1,  -8,  -4,   4,   2, -12,  -1,   5,   
           5,  16,  16, -14, -14,  13,  15,   8,   
           0,   0,   0,   0,   0,   0,   0,   0,   
      },

      // knight
      {
         -55, -40, -30, -28, -26, -30, -40, -50,   
         -37, -15,   0,  -6,   4,   3, -17, -40,   
         -25,   5,  16,  12,  11,   6,   6, -29,   
         -24,   5,  21,  14,  18,   9,  11, -26,   
         -36,  -5,   9,  23,  24,  21,   2, -24,   
         -32,  -1,   4,  19,  20,   4,  11, -25,   
         -38, -22,   4,  -1,   8,  -5, -18, -34,   
         -50, -46, -32, -24, -36, -25, -34, -50,   
      },

      // bishop
      {
         -16, -15, -12,  -5, -10, -12, -10, -20,   
         -13,   5,   6,   1,  -6,  -5,   3,  -6,   
         -16,   6,  -1,  16,   7,  -1,  -6,  -5,   
         -14,  -1,  11,  14,   4,  10,  11, -13,   
          -4,   5,  12,  16,   4,   6,   2, -16,   
         -15,   4,  14,   8,  16,   4,  16, -15,   
          -5,   6,   6,   6,   3,   6,   9,  -7,   
         -14,  -4, -15,  -4,  -9,  -4, -12, -14,   
      },

      // rook
      {
           5,  -2,   6,   2,  -2,  -6,   4,  -2,   
           8,  13,  11,  15,  11,  15,  16,   4,   
          -6,   3,   3,   6,   1,  -2,   3,  -5,   
         -10,   5,  -4,  -4,  -1,  -6,   3,  -2,   
          -4,   3,   5,  -2,   4,   1,  -5,   1,   
           0,   1,   1,  -3,   5,   6,   1,  -9,   
         -10,  -1,  -4,   0,   5,  -6,  -6,  -9,   
          -1,  -2,  -6,   9,   9,   5,   4,  -5,   
      },

      // queen
      {
         -25,  -9, -11,  -3,  -7, -13, -10, -17,   
          -4,  -6,   4,  -5,  -1,   6,   4,  -5,   
          -8,  -5,   2,   0,   7,   6,  -4,  -5,   
           0,  -4,   7,  -1,   7,  11,   0,   1,   
          -6,   4,   7,   1,  -1,   2,  -6,  -2,   
         -15,  11,  11,  11,   4,  11,   6, -15,   
          -5,  -6,   1,  -6,   3,  -3,   3, -10,   
         -15,  -4, -13,  -8,  -3, -16,  -8, -24,   
      },

      // king
      {
         -30, -40, -40, -50, -50, -40, -40, -30,   
         -30, -37, -43, -49, -50, -39, -40, -30,   
         -32, -41, -40, -46, -49, -40, -46, -30,   
         -32, -38, -39, -52, -54, -39, -39, -30,   
         -20, -33, -29, -42, -44, -29, -30, -19,   
         -10, -18, -17, -20, -22, -21, -20, -13,   
          14,  18,  -1,  -1,   4,  -1,  15,  14,   
          21,  35,  11,   6,   1,  14,  32,  22,   
      }
    },

    // endgame phase score
    {
      // pawn
      {
           0,   0,   0,   0,   0,   0,   0,   0,   
          -4, 174, 120,  94,  85,  98,  68,   4,   
           6,  48,  44,  45,  31,  38,  37,  -6,   
          -6,  -4,  -1,  -6,   2,  -1,  -2,  -2,   
           2,   2,   5,  -3,   0,  -5,   4,  -3,   
          -2,   0,   1,   5,   0,  -1,   0,   1,   
          -2,   5,   6,  -6,   0,   3,   4,  -4,   
           0,   0,   0,   0,   0,   0,   0,   0,   
      },

      // knight
      {
         -50, -40, -30, -24, -24, -35, -40, -50,   
         -38, -17,   6,  -5,   5,  -4, -15, -40,   
         -24,   3,  15,   9,  15,  10,  -6, -26,   
         -29,   5,  21,  17,  18,   9,  10, -28,   
         -36,  -5,  18,  16,  14,  20,   5, -26,   
         -32,   7,   5,  20,  11,  15,   9, -27,   
         -43, -20,   5,  -1,   5,   1, -22, -40,   
         -50, -40, -32, -27, -30, -25, -35, -50,   
      },

      // bishop
      {
         -14, -13,  -4,  -7, -14,  -9, -16, -20,   
         -11,   6,   3,  -6,   4,  -3,   5,  -4,   
         -11,  -3,   5,  15,   4,  -1,  -5, -10,   
          -7,  -1,  11,  16,   5,  11,   7, -13,   
          -4,   4,  10,  16,   6,  12,   4, -16,   
          -4,   4,  11,  12,  10,   7,   7, -12,   
         -11,   7,   6,   6,  -3,   2,   1,  -7,   
         -15,  -4, -11,  -4, -10, -10,  -6, -17,   
      },

      // rook
      {
           5,  -6,   1,  -4,  -4,  -6,   6,  -3,   
          -6,   4,   2,   5,  -1,   3,   4, -15,   
         -15,   3,   3,   0,  -1,  -6,   5,  -9,   
         -16,   6,   0,  -6,  -3,  -3,  -4,  -4,   
         -15,   6,   2,  -6,   6,   0,  -6, -10,   
          -6,  -1,   3,  -2,   6,   5,   0, -15,   
          -8,  -4,   1,  -4,   3,  -5,  -6,  -5,   
           1,   0,  -2,   1,   1,   4,   2,   0,   
      },

      // queen
      {
         -21,  -7,  -6,   1,  -8, -15, -10, -16,   
          -4,  -5,   3,  -4,   2,   6,   3, -10,   
         -13,  -2,   7,   2,   6,  10,  -4,  -6,   
          -1,  -4,   3,   1,   8,   8,  -2,  -2,   
           0,   6,   8,   1,  -1,   1,   0,  -3,   
         -11,  10,   6,   3,   7,   9,   4, -10,   
         -12,  -6,   5,   0,   0,  -5,   4, -10,   
         -20,  -6,  -7,  -7,  -4, -12,  -9, -20,   
      },

      // king
      {
         -50, -40, -30, -20, -20, -30, -40, -50,   
         -30, -18, -15,   6,   3,  -6, -24, -30,   
         -35, -16,  20,  32,  34,  14, -11, -30,   
         -34,  -5,  24,  35,  34,  35, -16, -35,   
         -36,  -7,  31,  34,  34,  34, -12, -31,   
         -30,  -7,  14,  33,  36,  16, -13, -33,   
         -36, -27,   5,   2,   5,  -1, -31, -33,   
         -48, -26, -26, -26, -28, -25, -30, -51,   
      }
    }
};

  // mirror positional score tables for opposite side
const int mirrorSquare[64] = {
    a1, b1, c1, d1, e1, f1, g1, h1,   
    a2, b2, c2, d2, e2, f2, g2, h2,   
    a3, b3, c3, d3, e3, f3, g3, h3,   
    a4, b4, c4, d4, e4, f4, g4, h4,   
    a5, b5, c5, d5, e5, f5, g5, h5,   
    a6, b6, c6, d6, e6, f6, g6, h6,   
    a7, b7, c7, d7, e7, f7, g7, h7,   
    a8, b8, c8, d8, e8, f8, g8, h8,   
};
  
int get_game_phase_score(State &state)
{
    int p;
    int score = 0;

    for (int p = wKNIGHT; p <= wQUEEN; p++)
        score += state.position.pieces[p].pop_count() * piece_value[opening][p];

    for (int p = bKNIGHT; p <= bQUEEN; p++)
        score += state.position.pieces[p].pop_count() * -piece_value[opening][p];

    return score;
}

int eval(State &state)
{
    int game_phase_score = get_game_phase_score(state);

    int game_phase = -1;
    if (game_phase_score > opening_phase_score)
        game_phase = opening;
    else if (game_phase_score < endgame_phase_score)
        game_phase = endgame;
    else
        game_phase = middlegame;

    int score = 0;
    int scoreOpening = 0;
    int scoreEndgame = 0;

    for (int p = wPAWN; p <= bKING; p++)
    {
        BitBoard board = state.position.pieces[p];

        while (board)
        {
            scoreOpening += piece_value[opening][p];
            scoreEndgame += piece_value[endgame][p];

            int square = board.get_ls1b_index();

            switch (p)
            {
            case wPAWN:
                scoreOpening += pst[opening][PAWN][square];
                scoreEndgame += pst[endgame][PAWN][square];
                break;
            
            case wKNIGHT:
                scoreOpening += pst[opening][KNIGHT][square];
                scoreEndgame += pst[endgame][KNIGHT][square];
                break;
            
            case wBISHOP:
                scoreOpening += pst[opening][BISHOP][square];
                scoreEndgame += pst[endgame][BISHOP][square];
                break;
            
            case wROOK:
                scoreOpening += pst[opening][ROOK][square];
                scoreEndgame += pst[endgame][ROOK][square];
                break;
            
            case wQUEEN:
                scoreOpening += pst[opening][QUEEN][square];
                scoreEndgame += pst[endgame][QUEEN][square];
                break;
            
            case wKING:
                scoreOpening += pst[opening][KING][square];
                scoreEndgame += pst[endgame][KING][square];
                break;

            case bPAWN:
                scoreOpening -= pst[opening][PAWN][mirrorSquare[square]];
                scoreEndgame -= pst[endgame][PAWN][mirrorSquare[square]];
                break;

            case bKNIGHT:
                scoreOpening -= pst[opening][KNIGHT][mirrorSquare[square]];
                scoreEndgame -= pst[endgame][KNIGHT][mirrorSquare[square]];
                break;
            
            case bBISHOP:
                scoreOpening -= pst[opening][BISHOP][mirrorSquare[square]];
                scoreEndgame -= pst[endgame][BISHOP][mirrorSquare[square]];
                break;
            
            case bROOK:
                scoreOpening -= pst[opening][ROOK][mirrorSquare[square]];
                scoreEndgame -= pst[endgame][ROOK][mirrorSquare[square]];
                break;
            
            case bQUEEN:
                scoreOpening -= pst[opening][QUEEN][mirrorSquare[square]];
                scoreEndgame -= pst[endgame][QUEEN][mirrorSquare[square]];
                break;
            
            case bKING:
                scoreOpening -= pst[opening][KING][mirrorSquare[square]];
                scoreEndgame -= pst[endgame][KING][mirrorSquare[square]];
                break;
            }

            board.unset_bit(square);
        }
    }

    // interpolate score in the middlegame
    if (game_phase == middlegame)
        score = (
            scoreOpening * game_phase_score +
            scoreEndgame * (opening_phase_score - game_phase_score)
        ) / opening_phase_score;
    else if (game_phase == opening) score = scoreOpening;
    else if (game_phase == endgame) score = scoreEndgame;

    return (state.current_color == WHITE) ? score: -score;
}