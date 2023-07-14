#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <cmath>
#include <random>

#include "C://SFML-2.6.0//include//SFML//System.hpp"
#include "C://SFML-2.6.0//include//SFML//Window.hpp"
#include "C://SFML-2.6.0//include//SFML//Graphics.hpp"

using namespace std;

pair<int, int> fromnametocoordinates(const string &s) {
    return make_pair(9 - int(char(s[0])) + 96, stoi(s.substr(1)));
}

string fromcoordinatestoname(pair<int, int> p) {
    return ((char((9 - p.first) + 96) + to_string(p.second)));
}

sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
sf::Font font;


class textures {
public:
    static sf::Texture white_rook_texture;
    static sf::Texture black_rook_texture;
    static sf::Texture white_queen_texture;
    static sf::Texture black_queen_texture;
    static sf::Texture white_king_texture;
    static sf::Texture black_king_texture;
    static sf::Texture white_pawn_texture;
    static sf::Texture black_pawn_texture;
    static sf::Texture white_knight_texture;
    static sf::Texture black_knight_texture;
    static sf::Texture white_bishop_texture;
    static sf::Texture black_bishop_texture;

    void static create_white_rook_texture() {
        white_rook_texture.loadFromFile("assets\\piece_icons\\white_rook.png");
    }

    void static create_black_rook_texture() {
        black_rook_texture.loadFromFile("assets\\piece_icons\\black_rook.png");
    }

    void static create_black_queen_texture() {
        black_queen_texture.loadFromFile("assets\\piece_icons\\black_queen.png");
    }

    void static create_white_queen_texture() {
        white_queen_texture.loadFromFile("assets\\piece_icons\\white_queen.png");
    }

    void static create_white_king_texture() {
        white_king_texture.loadFromFile("assets\\piece_icons\\white_king.png");
    }

    void static create_black_king_texture() {
        black_king_texture.loadFromFile("assets\\piece_icons\\black_king.png");
    }

    void static create_white_pawn_texture() {
        white_pawn_texture.loadFromFile("assets\\piece_icons\\white_pawn.png");
    }

    void static create_black_pawn_texture() {
        black_pawn_texture.loadFromFile("assets\\piece_icons\\black_pawn.png");
    }

    void static create_white_knight_texture() {
        white_knight_texture.loadFromFile("assets\\piece_icons\\white_knight.png");
    }

    void static create_black_knight_texture() {
        black_knight_texture.loadFromFile("assets\\piece_icons\\black_knight.png");
    }

    void static create_white_bishop_texture() {
        white_bishop_texture.loadFromFile("assets\\piece_icons\\white_bishop.png");
    }

    void static create_black_bishop_texture() {
        black_bishop_texture.loadFromFile("assets\\piece_icons\\black_bishop.png");
    }

    void static create_all_piece_textures() {
        create_white_rook_texture();
        create_black_rook_texture();
        create_white_queen_texture();
        create_black_queen_texture();
        create_black_bishop_texture();
        create_white_bishop_texture();
        create_black_king_texture();
        create_white_king_texture();
        create_black_pawn_texture();
        create_white_pawn_texture();
        create_black_knight_texture();
        create_white_knight_texture();
    }
};

sf::Texture textures::white_rook_texture = sf::Texture();
sf::Texture textures::black_rook_texture = sf::Texture();
sf::Texture textures::white_pawn_texture = sf::Texture();
sf::Texture textures::black_pawn_texture = sf::Texture();
sf::Texture textures::white_knight_texture = sf::Texture();
sf::Texture textures::black_knight_texture = sf::Texture();
sf::Texture textures::white_bishop_texture = sf::Texture();
sf::Texture textures::black_bishop_texture = sf::Texture();
sf::Texture textures::white_king_texture = sf::Texture();
sf::Texture textures::black_king_texture = sf::Texture();
sf::Texture textures::white_queen_texture = sf::Texture();
sf::Texture textures::black_queen_texture = sf::Texture();
class game;

class tile {
private:
    shared_ptr<game> t;
    int row;
    int column;
    string letter;
    string color;
    string ontile;
    static int dimension;
    sf::RectangleShape tilerectangle;
    sf::Sprite tilesprite;
    bool highlighted;
    //sf::Color sfcolor;
public:
    sf::RenderTexture tiletexture;

    tile(int r, int c) : row(r), column(c), letter(string(1, char(96 + (9 - c)))),
                         color((c + r) % 2 == 0 ? "white" : "black"), ontile("empty"), highlighted(false) {}

    tile(const tile &other) : row(other.row), column(other.column), letter(other.letter),
                              color(other.color), ontile(other.ontile) {}

    virtual ~tile() {};

/*    void setT(shared_ptr<game> u)
    {
        t=u;
    }*/

    void setontile(const string &s) {
        ontile = s;
    };

