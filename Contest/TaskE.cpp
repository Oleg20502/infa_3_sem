#include <iostream>
#include <vector>

class Cell final {
public:
    char v;                                              // Вертикаль, от 'A' до 'H'
    unsigned short int h;                                // Горизонталь, от '1' до '8'
    Cell(): Cell('A',1) {}                               // Конструктор клетки по умолчанию
    Cell(char v, unsigned short int h): v(v), h(h) {}    // Конструктор заданной клетки поля с параметрами
};


class Piece{
public:
    virtual bool available(Cell c) const = 0;

    virtual ~Piece() = default;
};

class King: public Piece{
private:
    Cell pos;

public:
    King(Cell c)
    {
        pos.v = c.v;
        pos.h = c.h;
    }

    bool available(Cell c) const override {
        int dv = pos.v - c.v;
        int dh = pos.h - c.h;
        if (dv < 0){
            dv = -dv;
        }
        if (dh < 0){
            dh = -dh;
        }
        if((dv == 1 && dh == 1) || (dv == 0 && dh == 1) ||
            (dv == 1 && dh == 0)){
            return true;
        }
        else{
            return false;
        }
    }
};

class Bishop: public Piece{
private:
    Cell pos;

public:
    Bishop(Cell c)
    {
        pos.v = c.v;
        pos.h = c.h;
    }

    bool available(Cell c) const override {
        int dv = pos.v - c.v;
        int dh = pos.h - c.h;
        if (dv < 0){
            dv = -dv;
        }
        if (dh < 0){
            dh = -dh;
        }
        if(dv == dh && dv > 0){
            return true;
        }
        else{
            return false;
        }
    }
};


class Rook: public Piece{
private:
    Cell pos;

public:
    Rook(Cell c)
    {
        pos.v = c.v;
        pos.h = c.h;
    }

    bool available(Cell c) const override {
        if((pos.v == c.v || pos.h == c.h) && !(pos.v == c.v && pos.h == c.h)){
            return true;
        }
        else{
            return false;
        }
    }
};

class Queen: public Piece{
private:
    Cell pos;

public:
    Queen(Cell c)
    {
        pos.v = c.v;
        pos.h = c.h;
    }

    bool available(Cell c) const override {
        int dv = pos.v - c.v;
        int dh = pos.h - c.h;
        if (dv < 0){
            dv = -dv;
        }
        if (dh < 0){
            dh = -dh;
        }
        if((dv == dh && dv > 0) ||
           ((pos.v == c.v || pos.h == c.h) && !(pos.v == c.v && pos.h == c.h))){
            return true;
        }
        else{
            return false;
        }
    }
};

std::vector<bool> are_available(Cell c, std::vector<Piece*> const &pieces);

int main() {
    std::vector<Piece*> pieces;
    pieces.push_back(new King(Cell('A',1)));
    pieces.push_back(new Queen(Cell('B',2)));
    pieces.push_back(new Rook(Cell('C',3)));
    pieces.push_back(new Bishop(Cell('D',4)));

    for(auto b : are_available(Cell('H',8),pieces))
        std::cout << b << ' ';
    std::cout << std::endl;

    for (auto p : pieces)
        delete p;

    return 0;
}

std::vector<bool> are_available(Cell c, std::vector<Piece*> const &pieces) {
    std::vector<bool> answ;
    for (auto p : pieces)
        answ.push_back(p->available(c));
    return answ;
}
