#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <list>
#include <map>

template<typename P>
class Point{
private:
	P x, y;
public:
	Point( const P nx, const P ny ) : x(nx), y(ny) {}
	~Point(){}
	P getX() const{ return x; }
	P getY() const{ return y; }
	void setX( const P x ){ this->x = x; }
	void setY( const P y ){ this->y = y; }
};

template<typename V>
class Vertex{
	V* elem;
	bool visit;
public:
	Vertex( const V &elem ){
        visit = false;
        this->elem = elem;
	}
	~Vertex(){}
	V* getElem(){ return elem; }
	bool visited(){ return visit; }
	void setVisit( bool visit ){ this->visit = visit; }
};

template<typename V, typename E>
class Edge{
	Vertex<V> start, end;
	E* elem;
	bool trav;
public:
	Edge( const Vertex<V> &start, const Vertex<V> &end, const E* const elem ){
        this->start = start;
        this->end = end;
        this->elem = elem;
        trav = false;
	}
	~Edge(){}
	Vertex<V> opposite( const Vertex<V> &v1 ) const{
        if( v1 == start ){
            return end;
        } else {
            return start;
        }
	}
	const E* const getElem() const{ return elem; }
	bool travelled(){ return trav; }
};

template<typename V, typename E>
class ListGraph {
private:
    std::vector<Vertex<V> > vertices;
    std::vector<std::list<Edge<V,E> > > adjList;
public:
    ListGraph(){
        vertices = std::vector<Vertex<V> >();
    }
	ListGraph( std::vector<V> vertices ){
	    for( int i = 0 ; i < vertices.size() ; i++ ){
            insertVertex( vertices[i] );
	    }
	}
	~ListGraph(){
	}
	std::vector<Edge<V,E>*> adjEdges( Vertex<V>* vertex ){}
	Vertex<V> insertVertex( Vertex<V> elem ){
	    Vertex<V> t = new Vertex<V>( elem );
        vertices.push_back( t );
        adjList.push_back( std::list<Edge<V,E> >() );
        return t;
	}
	Edge<V,E> insertEdge( int v1, int v2, E elem ){
        Vertex<V> vert1 = vertices[v1];
        Vertex<V> vert2 = vertices[v2];
        Edge<V,E> edge = Edge<V,E>(vert1, vert2, elem);
        adjList[v1].push_back( edge );
        adjList[v2].push_back( edge );
	}
	Vertex<V> opposite( Edge<V,E> edge, Vertex<V> v ){
        return edge.opposite( &v );
	}
};

std::string gridName( int x, int y ){ return x + ", " + y; }

class Cell{
    std::string name;
    int x, y;
    bool alive, nextState;
public:
	Cell( int nx, int ny ) : name(gridName(nx,ny)), x(nx), y(ny) { alive = true; nextState = true; }
	Cell( std::string n ) : name(n), x(0), y(0) { alive = true; nextState = true; }
	~Cell(){}
	std::string* getName(){ return &name; }
	bool isAlive(){ return alive; }
	void step(){ alive = nextState; }
	void setNext( bool next ){ nextState = next; }
	virtual std::vector<std::string> operator^(Cell *cell) const = 0;
};

class GridCell : public Cell {
public:
	GridCell( int x, int y ) : Cell( gridName(x,y) ){}
	~GridCell(){}
	std::vector<std::string> operator^(Cell *cell) const{
        std::vector<std::string> adj;

        return adj;
	}
};

class WordCell : public Cell {
	std::string word;
public:
	WordCell( std::string word ) : Cell( word ){}
	~WordCell(){}
	std::vector<std::string> operator^(Cell *cell) const{
        std::vector<std::string> adj;
        std::string l1, l2;
        for( int i = 0 ; i < word.size() ; i++ ){
            l1 = word[i];
            for( int j = i + 1 ; j < cell->getName()->size() ; j++ ){
                l2 = cell->getName()[j];
                if( l1 == l2 ){
                    adj.push_back( l1 );
                }
            }
        }
        return adj;
	}
};

class GameOfLife {
    ListGraph<Cell,std::string> board;
public:
    GameOfLife(){
    }
    GameOfLife( int x, int y ){
    }
    GameOfLife( std::vector<std::string> ){
    }
    void step(){
    }
    friend void display();
};

void display(){

}

int main(){
    std::string gameType, gameOption;
    const std::string TRAD = "T", WORD = "W", NOTE = "N", DISP = "D", STEP = "S", QUIT = "Q";
    const std::string TYPE_PROMPT = "Which game type do you wish to play?: 2D Grid '" + TRAD + "' : Words '" + WORD + "' : Quit '" + QUIT + "'\n";
    const std::string OPT_PROMPT = "What would you like to do? Calculate Next Step: '" + STEP + "' Display Current Step: '" + DISP + "' Stop: '" + QUIT + "'\n";
    const std::string STARVE_PROMPT = "What is the minimum number of adjacent cells needed for survival?\n";
    const std::string OVERPOP_PROMPT = "What is the maximum number of adjacent cells needed for survival?\n";
    const std::string WIDTH_PROMPT = "Enter the width for our game:\n";
    const std::string HEIGHT_PROMPT = "Enter the height for our game:\n";
    const std::string WORD_PROMPT = "Enter a word: '" + QUIT + "' to stop entering words.\n";
    int starve, overpopulation, width, height;
    std::string word;
    std::vector<std::string> words;
    GameOfLife game;
    std::cout << TYPE_PROMPT;
    std::cin >> gameType;
    while( !( gameType == QUIT ) ){
        std::cout << STARVE_PROMPT;
        std::cin >> starve;
        std::cout << OVERPOP_PROMPT;
        std::cin >> overpopulation;
        if( gameType == TRAD ){
            std::cout << WIDTH_PROMPT;
            std::cin >> width;
            std::cout << HEIGHT_PROMPT;
            std::cin >> height;
            game = GameOfLife( width, height );
        }
        if( gameType == WORD ){
            words = std::vector<std::string>();
            std::cout << WORD_PROMPT;
            std::cin >> word;
            while( !( word == QUIT ) ){
                words.push_back( word );
                std::cout << WORD_PROMPT;
                std::cin >> word;
            }
            game = GameOfLife( words );
        }
        gameOption = DISP;
        if( gameType == TRAD || gameType == WORD ){
            while( !( gameOption == QUIT ) ){
                if( gameOption == DISP ){
                    display();
                }
                if( gameOption == STEP ){
                    game.step();
                }
                std::cout << OPT_PROMPT;
                std::cin >> gameOption;
            }
        }
        std::cout << TYPE_PROMPT;
        std::cin >> gameType;
   }
    return 0;
}
