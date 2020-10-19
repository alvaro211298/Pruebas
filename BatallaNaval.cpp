#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

// flechas dirrecionales
#define UP    72
#define DOWN  80
#define RIGHT 77
#define LEFT  75
#define SPACE 32

using namespace std;
const int fil = 11,col = 11;

void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

class Tablero{
	public:
		
	char VectorMapa[fil][col];
	char VectorInterno[fil][col];
	char Letra;
	int Barco;
	int spacef;
	int spacec; 
	// Variables para el menu de ubicacion de barcos
	int Fila,Columna,Direccion;
	int NumeroBarcos;

	public:
	Tablero();
	void PintarMapa(char Vector[][11],int posx,int posy);
	void MenuUbicar();
	void UbicarBarcos();
	void OrientarBarcos();
	bool CargarBarco();
};

Tablero::Tablero(){
	NumeroBarcos = 2;
	Barco = 2;
	for (int i = 1;i < fil;i++){
		for(int k = 1;k < col;k++){
			VectorMapa[i][k] = 223;
			VectorInterno[i][k] = 176;
		}
	}
}

void Tablero::PintarMapa(char Vector[][11],int posx,int posy){
	gotoxy(posx,posy);
	cout<<"    1 2 3 4 5 6 7 8 9 10";
	Letra = 'A';
	posy += 2;
	for (int i = 1;i < fil;i++){
		cout<<endl;
		gotoxy(posx,posy);
		cout<<Letra<<"  ";
		posy++;
		Letra++;
		for(int k = 1;k < col;k++){
			printf(" %c",Vector[i][k]);
		}
	}
	cout<<endl;
}

void Tablero::UbicarBarcos(){
	for(int i = 1;i < 5;i++){
		this->MenuUbicar();
		this->OrientarBarcos();	
	}
}

bool Tablero::CargarBarco(){
	bool UbicacionValida = true;
	char VectorAux[fil][col];
	
	for (int i = 1;i < fil;i++){
		for(int k = 1;k < col;k++){
			VectorAux[i][k] = this->VectorInterno[i][k];
		}
	}

	switch (Direccion){
		case (UP):
			for(int i = 0; i < Barco;i++){
				if(VectorAux[Fila-i][Columna] != '#'){
					VectorAux[Fila-i][Columna] = '#' ;			
				} else {
					UbicacionValida = false;
					break;
				}
			}
		break;
		case (DOWN):
			for(int i = 0; i < Barco;i++){
				if(VectorAux[Fila+i][Columna] != '#'){
					VectorAux[Fila+i][Columna] = '#';
				} else {
					UbicacionValida = false;
					break;
				}
			}
		break;
		case (LEFT):
			for(int i = 0; i < Barco;i++){
				if(VectorAux[Fila][Columna-i] != '#'){
					VectorAux[Fila][Columna-i] = '#';
				} else {
					UbicacionValida = false;
					break;
				}
			}
		break;
		case (RIGHT):
			for(int i = 0; i < Barco;i++){
				if(VectorAux[Fila][Columna+i] != '#'){
					VectorAux[Fila][Columna+i] = '#';
				} else {
					UbicacionValida = false;
					break;
				}
			}
		break;
		default:break;	
	}
	if(!UbicacionValida){
		return false;
	}
	for (int i = 1;i < fil;i++){
		for(int k = 1;k < col;k++){
			this->VectorInterno[i][k] = VectorAux[i][k];
		}
	}
	++Barco;
	return true;
}

void Tablero::MenuUbicar(){
	bool Opcion,LetraValida = false,ColumnaValida = false;	
	do{
		LetraValida = false,ColumnaValida = false,Opcion = false;
		spacef = 0,spacec = 0;
		while(!LetraValida){
			system("cls");
			this->PintarMapa(VectorInterno,0,0);
			cout<<"\nMarque el punto central de su barco "<<endl;
			cout<<"Ingrese una Letra entre A y J"<<endl;
			Fila = getchar();
			if(isalpha(Fila) && (( Fila >= 'A' && Fila <= 'J') || (Fila >= 'a' && Fila <= 'j'))){
				if(!isupper(Fila)){
					Fila = toupper(Fila);
				}
				Fila -=64;
				LetraValida = true;
			}
		}
		
		while(!ColumnaValida){
			system("cls");
			this->PintarMapa(VectorInterno,0,0);
			cout<<"Ingrese un numero entre 1 y 10"<<endl;
			cin>>Columna;
			
			if(!isdigit(Columna) && (Columna > 0 && Columna < 11)){
				ColumnaValida = true;
			} else {
				cout<<"Coordenadas invalidas, esta fuera del mapa"<<endl;
				cout<<"Debe estar en un rango 1 - 10 "<<endl;
				system("pause");
			}
		}
		if(this->VectorInterno[Fila][Columna] == '#'){
			cout<<"Punto central invalido"<<endl;
			cout<<"No puede ir un barco, sobre otro"<<endl;
			system("pause");
		} else{
			Opcion = true;
		}
		spacec = 2*Columna+2;
		spacef = Fila+1;
	} while(!Opcion);
}