    static int gettiledimension() {
        return dimension;
    }

    /*shared_ptr<sf::RenderTexture> gettiletexture()
    {
        return make_shared<sf::RenderTexture>(tiletexture) ;
    }*/
    void drawtile() {
        tiletexture.create(dimension, dimension);
        tilerectangle.setSize(sf::Vector2f(dimension, dimension));
        tilerectangle.setFillColor(
                (column + row) % 2 == 0 ? sf::Color(240, 227, 182, 255) : sf::Color(36, 36, 36, 255));
        //cout<<" "<<row<<" "<<column<<" "<<fromcoordinatestoname(make_pair(row,column))<<" "<<(column - 1) * dimension<<" "<< (row - 1) * dimension<<" ";
        sf::Text text(fromcoordinatestoname(make_pair(row, column)), font);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::Red);
        tiletexture.draw(tilerectangle);
        tiletexture.draw(text);

    }

    void drawtilesprite(sf::RenderTexture &t, const string &vp) {
        tilesprite.setTexture(tiletexture.getTexture());
        if (vp == "black")
            tilesprite.setPosition((row - 1) * dimension, (8 - column) * dimension);
        else
            tilesprite.setPosition((8 - row) * dimension, (column - 1) * dimension);
        t.draw(tilesprite);
    }

    string getontile() {
        return ontile;
    }

    pair<int, int> getcoordinates() {
        return make_pair(row, column);
    }


    friend ostream &operator<<(ostream &os, const tile &tile) {
        os << "row: " << tile.row << " column: " << tile.column << " letter: " << tile.letter
           << " color: " << tile.color << " on tile: " << tile.ontile << endl;
        return os;
    }
};

int tile::dimension = max(int(window.getSize().y / 12), 60);


class piece {
protected:
    //static vector<shared_ptr<piece>> pieces;
    static map<string, shared_ptr<tile>> totaltiles;
    pair<string, shared_ptr<tile>> tilepair;
    map<string, shared_ptr<tile>> possiblesquares;
    int value;
    string piececolor;
    int piecedimension = max(int(window.getSize().y / 15), 48);
    int piecepadding = max((int(window.getSize().y / 15) - int(window.getSize().y / 12)) / 2, 6);
    sf::Sprite piece_sprite;
    bool moved = false;
public:

    piece(const pair<string, shared_ptr<tile>> &tp, int v,const string &piececolor)
            : tilepair(
            tp), possiblesquares({}), value(v), piececolor(piececolor) {
        //pieces.push_back(make_shared<piece>(*this));
    }

    static void addtile(const shared_ptr<tile> &t, const string &x) {
        totaltiles[x] = t;
    }

    virtual ~piece() {}

    void setMoved(bool moved);

    bool getMoved() const;

    void setTilepair(const pair<string, shared_ptr<tile>> &tilepair);

    static const map<string, shared_ptr<tile>> &getTotaltiles();

    const pair<string, shared_ptr<tile>> &getTilepair() const;

    const map<string, shared_ptr<tile>> &getPossiblesquares() const;

    int getValue() const;

    const string &getPiececolor() const;

    int getPiecedimension() const;

    int getPiecepadding() const;

    const sf::Sprite &getPieceSprite() const;

    void drawpiece() {
        piece_sprite.setScale(float(piecedimension) / 128.0f, float(piecedimension) / 128.0f);
        piece_sprite.setPosition(0, 0);
        tilepair.second->tiletexture.draw(piece_sprite);
    }

    friend ostream &operator<<(ostream &os, const piece &piece) {
        os << "currenttile: " << piece.tilepair.second << " possiblesquares: ";
        for (auto itr = piece.possiblesquares.begin(); itr != piece.possiblesquares.end(); itr++) {
            cout << itr->second << " " << endl;
        }
        os << " value: " << piece.value;
        return os;
    }

    bool between1and8(int x) {
        if (x >= 1 && x <= 8)
            return true;
        return false;
    }

    virtual void calculatepossiblemoves() = 0;
};

map<string, shared_ptr<tile>>  piece::totaltiles = {};

const map<string, shared_ptr<tile>> &piece::getTotaltiles() {
    return totaltiles;
}

const pair<string, shared_ptr<tile>> &piece::getTilepair() const {
    return tilepair;
}

const map<string, shared_ptr<tile>> &piece::getPossiblesquares() const {
    return possiblesquares;
}

int piece::getValue() const {
    return value;
}

const string &piece::getPiececolor() const {
    return piececolor;
}

int piece::getPiecedimension() const {
    return piecedimension;
}

int piece::getPiecepadding() const {
    return piecepadding;
}

const sf::Sprite &piece::getPieceSprite() const {
    return piece_sprite;
}

void piece::setTilepair(const pair<string, shared_ptr<tile>> &tilepair) {
    piece::tilepair = tilepair;
}

