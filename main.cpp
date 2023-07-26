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


void operator!(string &color)
{
if(color=="white")
    color="black";
else
    color="white";
}

pair<int, int> fromnametocoordinates(const string &s) {
    return make_pair(9 - int(char(s[0])) + 96, stoi(s.substr(1)));
}

string fromcoordinatestoname(pair<int, int> p) {
    return ((char((9 - p.first) + 96) + to_string(p.second)));
}

bool between1and8(int x) {
    if (x >= 1 && x <= 8)
        return true;
    return false;
}

map <string,int> colordir;


sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
sf::Clock appclock;
sf::Clock checkclock;
sf::Event event;
sf::Font font;

class textures {
public:
    static sf::Texture white_rook_texture;
    static sf::Texture black_rook_texture;
    static sf::Texture white_promotion_texture;
    static sf::Texture black_promotion_texture;
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

    void static create_white_promotion_texture()
    {
        white_promotion_texture.loadFromFile("assets\\promotions\\white_promotion.png");
    }
    void static create_black_promotion_texture()
    {
        black_promotion_texture.loadFromFile("assets\\promotions\\black_promotion.png");
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
        create_white_promotion_texture();
        create_black_promotion_texture();
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
sf::Texture textures::white_promotion_texture= sf::Texture();
sf::Texture textures::black_promotion_texture= sf::Texture();
class table;
class tile {
private:
    int row;
    int column;
    string letter;
    string color;
    string ontile;
    static int tile_dimension;
    sf::RectangleShape tilerectangle;
    sf::Sprite tilesprite;
    bool highlighted;
    bool checkhisghlight;
    sf::Color whitecolor=sf::Color(240,227,182);
    sf::Color blackcolor=sf::Color(36,36,36);
    sf::Color yellowcolor=sf::Color(255,249,128);
    sf::Color redcolor=sf::Color(255,97,97);
public:
    sf::RenderTexture tiletexture;

    tile(int r, int c) : row(r), column(c), letter(string(1, char(96 + (9 - c)))),
                         color((c + r) % 2 == 0 ? "white" : "black"), ontile("empty"), highlighted(false),checkhisghlight(false) {
    }

    tile(const tile &other) : row(other.row), column(other.column), letter(other.letter),
                              color(other.color), ontile(other.ontile), highlighted(other.highlighted),checkhisghlight(other.checkhisghlight) {}

    virtual ~tile() {};


    void setontile(const string &s) {
        ontile = s;
    };

    static int gettiledimension() {
        return tile_dimension;
    }

    void setCheckhisghlight(bool n){
        checkclock.restart();
        checkhisghlight=n;
    }

    void drawtile() {
        tiletexture.create(tile_dimension, tile_dimension);
        tilerectangle.setSize(sf::Vector2f(tile_dimension, tile_dimension));
        if(!highlighted)
            tilerectangle.setFillColor((column + row) % 2 == 0 ? whitecolor: blackcolor);
        else
            tilerectangle.setFillColor(yellowcolor);
        if(checkhisghlight)
        {
            if(checkclock.getElapsedTime().asSeconds()<1 && appclock.getElapsedTime().asSeconds()>1)
            {
                tilerectangle.setFillColor(redcolor);
            }
            else
                checkhisghlight= false;
        }
        sf::Text text(fromcoordinatestoname(make_pair(row, column)), font);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::Red);
        tiletexture.draw(tilerectangle);
        tiletexture.draw(text);
        tiletexture.display();
    }

    void drawtilesprite(sf::RenderTexture &t, const string &vp) {
        tilesprite.setTexture(tiletexture.getTexture());
        if (vp == "white")
            tilesprite.setPosition((8-row) * tile_dimension, (8-column) * tile_dimension);
        else
            tilesprite.setPosition((row-1) * tile_dimension, (column - 1) * tile_dimension);
        t.draw(tilesprite);
    }

    string getontile() {
        return ontile;
    }

    void setHighlighted(bool highlighted);

    pair<int, int> getcoordinates() {
        return make_pair(row, column);
    }


    friend ostream &operator<<(ostream &os, const tile &tile) {
        os << "row: " << tile.row << " column: " << tile.column << " letter: " << tile.letter
           << " color: " << tile.color << " on tile: " << tile.ontile << endl;
        return os;
    }
};

int tile::tile_dimension = max(int(window.getSize().y / 12), 60);

void tile::setHighlighted(bool highlighted) {
    tile::highlighted = highlighted;
}

class piece {
protected:
    static map<string, shared_ptr<tile>> totaltiles;
    pair<string, shared_ptr<tile>> tilepair;
    map<string, shared_ptr<tile>> possiblesquares;
    int value;
    string piececolor;
    int piece_dimension = max(int(window.getSize().y / 15), 48);
    int piecepadding = max((int(window.getSize().y / 15) - int(window.getSize().y / 12)) / 2, 6);
    sf::Sprite piece_sprite;
    bool moved = false;
public:

