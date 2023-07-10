#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <cmath>

#include "C://SFML-2.6.0//include//SFML//System.hpp"
#include "C://SFML-2.6.0//include//SFML//Window.hpp"
#include "C://SFML-2.6.0//include//SFML//Graphics.hpp"

#define getName(VariableName) # VariableName

using namespace std;
pair<int,int>  fromnametocoordinates(const string& s)
{
    return make_pair(9-int (char(s[0]))+96,stoi(s.substr(1)));
}
string fromcoordinatestoname(pair<int ,int > p)
{
    return ((char((9-p.first)+96) +to_string(p.second)));
}

sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
sf::Font font;


class textures{
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
    void static create_white_rook_texture(){
        white_rook_texture.loadFromFile("assets\\piece_icons\\white_rook.png");
    }
    void static create_black_rook_texture(){
        black_rook_texture.loadFromFile("assets\\piece_icons\\black_rook.png");
    }
    void static create_black_queen_texture(){
        black_queen_texture.loadFromFile("assets\\piece_icons\\black_queen.png");
    }
    void static create_white_queen_texture(){
        white_queen_texture.loadFromFile("assets\\piece_icons\\white_queen.png");
    }
    void static create_white_king_texture(){
        white_king_texture.loadFromFile("assets\\piece_icons\\white_king.png");
    }
    void static create_black_king_texture(){
        black_king_texture.loadFromFile("assets\\piece_icons\\black_king.png");
    }
    void static create_white_pawn_texture(){
        white_pawn_texture.loadFromFile("assets\\piece_icons\\white_pawn.png");
    }
    void static create_black_pawn_texture(){
        black_pawn_texture.loadFromFile("assets\\piece_icons\\black_pawn.png");
    }
    void static create_white_knight_texture(){
        white_knight_texture.loadFromFile("assets\\piece_icons\\white_knight.png");
    }
    void static create_black_knight_texture(){
        black_knight_texture.loadFromFile("assets\\piece_icons\\black_knight.png");
    }
    void static create_white_bishop_texture(){
        white_bishop_texture.loadFromFile("assets\\piece_icons\\white_bishop.png");
    }
    void static create_black_bishop_texture(){
        black_bishop_texture.loadFromFile("assets\\piece_icons\\black_bishop.png");
    }
    void static create_all_piece_textures()
    {
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
sf::Texture textures::white_rook_texture=sf::Texture();
sf::Texture textures::black_rook_texture=sf::Texture();
sf::Texture textures::white_pawn_texture=sf::Texture();
sf::Texture textures::black_pawn_texture=sf::Texture();
sf::Texture textures::white_knight_texture=sf::Texture();
sf::Texture textures::black_knight_texture=sf::Texture();
sf::Texture textures::white_bishop_texture=sf::Texture();
sf::Texture textures::black_bishop_texture=sf::Texture();
sf::Texture textures::white_king_texture=sf::Texture();
sf::Texture textures::black_king_texture=sf::Texture();
sf::Texture textures::white_queen_texture=sf::Texture();
sf::Texture textures::black_queen_texture=sf::Texture();
class tile {
private:
    int row;
    int column;
    string letter;
    string color;
    string ontile;
    static int dimension;

    sf::RectangleShape tilerectangle;
    sf::Sprite tilesprite;
public:
    sf::RenderTexture tiletexture;
    tile(int r, int c) : row(r), column(c), letter(string(1, char(96 + (9-c)))),
                         color((c + r) % 2 == 0 ? "white" : "black"), ontile("empty") {}

    tile(const tile &other) : row(other.row), column(other.column), letter(other.letter),
                              color(other.color) , ontile(other.ontile) {}

    virtual ~tile() {}

    void setontile(const string &s){
        ontile=s;
    };
    /*shared_ptr<sf::RenderTexture> gettiletexture()
    {
        return make_shared<sf::RenderTexture>(tiletexture) ;
    }*/
    void drawtile(){
        tiletexture.create(dimension,dimension);
        tilerectangle.setSize(sf::Vector2f(dimension, dimension));
        tilerectangle.setFillColor(color == "black" ? *new sf::Color(36, 36, 36) : *new sf::Color(235, 233, 209));
        cout<<" "<<row<<" "<<column<<" "<<fromcoordinatestoname(make_pair(row,column))<<" "<<(column - 1) * dimension<<" "<< (row - 1) * dimension<<" ";
        sf::Text text(fromcoordinatestoname(make_pair(row,column)), font);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::Red);
        tiletexture.draw(tilerectangle);
        tiletexture.draw(text);

    }
    void drawtilesprite(sf::RenderTexture& t){
        tilesprite.setTexture(tiletexture.getTexture());
        tilesprite.setPosition((row - 1) * dimension, (8-column) * dimension);
        t.draw(tilesprite);
    }
    string getontile()
    {
        return ontile;
    }

    pair<int,int> getcoordinates(){
        return make_pair(row,column);
    }

    static int gettiledimension()
    {
        return dimension;
    }

    friend ostream &operator<<(ostream &os, const tile &tile) {
        os << "row: " << tile.row << " column: " << tile.column << " letter: " << tile.letter
           << " color: " << tile.color<<" on tile: "<< tile.ontile<<endl;
        return os;
    }
};
int tile::dimension=max(int(window.getSize().y/12),60);
sf::Texture texture2;
class piece {
protected:
    static vector<shared_ptr<piece>> pieces;
    static map<string,shared_ptr<tile>> totaltiles;
    pair<shared_ptr<tile>, string> tilepair;
    map<string,shared_ptr<tile>> possiblesquares;
    int value;
    string piececolor;
    int piecedimension=max(int(window.getSize().y/15),48);
    int piecepadding=max((int(window.getSize().y/15)-int(window.getSize().y/12))/2,6);
    sf::Sprite piece_sprite;
public:
    piece(pair<shared_ptr<tile>, string> tp, const map<string,shared_ptr<tile>> ps, int v, string piececolor) : tilepair(
            tp), possiblesquares(ps), value(v), piececolor(piececolor){
        pieces.push_back(make_shared<piece>(*this));
    }
    static void addtile(shared_ptr<tile> t,const string &x)
    {
        totaltiles[x]=t;
    }
    virtual ~piece() {}
    pair<shared_ptr<tile>, string> gettile(){
        return tilepair;
    }
    void drawpiece(){
        piece_sprite.setScale(float(piecedimension) / 128.0f, float(piecedimension) / 128.0f);
        piece_sprite.setPosition(0,0);
        tilepair.first->tiletexture.draw(piece_sprite);
    }
    sf::Sprite getpiecesprite()
    {
        return piece_sprite;
    }
    friend ostream &operator<<(ostream &os, const piece &piece) {
        os << "currenttile: " << piece.tilepair.second << " possiblesquares: ";
        for(auto itr=piece.possiblesquares.begin();itr!=piece.possiblesquares.end();itr++)
        {
            cout<<itr->first<<" "<<endl;
        }
        os << " value: " << piece.value;
        return os;
    }
    bool between1and8(int x){
        if(x>=1 && x<=8)
            return true;
        return false;
    }
};
map<string,shared_ptr<tile>>  piece::totaltiles={};
vector<shared_ptr<piece>> piece::pieces = {};

class rook : public piece {
private:
    vector<pair<int,int>> const movement={{1,0},{0,-1},{0,1},{-1,0}};
    bool moved=false;
public:
    rook(pair<shared_ptr<tile>, string> tp, const map<string,shared_ptr<tile>> ps, string piececolor) : piece(tp, ps, 5,piececolor) {
        piececolor=="white" ? piece_sprite.setTexture(textures::white_rook_texture) : piece_sprite.setTexture(textures::black_rook_texture);
    }