void piece::setMoved(bool moved) {
    piece::moved = moved;
}

bool piece::getMoved() const {
    return moved;
}
//vector<shared_ptr<piece>> piece::pieces = {};

class rook : public piece {
private:
    vector<pair<int, int>> const movement = {{1,  0},
                                             {0,  -1},
                                             {0,  1},
                                             {-1, 0}};

public:
    rook(const pair<string, shared_ptr<tile>> &tp, const string &piececolor) : piece(tp,
                                                                                                               5,
                                                                                                               piececolor) {
        piececolor == "white" ? piece_sprite.setTexture(textures::white_rook_texture) : piece_sprite.setTexture(
                textures::black_rook_texture);
    }

    void calculatepossiblemoves() override {

        pair<int, int> currentposition = fromnametocoordinates(tilepair.first);
        int currentx = currentposition.first;
        int currenty = currentposition.second;
        possiblesquares = {};
        for (auto &i: movement) {
            currentx = currentx = currentposition.first;
            currenty = currentposition.second;
            while (between1and8(currentx + i.first) && between1and8(currenty + i.second)) {
                string tilename = fromcoordinatestoname(make_pair(currentx + i.first, currenty + i.second));
                if (totaltiles[tilename]->getontile() == "empty") {
                    possiblesquares[tilename] = totaltiles[tilename];
                } else if (totaltiles[tilename]->getontile() == piececolor) {
                    break;
                } else {
                    possiblesquares[tilename] = totaltiles[tilename];
                    break;
                }
                currentx += i.first;
                currenty += i.second;
            }
        }
    }

    ~rook(){};

    friend ostream &operator<<(ostream &os, const rook &rook) {
        os << static_cast<const piece &>(rook);
        return os;
    }
};

class bishop : public piece {
private:
    vector<pair<int, int>> const movement = {{1,  1},
                                             {1,  -1},
                                             {-1, 1},
                                             {-1, -1}};
public:
    bishop(const pair<string, shared_ptr<tile>> &tp, const string &piececolor) : piece(tp,
                                                                                                                 3,
                                                                                                                 piececolor) {
        piececolor == "white" ? piece_sprite.setTexture(textures::white_bishop_texture) : piece_sprite.setTexture(
                textures::black_bishop_texture);
    }

    void calculatepossiblemoves() override {
        pair<int, int> currentposition = fromnametocoordinates(tilepair.first);
        int currentx = currentposition.first;
        int currenty = currentposition.second;
        possiblesquares = {};
        for (auto &i: movement) {
            currentx = currentx = currentposition.first;
            currenty = currentposition.second;
            while (between1and8(currentx + i.first) && between1and8(currenty + i.second)) {
                string tilename = fromcoordinatestoname(make_pair(currentx + i.first, currenty + i.second));
                if (totaltiles[tilename]->getontile() == "empty") {
                    possiblesquares[tilename] = totaltiles[tilename];
                } else if (totaltiles[tilename]->getontile() == piececolor) {
                    break;
                } else {
                    possiblesquares[tilename] = totaltiles[tilename];
                    break;
                }
                currentx += i.first;
                currenty += i.second;
            }
        }
    }

    ~bishop() {};

    friend ostream &operator<<(ostream &os, const bishop &bishop) {
        os << static_cast<const piece &>(bishop);
        return os;
    }
};

class knight : public piece {
private:
    vector<pair<int, int>> const movement = {{2,  1},
                                             {2,  -1},
                                             {-2, 1},
                                             {-2, -1},
                                             {1,  2},
                                             {-1, 2},
                                             {1,  -2},
                                             {-1, -2}};
public:
    knight(const pair<string, shared_ptr<tile>> &tp, const string &piececolor) : piece(tp,
                                                                                                                 3,
                                                                                                                 piececolor) {
        piececolor == "white" ? piece_sprite.setTexture(textures::white_knight_texture) : piece_sprite.setTexture(
                textures::black_knight_texture);
    }

    ~knight() {};

    friend ostream &operator<<(ostream &os, const knight &knight) {
        os << static_cast<const piece &>(knight);
        return os;
    }

    void calculatepossiblemoves() override {
        pair<int, int> currentposition = fromnametocoordinates(tilepair.first);
        int currentx = currentposition.first;
        int currenty = currentposition.second;
        possiblesquares = {};
        for (auto &i: movement) {
            if (between1and8(currentx + i.first) && between1and8(currenty + i.second)) {
                string tilename = fromcoordinatestoname(make_pair(currentx + i.first, currenty + i.second));
                if (totaltiles[tilename]->getontile() != piececolor) {
                    possiblesquares[tilename] = totaltiles[tilename];
                }
            }
        }
    }
};