    piece(const pair<string, shared_ptr<tile>> &tp, int v,const string &piececolor)
            : tilepair(
            tp), possiblesquares({}), value(v), piececolor(piececolor) {
    }

    static void addtile( const string &x,const shared_ptr<tile> &t) {
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

    void drawpiecesprite() {
        piece_sprite.setScale(float(piece_dimension) / 128.0f, float(piece_dimension) / 128.0f);
        tilepair.second->tiletexture.draw(piece_sprite);
    }

    friend ostream &operator<<(ostream &os, const piece &piece) {
        os << "currenttile: " << piece.tilepair.second << " possiblesquares: ";
        for (auto itr = piece.possiblesquares.begin(); itr != piece.possiblesquares.end(); itr++) {
            os << itr->second << " " << endl;
        }
        os << " value: " << piece.value;
        return os;
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
    return piece_dimension;
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
            currentx = currentposition.first;
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
            currentx = currentposition.first;
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

    vector<pair<int, int>> movement;
public:
    pair <string,shared_ptr<tile>> enpassantsquare;
    pawn(const pair<string, shared_ptr<tile>> &tp, const string &piececolor) : piece(tp,
                                                                                     1,
                                                                                     piececolor) {
        enpassantsquare.second=0;
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

    void add_enpassantsquare(const string &s,shared_ptr<tile> &t){
        enpassantsquare= make_pair(s,t);
    };

    const shared_ptr<tile> &getEnpassantsquare() const {
        return enpassantsquare.second;
    }

    void remove_enpassant()
    {
        enpassantsquare.second=0;
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
                    }
                } else if (pawnmovetype > 2 && totaltiles[tilename]->getontile() != "empty" && totaltiles[tilename]->getontile() != piececolor) {
                    possiblesquares[tilename] = totaltiles[tilename];
                }
            }
        }
        if(enpassantsquare.second!=0)
        {
            possiblesquares[enpassantsquare.first]=enpassantsquare.second;
        }

    }

    ~pawn() {};


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
    bool longcastle;
    bool shortcastle;
public:
    king(const pair<string, shared_ptr<tile>> &tp,const string &piececolor) : piece(tp,  0,
                                                                                    piececolor),shortcastle(false),longcastle(false) {
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
        if(shortcastle)
        {
            //cout<<"SHORT CASTLE"<<fromcoordinatestoname(make_pair(currentx - 2, currenty));
            possiblesquares[fromcoordinatestoname(make_pair(currentx -2, currenty))]=totaltiles[fromcoordinatestoname(make_pair(currentx - 2, currenty))];
        }
        if(longcastle)
        {
            //cout<<"LONG CASTLE"<<fromcoordinatestoname(make_pair(currentx +2, currenty));
            possiblesquares[fromcoordinatestoname(make_pair(currentx +2, currenty))]=totaltiles[fromcoordinatestoname(make_pair(currentx + 2, currenty))];
        }
    }

    ~king() {};

    friend ostream &operator<<(ostream &os, const king &king) {
        os << static_cast<const piece &>(king);
        return os;
    }

    void setLongcastle(bool longcastle) {

        king::longcastle = longcastle;
    }

    void setShortcastle(bool shortcastle) {
        king::shortcastle = shortcastle;
    }
};

class table {
private:

    map<std::string, std::shared_ptr<piece>> tablepieces;
    map<std::string, std::shared_ptr<tile>> tabletiles;
    map<std::string, std::string> pieceontile;
    sf::RenderTexture tabletexture;
    sf::Sprite tablesprite;
    string viewposition;
    int table_dimension;
public:
    map<std::string, std::shared_ptr<piece>> backuppieces;
    explicit table(const string &gamemodetype): table_dimension(max(int(window.getSize().y * 2 / 3), 480)) {
        if (gamemodetype == "standard") {
            for (int i = 1; i <= 8; i++)
                for (int j = 1; j <= 8; j++) {
                    if (rand() % 2 == 1 )
                        viewposition = "white";
                    else
                        viewposition = "black";
                    shared_ptr<tile> newtilepointer = make_shared<tile>(tile(i, j));

                    string squarenamecreated = string(1, char(96 + (9 - i))) + to_string(j);

                    tabletiles[squarenamecreated] = newtilepointer;

                    pair<string, shared_ptr<tile>> paircreated = make_pair(squarenamecreated, newtilepointer);

                    piece::addtile(squarenamecreated, newtilepointer);

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
            tabletexture.create(table_dimension, table_dimension);
        }
    }

    const map<std::string, std::shared_ptr<piece>> &getBackuppieces() const {
        return backuppieces;
    }

    const map<std::string, std::shared_ptr<piece>> &getTablepieces() const {
        return tablepieces;
    }

    const map<std::string, std::shared_ptr<tile>> &getTabletiles() const {
        return tabletiles;
    }

    const map<std::string, std::string> &getPieceontile() const {
        return pieceontile;
    }

    const sf::RenderTexture &getTabletexture() const {
        return tabletexture;
    }

    const sf::Sprite &getTablesprite() const {
        return tablesprite;
    }

    const string &getViewposition() const {
        return viewposition;
    }

    int getTableDimension() const {
        return table_dimension;
    }

    ~table() {};

    bool  check_if_in_check(const string &color) {
        bool check = false;
        string king;
        if (color == "white")
            king="WK";
        else if (color == "black")
        king="BK";
        for (auto &i: tablepieces)
            if (i.second->getPiececolor() != color) {
                i.second->calculatepossiblemoves();
                for (auto &ps: i.second->getPossiblesquares()) {
                    if (ps.second == tablepieces[king]->getTilepair().second) {
                        cout << "CHECK "<<color  << endl;
                        check = true;
                    }
                }
            }
        return check;
    }
    void modify_pieceontile(const string &t,const string &p)
    {
        pieceontile[t]=p;
    }

    void modify_tablepieces(const string &p,shared_ptr<piece> &s)
    {
        tablepieces[p]=s;
    }

    void modify_tabletiles(const string &t,shared_ptr<piece> &s)
    {
        tablepieces[t]=s;
    }

    void modify_backuppieces(const string &t,shared_ptr<piece> &s)
    {
        backuppieces[t]=s;
    }

    void  calculateallmoves() {
        for (auto &j: tablepieces) {
            j.second->calculatepossiblemoves();
        }
    }

    void  takepiece(const string &piece_name) {
        tablepieces.erase(piece_name);
    }

    void  drawtable() {
        for (auto &i: tabletiles) {
            i.second->drawtile();
        }
        for (auto &j: tablepieces) {
            j.second->drawpiecesprite();
        }
        for (auto &i: tabletiles) {

            i.second->drawtilesprite(tabletexture, viewposition);
        }
        tabletexture.display();
    }

    void  drawtablesprite( sf::RenderTexture &t) {
        tablesprite.setTexture(tabletexture.getTexture());
        t.draw(tablesprite);
    }

    friend ostream &operator<<(ostream &os, const table &table) {
        os << "Table:" << endl;
        os << "pieces: ";
        for (auto &i: table.tablepieces)
            os << i.first << " " << i.second << " ";
        os << endl << "tiles: ";
        for (auto &i: table.tabletiles)
            os << i.first << " " << i.second << " " << endl;
        os << "viewpoint: " << table.viewposition << endl;
        return os;
    }
    void restore_table_from_history(const map<string ,string> &hist)
    {
        pieceontile=hist;
        for(auto &i:pieceontile)
        {
            if(i.second!="empty")
            {
                tablepieces[i.second]=backuppieces[i.second];
                tablepieces[i.second]->setTilepair(make_pair(i.first,tabletiles[i.first]));
                tabletiles[i.first]->setontile(tablepieces[i.second]->getPiececolor());
            }
            else
            {
                tabletiles[i.first]->setontile("empty");
            }
        }
        calculateallmoves();
    }

    void check_for_castle(const string &pt)
    {
        string sking;
        string sleftrook;
        string srightrook;
        int rank;
        if(pt=="white") {
            sking = "WK";
            rank = 1;
            sleftrook="lWR";
            srightrook="rWR";
        }
        else
        {
            sking="BK";
            rank=8;
            sleftrook="lBR";
            srightrook="rBR";
        }
        if(tablepieces[sking]->getMoved()== false) {
            int fin;
            int start;
            if(tablepieces.count(sleftrook))
            if (tablepieces[sleftrook]->getMoved() == false) {
                fin = tablepieces[sleftrook]->getTilepair().second->getcoordinates().first - 1;
                start = tablepieces[sking]->getTilepair().second->getcoordinates().first + 1;
                bool valid = true;
                for (int i = start; i <= fin; i++) {
                    if (tabletiles[fromcoordinatestoname(make_pair(i, rank))]->getontile() != "empty") {
                        valid = false;
                        break;
                    }
                }
                if (valid)
                {for (int g = fin - 1; g >= start - 1; g--) {
                        string initial = tabletiles[fromcoordinatestoname(make_pair(g, rank))]->getontile();
                        tabletiles[fromcoordinatestoname(make_pair(g, rank))]->setontile(pt);
                        for (auto &i: tablepieces)
                            if (i.second->getPiececolor() != pt) {
                                i.second->calculatepossiblemoves();//crapa
                                for (auto &ps: i.second->getPossiblesquares()) {
                                    if (ps.first == fromcoordinatestoname(make_pair(g, rank))) {
                                        valid = false;
                                        break;
                                    }
                                }
                            }
                        tabletiles[fromcoordinatestoname(make_pair(g, rank))]->setontile(initial);
                    }
            }
                dynamic_pointer_cast<king>(tablepieces[sking])->setLongcastle(valid);

            }
            if(tablepieces.count(srightrook))
            if (tablepieces[srightrook]->getMoved() == false) {
                start = tablepieces[srightrook]->getTilepair().second->getcoordinates().first + 1;
                fin = tablepieces[sking]->getTilepair().second->getcoordinates().first - 1;
                bool valid = true;
                for (int i = start; i <= fin; i++) {
                    if (tabletiles[fromcoordinatestoname(make_pair(i, rank))]->getontile() != "empty") {
                        valid = false;
                        break;
                    }
                }
                if(valid) {
                    for (int g = start; g <= start + 2; g++) {
                        string initial = tabletiles[fromcoordinatestoname(make_pair(g, rank))]->getontile();
                        tabletiles[fromcoordinatestoname(make_pair(g, rank))]->setontile(pt);
                        for (auto &i: tablepieces)
                            if (i.second->getPiececolor() != pt) {
                                i.second->calculatepossiblemoves();//crapa
                                for (auto &ps: i.second->getPossiblesquares()) {
                                    if (ps.first == fromcoordinatestoname(make_pair(g, rank))) {
                                        valid = false;
                                        break;
                                    }
                                }
                            }
                        tabletiles[fromcoordinatestoname(make_pair(g, rank))]->setontile(initial);
                    }
                }
                dynamic_pointer_cast<king>(tablepieces[sking])->setShortcastle(valid);
            }
        }
        };

    void move_rook_for_castling(const string &rook,const string &king,const string &dest_tile,const string &pt)
    {
        tablepieces[rook]->getTilepair().second->setontile("empty");
        pieceontile[tablepieces[rook]->getTilepair().first] = "empty";
        tablepieces[rook]->setTilepair(make_pair(dest_tile, tabletiles[dest_tile]));
        tablepieces[rook]->getTilepair().second->setontile(pt);
        pieceontile[dest_tile] = rook;
    }

    void short_castle(const string &pt)
    {
        string rightrook;string king;
        if(pt=="white") {
            rightrook="rWR";
            king="WK";
        }
        else
        {
            rightrook="rBR";
            king="BK";
        }
        //move rook
        string tile_rook_destination = fromcoordinatestoname(make_pair(tablepieces[king]->getTilepair().second->getcoordinates().first + 1,tablepieces[king]->getTilepair().second->getcoordinates().second));
        move_rook_for_castling(rightrook,king,tile_rook_destination,pt);
    }

    void long_castle(const string &pt)
    {
        string leftrook;string king;
        if(pt=="white") {
            leftrook="lWR";
            king="WK";
        }
        else
        {
            leftrook="lBR";
            king="BK";
        }
        //move rook
        string tile_rook_destination = fromcoordinatestoname(make_pair(tablepieces[king]->getTilepair().second->getcoordinates().first - 1,tablepieces[king]->getTilepair().second->getcoordinates().second));
        move_rook_for_castling(leftrook,king,tile_rook_destination,pt);
    }
};


class game {
private:
    string playerturn;
    string gamemode;
    int winner;
    string gamestate;
    int piecediffernce;
    float positiondifference;
    int movenumber;
    string string_pieceselected;
    string string_tileselected;
    string string_previous_tileselected;
    shared_ptr<piece> pieceselected;
    shared_ptr<tile> tileselected;
    shared_ptr<tile> previous_tileselected;
    sf::RectangleShape menu;
    bool promotionmenuopened;
    int game_dimension_x;
    int game_dimension_y;
    sf::Sprite white_promotion_sprite;
    sf::Sprite black_promotion_sprite;
    sf::RenderTexture gametexture;
    sf::Sprite gamesprite;
public:
    static vector<map<string ,string>> history;
    table gametable;