void Tablero::OrientarBarcos(){
	int Flecha;
	bool Salir = false,Ubicacion = false;
	bool LetraValida = false,ColumnaValida = false;	
	Salir = false;
	
	cout<<"Oriente con las flechas el barco "<<endl;
	cout<<"CUANDO ESTE SEGURO DE SU ORIENTACION PRESIONE -> ESPACIO <-"<<endl;
	while(!Salir){
		if(kbhit()){
			Flecha = getch();
			system("cls");
			this->PintarMapa(VectorInterno,0,0);
			
			switch (Flecha){
				case (UP):
				Direccion = UP;
				system("cls");
				this->PintarMapa(VectorInterno,0,0);
				for(int i = 0; i < NumeroBarcos;i++){
					if(spacef-i < 2){
						Ubicacion = false;
						system("cls");
						this->PintarMapa(VectorInterno,0,0);
						break;
					} else{
						Ubicacion = true;
					}
					gotoxy(spacec,spacef-i);printf("%c",'#');
				}
				break;
				
				case (DOWN):
				Direccion = DOWN;
				system("cls");
				this->PintarMapa(VectorInterno,0,0);
				for(int i = 0; i < NumeroBarcos;i++){
					if(spacef+i > 11){
						Ubicacion = false;
						system("cls");
						this->PintarMapa(VectorInterno,0,0);
						break;
				} else{
						Ubicacion = true;
					}
					gotoxy(spacec,spacef+i);printf("%c",'#');
				}
				break;
				
				case (RIGHT):
				Direccion = RIGHT;
				system("cls");
				this->PintarMapa(VectorInterno,0,0);
				for(int i = 0; i < NumeroBarcos;i++){
					if(spacec+i*2 > 22){
						Ubicacion = false;
					system("cls");
							this->PintarMapa(VectorInterno,0,0);
					break;
					} else{
							Ubicacion = true;
					} 
					gotoxy(spacec+i*2,spacef);printf("%c",'#');
				}
				break;
				
				case (LEFT):
				Direccion = LEFT;
				system("cls");
				this->PintarMapa(VectorInterno,0,0);
				for(int i = 0; i < NumeroBarcos;i++){
					if(spacec-i*2 < 3){
						Ubicacion = false;
						system("cls");
						this->PintarMapa(VectorInterno,0,0);
						break;
					} else{
						Ubicacion = true;
					}
					gotoxy(spacec-i*2,spacef);printf("%c",'#');
				}
				break;
				
				case (SPACE):
				system("cls");
				if(Ubicacion && Direccion){
					if(this->CargarBarco()){
						Salir = true;
						NumeroBarcos++;
					} else {
						cout<<"Posicion invalida"<<endl;
						cout<<"No puede ubicar un barco sobre otro"<<endl;
						system("pause");
					}
				}
				break;
				default:break;
			}
		}
	}
}

class Jugador{
	public:
	int NumeroPlayer;
	int coordx,coordy;
	int DisparoAcertado;
	int DisparoFallido;
	Tablero* MiTablero;
	bool Win;
	
	public:
	Jugador(Tablero* TableroPlayer,int x);
	void Disparar(Tablero* Obj); //parametro el tablero enemigo
	void Estadisticas(Tablero* Obj);
	void Ganador();
};

void Jugador::Estadisticas(Tablero* Obj){
	
	system("cls");
	
	gotoxy(58,5);
	cout<<"DISPAROS ACERTADOS "<<DisparoAcertado;
	gotoxy(58,8);
	cout<<"DISPAROS FALLIDOS  "<<DisparoFallido;
	
	MiTablero->PintarMapa(MiTablero->VectorInterno,0,0);
	gotoxy(0,15);
	cout<<"TABLERO DE JUGADOR EN TURNO\n";
	Obj->PintarMapa(Obj->VectorMapa,30,0);
	gotoxy(36,15);
	cout<<"TABLERO ENEMIGO\n";
}

void Jugador::Ganador(){
	system("cls");
	if(DisparoAcertado == 14){
		Win = true;
		cout<<("FELICIDADES HA GANADO SU BATALLA NAVAL\n");
		cout<<("SOLO UNA BATALLA,LA GUERRA CONTINUA\n");
	}
}

Jugador::Jugador(Tablero* TableroPlayer,int x){
	NumeroPlayer = x;
	MiTablero = TableroPlayer;
	TableroPlayer->UbicarBarcos();
	DisparoAcertado = 0;
	DisparoFallido = 0;
}

