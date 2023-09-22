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

map <string,int> colordir={{"white",-1},{"black",1}};


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

    void drawTile() {
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
                checkhisghlight=false;
        }
        sf::Text text(fromcoordinatestoname(make_pair(row, column)), font);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::Red);
        tiletexture.draw(tilerectangle);
        tiletexture.draw(text);
        tiletexture.display();
    }

    void drawTileSprite(sf::RenderTexture &t, const string &vp) {
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
    float value;
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

    void drawPieceSprite() {
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

    virtual void calculatePossibleMoves() = 0;
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

    void calculatePossibleMoves() override {
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
                                                                                       3.2,
                                                                                       piececolor) {
        piececolor == "white" ? piece_sprite.setTexture(textures::white_bishop_texture) : piece_sprite.setTexture(
                textures::black_bishop_texture);
    }

    void calculatePossibleMoves() override {
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

    void calculatePossibleMoves() override {
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
                                                                                     9.25,
                                                                                     piececolor) {
        piececolor == "white" ? piece_sprite.setTexture(textures::white_queen_texture) : piece_sprite.setTexture(
                textures::black_queen_texture);
    }

    void calculatePossibleMoves() override {
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
        enpassantsquare.second=nullptr;
    }

    void calculatePossibleMoves() override {
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
        if(enpassantsquare.second!=nullptr)
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

    void calculatePossibleMoves() override {
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

class game {
private:
    string gamemode;
    int winner;
    string gamestate;
    sf::RectangleShape menu;
    bool promotionmenuopened;
    int game_dimension_x;
    int game_dimension_y;
    sf::Sprite white_promotion_sprite;
    sf::Sprite black_promotion_sprite;
    sf::RenderTexture gametexture;
    sf::Sprite gamesprite;
    class table {
    public:
        vector <string> flags;
        string playerControl;
        string stringPieceSelected;
        string stringTileSelected;
        string stringPreviousTileSelected;
        string stringPieceTaken;
        shared_ptr<piece> pieceSelected;
        shared_ptr<piece> pieceTaken;
        shared_ptr<tile> tileSelected;
        shared_ptr<tile> previousTileSelected;
        pair <bool,vector<shared_ptr<pawn>>> enpassantpair;
        map<std::string, std::shared_ptr<piece>> tablePieces;
        map<std::string, std::shared_ptr<tile>> tableTiles;
        map<std::string, std::string> piecesOnTiles;
        sf::RenderTexture tabletexture;
        sf::Sprite tablesprite;
        string viewposition;
        int table_dimension;
        shared_ptr<game> gameref;
        map<std::string, std::shared_ptr<piece>> backuppieces;

        int movenumber;
        string playerTurn;
    public:
        explicit table(const string &gamemodetype,const string &p): table_dimension(max(int(window.getSize().y * 2 / 3), 480)), tileSelected(nullptr), pieceSelected(nullptr), pieceTaken(nullptr), playerTurn("white"),
                                                                    movenumber(0), playerControl(p),flags({"n","n","n","n","n"}) {
            if (gamemodetype == "standard") {
                for (int i = 1; i <= 8; i++)
                    for (int j = 1; j <= 8; j++) {
                        if (rand() % 2==0 )
                            viewposition = "white";
                        else
                            viewposition = "black";
                        shared_ptr<tile> newtilepointer = make_shared<tile>(tile(i, j));

                        string squarenamecreated = string(1, char(96 + (9 - i))) + to_string(j);

                        tableTiles[squarenamecreated] = newtilepointer;

                        pair<string, shared_ptr<tile>> paircreated = make_pair(squarenamecreated, newtilepointer);

                        piece::addtile(squarenamecreated, newtilepointer);

                        piecesOnTiles[squarenamecreated] = "empty";

                        // black pieces
                        if (squarenamecreated == "a8") {
                            rook lBR(paircreated,  "black");
                            tablePieces["lBR"] = std::make_shared<rook>(lBR);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "lBR";
                        } else if (squarenamecreated == "b8") {
                            knight lBN(paircreated, "black");
                            tablePieces["lBN"] = std::make_shared<knight>(lBN);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "lBN";
                        } else if (squarenamecreated == "c8") {
                            bishop lBB(paircreated, "black");
                            tablePieces["lBB"] = std::make_shared<bishop>(lBB);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "lBB";
                        } else if (squarenamecreated == "d8") {
                            queen BQ(paircreated, "black");
                            tablePieces["BQ"] = std::make_shared<queen>(BQ);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "BQ";
                        } else if (squarenamecreated == "e8") {
                            king BK(paircreated,  "black");
                            tablePieces["BK"] = std::make_shared<king>(BK);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "BK";
                        } else if (squarenamecreated == "f8") {
                            bishop rBB(paircreated,  "black");
                            tablePieces["rBB"] = std::make_shared<bishop>(rBB);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "rBB";
                        } else if (squarenamecreated == "g8") {
                            knight rBN(paircreated, "black");
                            tablePieces["rBN"] = std::make_shared<knight>(rBN);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "rBN";
                        } else if (squarenamecreated == "h8") {
                            rook rBR(paircreated,  "black");
                            tablePieces["rBR"] = std::make_shared<rook>(rBR);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "rBR";
                        } else if (squarenamecreated == "a7") {
                            pawn aBP(paircreated,  "black");
                            tablePieces["aBP"] = std::make_shared<pawn>(aBP);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "aBP";
                        } else if (squarenamecreated == "b7") {
                            pawn bBP(paircreated,  "black");
                            tablePieces["bBP"] = std::make_shared<pawn>(bBP);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "bBP";
                        } else if (squarenamecreated == "c7") {
                            pawn cBP(paircreated, "black");
                            tablePieces["cBP"] = std::make_shared<pawn>(cBP);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "cBP";
                        } else if (squarenamecreated == "d7") {
                            pawn dBP(paircreated,  "black");
                            tablePieces["dBP"] = std::make_shared<pawn>(dBP);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "dBP";
                        } else if (squarenamecreated == "e7") {
                            pawn eBP(paircreated,  "black");
                            tablePieces["eBP"] = std::make_shared<pawn>(eBP);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "eBP";
                        } else if (squarenamecreated == "f7") {
                            pawn fBP(paircreated,  "black");
                            tablePieces["fBP"] = std::make_shared<pawn>(fBP);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "fBP";
                        } else if (squarenamecreated == "g7") {
                            pawn gBP(paircreated,  "black");
                            tablePieces["gBP"] = std::make_shared<pawn>(gBP);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "gBP";
                        } else if (squarenamecreated == "h7") {
                            pawn hBP(paircreated, "black");
                            tablePieces["hBP"] = std::make_shared<pawn>(hBP);
                            newtilepointer->setontile("black");
                            piecesOnTiles[squarenamecreated] = "hBP";
                        }
// white pieces
                        else if (squarenamecreated == "a1") {
                            rook lWR(paircreated, "white");
                            tablePieces["lWR"] = std::make_shared<rook>(lWR);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "lWR";
                        } else if (squarenamecreated == "b1") {
                            knight lWN(paircreated,  "white");
                            tablePieces["lWN"] = std::make_shared<knight>(lWN);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "lWN";
                        } else if (squarenamecreated == "c1") {
                            bishop lWB(paircreated,  "white");
                            tablePieces["lWB"] = std::make_shared<bishop>(lWB);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "lWB";
                        } else if (squarenamecreated == "d1") {
                            queen WQ(paircreated,  "white");
                            tablePieces["WQ"] = std::make_shared<queen>(WQ);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "WQ";
                        } else if (squarenamecreated == "e1") {
                            king WK(paircreated,  "white");
                            tablePieces["WK"] = std::make_shared<king>(WK);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "WK";
                        } else if (squarenamecreated == "f1") {
                            bishop rWB(paircreated,  "white");
                            tablePieces["rWB"] = std::make_shared<bishop>(rWB);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "rWB";
                        } else if (squarenamecreated == "g1") {
                            knight rWN(paircreated,  "white");
                            tablePieces["rWN"] = std::make_shared<knight>(rWN);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "rWN";
                        } else if (squarenamecreated == "h1") {
                            rook rWR(paircreated,  "white");
                            tablePieces["rWR"] = std::make_shared<rook>(rWR);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "rWR";
                        } else if (squarenamecreated == "a2") {
                            pawn aWP(paircreated,  "white");
                            tablePieces["aWP"] = std::make_shared<pawn>(aWP);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "aWP";
                        } else if (squarenamecreated == "b2") {
                            pawn bWP(paircreated,  "white");
                            tablePieces["bWP"] = std::make_shared<pawn>(bWP);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "bWP";
                        } else if (squarenamecreated == "c2") {
                            pawn cWP(paircreated,  "white");
                            tablePieces["cWP"] = std::make_shared<pawn>(cWP);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "cWP";
                        } else if (squarenamecreated == "d2") {
                            pawn dWP(paircreated,  "white");
                            tablePieces["dWP"] = std::make_shared<pawn>(dWP);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "dWP";
                        } else if (squarenamecreated == "e2") {
                            pawn eWP(paircreated,  "white");
                            tablePieces["eWP"] = std::make_shared<pawn>(eWP);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "eWP";
                        } else if (squarenamecreated == "f2") {
                            pawn fWP(paircreated,  "white");
                            tablePieces["fWP"] = std::make_shared<pawn>(fWP);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "fWP";
                        } else if (squarenamecreated == "g2") {
                            pawn gWP(paircreated,  "white");
                            tablePieces["gWP"] = std::make_shared<pawn>(gWP);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "gWP";
                        } else if (squarenamecreated == "h2") {
                            pawn hWP(paircreated,  "white");
                            tablePieces["hWP"] = std::make_shared<pawn>(hWP);
                            newtilepointer->setontile("white");
                            piecesOnTiles[squarenamecreated] = "hWP";
                        }
                    }
                backuppieces=tablePieces;
                tabletexture.create(table_dimension, table_dimension);
            }
        }

        table(const table& t): stringPieceSelected(t.stringTileSelected), stringTileSelected(t.stringTileSelected), stringPreviousTileSelected(t.stringPreviousTileSelected), stringPieceTaken(t.stringPieceTaken),
                               pieceSelected(t.pieceSelected), pieceTaken(t.pieceTaken), tileSelected(t.tileSelected), previousTileSelected(t.previousTileSelected), tablePieces(t.tablePieces), tableTiles(t.tableTiles), piecesOnTiles(t.piecesOnTiles),
                               tablesprite(t.tablesprite), viewposition(t.viewposition), table_dimension(t.table_dimension), gameref(t.gameref), backuppieces(t.backuppieces), enpassantpair(t.enpassantpair){}

        const string &getViewposition() const {
            return viewposition;
        }

        int getTableDimension() const {
            return table_dimension;
        }

        ~table() {};
        bool  checkIfInCheck() {

    string king;

    if (playerTurn == "white")
        king="WK";
    else if (playerTurn == "black")
        king="BK";
    for (auto &i: tablePieces) {
        if (i.second->getPiececolor() != playerTurn) {
            i.second->calculatePossibleMoves();
            for (auto &ps: i.second->getPossiblesquares()) {
                if (ps.second == tablePieces[king]->getTilepair().second) {
                    return true;
                }
            }
        }
    }
            return false;
        }

        void  calculateallmoves() {
            for (auto &j: tablePieces) {
                j.second->calculatePossibleMoves();
            }
        }

        void takepiece(const string &piece_name) {
            tablePieces.erase(piece_name);
        }

        void drawTable() {
            for (auto &i: tableTiles) {
                i.second->drawTile();
            }
            for (auto &j: tablePieces) {
                j.second->drawPieceSprite();
            }
            for (auto &i: tableTiles) {

                i.second->drawTileSprite(tabletexture, viewposition);
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
            for (auto &i: table.tablePieces)
                os << i.first << " " << i.second << " ";
            os << endl << "tiles: ";
            for (auto &i: table.tableTiles)
                os << i.first << " " << i.second << " " << endl;
            os << "viewpoint: " << table.viewposition << endl;
            return os;
        }
        void clicktile(int x, int y) {
            if (playerControl != "bvb") {
                selecttile(x, y);
                if (pieceSelected == nullptr) {
                    if (tileSelected->getontile() == playerTurn)
                        selectpiece();
                } else {
                    if (tileSelected->getontile() != pieceSelected->getPiececolor() &&
                        playerTurn == pieceSelected->getPiececolor()) {
                        pieceSelected->calculatePossibleMoves();
                        for (auto &ps: pieceSelected->getPossiblesquares()) {
                            if (stringTileSelected == ps.first && (playerControl == "pvp" || playerTurn == viewposition))
                                if (executemove())
                                    break;
                        }
                    } else if (tileSelected->getontile() == playerTurn) {
                        pieceSelected == nullptr;
                        selectpiece();
                    }
                }
            }
        }

        bool executemove() {
            flags={"n","n","n"};
            executemovepart1();
            if (watch_for_check())
                return true;
            if (check_and_treat_pawn_exceptions()) {
                gameref->setpromotionmenutrue();
                return true;
            }
            execute_castle();
            check_for_castle();
            executemovepart2();
            increasemovenumber();
            turnfinished();
            check_for_checkmate_or_stalemate();
            return true;
        }

        void undoEntireMove(vector <string> f,const string& sps,const string& sts,const string& spts,const string& spt,shared_ptr<piece> ps,shared_ptr<piece> pt,shared_ptr<tile> ts,shared_ptr<tile> pts)
        {
            flags=f;
            stringTileSelected=sts;
            stringPieceSelected=sps;
            stringPreviousTileSelected=spts;
            stringPieceTaken=spt;
            tileSelected=ts;
            pieceSelected=ps;
            previousTileSelected=pts;
            pieceTaken=pt;
            if(pieceTaken==nullptr)
            {
                piecesOnTiles[stringTileSelected]="empty";
            }
            else
            {
                piecesOnTiles[stringTileSelected]=stringPieceTaken;
            }
            undoInvalidMove();
            if(flags[0]=="t")
            pieceSelected->setMoved(false);
            if(flags[1]=="lw")
                {
                    tablePieces["lWR"]->getTilepair().second->setontile("empty");
                    piecesOnTiles[tablePieces["lWR"]->getTilepair().first] = "empty";
                    tablePieces["lWR"]->setTilepair(make_pair("a1",tableTiles["a1"]));
                    tablePieces["lWR"]->getTilepair().second->setontile("white");
                    piecesOnTiles["a1"] = "lWR";
                }
            else if(flags[1]=="rw")
            {
                tablePieces["rWR"]->getTilepair().second->setontile("empty");
                piecesOnTiles[tablePieces["rWR"]->getTilepair().first] = "empty";
                tablePieces["rWR"]->setTilepair(make_pair("h1",tableTiles["h1"]));
                tablePieces["rWR"]->getTilepair().second->setontile("white");
                piecesOnTiles["h1"] = "rWR";
            }
            else if(flags[1]=="rb")
            {
                tablePieces["rBR"]->getTilepair().second->setontile("empty");
                piecesOnTiles[tablePieces["rBR"]->getTilepair().first] = "empty";
                tablePieces["rBR"]->setTilepair(make_pair("h8",tableTiles["h8"]));
                tablePieces["rBR"]->getTilepair().second->setontile("black");
                piecesOnTiles["h8"] = "rBR";
            }
            else if(flags[1]=="lb")
            {
                tablePieces["lBR"]->getTilepair().second->setontile("empty");
                piecesOnTiles[tablePieces["rBR"]->getTilepair().first] = "empty";
                tablePieces["lBR"]->setTilepair(make_pair("a8",tableTiles["h8"]));
                tablePieces["lBR"]->getTilepair().second->setontile("black");
                piecesOnTiles["a8"] = "lBR";
            }
            if(flags[2]!="n")
            {
                takepiece(stringPieceSelected);
                tablePieces[stringPieceSelected]=make_shared<pawn>(pawn(make_pair(stringPreviousTileSelected, previousTileSelected), pieceSelected->getPiececolor()));;
            }/*
            if(flags[3]!="n")
            {
                enpassantpair.first=true;
                enpassantpair.second.push_back(dynamic_pointer_cast<pawn>(tablePieces[flags[3].substr(0,3)]));
                dynamic_pointer_cast<pawn>(tablePieces[flags[3].substr(0,3)])->add_enpassantsquare(flags[3].substr(3,2),tableTiles[flags[3].substr(3,2)]);
            }*/
            piecesOnTiles[stringPreviousTileSelected]=stringPieceSelected;
            !playerTurn;
        }

        bool executevirtualmove()
        {
            flags={"n","n","n"};
            executemovepart1();
            if (checkIfInCheck())
            {

                undoInvalidMove();
                return false;
            }
            if (check_and_treat_pawn_exceptions()) {

                promote("queen");
            }
            execute_castle();
            check_for_castle();
            virtualexecutemovepart2();
            turnfinished();
            check_for_checkmate_or_stalemate();
            return true;
        }
        //increasemovenumber()
        void checkenpassant()
        {
            string rightsquare=fromcoordinatestoname(make_pair(tileSelected->getcoordinates().first + 1, tileSelected->getcoordinates().second));
            string leftsquare=fromcoordinatestoname(make_pair(tileSelected->getcoordinates().first - 1, tileSelected->getcoordinates().second));
            shared_ptr<piece> npawn;
            for (auto &i:{leftsquare,rightsquare}) {
                if (tableTiles.count(i) && piecesOnTiles[i] != "empty")
                {
                    npawn = tablePieces[piecesOnTiles[i]];
                    if (dynamic_pointer_cast<pawn>(npawn)) {
                        if (pieceSelected->getPiececolor() != npawn->getPiececolor() ) {
                            dynamic_pointer_cast<pawn>(npawn)->add_enpassantsquare(fromcoordinatestoname(make_pair(tileSelected->getcoordinates().first, tileSelected->getcoordinates().second + colordir[playerTurn])),
                                                                                   tableTiles[fromcoordinatestoname(make_pair(tileSelected->getcoordinates().first, tileSelected->getcoordinates().second + colordir[playerTurn]))]);
                        //flags[3]=piecesOnTiles[i]+fromcoordinatestoname(make_pair(tileSelected->getcoordinates().first, tileSelected->getcoordinates().second + colordir[playerTurn]));
                        enpassantpair.first=true;
                        enpassantpair.second.push_back(dynamic_pointer_cast<pawn>(npawn));
                        }
                    }
                }
            }
        }

        void promote(const string &promotion_piece)
        {
            flags[2]=stringPieceSelected;
            takepiece(stringPieceSelected);
            shared_ptr<piece> pointer_to_new_piece;
            if(promotion_piece=="queen")
            { pointer_to_new_piece=make_shared<queen>(queen(make_pair(stringTileSelected, tileSelected), pieceSelected->getPiececolor()));}
            else if(promotion_piece=="rook")
                pointer_to_new_piece=make_shared<rook>(rook(make_pair(stringTileSelected, tileSelected), pieceSelected->getPiececolor()));
            else if(promotion_piece=="knight")
                pointer_to_new_piece=make_shared<knight>(knight(make_pair(stringTileSelected, tileSelected), pieceSelected->getPiececolor()));
            else if(promotion_piece=="bishop")
                pointer_to_new_piece=make_shared<bishop>(bishop(make_pair(stringTileSelected, tileSelected), pieceSelected->getPiececolor()));
            tablePieces[stringPieceSelected]=pointer_to_new_piece;
        }

        void executemovepart2()
        {
            if(!pieceSelected->getMoved())
            {
                pieceSelected->setMoved(true);
                flags[0]="t";
            }
            piecesOnTiles[stringTileSelected]=stringPieceSelected;
            piecesOnTiles[stringPreviousTileSelected]="empty";
            for (auto &i:tableTiles)
                i.second->setHighlighted(false);
            tileSelected->setHighlighted(true);
            previousTileSelected->setHighlighted(true);
            //pieceSelected = nullptr;
            //tileSelected = nullptr;
        }



        void virtualexecutemovepart2(){
            if(!pieceSelected->getMoved())
            {
                pieceSelected->setMoved(true);
                flags[0]="t";
            }
            piecesOnTiles[stringTileSelected]=stringPieceSelected;
            piecesOnTiles[stringPreviousTileSelected]="empty";
            pieceSelected = nullptr;
            tileSelected = nullptr;
        }

        void take_en_passant_pawn()
        {
            string pawn_to_be_taken_tile;
            pawn_to_be_taken_tile=fromcoordinatestoname(make_pair(tileSelected->getcoordinates().first, tileSelected->getcoordinates().second + colordir[playerTurn]));
            takepiece(piecesOnTiles[pawn_to_be_taken_tile]);
            piecesOnTiles[pawn_to_be_taken_tile]="empty";
            tableTiles[pawn_to_be_taken_tile]->setontile("empty");
        }

        void selectpiece()
        {
            if(piecesOnTiles[stringTileSelected] != "empty")
            {
                if(tablePieces[piecesOnTiles[stringTileSelected]]->getPiececolor() == playerTurn) {
                    stringPieceSelected = piecesOnTiles[stringTileSelected];
                    pieceSelected = tablePieces[stringPieceSelected];
                }
            }
        }

        void executemovepart1()
        {
            pieceSelected->setTilepair(make_pair(stringTileSelected, tileSelected));
            tileSelected->setontile(pieceSelected->getPiececolor());
            previousTileSelected->setontile("empty");
            if (tileSelected->getontile() != "empty") {
                stringPieceTaken=piecesOnTiles[stringTileSelected];
                pieceTaken=tablePieces[stringPieceTaken];
                takepiece(stringPieceTaken);
            }
        }

        void execute_castle()
        {
            if(dynamic_pointer_cast<king>(pieceSelected)) {
                if (tileSelected->getcoordinates().first - previousTileSelected->getcoordinates().first == 2) {
                    long_castle(playerTurn);
                    dynamic_pointer_cast<king>(pieceSelected)->setLongcastle(false);
                } else if (tileSelected->getcoordinates().first - previousTileSelected->getcoordinates().first == -2) {
                    short_castle(playerTurn);
                    dynamic_pointer_cast<king>(pieceSelected)->setShortcastle(false);
                }
            }
        }

        bool check_and_treat_pawn_exceptions()
        {
            if(auto x= dynamic_pointer_cast<pawn>(pieceSelected)) {
                if (tileSelected == x->getEnpassantsquare()) {
                    take_en_passant_pawn();
                } else if (abs(tileSelected->getcoordinates().second - previousTileSelected->getcoordinates().second) !=
                           1) {
                    checkenpassant();
                } else if (x->getPiececolor() == "white" && stringTileSelected[1] == 56) {//==8
                    return true;
                } else if (x->getPiececolor() == "black" && stringTileSelected[1] == 49) {//==1
                    return true;
                }
            }
            return false;
        }

        bool watch_for_check() {

            if (checkIfInCheck()) {
                if (playerTurn == "white")
                    tablePieces["WK"]->getTilepair().second->setCheckhisghlight(true);
                else
                    tablePieces["BK"]->getTilepair().second->setCheckhisghlight(true);
                undoInvalidMove();
                cout << "CHECK " << playerTurn << endl;
                return true;

                return false;
            }
        }
        void turnfinished() {
            if(enpassantpair.first)
            {
                for(auto &i:enpassantpair.second)
                    if(i->getPiececolor() == playerTurn)
                        i->remove_enpassant();
            }
            !playerTurn;
        }

        void increasemovenumber()
        {
            ++movenumber;
        }



        void check_for_castle()
        {   !playerTurn;
            string sking;
            string sleftrook;
            string srightrook;
            int rank;
            bool lvalid=false;
            bool rvalid=false;
            if(playerTurn == "white") {
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
            !playerTurn;
            if(!tablePieces[sking]->getMoved()) {
                int fin;
                int start;
                if(tablePieces.count(sleftrook))
                    if (!tablePieces[sleftrook]->getMoved()) {
                        fin = tablePieces[sleftrook]->getTilepair().second->getcoordinates().first - 1;
                        start = tablePieces[sking]->getTilepair().second->getcoordinates().first + 1;
                        lvalid = true;
                        for (int i = start; i <= fin; i++) {
                            if (tableTiles[fromcoordinatestoname(make_pair(i, rank))]->getontile() != "empty") {
                                lvalid = false;
                                break;
                            }
                        }
                        if (lvalid)
                        {for (int g = fin - 1; g >= start - 1; g--) {
                                {
                                    for (auto &i: tablePieces)
                                        if (i.second->getPiececolor() == playerTurn) {
                                            i.second->calculatePossibleMoves();//crapa
                                            for (auto &ps: i.second->getPossiblesquares()) {
                                                if (ps.first == fromcoordinatestoname(make_pair(g, rank))) {
                                                    lvalid = false;
                                                    break;
                                                }
                                            }
                                        }
                                }
                            }
                        }

                    }

                if(tablePieces.count(srightrook))
                    if (!tablePieces[srightrook]->getMoved()) {
                        start = tablePieces[srightrook]->getTilepair().second->getcoordinates().first + 1;
                        fin = tablePieces[sking]->getTilepair().second->getcoordinates().first - 1;
                        rvalid = true;
                        for (int i = start; i <= fin; i++) {
                            if (tableTiles[fromcoordinatestoname(make_pair(i, rank))]->getontile() != "empty") {
                                rvalid = false;
                                break;
                            }
                        }
                        if (rvalid) {
                            for (int g = start; g <= start + 2; g++) {
                                {
                                    for (auto &i: tablePieces)
                                        if (i.second->getPiececolor() == playerTurn) {
                                            i.second->calculatePossibleMoves();//crapa
                                            for (auto &ps: i.second->getPossiblesquares()) {
                                                if (ps.first == fromcoordinatestoname(make_pair(g, rank))) {
                                                    rvalid = false;
                                                    break;
                                                }
                                            }
                                        }
                                }
                            }

                        }
                    }

            }
            dynamic_pointer_cast<king>(tablePieces[sking])->setLongcastle(lvalid);
            dynamic_pointer_cast<king>(tablePieces[sking])->setShortcastle(rvalid);
        };

        void move_rook_for_castling(const string &rook,const string &king,const string &dest_tile,const string &pt)
        {
            tablePieces[rook]->getTilepair().second->setontile("empty");
            piecesOnTiles[tablePieces[rook]->getTilepair().first] = "empty";
            tablePieces[rook]->setTilepair(make_pair(dest_tile, tableTiles[dest_tile]));
            tablePieces[rook]->getTilepair().second->setontile(pt);
            piecesOnTiles[dest_tile] = rook;
        }

        void short_castle(const string &pt)
        {
            string rightrook;string king;
            if(pt=="white") {
                rightrook="rWR";
                king="WK";
                flags[1]="rw";
            }
            else
            {
                rightrook="rBR";
                king="BK";
                flags[1]="rb";
            }
            //move rook
            string tile_rook_destination = fromcoordinatestoname(make_pair(tablePieces[king]->getTilepair().second->getcoordinates().first + 1, tablePieces[king]->getTilepair().second->getcoordinates().second));
            move_rook_for_castling(rightrook,king,tile_rook_destination,pt);

        }

        void long_castle(const string &pt)
        {
            string leftrook;string king;
            if(pt=="white") {
                leftrook="lWR";
                king="WK";
                flags[1]="lw";
            }
            else
            {
                leftrook="lBR";
                king="BK";
                flags[1]="lb";
            }
            //move rook
            string tile_rook_destination = fromcoordinatestoname(make_pair(tablePieces[king]->getTilepair().second->getcoordinates().first - 1, tablePieces[king]->getTilepair().second->getcoordinates().second));
            move_rook_for_castling(leftrook,king,tile_rook_destination,pt);
            flags[1]="l";
        }

        void selecttile(int x,int y)
        {
            if (tileSelected != nullptr) {
                previousTileSelected = tileSelected;
                previousTileSelected->setHighlighted(false);
                stringPreviousTileSelected = stringTileSelected;
            }
            if (getViewposition() == "white")
                stringTileSelected = fromcoordinatestoname(
                        make_pair((8 - x / tile::gettiledimension()) , 8 - y / tile::gettiledimension()));
            else
                stringTileSelected = fromcoordinatestoname(
                        make_pair((x / tile::gettiledimension()) + 1, y / tile::gettiledimension() + 1));
            tileSelected = tableTiles[stringTileSelected];
            tileSelected->setHighlighted(true);
        }

        void undoInvalidMove() {
            pieceSelected->setTilepair(make_pair(stringPreviousTileSelected, previousTileSelected));
            previousTileSelected->setontile(pieceSelected->getPiececolor());
            if (pieceTaken != nullptr) {
                tablePieces[stringPieceTaken]=pieceTaken;
                piecesOnTiles[stringTileSelected]=stringPieceTaken;
                tileSelected->setontile(pieceTaken->getPiececolor());
                pieceTaken=nullptr;
            }
            else
            {
                tileSelected->setontile("empty");
            }
        }

        string check_for_checkmate_or_stalemate() {
            bool can_avoid_check = false;
            bool in_check= checkIfInCheck();
            pair<string,shared_ptr<tile>> prevtile;
            shared_ptr <piece> piet=nullptr;//err
            string piets;
            for(auto &possiblepiece:tablePieces) {
                if (possiblepiece.second->getPiececolor() == playerTurn) {
                    for (auto &possiblemove: possiblepiece.second->getPossiblesquares()) {
                        prevtile=possiblepiece.second->getTilepair();
                        if (possiblemove.second->getontile() != "empty") {
                            piets=piecesOnTiles[possiblemove.first];
                            piet=tablePieces[piets];
                            takepiece(piecesOnTiles[possiblemove.first]);
                        }
                        possiblepiece.second->setTilepair(make_pair(possiblemove.first, possiblemove.second));
                        possiblemove.second->setontile(possiblepiece.second->getPiececolor());
                        prevtile.second->setontile("empty");
                        if (!checkIfInCheck())
                        {
                            possiblepiece.second->setTilepair(make_pair(prevtile.first, prevtile.second));
                            prevtile.second->setontile(possiblepiece.second->getPiececolor());
                            if (piet!=nullptr) {
                                tablePieces[piets]=piet;
                                possiblemove.second->setontile(piet->getPiececolor());
                                piet=nullptr;
                            }
                            else
                            {
                                possiblemove.second->setontile("empty");
                            }
                            can_avoid_check = true;
                            break;
                        }
                        possiblepiece.second->setTilepair(make_pair(prevtile.first, prevtile.second));
                        prevtile.second->setontile(possiblepiece.second->getPiececolor());
                        if (piet!=nullptr) {
                            tablePieces[piets]=piet;
                            possiblemove.second->setontile(piet->getPiececolor());
                            piet=nullptr;
                        }
                        else
                        {
                            possiblemove.second->setontile("empty");
                        }
                    }
                    if(can_avoid_check)
                        return "p";
                }
                if(can_avoid_check)
                    return "p";
            }
            if(can_avoid_check==false) {
                //cout<<"GAME DONE";
                if(in_check==false)
                {
                    return "draw";
                }
                if(playerTurn == "white")
                    return "black_won";
                else
                    return "white_won";
            }
        };
        void endPromotion(){
            check_for_castle();
            executemovepart2();
            increasemovenumber();
            turnfinished();
            check_for_checkmate_or_stalemate();
        }
    };

    table gametable;
    class bot {
    private:
        int depth;
        table &gametable;
        float piecedifference;
        float positiondifference;
        int number;
        vector<string> flagss;
        string stringPieceTakenn;
        shared_ptr<piece> pieceTakenn;
        string gameStatus;
        float eval;
        pair<float, float> resultOfRecursion;
        bool passed = false;
        map<string, bool> colorToBool;
        vector<int> v={-1,3,5,8,-6,-4,7,8};
        int indice=0;
    public:
        bool minMaxOrMaxMin;

        bot(table &t) : gametable(t), depth(2), number(0), piecedifference(0), gameStatus(""), colorToBool(
                {{"white", 1},
                 {"black", 0}}) {}

        void freef()
        {
            minMaxOrMaxMin=0;
            cout<<minMaxOrMaxMin<<"COL"<<endl;
        }
        pair<float,float> rec(int d,float mi,float ma,float alpha,float beta) {
            d--;
            float minn = 100;
            float maxx = 0;
            for (int i = 0; i < 1; i++)
            {
                for (int j = 1; j >= 0; j--) {
                    if (d == 0) {
                        eval = v[indice];
                        indice++;
                        cout << eval << " ";
                        if (eval > maxx)
                            maxx = eval;
                        return make_pair(minn,maxx);
                    } else {
                        resultOfRecursion = rec(d, minn, maxx, alpha, beta);
                        if (d % 2 == minMaxOrMaxMin) {
                            eval = resultOfRecursion.first;
                            if (eval > maxx)
                                maxx = eval;
                            beta = min(eval, beta);
                            if (beta <= alpha) {
                                cout << "BREAK DIN FOR" << endl;
                                return make_pair(minn,maxx);
                            }
                        } else if (d % 2 !=minMaxOrMaxMin) {

                            eval = resultOfRecursion.second;
                            if (eval < minn)
                                minn = eval;
                            alpha = max(eval, alpha);
                            if (beta <= alpha)
                            {
                            cout << "BREAK DIN FOR" << endl;
                                return make_pair(minn,maxx);
                            }
                        }
                        //cout << endl<<alpha<<" "<<beta<<endl;
                    }
                }
        }
            return make_pair(minn,maxx);
        }
        void calculatePieceDifference()
        {
            piecedifference=0;
            for(auto &i:gametable.tablePieces)
                if(i.second->getPiececolor()=="white")
                    piecedifference+=i.second->getValue();
                else
                    piecedifference-=i.second->getValue();
        }
        float calculatePiecePositionValue()
        {
            float piecePositionValue=0;
            for(auto &i:gametable.tablePieces)
                    for(int j=0;j<i.second->getPossiblesquares().size();j++)
                        if(i.second->getPiececolor()=="white")
                            piecePositionValue+=0.2;
                        else
                            piecePositionValue-=0.2;
                        return piecePositionValue;
        }
        void evaluateposition()
        {
            gameStatus=gametable.check_for_checkmate_or_stalemate();
            if(gameStatus=="white_won")
                positiondifference=1000;
            else  if(gameStatus=="black_won")
                positiondifference=-1000;
            else if(gameStatus=="draw")
                positiondifference=0;
            else
            {
                calculatePieceDifference();
                positiondifference=piecedifference+calculatePiecePositionValue();
            }
        }
        void searchBestMove(int d)
        {
            sf::Clock c1;
            d*=2;
            minMaxOrMaxMin=colorToBool[gametable.playerTurn];
            cout<<minMaxOrMaxMin<<"COL"<<endl;
            if(minMaxOrMaxMin)
                cout<<searchBestMoveLoop(d,1001,-1001).second;
            else
                cout<<searchBestMoveLoop(d,1001,-1001).first;
            cout<<"GATA"<<number<<endl;
            cout<<c1.getElapsedTime().asMilliseconds();
        }
        pair<float,float> searchBestMoveLoop(int d,float minn,float maxx)
        {
            float min=1001;
            float max=-1001;
            d--;
            string stringPrevTile;
            shared_ptr<tile> PrevTile;
            map<string,shared_ptr<piece>> tp=gametable.tablePieces;
            for (auto &i:tp) {
                if (i.second->getPiececolor() == gametable.playerTurn) {
                    i.second->calculatePossibleMoves();
                    map<string, shared_ptr<tile>> ty = i.second->getPossiblesquares();
                    for (auto &j: ty) {
                        //cout<<"EXECUTE";
                        gametable.pieceSelected = i.second;
                        gametable.stringPieceSelected = i.first;
                        gametable.previousTileSelected = i.second->getTilepair().second;
                        gametable.stringPreviousTileSelected = i.second->getTilepair().first;
                        gametable.tileSelected = j.second;
                        gametable.stringTileSelected = j.first;
                        stringPrevTile=i.second->getTilepair().first;
                        PrevTile=i.second->getTilepair().second;
                        if (gametable.tileSelected->getontile() != gametable.playerTurn &&
                            gametable.tileSelected->getontile() != "empty") {
                            stringPieceTakenn = gametable.piecesOnTiles[gametable.stringTileSelected];
                            pieceTakenn = gametable.tablePieces[stringPieceTakenn];
                        } else {
                            pieceTakenn = nullptr;
                        }
                        //cout << " " << i.first << " " << i.second->getTilepair().first << " "<< gametable.stringTileSelected<<endl;
                        if (gametable.executevirtualmove()) {
                            flagss = gametable.flags;
                            if (d == 0) {
                                {
                                    evaluateposition();
                                    if(abs(positiondifference)<0.1)
                                        positiondifference=0;
                                    cout<<positiondifference<<" ";
                                    number++;
                                }
                            } else {
                                resultOfRecursion=searchBestMoveLoop(d,min,max);
                                if(d%2==minMaxOrMaxMin)
                                {
                                    positiondifference=resultOfRecursion.first;
                                }
                                else
                                {
                                    positiondifference=resultOfRecursion.second;
                                }
                               cout<<endl<<positiondifference<<endl;
                            }
                            if(d%2!=minMaxOrMaxMin)
                            {
                                if(positiondifference<min)
                                    min=positiondifference;
                            }
                            else
                            {
                                if(positiondifference>max)
                                    max=positiondifference;
                            }

                            gametable.undoEntireMove(flagss, i.first, j.first, stringPrevTile,stringPieceTakenn, i.second, pieceTakenn, j.second,PrevTile);
                        }
                    }
                }

            }
            return make_pair(min,max);
        }
        virtual ~bot(){};
    };
    bot gamebot;
public:
    explicit game(const string &g,const string &p) : gamemode(g), gametable(g,p),promotionmenuopened(false),gamebot(gametable){

        game_dimension_y=gametable.getTableDimension();
        game_dimension_x=game_dimension_y*5/4;
        gametexture.create(game_dimension_x, game_dimension_y);
        initialize_menu();
        white_promotion_sprite.setTexture(textures::white_promotion_texture);
        black_promotion_sprite.setTexture(textures::black_promotion_texture);
        white_promotion_sprite.setScale((3.0f*float(gametable.getTableDimension()/8)/white_promotion_sprite.getTexture()->getSize().x),
                                        (0.75f*float(gametable.getTableDimension()/8)/white_promotion_sprite.getTexture()->getSize().y));
        black_promotion_sprite.setScale((3.0f*float(gametable.getTableDimension()/8)/black_promotion_sprite.getTexture()->getSize().x),
                                        (0.75f*float(gametable.getTableDimension()/8)/black_promotion_sprite.getTexture()->getSize().y));
        gametable.gameref=static_cast<const shared_ptr<game>>(this);
    };
    game(const game& other):gamemode(other.gamemode),winner(other.winner),gamestate(other.gamestate),menu(other.menu),promotionmenuopened(other.promotionmenuopened),game_dimension_x(other.game_dimension_x),
     game_dimension_y(other.game_dimension_y),white_promotion_sprite(other.white_promotion_sprite),black_promotion_sprite(other.black_promotion_sprite),gamesprite(other.gamesprite),
                            gametable(other.gametable), gamebot(other.gamebot){}

    ~game() {};



    void setpromotionmenutrue(){
        promotionmenuopened=true;
    }

    void clickgame(int x,int y)
    {

        if(promotionmenuopened)
            clickpromotion(x,y);
        else
        {
            if(x<game_dimension_y && y<game_dimension_y)
                gametable.clicktile(x,y);
            else if(x>game_dimension_y && y<game_dimension_y && x<game_dimension_x)
            {
                //gametable.undoEntireMove();
            }
        }
        if(gametable.playerTurn != gametable.viewposition && gametable.playerControl != "pvp")
        {
            //gamebot.searchBestMove(1);
            gamebot.freef();
            pair<float,float> b=gamebot.rec(3,100,0,-100,100);
                cout<<b.first<<"   "<<b.second<<"REZ";
        }
    }

    void clickpromotion(int x,int y) {

        int unit = tile::gettiledimension();
        pair<int, int> tilecoords = gametable.tableTiles[gametable.stringTileSelected]->getcoordinates();
        float piecejump;
        float promstart;
        bool promoted = false;
        sf::Sprite sp;
        if (gametable.playerTurn == "white") {
            piecejump = white_promotion_sprite.getGlobalBounds().width / 4;
            promstart = white_promotion_sprite.getPosition().x;
            sp = white_promotion_sprite;
        } else {
            piecejump = black_promotion_sprite.getGlobalBounds().width / 4;
            promstart = black_promotion_sprite.getPosition().x;
            sp = black_promotion_sprite;
        }
        if (y > sp.getPosition().y && y < sp.getPosition().y + unit) {
            if (x > promstart && x < promstart + piecejump) {
                gametable.promote("queen");
                promoted = true;//can add a bool function which returns true
            } else if (x > promstart + piecejump && x < promstart + 2 * piecejump) {
                gametable.promote("bishop");
                promoted = true;
            } else if (x > promstart + 2 * piecejump && x < promstart + 3 * piecejump) {
                gametable.promote("knight");
                promoted = true;
            } else if (x > promstart + 3 * piecejump && x < promstart + 4 * piecejump) {
                gametable.promote("rook");
                promoted = true;
            }
        }
        if (promoted) {
            gametable.endPromotion();
        } else
            gametable.undoInvalidMove();
        promotionmenuopened = false;
    }

    void initialize_menu()
    {
        menu.setSize(sf::Vector2f (game_dimension_x/5,game_dimension_y));
        menu.setPosition(game_dimension_y,0);
        menu.setFillColor(sf::Color::Green);
    }

    void drawgame()
    {
        gametable.drawTable();
        gametable.drawtablesprite(gametexture);
        gametexture.draw(menu);
        int unit=tile::gettiledimension();
        if(promotionmenuopened)
        {
            shared_ptr<tile> spritestrtingpostile=gametable.tableTiles[gametable.stringTileSelected];
            if(gametable.playerTurn == "white")
            {

                if(gametable.getViewposition()=="white")
                {
                    white_promotion_sprite.setPosition((8-spritestrtingpostile->getcoordinates().first)*unit,(9-spritestrtingpostile->getcoordinates().second)*unit);
                }
                else
                    white_promotion_sprite.setPosition((spritestrtingpostile->getcoordinates().first-1)*unit,(spritestrtingpostile->getcoordinates().second-2)*unit);
                gametexture.draw(white_promotion_sprite);
            }
            else if (gametable.playerTurn == "black")
            {
                if(gametable.getViewposition()=="white")
                {
                    black_promotion_sprite.setPosition((8-spritestrtingpostile->getcoordinates().first)*unit,(7-spritestrtingpostile->getcoordinates().second)*unit);
                }
                else
                    black_promotion_sprite.setPosition((spritestrtingpostile->getcoordinates().first-1)*unit,(spritestrtingpostile->getcoordinates().second)*unit);
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
        os  << " winner: " << game.winner
           << game.gametable << " game mode: " << game.gamemode;
        return os;
    }
};



class selectGameMenu{
private:
    sf::RenderTexture selectGameMenuTexture;
    sf::Sprite selectGameMenuSprite;
    sf::Text  cg;
    sf::Text  pvp;
    sf::Text  pvb;
    sf::Text  bvb;
    int selectGameMenuLeft;
    int selectGameMenuTop;
public:

    selectGameMenu():cg("Choose Gamemode",font),pvp("2 players",font),pvb("Player vs bot",font),bvb("Bot vs bot",font),selectGameMenuLeft(window.getSize().x/2-150),selectGameMenuTop(window.getSize().y/2-250){
        drawselectgamemenu();
    }
    virtual ~selectGameMenu(){

    };
    void drawselectgamemenu()
    {
        selectGameMenuTexture.create(300,300);
        int startingh=100;
        vector <shared_ptr<sf::Text>> texts={make_shared<sf::Text>(cg),make_shared<sf::Text>(pvp),make_shared<sf::Text>(pvb),make_shared<sf::Text>(bvb)};
        for (auto &i:texts)
        {
            i->setCharacterSize(25);
            i->setPosition(0,startingh);
            selectGameMenuTexture.draw(*i);
            startingh+=25;
        }
        selectGameMenuTexture.display();
        selectGameMenuSprite.setTexture(selectGameMenuTexture.getTexture());
        selectGameMenuSprite.setPosition(selectGameMenuLeft,selectGameMenuTop);
    }
    string clickSelectGame(int x,int y){
        if (x>selectGameMenuLeft && x<selectGameMenuLeft+pvp.getGlobalBounds().width) {
            int startingy=selectGameMenuTop + 125;
            if (y > startingy && y < startingy + pvp.getGlobalBounds().height)
                return "pvp";
            else if (y > startingy + pvp.getGlobalBounds().height && y < startingy + pvp.getGlobalBounds().height + pvb.getGlobalBounds().height-2)
                return "pvb";
            else if (y > startingy + pvp.getGlobalBounds().height + pvb.getGlobalBounds().height-2 && y < startingy + pvp.getGlobalBounds().height + pvb.getGlobalBounds().height + bvb.getGlobalBounds().height)
                return "bvb";
        }
            return "";
    };
    const sf::Sprite &getSelectGameMenuSprite() const {
        return selectGameMenuSprite;
    }
};
class app{
    string draw;
    string mouse;
    sf::Sprite appSprite;
    selectGameMenu sgm1;
    shared_ptr<game> appGame;
public:

    app():draw("selectGameMenu"),mouse("selectGameMenu"){};
    sf::Sprite getAppSprite()
    {
        if(draw=="selectGameMenu")
            return sgm1.getSelectGameMenuSprite();
        else if (draw=="game")
            return appGame->getGamesprite();
    }
    void clickOnApp(int x,int y){
        if(mouse=="selectGameMenu" && sgm1.clickSelectGame(x,y)!="")
        {
            appGame = make_shared<game>("standard",sgm1.clickSelectGame(x,y));
            mouse="game";
            draw="game";
        }
        else if(mouse=="game")
        {
            appGame->clickgame(x,y);
        }
    };
};

int main() {
    srand(time(nullptr));
    font.loadFromFile("assets\\font\\OpenSans-Regular.ttf");
    textures::create_all_piece_textures();
    // create the window//minw
    // run the program as long as the window is open
    window.setFramerateLimit(60);
    app a1;
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == 0) {
                    a1.clickOnApp(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
        // clear the window with black color
        window.clear(sf::Color::Black);
        // Draw it
        window.draw(a1.getAppSprite());
        // end the current frame
        window.display();
    }
    return 0;
}
/* string positionString;
                    int spaces;
                    for(auto tile:gametable.tableTiles)
                        if (gametable.piecesOnTiles[tile.first]!="empty")
                        {
                            positionString+=gametable.piecesOnTiles[tile.first];
                            positionString+=spaces;
                            spaces=0;
                        }
                    else
                        ++spaces;*/