    explicit game(const string &g) : gamemode(g), gametable(g), playerturn("white"), tileselected(nullptr),pieceselected(nullptr),
                                     movenumber(0),promotionmenuopened(false){
        game_dimension_y=gametable.getTableDimension();
        game_dimension_x=game_dimension_y*5/4;
        gametexture.create(game_dimension_x, game_dimension_y);
        initialize_menu();
        history.push_back(gametable.getPieceontile());
        white_promotion_sprite.setTexture(textures::white_promotion_texture);
        black_promotion_sprite.setTexture(textures::black_promotion_texture);
        white_promotion_sprite.setScale((3.0f*float(gametable.getTableDimension()/8)/white_promotion_sprite.getTexture()->getSize().x),
                                        (0.75f*float(gametable.getTableDimension()/8)/white_promotion_sprite.getTexture()->getSize().y));
        black_promotion_sprite.setScale((3.0f*float(gametable.getTableDimension()/8)/white_promotion_sprite.getTexture()->getSize().x),
                                        (0.75f*float(gametable.getTableDimension()/8)/white_promotion_sprite.getTexture()->getSize().y));
        //cout<<playerturn<<" turn" <<movenumber<<endl;
    };

    virtual ~game() {};

    void turnfinished() {
        map <string,shared_ptr<piece>> tp=gametable.getTablepieces();
        for(auto i:tp)
            if(dynamic_pointer_cast<pawn>(i.second))
                if(dynamic_pointer_cast<pawn>(i.second)->getEnpassantsquare()!=0 && dynamic_pointer_cast<pawn>(i.second)->getPiececolor()==playerturn)
                    dynamic_pointer_cast<pawn>(i.second)->remove_enpassant();
        !playerturn;
    }