void Jugador::Disparar(Tablero* Obj){
	bool Acertado = true,DisparoValido = true;
	bool LetraValida = false,ColumnaValida = false;
	
	system("cls");
	cout<<"\nTURNO DEL JUGADOR NUMERO "<<NumeroPlayer<<endl;
	system("pause");
	
	while(Acertado && DisparoAcertado != 14){
		do{
			LetraValida = false,ColumnaValida = false;
			while(!LetraValida){
				coordy = 0, coordx = 0;
				this->Estadisticas(Obj);
				cout<<"\n\n\nIngrese coordenadas para su disparo letra entre A-J\n";
				coordy = getchar();
				if( isalpha(coordy) && (( coordy >= 'A' && coordy <= 'J') || (coordy >= 'a' && coordy <= 'j')) ){
					if(!isupper(coordy)){
						coordy = toupper(coordy);
					}
					coordy -=64;
					LetraValida = true;
				}
			}
			while(!ColumnaValida){
				this->Estadisticas(Obj);
				cout<<"Ingrese un numero entre 1 y 10"<<endl;
				cin>>coordx;
		
				if(!isdigit(coordx) && (coordx > 0 && coordx < 11)){
					ColumnaValida = true;
				} else {
					cout<<"Coordenadas invalidas, esta fuera del mapa"<<endl;
					cout<<"Debe estar en un rango 1 - 10 "<<endl;
					system("pause");
				}
			}
			if(Obj->VectorInterno[coordy][coordx] == 158 || Obj->VectorInterno[coordy][coordx] == 184){
				cout<<"YA REALIZO UN DISPARO EN ESA COORDENADA"<<endl;
				cout<<"INTENTE UNA NUEVA COORDENADA"<<endl;
				DisparoValido = false;
			} else {
				DisparoValido = true;
			}
		}while(!DisparoValido);
		
		if(Obj->VectorInterno[coordy][coordx] == '#'){
			Obj->VectorMapa[coordy][coordx] = 158;  // 158 marca tiro acertado 
			Obj->VectorInterno[coordy][coordx] = 158;
			++DisparoAcertado;
			
			this->Estadisticas(Obj);
			cout <<"\n\nUsted ha acertado en blanco"<<endl;
			system("pause");
		} else {
			Obj->VectorMapa[coordy][coordx] = 184;
			Obj->VectorInterno[coordy][coordx] = 184;
			Acertado = false;
			++DisparoFallido;
			
			this->Estadisticas(Obj);
			cout <<"\n\nUsted ha fallado el blanco"<<endl;
			system("pause");
		}
	}
	this->Ganador();
}

void Inicio(){
	char Presenta[20][76] = {
		"                                                                          ",
		" *******   *********  *********  ********   **        **        ********* ",
		" **    *   **      *     **      **     *   **        **        **      * ",
		" **    *   **      *     **      **     *   **        **        **      * ",
		" *******   *********     **      ********   **        **        ********* ",
		" **    *   **      *     **      **     *   **        **        **      * ",
		" **    *   **      *     **      **     *   **        **        **      * ",
		" *******   **      *     **      **     *   *******   *******   **      * ",
		"                                                                          ",
		"                                                                          ",
		"          ***      **   *********  *           *  *********  **          ",
		"          ** *     **   **      *   *         *   **      *  **          ",
		"          **  *    **   **      *    *       *    **      *  **          ",
		"          **   *   **   *********     *     *     *********  **          ",
		"          **    *  **   **      *      *****      **      *  **          ",
		"          **     * **   **      *       ***       **      *  **          ",
		"          **      ***   **      *        *        **      *  ********    ",
	};
	system("color 17");
	for (int i = 0; i < 20;i++){
		printf("\n");
		for (int k = 0; k < 76;k++){
			if(Presenta[i][k] == '*'){
				printf("%c",217);
			} else{
				printf("%c",219);
			}
		}
	}
	printf("\n");
	system("pause");
}

void Final(){
	char Fin[19][62] = {
		"                                                           ",
		"     **********  **********  **         ***  **********    ",
		"     **********  **      **  ** *      * **  **            ",
		"     **          **      **  **  *    *  **  **            ",
		"     **  ******  **********  **   *  *   **  ******        ",
		"     **  ******  **********  **    **    **  **            ",
		"     **      **  **      **  **          **  **            ",
		"     **********  **      **  **          **  **********    ",
		"                                                           ",
		"                                                           ",
		"         *****    *             *  *********  *******      ",
		"       **     **   *           *   **         *********    ",
		"      **       **   *         *    **         **     **    ",
		"      **       **    *       *     ******     *********    ",
		"      **       **     *******      **         **      **   ",
		"       **     **       *****       **         **       **  ",
		"         *****           *         *********  **        ** ",
	};
	for (int i = 0; i < 19;i++){
		printf("\n         ");
		for (int k = 0; k < 62;k++){
			if(Fin[i][k] == '*'){
				printf("%c",217);
			} else{
				printf("%c",219);
			}
		}
	}
	printf("\n");
	system("pause");
	exit(0);
}

void Jugar(bool *GameOver){
	Inicio();
	bool Salir = false;
	Tablero* ptr1 = new Tablero;
	Tablero* ptr2 = new Tablero;
	
	Jugador* player1 = new Jugador(ptr1,1);
	Jugador* player2 = new Jugador(ptr2,2);
	
	while(!Salir){
		player1->Disparar(ptr2);
		if(player1->Win){
			Salir = true;
			break;
		}
		player2->Disparar(ptr1);
		if(player2->Win){
			Salir = true;
			break;
		}
	}
	*GameOver = true;
}

main (){
	bool GameOver;
	while(!GameOver){
		Jugar(&GameOver);
	}
	Final();
}