class queen : public piece {
private:
    vector<pair<int, int>> const movement = {{1,  1},
                                             {1,  -1},
                                             {-1, 1},
                                             {-1, -1},
                                             {0,  1},
                                             {0,  -1},
                                             {1,  0},
                                             {-1, 0}};
public:
    queen(const pair<string, shared_ptr<tile>> &tp,const string &piececolor) : piece(tp,
                                                                                                                9,
                                                                                                                piececolor) {
        piececolor == "white" ? piece_sprite.setTexture(textures::white_queen_texture) : piece_sprite.setTexture(
                textures::black_queen_texture);
    }

    void calculatepossiblemoves() override {
        pair<int, int> currentposition = fromnametocoordinates(tilepair.first);
        int currentx = currentposition.first;
        int currenty = currentposition.second;
        possiblesquares = {};
        for (auto &i: movement) {
            currentx = currentx = currentposition.first;
            currenty = currentposition.second;
            while (between1and8(currentx + i.first) && between1and8(currenty + i.second)) {
                string tilename = fromcoordinatestoname(make_pair(currentx + i.first, currenty + i.second));
                if (totaltiles[tilename]->getontile() == "empty") {
                    possiblesquares[tilename] = totaltiles[tilename];
                } else if (totaltiles[tilename]->getontile() == piececolor) {
                    break;
                } else {
                    possiblesquares[tilename] = totaltiles[tilename];
                    break;
                }
                currentx += i.first;
                currenty += i.second;
            }
        }
    }

    ~queen() {};

    friend ostream &operator<<(ostream &os, const queen &queen) {
        os << static_cast<const piece &>(queen);
        return os;
    }
};

class pawn : public piece {
private:
    bool enpassantable = false;
    vector<pair<int, int>> movement;
public:
    pawn(const pair<string, shared_ptr<tile>> &tp, const string &piececolor) : piece(tp,
                                                                                                               1,
                                                                                                               piececolor) {
        if (piececolor == "black")
            movement = {{0,  -1},
                        {0,  -2},
                        {1,  -1},
                        {-1, -1}};
        else
            movement = {{0,  1},
                        {0,  2},
                        {1,  1},
                        {-1, 1}};
        piececolor == "white" ? piece_sprite.setTexture(textures::white_pawn_texture) : piece_sprite.setTexture(
                textures::black_pawn_texture);
    }

    void calculatepossiblemoves() override {
        pair<int, int> currentposition = fromnametocoordinates(tilepair.first);
        int currentx = currentposition.first;
        int currenty = currentposition.second;
        possiblesquares = {};
        int pawnmovetype = 0;
        for (auto &i: movement) {
            pawnmovetype += 1;

            if (between1and8(currentx + i.first) && between1and8(currenty + i.second)) {
                string tilename = fromcoordinatestoname(make_pair(currentx + i.first, currenty + i.second));
                if (pawnmovetype == 1 && totaltiles[tilename]->getontile() == "empty") {
                    possiblesquares[tilename] = totaltiles[tilename];
                } else if (pawnmovetype == 2 && totaltiles[tilename]->getontile() == "empty" && !moved) {
                    {
                        possiblesquares[tilename] = totaltiles[tilename];
                        enpassantable=true;
                    }
                } else if (pawnmovetype > 2 && totaltiles[tilename]->getontile() != "empty" && totaltiles[tilename]->getontile() != piececolor) {//or enpassant
                    possiblesquares[tilename] = totaltiles[tilename];
                }
            }
        }
    }

    ~pawn() {};

    bool isEnpassantable() const {
        return enpassantable;
    }

    friend ostream &operator<<(ostream &os, const pawn &pawn) {
        os << static_cast<const piece &>(pawn);
        return os;
    }
};

class king : public piece {
private:
    vector<pair<int, int>> const movement = {{1,  1},
                                             {1,  -1},
                                             {-1, 1},
                                             {-1, -1},
                                             {0,  1},
                                             {0,  -1},
                                             {1,  0},
                                             {-1, 0}};
public:
    king(const pair<string, shared_ptr<tile>> &tp,const string &piececolor) : piece(tp,  0,
                                                                                                         piececolor) {
        piececolor == "white" ? piece_sprite.setTexture(textures::white_king_texture) : piece_sprite.setTexture(
                textures::black_king_texture);
    }

    void calculatepossiblemoves() override {
        pair<int, int> currentposition = fromnametocoordinates(tilepair.first);
        int currentx = currentposition.first;
        int currenty = currentposition.second;
        possiblesquares = {};
        for (auto &i: movement) {
            if (between1and8(currentx + i.first) && between1and8(currenty + i.second)) {
                string tilename = fromcoordinatestoname(make_pair(currentx + i.first, currenty + i.second));
                if (totaltiles[tilename]->getontile() != piececolor) {
                    possiblesquares[tilename] = totaltiles[tilename];
                }
            }
        }
    }