    void check_for_checkmate_or_stalemate() {
        bool can_avoid_check = false;
        bool in_check=gametable.check_if_in_check(playerturn);
        //map<string,shared_ptr<piece>> xyu=table::tablepieces;//may cause a bug if not added
        for(auto &possiblepiece:gametable.getTablepieces()) {
            if (possiblepiece.second->getPiececolor() == playerturn) {
                const map<string, shared_ptr<tile>> aps = possiblepiece.second->getPossiblesquares();
                for (auto &possiblemove: aps) {
                    shared_ptr<tile> prevtile=possiblepiece.second->getTilepair().second;
                    if (possiblemove.second->getontile() != "empty") {
                        map <string,string> up=gametable.getPieceontile();
                        gametable.takepiece(up[possiblemove.first]);
                    }
                    possiblepiece.second->setTilepair(make_pair(possiblemove.first, possiblemove.second));
                    possiblemove.second->setontile(possiblepiece.second->getPiececolor());
                    prevtile->setontile("empty");
                    if (!gametable.check_if_in_check(playerturn))
                    {
                        //    cout<<possiblepiece.first<<" "<<possiblemove.first<<endl;
                        can_avoid_check = true;
                        restore_game_from_history(history[movenumber], movenumber);
                        break;
                    }
                    restore_game_from_history(history[movenumber], movenumber);
                }
                if(can_avoid_check)
                    break;
            }
        }
        if(can_avoid_check==false) {
            cout<<"GAME DONE";
            if(in_check==false)
            {
                cout<< "draw";
            }
            if(playerturn=="white")
                cout<<"black_won";
            else
                cout<< "white_won";
        }

    };

