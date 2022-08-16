#include<bits/stdc++.h>

using namespace std;


float piecesValues[6] = {9, 0, 5, 3.5, 3, 1};
string piecesFigures[2][7] = {{"DN", "RN", "AN", "TN" , "CN", "PN", ".."}, {"DB", "RB", "AB", "TB" , "CB", "PB", ".."}};

struct Piece {
    int type; 
    int color;
    float value;
    bool checkMove(vector< vector<int> > positions){
        return false;
    };

    string getFigure(int x, int y){
        if(type == 6){ //Casilla
            if(x % 2 == 0 && y % 2 != 0 || x % 2 != 0 && y % 2 == 0) return piecesFigures[1][type];
            else return piecesFigures[0][type];
        }
        return piecesFigures[color][type];
    }
    Piece(int t, int pos): type(t), value(piecesValues[t]), color(pos >= 4 ? 1 : 0) {};
};

struct Player{
	vector<Piece> piecesStack; //Piecas comida
	bool winner;
	string name;
	vector<string> getFiguresStack(){
		vector<string> arr;
		return arr;
	}
	
	float getPoints(){
		int points;
		for(int i = 0; i < piecesStack.size() - 1; i++){
			points += piecesStack[i].value;
		}
		return points;
	}
	Player(string n): name(n) {};
};

string abc = "ABCDEFGHIJKLM";

struct Chess {
	vector<vector<Piece> > table;
	Player playerB;
	Player playerN;
	Chess(string s1 , string s2 ): playerB(Player(s1)), playerN(Player(s2)) {};
	
	void print_table(){
		for(int i = 0; i <= 8; i++){
            i == 0 ? cout << " " << " " : cout << i-1 << "\t ";
    	}
        cout << endl;
        for(int i = 0; i < 8; i++){
                cout << i << " ";
            for(int j = 0; j < 8; j++){
                cout << table[i][j].getFigure(i, j) << "\t ";
            }
            cout << endl << endl;
        }
	}
	


	
};

Chess move(vector<int> beg, vector<int> end, Chess game){
	game.table[end[0]][end[1]] = game.table[beg[0]][beg[1]];
	game.table[beg[0]][beg[1]] = Piece(6, 0);
	return game;
}

bool checkMove(vector<int> beg, vector<int> end, Chess game){
	if(game.table[beg[0]][beg[1]].type == 6){
		cout << "Seleccione una pieza!" << endl;
		return false;
	}
	return true;
}

void init_game_loop(Chess game){
	while(true){
		system("cls");
		//Preguntar movimiento // ernoque
		//Si se puede mover, si no preguntar de nuevo
		game.print_table(); // Print table
		vector<int> beg (2), end (2);
		cout << "Elija pieza (coordenadas X, Y): "; //Inicio => Pieza || Casilla vacia || Ficha clavada
		cin >> beg[0] >> beg[1];
		while(beg[0] < 0 || beg[0] > 7 || beg[1] < 0 || beg[1] > 7){
			cout << "Ingrese valores entre 0 y 7: ";
			cin >> beg[0] >> beg[1];	
		}
		cout << "Elija lugar (coordenadas X, Y): "; //Fin => Casilla Vacia || Pieza Aliada (Ilegal) || Pieza Enemiga (Comer) || Rey
		cin >> end[0] >> end[1];
		while(end[0] < 0 || end[0] > 7 || end[1] < 0 || end[1] > 7){
			cout << "Ingrese valores entre 0 y 7: ";
			cin >> end[0] >> end[1];	
		}
		//TERMINAR
		if(checkMove(beg, end, game)){
			//Move =>		
			game.table[end[0]][end[1]] = game.table[beg[0]][beg[1]];
			game.table[beg[0]][beg[1]] = Piece(6, 0);
		}

	}
	
}

int main(){
    vector< vector<Piece> > initTable;
  
    
    //0 => Dama
    //1 => Rey
    //2 => Alfil
    //3 => Torre
    //4 => Caballo
    //5 => Peon
    //6 => Casilla
    
	//Ajedrez 
	// 	Dos jugadores
	//	Tablero => Piezas
	
	    
    for(int i = 0; i < 8; i++){
        vector< Piece> newRow;
        for(int j = 0; j < 8; j++){
            if(i > 1 && i < 6) {newRow.push_back(Piece(6, i)); continue;} 
            if(i == 1 || i == 6){newRow.push_back(Piece(5, i)); continue;} 
            switch(j){
                case 0: case 7:
                newRow.push_back(Piece(3, i)); //Torre
                break;     
                case 1: case 6:
                newRow.push_back(Piece(4, i)); //Caballo
                break;
                case 2: case 5:
                newRow.push_back(Piece(2, i)); //Alfil
                break;
                case 4: //Dama
                if(j == 0) {newRow.push_back(Piece(1, i)); break;}
                newRow.push_back(Piece(0, i)); break;
                case 3: //Rey
                if(j == 0) {newRow.push_back(Piece(0, i)); break;}
                newRow.push_back(Piece(1, i)); break;
            }
        }
        initTable.push_back(newRow);
    }

    while(true){
		Chess game = Chess("a", "b");
		game.table = initTable;
		init_game_loop(game);
		
    }
};