    ~king() {};

    friend ostream &operator<<(ostream &os, const king &king) {
        os << static_cast<const piece &>(king);
        return os;
    }
};




class game {
    class table {
    public:
        static map<std::string, std::shared_ptr<piece>> backuppieces;
        static map<std::string, std::shared_ptr<piece>> tablepieces;
        static map<std::string, std::shared_ptr<tile>> tabletiles;
        static map<std::string, std::string> pieceontile;
        static sf::RenderTexture tabletexture;
        static sf::Sprite tablesprite;
        static string viewposition;
    public:
        explicit table(const string &gamemodetype) {
            if (gamemodetype == "standard") {
                for (int i = 1; i <= 8; i++)
                    for (int j = 1; j <= 8; j++) {
                        if (rand() % 2 == 2343)
                            viewposition = "white";
                        else
                            viewposition = "black";
                        shared_ptr<tile> newtilepointer = make_shared<tile>(tile(i, j));

                        string squarenamecreated = string(1, char(96 + (9 - i))) + to_string(j);

                        tabletiles[squarenamecreated] = newtilepointer;

                        pair<string, shared_ptr<tile>> paircreated = make_pair(squarenamecreated, newtilepointer);

                        piece::addtile(newtilepointer, squarenamecreated);

                        pieceontile[squarenamecreated] = "empty";

                        // black pieces
                        if (squarenamecreated == "a8") {
                            rook lBR(paircreated,  "black");
                            tablepieces["lBR"] = std::make_shared<rook>(lBR);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "lBR";
                        } else if (squarenamecreated == "b8") {
                            knight lBN(paircreated, "black");
                            tablepieces["lBN"] = std::make_shared<knight>(lBN);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "lBN";
                        } else if (squarenamecreated == "c8") {
                            bishop lBB(paircreated, "black");
                            tablepieces["lBB"] = std::make_shared<bishop>(lBB);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "lBB";
                        } else if (squarenamecreated == "d8") {
                            queen BQ(paircreated, "black");
                            tablepieces["BQ"] = std::make_shared<queen>(BQ);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "BQ";
                        } else if (squarenamecreated == "e8") {
                            king BK(paircreated,  "black");
                            tablepieces["BK"] = std::make_shared<king>(BK);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "BK";
                        } else if (squarenamecreated == "f8") {
                            bishop rBB(paircreated,  "black");
                            tablepieces["rBB"] = std::make_shared<bishop>(rBB);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "rBB";
                        } else if (squarenamecreated == "g8") {
                            knight rBN(paircreated, "black");
                            tablepieces["rBN"] = std::make_shared<knight>(rBN);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "rBN";
                        } else if (squarenamecreated == "h8") {
                            rook rBR(paircreated,  "black");
                            tablepieces["rBR"] = std::make_shared<rook>(rBR);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "rBR";
                        } else if (squarenamecreated == "a7") {
                            pawn aBP(paircreated,  "black");
                            tablepieces["aBP"] = std::make_shared<pawn>(aBP);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "aBP";
                        } else if (squarenamecreated == "b7") {
                            pawn bBP(paircreated,  "black");
                            tablepieces["bBP"] = std::make_shared<pawn>(bBP);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "bBP";
                        } else if (squarenamecreated == "c7") {
                            pawn cBP(paircreated, "black");
                            tablepieces["cBP"] = std::make_shared<pawn>(cBP);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "cBP";
                        } else if (squarenamecreated == "d7") {
                            pawn dBP(paircreated,  "black");
                            tablepieces["dBP"] = std::make_shared<pawn>(dBP);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "dBP";
                        } else if (squarenamecreated == "e7") {
                            pawn eBP(paircreated,  "black");
                            tablepieces["eBP"] = std::make_shared<pawn>(eBP);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "eBP";
                        } else if (squarenamecreated == "f7") {
                            pawn fBP(paircreated,  "black");
                            tablepieces["fBP"] = std::make_shared<pawn>(fBP);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "fBP";
                        } else if (squarenamecreated == "g7") {
                            pawn gBP(paircreated,  "black");
                            tablepieces["gBP"] = std::make_shared<pawn>(gBP);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "gBP";
                        } else if (squarenamecreated == "h7") {
                            pawn hBP(paircreated, "black");
                            tablepieces["hBP"] = std::make_shared<pawn>(hBP);
                            newtilepointer->setontile("black");
                            pieceontile[squarenamecreated] = "hBP";
                        }

// white pieces
                        else if (squarenamecreated == "a1") {
                            rook lWR(paircreated, "white");
                            tablepieces["lWR"] = std::make_shared<rook>(lWR);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "lWR";
                        } else if (squarenamecreated == "b1") {
                            knight lWN(paircreated,  "white");
                            tablepieces["lWN"] = std::make_shared<knight>(lWN);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "lWN";
                        } else if (squarenamecreated == "c1") {
                            bishop lWB(paircreated,  "white");
                            tablepieces["lWB"] = std::make_shared<bishop>(lWB);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "lWB";
                        } else if (squarenamecreated == "d1") {
                            queen WQ(paircreated,  "white");
                            tablepieces["WQ"] = std::make_shared<queen>(WQ);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "WQ";
                        } else if (squarenamecreated == "e1") {
                            king WK(paircreated,  "white");
                            tablepieces["WK"] = std::make_shared<king>(WK);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "WK";
                        } else if (squarenamecreated == "f1") {
                            bishop rWB(paircreated,  "white");
                            tablepieces["rWB"] = std::make_shared<bishop>(rWB);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "rWB";
                        } else if (squarenamecreated == "g1") {
                            knight rWN(paircreated,  "white");
                            tablepieces["rWN"] = std::make_shared<knight>(rWN);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "rWN";
                        } else if (squarenamecreated == "h1") {
                            rook rWR(paircreated,  "white");
                            tablepieces["rWR"] = std::make_shared<rook>(rWR);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "rWR";
                        } else if (squarenamecreated == "a2") {
                            pawn aWP(paircreated,  "white");
                            tablepieces["aWP"] = std::make_shared<pawn>(aWP);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "aWP";
                        } else if (squarenamecreated == "b2") {
                            pawn bWP(paircreated,  "white");
                            tablepieces["bWP"] = std::make_shared<pawn>(bWP);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "bWP";
                        } else if (squarenamecreated == "c2") {
                            pawn cWP(paircreated,  "white");
                            tablepieces["cWP"] = std::make_shared<pawn>(cWP);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "cWP";
                        } else if (squarenamecreated == "d2") {
                            pawn dWP(paircreated,  "white");
                            tablepieces["dWP"] = std::make_shared<pawn>(dWP);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "dWP";
                        } else if (squarenamecreated == "e2") {
                            pawn eWP(paircreated,  "white");
                            tablepieces["eWP"] = std::make_shared<pawn>(eWP);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "eWP";
                        } else if (squarenamecreated == "f2") {
                            pawn fWP(paircreated,  "white");
                            tablepieces["fWP"] = std::make_shared<pawn>(fWP);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "fWP";
                        } else if (squarenamecreated == "g2") {
                            pawn gWP(paircreated,  "white");
                            tablepieces["gWP"] = std::make_shared<pawn>(gWP);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "gWP";
                        } else if (squarenamecreated == "h2") {
                            pawn hWP(paircreated,  "white");
                            tablepieces["hWP"] = std::make_shared<pawn>(hWP);
                            newtilepointer->setontile("white");
                            pieceontile[squarenamecreated] = "hWP";
                        }

                    }
                backuppieces=tablepieces;
            }
        }