    void checkenpassant()
    {
        map <string,string> pot=gametable.getPieceontile();
        map <string,shared_ptr<piece>> tp=gametable.getTablepieces();
        map <string,shared_ptr<tile>> tt=gametable.getTabletiles();
        int tile_selected_column;
        int tile_selected_row;
        string rightsquare=fromcoordinatestoname(make_pair(tileselected->getcoordinates().first + 1, tileselected->getcoordinates().second));
        string leftsquare=fromcoordinatestoname(make_pair(tileselected->getcoordinates().first - 1, tileselected->getcoordinates().second));
        if(tt.count(rightsquare) && pot[rightsquare] != "empty")//pion in dreapta
        {
            shared_ptr<piece> n1pawn  = tp[pot[rightsquare]];
            if(auto c= dynamic_pointer_cast<pawn>(n1pawn))
            {
                if(pieceselected->getPiececolor()=="white" && n1pawn->getPiececolor()=="black") {
                    c->add_enpassantsquare(fromcoordinatestoname(
                                                   make_pair(tileselected->getcoordinates().first, tileselected->getcoordinates().second - 1)),
                                           tt[fromcoordinatestoname(make_pair(tileselected->getcoordinates().first,
                                                                              tileselected->getcoordinates().second -
                                                                              1))]);
                }
                else  if(pieceselected->getPiececolor()=="black" && n1pawn->getPiececolor()=="white"){
                    c->add_enpassantsquare(fromcoordinatestoname(
                                                   make_pair(tileselected->getcoordinates().first, tileselected->getcoordinates().second + 1)),
                                           tt[fromcoordinatestoname(make_pair(tileselected->getcoordinates().first,
                                                                              tileselected->getcoordinates().second +
                                                                              1))]);
                }
            }
        }
        if(tt.count(leftsquare) && pot[leftsquare] != "empty")//pion in stanga
        {
            shared_ptr <piece> n2pawn = tp[pot[fromcoordinatestoname(make_pair(tileselected->getcoordinates().first - 1, tileselected->getcoordinates().second))]];
            if (auto c = dynamic_pointer_cast<pawn>(n2pawn)) {
                c->add_enpassantsquare(fromcoordinatestoname(make_pair( tileselected->getcoordinates().first , tileselected->getcoordinates().second+1)),tt[fromcoordinatestoname(make_pair( tileselected->getcoordinates().first , tileselected->getcoordinates().second+1))]);
                if(pieceselected->getPiececolor()=="white" && n2pawn->getPiececolor()=="black") {
                    c->add_enpassantsquare(fromcoordinatestoname(
                                                   make_pair(tileselected->getcoordinates().first, tileselected->getcoordinates().second - 1)),
                                           tt[fromcoordinatestoname(make_pair(tileselected->getcoordinates().first,
                                                                              tileselected->getcoordinates().second -
                                                                              1))]);
                }
                else if(pieceselected->getPiececolor()=="black" && n2pawn->getPiececolor()=="white"){
                    c->add_enpassantsquare(fromcoordinatestoname(
                                                   make_pair(tileselected->getcoordinates().first, tileselected->getcoordinates().second + 1)),
                                           tt[fromcoordinatestoname(make_pair(tileselected->getcoordinates().first,
                                                                              tileselected->getcoordinates().second +
                                                                              1))]);
                }
            }
        }
    }

    void restore_game_from_history(const map<string ,string> &hist, const int &mn){
        movenumber=mn;
        if(movenumber%2==0)
            playerturn="white";
        else
            playerturn="black";
        gametable.restore_table_from_history(hist);

    };
    void redo_invalid_move() {
        restore_game_from_history(history[movenumber], movenumber);
    }

    void selecttile(int x,int y)
    {
        map <string,shared_ptr<tile>> tt=gametable.getTabletiles();
        if (tileselected != nullptr) {
            previous_tileselected = tileselected;
            previous_tileselected->setHighlighted(false);
            string_previous_tileselected = string_tileselected;
        }
        if (gametable.getViewposition() == "white")
            string_tileselected = fromcoordinatestoname(
                    make_pair((8 - x / tile::gettiledimension()) , 8 - y / tile::gettiledimension() ));
        else
            string_tileselected = fromcoordinatestoname(
                    make_pair((x / tile::gettiledimension()) + 1, y / tile::gettiledimension() + 1));
        tileselected = tt[string_tileselected];
        tileselected->setHighlighted(true);
    }
    void selectpiece()
    {
        map <string,string> pot=gametable.getPieceontile();
        map <string,shared_ptr<piece>> tp=gametable.getTablepieces();
        if(pot[string_tileselected]!="empty")
        {
            if(tp[pot[string_tileselected]]->getPiececolor()==playerturn) {
                string_pieceselected = pot[string_tileselected];
                pieceselected = tp[string_pieceselected];
            }
        }
    }

    void executemovepart1()
    {
        map <string,string> pot=gametable.getPieceontile();
        pieceselected->setTilepair(make_pair(string_tileselected, tileselected));
        tileselected->setontile(pieceselected->getPiececolor());
        previous_tileselected->setontile("empty");
        if (tileselected->getontile() != "empty") {
            gametable.takepiece(pot[string_tileselected]);
        }
    }

    void promote(const string &promotion_piece)
    {
        gametable.takepiece(string_pieceselected);
        shared_ptr<piece> pointer_to_new_piece;
        if(promotion_piece=="queen")
        { pointer_to_new_piece=make_shared<queen>(queen(make_pair(string_tileselected,tileselected),pieceselected->getPiececolor()));}
        else if(promotion_piece=="rook")
            pointer_to_new_piece=make_shared<rook>(rook(make_pair(string_tileselected,tileselected),pieceselected->getPiececolor()));
        else if(promotion_piece=="knight")
            pointer_to_new_piece=make_shared<knight>(knight(make_pair(string_tileselected,tileselected),pieceselected->getPiececolor()));
        else if(promotion_piece=="bishop")
            pointer_to_new_piece=make_shared<bishop>(bishop(make_pair(string_tileselected,tileselected),pieceselected->getPiececolor()));
        gametable.modify_tablepieces(string_pieceselected,pointer_to_new_piece);
        gametable.modify_backuppieces(string_pieceselected,pointer_to_new_piece);
    }

