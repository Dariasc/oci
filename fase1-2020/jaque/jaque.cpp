#include <cstdio>
#include <vector>

enum Color {
    None = -1,
    White = 0,
    Black = 1,
};

enum Type {
    Tower = 0,
    Bishop = 1,
    Queen = 2,
    King = 3,
    Knight = 4,
    Pawn = 5
};

struct Piece {
    Color color;
    Type type;
};
Piece none_piece = { None, (Type) None };

struct Point {
    int x;
    int y;
};

void print_board(Piece board[8][8]) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            Piece piece = board[y][x];

            if (piece.color == None) {
                printf("  |");
                continue;
            } else if (piece.color == White) {
                printf("w");
            } else {
                printf("b");
            }

            switch (piece.type) {
                case Tower:
                    printf("T");
                    break;
                case Bishop:
                    printf("B");
                    break;
                case Queen:
                    printf("Q");
                    break;
                case King:
                    printf("K");
                    break;
                case Knight:
                    printf("H");
                    break;
                case Pawn:
                    printf("P");
            }
            printf("|");
        }
        printf("\n");
    }
}

// TODO: repetitive but idc
std::vector<Point> straight_moves(Point point, Piece piece, Piece board[8][8]) {
    std::vector<Point> moves;

    // move right
    for (int x = point.x + 1; x < 8; x++) {
        Piece at = board[point.y][x];
        if (at.color == None) {
            moves.push_back({ x, point.y });
        } else {
            if (at.color != piece.color) {
                moves.push_back({ x, point.y });
            }
            break;
        }
    }

    // move left
    for (int x = point.x - 1; x >= 0; x--) {
        Piece at = board[point.y][x];
        if (at.color == None) {
            moves.push_back({ x, point.y });
        } else {
            if (at.color != piece.color) {
                moves.push_back({ x, point.y });
            }
            break;
        }
    }

    // move up
    for (int y = point.y - 1; y >= 0; y--) {
        Piece at = board[y][point.x];
        if (at.color == None) {
            moves.push_back({ point.x, y });
        } else {
            if (at.color != piece.color) {
                moves.push_back({ point.x, y });
            }
            break;
        }
    }

    // move down
    for (int y = point.y + 1; y < 8; y++) {
        Piece at = board[y][point.x];
        if (at.color == None) {
            moves.push_back({ point.x, y });
        } else {
            if (at.color != piece.color) {
                moves.push_back({ point.x, y });
            }
            break;
        }
    }

    return moves;
}

std::vector<Point> diagonal_helper(Point point, Point direction, Piece piece, Piece board[8][8]) {
    std::vector<Point> moves;

    int y = point.y;
    for (int x = point.x + direction.x; x >= 0 && x < 8; x += direction.x) {
        y += direction.y;
        if (y < 0 || y > 7) {
            break;
        }


        Piece at = board[y][x];
        if (at.color == None) {
            moves.push_back({ x, y });
        } else {
            if (at.color != piece.color) {
                moves.push_back({ x, y });
            }
            break;
        }
    }

    return moves;
}

std::vector<Point> diagonal_moves(Point point, Piece piece, Piece board[8][8]) {
    std::vector<Point> moves;

    std::vector<Point> down_right = diagonal_helper(point, { 1,1 }, piece, board);
    moves.insert(moves.end(), down_right.begin(), down_right.end());

    std::vector<Point> down_left = diagonal_helper(point, { -1,1 }, piece, board);
    moves.insert(moves.end(), down_left.begin(), down_left.end());
    
    std::vector<Point> up_right = diagonal_helper(point, { 1,-1 }, piece, board);
    moves.insert(moves.end(), up_right.begin(), up_right.end());

    std::vector<Point> up_left = diagonal_helper(point, { -1,-1 }, piece, board);
    moves.insert(moves.end(), up_left.begin(), up_left.end());

    return moves;
}

std::vector<Point> horse_moves(Point point, Piece piece, Piece board[8][8]) {
    std::vector<Point> offsets = {
        { 2, 1 },
        { 1, 2 },
        { -2, 1 },
        { -1, 2 },
        { 2, -1 },
        { 1, -2},
        { -2, -1},
        { -1, -2},
    };

    std::vector<Point> moves;
    for (auto offset : offsets) {
        Point pos = { offset.x + point.x, offset.y + point.y };
        if ((pos.x >= 0 && pos.x < 8) && (pos.y >= 0 && pos.y < 8)) {
            Piece target = board[pos.y][pos.x];
            if (target.color != piece.color) {
                moves.push_back(pos);
            }
        }
    }

    return moves;
}