        static const map<std::string, std::shared_ptr<piece>> &getTablepieces();

        static const map<std::string, std::shared_ptr<tile>> &getTabletiles();

        static const map<std::string, std::string> &getPieceontile();

        static const sf::RenderTexture &getTabletexture();

        static const sf::Sprite &getTablesprite();

        static const string &getViewposition();

        ~table() {};

        void static create_table_texture() {
            tabletexture.create(max(int(window.getSize().y * 2 / 3), 480), max(int(window.getSize().y * 2 / 3), 480));
        }

        void static modify_pieceontile(const string &s, const string &t) {
            pieceontile[s] = t;
        }

        void checkenpassant()
        {
            for(auto &piece:tablepieces)
                if(auto pAwn=std::dynamic_pointer_cast<pawn>(piece.second))
                    if(pAwn->isEnpassantable()) {
                        pair<int, int> pAwncoords = fromnametocoordinates(pAwn->getTilepair().first);
                        /*shared_ptr<piece> neighbour1=tablepieces[pieceontile[fromcoordinatestoname(make_pair(pAwncoords.first-1,pAwncoords.second))]];
                        if (pAwn->getPiececolor() == "white") {
                            if (neighbour1->getPiececolor()=="black")

                        }
                        else
                        {

                        }*/
                    }
        }

        bool static check_if_in_check(const string &color) {
            cout<<"o";
            bool check = false;
            if (color == "white") {
                for (auto &i: tablepieces)
                    if (i.second->getPiececolor() != "white") {
                        i.second->calculatepossiblemoves();//crapa
                        for (auto &ps: i.second->getPossiblesquares()) {
                            if (ps.second == tablepieces["WK"]->getTilepair().second) {
                                cout << "CHECKW" << endl << endl;
                                check = true;
                            }
                        }
                }
            } else if (color == "black") {
                for (auto &i: tablepieces)
                    if (i.second->getPiececolor() != "black") {
                        i.second->calculatepossiblemoves();
                        for (auto &ps: i.second->getPossiblesquares()) {
                            if (ps.second == tablepieces["BK"]->getTilepair().second) {
                                //cout << "CHECKB" << endl << endl;
                                check = true;
                            }
                        }
                    }
            }
            return check;
        }