    void executemovepart2()
    {
        map <string,string> pot=gametable.getPieceontile();
        map <string,shared_ptr<piece>> tp=gametable.getTablepieces();
        map <string,shared_ptr<tile>> tt=gametable.getTabletiles();
        pieceselected->setMoved(true);
        gametable.modify_pieceontile(string_tileselected,string_pieceselected);pot[string_tileselected]=string_pieceselected;
        gametable.modify_pieceontile(string_previous_tileselected,"empty");pot[string_previous_tileselected]="empty";
        for(auto &i:tp)
            if(i.second->getPiececolor()!=playerturn)
                gametable.calculateallmoves();
        for (auto &i:tt)
            i.second->setHighlighted(false);
        tileselected->setHighlighted(true);
        previous_tileselected->setHighlighted(true);
        pieceselected = nullptr;
        tileselected = nullptr;
        history.push_back(pot);
        movenumber+=1;
        turnfinished();
        cout<<playerturn<<" turn" <<movenumber<<endl;
    }

    void clickgame(int x,int y)
    {
        if(promotionmenuopened)
            clickpromotion(x,y);
        else
        {
            if(x<game_dimension_y && y<game_dimension_y)
                clicktile(x,y);
            else if(x>game_dimension_y && y<game_dimension_y && x<game_dimension_x)
            {

            }
        }
    }

    void clickpromotion(int x,int y)
    {
        map <string,shared_ptr<tile>> tt=gametable.getTabletiles();
        int unit=tile::gettiledimension();
        pair<int,int> tilecoords=tt[string_tileselected]->getcoordinates();
        float piecejump;
        float promstart;
        bool promoted=false;
        sf::Sprite sp;
        if(playerturn=="white") {
            piecejump = white_promotion_sprite.getGlobalBounds().width / 4;
            promstart = white_promotion_sprite.getPosition().x;
            sp=white_promotion_sprite;
        }

        else {
            piecejump = black_promotion_sprite.getGlobalBounds().width / 4;
            promstart = black_promotion_sprite.getPosition().x;
            sp=black_promotion_sprite;
        }
            if (y > sp.getPosition().y && y < sp.getPosition().y + unit) {
                if (x > promstart && x < promstart + piecejump) {
                    promote("queen");
                    promoted = true;//can add a bool function which returns true
                }
                else if (x > promstart + piecejump && x < promstart + 2 * piecejump) {
                    promote("bishop");
                    promoted = true;
                }
                else if (x > promstart + 2 * piecejump && x < promstart + 3 * piecejump) {
                    promote("knight");
                    promoted = true;
                }
                else if (x > promstart + 3 * piecejump && x < promstart + 4 * piecejump) {
                    promote("rook");
                    promoted = true;
                }
            }
        if(promoted) {
            executemovepart2();
            check_for_checkmate_or_stalemate();
        }
        else
            restore_game_from_history(history[movenumber],movenumber);
        promotionmenuopened= false;
    }

    void take_en_passant_pawn()
    {
        map <string,string> pot=gametable.getPieceontile();
        map <string,shared_ptr<tile>> tt=gametable.getTabletiles();
        string pawn_to_be_taken_tile;
        if (playerturn == "white") {
            pawn_to_be_taken_tile=fromcoordinatestoname(make_pair(tileselected->getcoordinates().first,tileselected->getcoordinates().second - 1));

        } else {
            pawn_to_be_taken_tile=fromcoordinatestoname(
                    make_pair(tileselected->getcoordinates().first,
                              tileselected->getcoordinates().second + 1));
        }
        gametable.takepiece(pot[pawn_to_be_taken_tile]);
        gametable.modify_pieceontile(pawn_to_be_taken_tile,"empty");
        tt[pawn_to_be_taken_tile]->setontile("empty");
    }

    void execute_castle()
    {
        if(auto x= dynamic_pointer_cast<king>(pieceselected)) {
            if (tileselected->getcoordinates().first - previous_tileselected->getcoordinates().first == 2) {
                gametable.long_castle(playerturn);
                dynamic_pointer_cast<king>(pieceselected)->setLongcastle(false);
            } else if (tileselected->getcoordinates().first - previous_tileselected->getcoordinates().first == -2) {
                gametable.short_castle(playerturn);
                dynamic_pointer_cast<king>(pieceselected)->setShortcastle(false);
            }
        }
    }