    void calculatepossiblemoves()
    {
        pair<int,int> currentposition= fromnametocoordinates(tilepair.second);
        int currentx=currentposition.first;int currenty=currentposition.second;
        possiblesquares={};
        for(auto& i:movement)
        {
            currentx=currentx=currentposition.first;currenty=currentposition.second;
            while(between1and8(currentx+i.first) && between1and8(currenty+i.second))
            {
                string tilename=fromcoordinatestoname(make_pair(currentx+i.first,currenty+i.second));
                if(totaltiles[tilename]->getontile()=="empty")
                {
                    possiblesquares[tilename]=totaltiles[tilename];
                }
                else if(totaltiles[tilename]->getontile()==piececolor)
                {
                    break;
                }
                else {
                    possiblesquares[tilename]=totaltiles[tilename];
                    break;
                }
                currentx+=i.first;
                currenty+=i.second;
            }
        }
    }

    ~rook() {};

    friend ostream &operator<<(ostream &os, const rook &rook) {
        os << static_cast<const piece &>(rook);
        return os;
    }
};

class bishop : public piece {
private:
    vector<pair<int,int>> const movement={{1,1},{1,-1},{-1,1},{-1,-1}};
public:
    bishop(pair<shared_ptr<tile>, string> tp, const map<string,shared_ptr<tile>> ps, string piececolor) : piece(tp, ps, 3,
                                                                                                                piececolor) {
        piececolor=="white" ? piece_sprite.setTexture(textures::white_bishop_texture) : piece_sprite.setTexture(textures::black_bishop_texture);
    }
    void calculatepossiblemoves()
    {
        pair<int,int> currentposition= fromnametocoordinates(tilepair.second);
        int currentx=currentposition.first;int currenty=currentposition.second;
        possiblesquares={};
        for(auto& i:movement)
        {
            currentx=currentx=currentposition.first;currenty=currentposition.second;
            while(between1and8(currentx+i.first) && between1and8(currenty+i.second))
            {
                string tilename=fromcoordinatestoname(make_pair(currentx+i.first,currenty+i.second));
                if(totaltiles[tilename]->getontile()=="empty")
                {
                    possiblesquares[tilename]=totaltiles[tilename];
                }
                else if(totaltiles[tilename]->getontile()==piececolor)
                {
                    break;
                }
                else {
                    possiblesquares[tilename]=totaltiles[tilename];
                    break;
                }
                currentx+=i.first;
                currenty+=i.second;
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
    vector<pair<int,int>> const movement={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{-1,2},{1,-2},{-1,-2}};
public:
    knight(pair<shared_ptr<tile>, string> tp, const map<string,shared_ptr<tile>> ps, string piececolor) : piece(tp, ps, 3,
                                                                                                                piececolor) {
        piececolor=="white" ? piece_sprite.setTexture(textures::white_knight_texture) : piece_sprite.setTexture(textures::black_knight_texture);
    }

    ~knight() {};

    friend ostream &operator<<(ostream &os, const knight &knight) {
        os << static_cast<const piece &>(knight);
        return os;
    }
    void calculatepossiblemoves()
    {
        pair<int,int> currentposition= fromnametocoordinates(tilepair.second);
        int currentx=currentposition.first;int currenty=currentposition.second;
        possiblesquares={};
        for(auto& i:movement)
        {
            if(between1and8(currentx+i.first) && between1and8(currenty+i.second))
            {
                string tilename=fromcoordinatestoname(make_pair(currentx+i.first,currenty+i.second));
                if(totaltiles[tilename]->getontile()!=piececolor)
                {
                    possiblesquares[tilename]=totaltiles[tilename];
                }
            }
        }
    }
};

class queen : public piece {
private:
    vector<pair<int,int>> const movement={{1,1},{1,-1},{-1,1},{-1,-1},{0,1},{0,-1},{1,0},{-1,0}};
public:
    queen(pair<shared_ptr<tile>, string> tp, const map<string,shared_ptr<tile>> ps, string piececolor) : piece(tp, ps, 9,
                                                                                                               piececolor) {
        piececolor=="white" ? piece_sprite.setTexture(textures::white_queen_texture) : piece_sprite.setTexture(textures::black_queen_texture);
    }
    void calculatepossiblemoves()
    {
        pair<int,int> currentposition= fromnametocoordinates(tilepair.second);
        int currentx=currentposition.first;int currenty=currentposition.second;
        possiblesquares={};
        for(auto& i:movement)
        {
            currentx=currentx=currentposition.first;currenty=currentposition.second;
            while(between1and8(currentx+i.first) && between1and8(currenty+i.second))
            {
                string tilename=fromcoordinatestoname(make_pair(currentx+i.first,currenty+i.second));
                if(totaltiles[tilename]->getontile()=="empty")
                {
                    possiblesquares[tilename]=totaltiles[tilename];
                }
                else if(totaltiles[tilename]->getontile()==piececolor)
                {
                    break;
                }
                else {
                    possiblesquares[tilename]=totaltiles[tilename];
                    break;
                }
                currentx+=i.first;
                currenty+=i.second;
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
    bool moved=false;
    bool enpassantable=false;
    vector<pair<int,int>> movement;
public:
    pawn(pair<shared_ptr<tile>, string> tp, const map<string,shared_ptr<tile>> ps, string piececolor) : piece(tp, ps, 1,
                                                                                                              piececolor){
        if(piececolor=="black")
            movement={{0,-1},{0,-2},{1,-1},{-1,-1}};
        else
            movement={{0,1},{0,2},{1,1},{-1,1}};
        piececolor=="white" ? piece_sprite.setTexture(textures::white_pawn_texture) : piece_sprite.setTexture(textures::black_pawn_texture);
    }
    void calculatepossiblemoves()
    {
        pair<int,int> currentposition= fromnametocoordinates(tilepair.second);
        int currentx=currentposition.first;int currenty=currentposition.second;
        possiblesquares={};
        int pawnmovetype=0;
        for(auto& i:movement)
        {
            pawnmovetype+=1;
            //cout<<i.first<<" "<<i.second<<endl;
            if(between1and8(currentx+i.first) && between1and8(currenty+i.second))
            {
                string tilename=fromcoordinatestoname(make_pair(currentx+i.first,currenty+i.second));

                //cout<<pawnmovetype<<totaltiles[tilename]->getontile()<<tilename<<endl;
                if(pawnmovetype==1 && totaltiles[tilename]->getontile()=="empty" )
                {
                    possiblesquares[tilename]=totaltiles[tilename];
                }
                else if(pawnmovetype==2 && totaltiles[tilename]->getontile()=="empty" and moved==false)
                {
                    possiblesquares[tilename]=totaltiles[tilename];
                }
                else if(pawnmovetype>2 && totaltiles[tilename]->getontile()!="empty" && totaltiles[tilename]->getontile()!=piececolor ){//or enpassant
                    possiblesquares[tilename]=totaltiles[tilename];
                }
            }
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
    bool moved=false;
private:
    vector<pair<int,int>> const movement={{1,1},{1,-1},{-1,1},{-1,-1},{0,1},{0,-1},{1,0},{-1,0}};
public:
    king(pair<shared_ptr<tile>, string> tp, map<string,shared_ptr<tile>> ps, string piececolor) : piece(tp, ps, 0,
                                                                                                        piececolor) {
        piececolor=="white" ? piece_sprite.setTexture(textures::white_king_texture) : piece_sprite.setTexture(textures::black_king_texture);
    }
    void calculatepossiblemoves() {
        pair<int, int> currentposition = fromnametocoordinates(tilepair.second);
        int currentx = currentposition.first;
        int currenty = currentposition.second;
        possiblesquares = {};
        for (auto &i: movement) {
            if (between1and8(currentx + i.first) && between1and8(currenty + i.second)) {
                string tilename = fromcoordinatestoname(make_pair(currentx + i.first, currenty + i.second));
                if (totaltiles[tilename]->getontile() != piececolor) {
                    possiblesquares[tilename] = totaltiles[tilename];
                    cout << tilename << endl;
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

class table {
private:
    static vector <std::shared_ptr<tile>> tilesvector;
    static vector <std::shared_ptr<piece>> piecevector;
    static map<std::string, std::shared_ptr<piece>> tablepieces;
    static map<std::string, std::shared_ptr<tile>> tabletiles;
    static sf::RenderTexture tabletexture;
    static sf::Sprite tablesprite;
public:

    table(const string &gamemodetype) {
        if (gamemodetype == "standard") {
            for (int i = 1; i <= 8; i++)
                for (int j = 1; j <= 8; j++) {
                    //push a pair of a pointer of tile (i,j) and then the name(e4)
                    shared_ptr<tile> newtilepointer=make_shared<tile>(tile(i, j));
                    tilesvector.push_back(newtilepointer);
                    cout<<newtilepointer<<" "<<i<<" "<<j<<endl;
                    string squarenamecreated = string(1, char(96 + (9-i))) + to_string(j);
                    tabletiles[squarenamecreated]=newtilepointer;
                    pair<shared_ptr<tile>,string> paircreated= make_pair(newtilepointer,squarenamecreated);
                    piece::addtile(newtilepointer,squarenamecreated);
                    //generate color and names automatically
                    // black pieces
                    if (squarenamecreated == "a8") {
                        rook lBR(paircreated, {}, "black");
                        tablepieces["lBR"] = std::make_shared<rook>(lBR);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "b8") {
                        knight lBN(paircreated, {}, "black");
                        tablepieces["lBN"] = std::make_shared<knight>(lBN);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "c8") {
                        bishop lBB(paircreated, {}, "black");
                        tablepieces["lBB"] = std::make_shared<bishop>(lBB);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "d8") {
                        queen BQ(paircreated, {}, "black");
                        tablepieces["BQ"] = std::make_shared<queen>(BQ);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "e8") {
                        king BK(paircreated, {}, "black");
                        tablepieces["BK"] = std::make_shared<king>(BK);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "f8") {
                        bishop rBB(paircreated, {}, "black");
                        tablepieces["rBB"] = std::make_shared<bishop>(rBB);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "g8") {
                        knight rBN(paircreated, {}, "black");
                        tablepieces["rBN"] = std::make_shared<knight>(rBN);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "h8") {
                        rook rBR(paircreated, {}, "black");
                        tablepieces["rBR"] = std::make_shared<rook>(rBR);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "a7") {
                        pawn aBP(paircreated, {}, "black");
                        tablepieces["aBP"] = std::make_shared<pawn>(aBP);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "b7") {
                        pawn bBP(paircreated, {}, "black");
                        tablepieces["bBP"] = std::make_shared<pawn>(bBP);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "c7") {
                        pawn cBP(paircreated, {}, "black");
                        tablepieces["cBP"] = std::make_shared<pawn>(cBP);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "d7") {
                        pawn dBP(paircreated, {}, "black");
                        tablepieces["dBP"] = std::make_shared<pawn>(dBP);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "e7") {
                        pawn eBP(paircreated, {}, "black");
                        tablepieces["eBP"] = std::make_shared<pawn>(eBP);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "f7") {
                        pawn fBP(paircreated, {}, "black");
                        tablepieces["fBP"] = std::make_shared<pawn>(fBP);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "g7") {
                        pawn gBP(paircreated, {}, "black");
                        tablepieces["gBP"] = std::make_shared<pawn>(gBP);
                        newtilepointer->setontile("black");
                    }
                    else if (squarenamecreated == "h7") {
                        pawn hBP(paircreated, {}, "black");
                        tablepieces["hBP"] = std::make_shared<pawn>(hBP);
                        newtilepointer->setontile("black");
                    }

// white pieces
                    else if (squarenamecreated == "a1") {
                        rook lWR(paircreated, {}, "white");
                        tablepieces["lWR"] = std::make_shared<rook>(lWR);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "b1") {
                        knight lWN(paircreated, {}, "white");
                        tablepieces["lWN"] = std::make_shared<knight>(lWN);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "c1") {
                        bishop lWB(paircreated, {}, "white");
                        tablepieces["lWB"] = std::make_shared<bishop>(lWB);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "d1") {
                        queen WQ(paircreated, {}, "white");
                        tablepieces["WQ"] = std::make_shared<queen>(WQ);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "e1") {
                        king WK(paircreated, {}, "white");
                        tablepieces["WK"] = std::make_shared<king>(WK);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "f1") {
                        bishop rWB(paircreated, {}, "white");
                        tablepieces["rWB"] = std::make_shared<bishop>(rWB);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "g1") {
                        knight rWN(paircreated, {}, "white");
                        tablepieces["rWN"] = std::make_shared<knight>(rWN);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "h1") {
                        rook rWR(paircreated, {}, "white");
                        tablepieces["rWR"] = std::make_shared<rook>(rWR);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "a2") {
                        pawn aWP(paircreated, {}, "white");
                        tablepieces["aWP"] = std::make_shared<pawn>(aWP);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "b2") {
                        pawn bWP(paircreated, {}, "white");
                        tablepieces["bWP"] = std::make_shared<pawn>(bWP);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "c2") {
                        pawn cWP(paircreated, {}, "white");
                        tablepieces["cWP"] = std::make_shared<pawn>(cWP);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "d2") {
                        pawn dWP(paircreated, {}, "white");
                        tablepieces["dWP"] = std::make_shared<pawn>(dWP);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "e2") {
                        pawn eWP(paircreated, {}, "white");
                        tablepieces["eWP"] = std::make_shared<pawn>(eWP);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "f2") {
                        pawn fWP(paircreated, {}, "white");
                        tablepieces["fWP"] = std::make_shared<pawn>(fWP);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "g2") {
                        pawn gWP(paircreated, {}, "white");
                        tablepieces["gWP"] = std::make_shared<pawn>(gWP);
                        newtilepointer->setontile("white");
                    }
                    else if (squarenamecreated == "h2") {
                        pawn hWP(paircreated, {}, "white");
                        tablepieces["hWP"] = std::make_shared<pawn>(hWP);
                        newtilepointer->setontile("white");
                    }

                }
//actual code
        }
    };

    ~table() {};
    void static create_table_texture(){
        tabletexture.create(max(int(window.getSize().y*2/3),480),max(int(window.getSize().y*2/3),480));
    }
    void static drawtable(){

        for(auto i:tilesvector)
        {
            i->drawtile();
            cout<<i<<" "<<i->getcoordinates().first<<" "<<i->getcoordinates().second<<endl;
        }
        for (auto j:tablepieces)
        {
            cout<<j.first<<" "<<j.second->gettile().first<<" "<<j.second->gettile().second<<endl;
            j.second->drawpiece();
        }
        for(auto i:tilesvector)
        {

            i->drawtilesprite(tabletexture);
        }

    }
    sf::Sprite static gettablesprite()
    {
        tablesprite.setTexture(tabletexture.getTexture());
        tablesprite.setScale(1.0f,1.0f);
        //tablesprite.rotate(180);
        tablesprite.setPosition(0,0);
        return tablesprite;
    }

};
map<string,shared_ptr<piece>> table::tablepieces={};
map<string,shared_ptr<tile>> table::tabletiles={};
sf::RenderTexture table::tabletexture={};
sf::Sprite table::tablesprite={};
vector <shared_ptr<tile>> table::tilesvector={};
vector <std::shared_ptr<piece>> piecevector={};

int main() {
    font.loadFromFile("assets\\font\\OpenSans-Regular.ttf");
    textures::create_all_piece_textures();
    cout<<fromcoordinatestoname(make_pair(4,4));
    cout<<fromnametocoordinates("b5").first<<fromnametocoordinates("b5").second<<endl;
    //cout << getName(i);
    table("standard");
    // create the window//minw
    // run the program as long as the window is open
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color

        //table::tabletexture.clear(sf::Color::Black);
        // draw everything here...
        // window.draw(...);
        //table::drawtable();
        //window.draw(s);

        //table::tabletexture.display();

// Draw it

        window.clear(sf::Color::Black);
        table::create_table_texture();
        table::drawtable();
        window.draw(table::gettablesprite());
        //window.draw(sprite);
        // end the current frame

        window.display();
        window.clear(sf::Color::Black);
    }
    //cout<<fromnametocoordinates("b5").first<<" "<<fromnametocoordinates("b5").second<<endl;
    return 0;
}


















/* sf::RenderTexture t;
 t.create(500,500);
 sf::Texture t2;
 t2.loadFromFile("C:\\Users\\Andrei\\CLionProjects\\chessbot\\assets\\white_rook.png");

 sf::Sprite s;
 s.setTexture(t2);*/