        void static calculateallmoves() {
            for (auto &j: tablepieces) {
                j.second->calculatepossiblemoves();
            }
        }

        void static takepiece(const string &piece_name) {
            tablepieces.erase(piece_name);
        }

        void static restorepiece(const string &piece_name,const shared_ptr<piece> &piece_pointer) {
            tablepieces[piece_name] = piece_pointer;
        }

        void static drawtable() {
            table::create_table_texture();
            for (auto &i: tabletiles) {
                i.second->drawtile();
                //cout<<i.second<<" "<<i.second->getcoordinates().first<<" "<<i.second->getcoordinates().second<<endl;
            }
            for (auto &j: tablepieces) {
                j.second->drawpiece();
            }
            for (auto &i: tabletiles) {

                i.second->drawtilesprite(tabletexture, viewposition);
            }

        }

        sf::Sprite static gettablesprite() {
            tablesprite.setTexture(tabletexture.getTexture());
            tablesprite.setPosition(0, 0);
            return tablesprite;
        }

        friend ostream &operator<<(ostream &os, const table &table) {
            os << "Table:" << endl;
            os << "pieces: ";
            for (auto &i: table::tablepieces)
                os << i.first << " " << i.second << " ";
            os << endl << "tiles: ";
            for (auto &i: table::tabletiles)
                os << i.first << " " << i.second << " " << endl;
            os << "viewpoint: " << table::viewposition << endl;
            return os;
        }

    };
private:

    string playerturn;
    string gamemode;
    int winner;
    int piecediffernce;
    float positiondifference;
    int movenumber;
    string string_pieceselected;
    string string_tileselected;
    string string_previous_tileselected;
    shared_ptr<piece> pieceselected;
    shared_ptr<tile> tileselected;
    shared_ptr<tile> previous_tileselected;
    shared_ptr<piece> piecetaken;
    string piecetakenname;
public:
    static vector<map<string ,string>> history;
    table gametable;

    explicit game(const string &g) : gamemode(g), gametable(g), playerturn("white"), tileselected(nullptr),pieceselected(nullptr),
    piecetaken(nullptr),movenumber(0){
        history.push_back(table::pieceontile);
    };

    virtual ~game() {};

    void turnfinished() {
        if (playerturn == "black")
            playerturn = "white";
        else
            playerturn = "black";
    }

    void check_for_checkmate_or_stalemate() {
        bool can_avoid_check = false;
        bool in_check=table::check_if_in_check(playerturn);
        for(auto possiblepiece:table::tablepieces) {
            if (possiblepiece.second->getPiececolor() == playerturn) {
                const map<string, shared_ptr<tile>> aps = possiblepiece.second->getPossiblesquares();
                for (auto &possiblemove: aps) {
                    //cout << possiblepiece.first << " " << possiblemove.first << " " << " ";
                    shared_ptr<tile> prevtile=possiblepiece.second->getTilepair().second;
                    possiblepiece.second->setTilepair(make_pair(possiblemove.first, possiblemove.second));
                    possiblemove.second->setontile(possiblepiece.second->getPiececolor());
                    prevtile->setontile("empty");
                    if (possiblemove.second->getontile() != "empty") {
                        takepiece();
                    }
                    if (!table::check_if_in_check(playerturn))
                    {
                        cout<<possiblepiece.first<<" "<<possiblemove.first;
                        can_avoid_check = true;
                        restore_game_table_from_history(history[movenumber],movenumber);
                        break;
                    }
                    restore_game_table_from_history(history[movenumber],movenumber);
                    //cout << "PP" << possiblepiece.second->getValue();
                }
                if(can_avoid_check)
                    break;
            }
        }
        if(can_avoid_check==false)
            cout<<"MATPAT";
    };
    void restore_game_table_from_history(const map<string ,string> &hist,const int &mn){
        movenumber=mn;
        if(movenumber%2==0)
            playerturn=="white";
        else
            playerturn="black";
        table::pieceontile=hist;
        for(auto &i:table::pieceontile)
        {
            if(i.second!="empty")
            {
                table::tablepieces[i.second]=table::backuppieces[i.second];
                table::tablepieces[i.second]->setTilepair(make_pair(i.first,table::tabletiles[i.first]));
                table::tabletiles[i.first]->setontile(table::tablepieces[i.second]->getPiececolor());
            }
            else
            {
                table::tabletiles[i.first]->setontile("empty");
            }
        }
    };
    void redo_invalid_move() {
        restore_game_table_from_history(history[movenumber],movenumber);
    }