std::vector<Point> pawn_moves(Point point, Piece piece, Piece board[8][8]) {
    std::vector<Point> moves;

    // black goes down white goes up
    int direction = piece.color == Black ? 1 : -1;
    int new_y = direction + point.y;

    if (new_y < 0 && new_y > 7) {
        return moves;
    }

    Point vertical = { point.x, new_y };
    if (board[vertical.y][vertical.x].color == None) {
        moves.push_back(vertical);
    }

    Point right = { point.x + 1, new_y };
    if (right.x < 8 && board[right.y][right.x].color == 1 - piece.color) {
        moves.push_back(right);
    }

    Point left = { point.x - 1, new_y };
    if (left.x >= 0 && board[left.y][left.x].color == 1 - piece.color) {
        moves.push_back(left);
    } 

    return moves;
}

std::vector<Point> king_moves(Point point, Piece piece, Piece board[8][8]) {
    std::vector<Point> moves;

    for (int x = 1; x >= -1; x--) {
        for (int y = 1; y >= -1; y--) {
            if (x == 0 && y == 0) {
                continue;
            }

            Point new_pos = { point.x + x, point.y + y };
            if ((new_pos.x >= 0 && new_pos.x < 8) && (new_pos.y >= 0 && new_pos.y < 8)) {
                if (board[new_pos.y][new_pos.x].color != piece.color) {
                    moves.push_back(new_pos);
                }
            }
        }
    }

    return moves;
}

std::vector<Point> get_piece_moves(Point point, Piece piece, Piece board[8][8]) {
    std::vector<Point> piece_moves; 

    switch (piece.type) {
        case Tower:
            piece_moves = straight_moves(point, piece, board);
            break;
        case Bishop:
            piece_moves = diagonal_moves(point, piece, board);
            break;
        case Queen: {
            piece_moves = diagonal_moves(point, piece, board);
            std::vector<Point> straights = straight_moves(point, piece, board);
            piece_moves.insert(piece_moves.end(), straights.begin(), straights.end());
            break;
        }
        case King:
            piece_moves = king_moves(point, piece, board);
            break;
        case Knight:
            piece_moves = horse_moves(point, piece, board);
            break;
        case Pawn:
            piece_moves = pawn_moves(point, piece, board);
    }

    return piece_moves;
}

std::vector<Point> generate_all_moves(Color color, Piece board[8][8]) {
    std::vector<Point> moves;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            Piece piece = board[y][x];
            if (piece.color == color) {
                Point pos = { x, y };
                std::vector<Point> piece_moves = get_piece_moves(pos, piece, board); 
                moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
            }
        }
    }

    return moves;
}

void print_all_moves(Color color, Piece board[8][8]) {
    std::vector<Point> moves = generate_all_moves(color, board);
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            bool found = false;
            for (auto move : moves) {
                if (move.x == x && move.y == y) {
                    found = true;
                    break;
                }
            }
            if (found) {
                printf(" x|");
            } else {
                printf("  |");
            }
        }
        printf("\n");
    }
}


bool is_check(Piece board[8][8]) {
    Point king;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[y][x].color == White && board[y][x].type == King) {
                king = { x, y };
                break;
            }
        }
    }

    // see if under "check" from black
    for (Point move : generate_all_moves(Black, board)) {
        // printf("(%i,%i)\n", move.x, move.y);
        if (move.x == king.x && move.y == king.y) {
            return true;
        }
    }
    return false;
}

bool is_checkmate(Piece board[8][8]) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            Piece piece = board[y][x];
            if (piece.color == White) {
                Point pos = { x, y };
                std::vector<Point> piece_moves = get_piece_moves(pos, piece, board); 

                for (auto move : piece_moves) {
                    if (board[move.y][move.x].type == King) {
                        // cant move into king xd
                        continue;
                    } 
                    Piece copy[8][8];
                    for (int y = 0; y < 8; y++) {
                        for (int x = 0; x < 8; x++) {
                            copy[y][x] = board[y][x];
                        }
                    }

                    copy[y][x] = none_piece;
                    copy[move.y][move.x] = piece;

                    if (!is_check(copy)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


int main(void) {
    int piece_count;
    scanf("%i", &piece_count);

    Piece board[8][8];
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            Piece piece = none_piece;
            board[y][x] = piece;
        }
    }

    for (int i = 0; i < piece_count; i++) {
        int color, type, y, x;
        scanf("%i%i%i%i", &color, &type, &y, &x);
        
        Piece piece;
        piece.color = (Color) color;
        piece.type = (Type) type;
        board[y][x] = piece;
    }
    /*
    print_board(board);
    printf("\n");
    print_all_moves(Black, board);
    printf("\n");
    print_all_moves(White, board);*/

    printf("%i\n", is_checkmate(board));

    return 0;
}