    bool check_and_treat_pawn_exceptions()
    {
        if(auto x= dynamic_pointer_cast<pawn>(pieceselected)) {
            if (tileselected == x->getEnpassantsquare()) {
                take_en_passant_pawn();
            } else if (abs(tileselected->getcoordinates().second - previous_tileselected->getcoordinates().second) !=
                       1) {
                checkenpassant();
            } else if (x->getPiececolor() == "white" && int(string_tileselected[1]) == 56) {//==8
                promotionmenuopened = true;
                return true;
            } else if (x->getPiececolor() == "black" && string_tileselected[1] == 49) {//==1
                promotionmenuopened = true;
                return true;
            }
        }
        return false;
    }
    bool watch_for_check() {
        map <string,shared_ptr<piece>> tp=gametable.getTablepieces();
        if (gametable.check_if_in_check(playerturn)) {
            if (playerturn == "white")
                tp["WK"]->getTilepair().second->setCheckhisghlight(true);
            else
                tp["BK"]->getTilepair().second->setCheckhisghlight(true);
            redo_invalid_move();
            return true;
        }
        return false;
    }
    void clicktile(int x, int y) {
        map <string,string> pot=gametable.getPieceontile();
        map <string,shared_ptr<piece>> tp=gametable.getTablepieces();
        map <string,shared_ptr<tile>> tt=gametable.getTabletiles();
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
                        if(check_and_treat_pawn_exceptions())
                            break;
                        if(watch_for_check())
                            break;
                        execute_castle();
                        gametable.check_for_castle(playerturn);
                        executemovepart2();
                        check_for_checkmate_or_stalemate();
                        break;
                    }
                }
            } else if (tileselected->getontile() == playerturn) {
                pieceselected==nullptr;
                selectpiece();
            }
        }
    }

    void initialize_menu()
    {
        menu.setSize(sf::Vector2f (game_dimension_x/5,game_dimension_y));
        menu.setPosition(game_dimension_y,0);
        menu.setFillColor(sf::Color::Green);
    }

    void drawgame()
    {
        map <string,string> pot=gametable.getPieceontile();
        map <string,shared_ptr<piece>> tp=gametable.getTablepieces();
        map <string,shared_ptr<tile>> tt=gametable.getTabletiles();
        gametable.drawtablesprite(gametexture);
        gametexture.draw(menu);
        int unit=tile::gettiledimension();
        if(promotionmenuopened)
        {
            if(playerturn=="white")
            {
                if(gametable.getViewposition()=="white")
                {
                    white_promotion_sprite.setPosition((8-tt[string_tileselected]->getcoordinates().first)*unit,(9-tt[string_tileselected]->getcoordinates().second)*unit);
                }
                else if (gametable.getViewposition()=="black")
                    white_promotion_sprite.setPosition((tt[string_tileselected]->getcoordinates().first-1)*unit,(tt[string_tileselected]->getcoordinates().second-2)*unit);
                gametexture.draw(white_promotion_sprite);
            }
            else if (playerturn=="black")
            {
                if(gametable.getViewposition()=="white")
                {
                    black_promotion_sprite.setPosition((8-tt[string_tileselected]->getcoordinates().first)*unit,(7-tt[string_tileselected]->getcoordinates().second)*unit);
                }
                else if (gametable.getViewposition()=="black")
                    black_promotion_sprite.setPosition((tt[string_tileselected]->getcoordinates().first-1)*unit,(tt[string_tileselected]->getcoordinates().second)*unit);
                gametexture.draw(black_promotion_sprite);
            }
        }
        gametexture.display();
        gamesprite.setTexture(gametexture.getTexture());
    }

    sf::Sprite &getGamesprite()
    {
        drawgame();
        return gamesprite;
    }

    friend ostream &operator<<(ostream &os, const game &game) {
        os << "playerturn: " << game.playerturn << " winner: " << game.winner << " piecediffernce: "
           << game.piecediffernce << " positiondifference: " << game.positiondifference << " gametable: "
           << game.gametable << " gamemode: " << game.gamemode;
        return os;
    }
};

vector<map<string ,string>> game::history={};


int main() {
    colordir["white"]=1;
    colordir["black"]=-1;
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

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == 0) {
                    g1.clickgame(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
        // clear the window with black color
        window.clear(sf::Color::Black);
// Draw it
        g1.gametable.drawtable();
        window.draw(g1.getGamesprite());
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