    void selecttile(int x,int y)
    {

        if (tileselected != nullptr) {
            previous_tileselected = tileselected;
            string_previous_tileselected = string_tileselected;
        }
        if (table::getViewposition() == "white")
            string_tileselected = fromcoordinatestoname(
                    make_pair((8 - x / tile::gettiledimension()) + 1, y / tile::gettiledimension() + 1));
        else
            string_tileselected = fromcoordinatestoname(
                    make_pair((x / tile::gettiledimension()) + 1, y / tile::gettiledimension() + 1));
        tileselected = table::tabletiles[string_tileselected];
        // cout<<string_pieceselected<<" "<<string_tileselected;
    }
    void selectpiece()
    {
        string_pieceselected = table::pieceontile[string_tileselected];
        pieceselected = table::tablepieces[string_pieceselected];
    }

    void takepiece()
    {
        piecetaken = table::tablepieces[table::pieceontile[string_tileselected]];
        piecetakenname = table::pieceontile[string_tileselected];
        table::takepiece(table::pieceontile[string_tileselected]);
    }

    void executemovepart1()
    {
        pieceselected->setTilepair(make_pair(string_tileselected, tileselected));
        tileselected->setontile(pieceselected->getPiececolor());
        previous_tileselected->setontile("empty");
        if (tileselected->getontile() != "empty") {
            takepiece();
        }
    }
    void executemovepart2()
    {
        pieceselected->setMoved(true);
        table::modify_pieceontile(string_tileselected, string_pieceselected);
        table::modify_pieceontile(string_previous_tileselected, "empty");
        table::calculateallmoves();

        pieceselected = nullptr;
        tileselected = nullptr;
        history.push_back(table::pieceontile);
        movenumber+=1;
        turnfinished();
    }
    void clicktile(int x, int y) {
        selecttile(x,y);

        if (pieceselected == nullptr) {
            if (tileselected->getontile() == playerturn)
                selectpiece();
        }
        else {

            if (tileselected->getontile() != pieceselected->getPiececolor() &&playerturn == pieceselected->getPiececolor()) {
                pieceselected->calculatepossiblemoves();

                for (auto &ps: pieceselected->getPossiblesquares()) {
                    if (string_tileselected==ps.first) {//if move is valid

                        executemovepart1();
                        if (table::check_if_in_check(playerturn)) {
                            redo_invalid_move();

                            break;
                        }

                        executemovepart2();
                        check_for_checkmate_or_stalemate();
                        break;
                    }
                }
            } else if (tileselected->getontile() == playerturn) {
                selectpiece();
            }
        }
    }

    friend ostream &operator<<(ostream &os, const game &game) {
        os << "playerturn: " << game.playerturn << " winner: " << game.winner << " piecediffernce: "
           << game.piecediffernce << " positiondifference: " << game.positiondifference << " gametable: "
           << game.gametable << " gamemode: " << game.gamemode;
        return os;
    }
};

map<string, shared_ptr<piece>> game::table::backuppieces = {};
map<string, shared_ptr<piece>> game::table::tablepieces = {};
map<string, shared_ptr<tile>> game::table::tabletiles = {};
sf::RenderTexture game::table::tabletexture = {};
sf::Sprite game::table::tablesprite = {};
string game::table::viewposition;
map<string, string> game::table::pieceontile = {};
vector<map<string ,string>> game::history={};

const map<std::string, std::shared_ptr<piece>> &game::table::getTablepieces() {
    return tablepieces;
}

const map<std::string, std::shared_ptr<tile>> &game::table::getTabletiles() {
    return tabletiles;
}

const map<std::string, std::string> &game::table::getPieceontile() {
    return pieceontile;
}

const sf::RenderTexture &game::table::getTabletexture() {
    return tabletexture;
}

const sf::Sprite &game::table::getTablesprite() {
    return tablesprite;
}

const string &game::table::getViewposition() {
    return viewposition;
}

int main() {
    srand(time(nullptr));
    font.loadFromFile("assets\\font\\OpenSans-Regular.ttf");
    textures::create_all_piece_textures();
    //table("standard");
    // create the window//minw
    // run the program as long as the window is open
    window.setFramerateLimit(60);
    game g1("standard");
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == 0) {
                    g1.clicktile(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
// Draw it
        g1.gametable.drawtable();
        window.draw(g1.gametable.gettablesprite());
        // end the current frame
        window.display();
        window.clear(sf::Color::Black);
    }

    return 0;
}



//restore
//if(tileselected->getontile()!="empty")
//
//moveback














/* sf::RenderTexture t;
 t.create(500,500);
 sf::Texture t2;
 t2.loadFromFile("C:\\Users\\Andrei\\CLionProjects\\chessbot\\assets\\white_rook.png");

 sf::Sprite s;
 s.setTexture(t2);*/