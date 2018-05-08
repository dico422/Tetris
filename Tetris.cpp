#include "Tetris.h"

Tetris::Tetris(int larg){
	jogo = new char*[larg];
	alturas = new int[larg];

	for(int i=0 ; i<larg ; i++){
		alturas[i] = 0;
		jogo[i] = NULL;
	}

	numColunas = larg;


}
Tetris::Tetris(const Tetris& T){
	constroi(T.getNumColunas());
	*this = T;
}
Tetris::~Tetris(){
	for(int i=0; i<numColunas ;i++){
		if(jogo[i]) delete [] jogo[i];
	}
	if(jogo) delete [] jogo;
	if(alturas) delete [] alturas;
}

void  Tetris::constroi(int larg){
	jogo = new char*[larg];
	alturas  = new int[larg];

	for(int i=0; i<larg ; i++){
		alturas[i] = 0;
		jogo[i] = NULL;
	}

	numColunas = larg;
}

void Tetris::destroi(){
	for(int i=0; i<numColunas ; i++)
		if(jogo[i]) delete [] jogo[i];
	if(jogo) delete [] jogo;
	if(alturas) delete [] alturas;
}

char Tetris::get(int c, int l) const{
	if(c < numColunas && l < getAltura(c))
		return ( jogo[c][l] == '\0' ? ' ' : jogo[c][l] );
	else
		return ' ';
}

void Tetris::removeColuna(int c){

}
void Tetris::removeLinhasCompletas(){

	for(int i=getAltura()-1, a=0;i>=0;i--){
		for(int j=0;j<getNumColunas();j++){
			if(get(j,i)!=' ') a++;
		}
		if(a==getNumColunas()) removeLinha(i);
		a = 0;
	}

}
void Tetris::removeLinha(int l){

	Tetris NewJogo(this->getNumColunas());

	for(int i=0;i<this->getNumColunas();i++){
		if(this->getAltura(i)<l)
			NewJogo.alturas[i] = this->getAltura(i);
		else 
			NewJogo.alturas[i] = this->getAltura(i)-1;
		std::cout << NewJogo.getAltura(i) << std::endl;
	}

	for(int i=0;i<NewJogo.getNumColunas();i++){
		NewJogo.jogo[i] = new char[NewJogo.getAltura(i)];
		for(int j=0;j<NewJogo.getAltura(i);j++)
			jogo[i][j] = ' ';
	}

	for(int i=0;i<NewJogo.getNumColunas();i++){
		for(int j=0;j<NewJogo.getAltura(i);j++){
			if(j<l)
				NewJogo.jogo[i][j] = this->get(i,j);
			else 
				NewJogo.jogo[i][j] = this->get(i,j+1);
		}
	}

	*this = NewJogo;

	NewJogo.destroi();

}

int Tetris::getAltura() const{
	int maxAlt = alturas[0];
	for(int i=1; i<numColunas; i++)
		if(maxAlt < alturas[i]) maxAlt = alturas[i];
	
	return maxAlt;
}


Tetris& Tetris::operator= (const Tetris& T){
	if(this == &T) return *this;

	this->destroi();
	this->constroi(T.getNumColunas());

	this->jogo = new char*[T.getNumColunas()];
	this->alturas = new int[T.getNumColunas()];

	for(int i=0;i<numColunas;i++){
		this->alturas[i] = T.getAltura(i);
		this->jogo[i] = new char[T.getAltura(i)];

	}

	for(int i=0;i<getNumColunas();i++){
		for(int j=0;j<getAltura(i);j++)
			jogo[i][j] = T.get(i,j);
	}	
	return *this;

}

void printForma(char (&Forma) [5][5]){
	
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(Forma[i][j] == ' ') std::cout << '_';
			else std::cout << Forma[i][j];
		}
		std::cout << std::endl;
	}

}

bool Tetris::adicionaForma(int c, int l, char id, int r){

	char peca[5][5];

	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			peca[i][j] = ' ';

	int Tx [2];
	int Ty [2];


	switch ((int)id){
		case (int)'I':		//T(x,y) = (y,-x)
			
			//Inicial  State
			
			peca[0][0] = id;
			peca[1][0] = id;
			peca[2][0] = id;
			peca[3][0] = id;

			//Inicial  State
			
			Tx[0] = 0; Tx[1] = 1;
			Ty[0] = -1; Ty[1] = 0;
			
			break;
		case (int)'Z':		//T(x,y) = (-y,x)

			//Inicial  State
			
			peca[0][0] = id;
			peca[0][1] = id;
			peca[1][1] = id;
			peca[1][2] = id;

			//Inicial  State
		
			Tx[0] = 0; Tx[1] = -1;
			Ty[0] = 1; Ty[1] = 0;

			break;
		case (int)'S':		//T(x,y) = (y,-x)

			//Inicial  State
			
			peca[1][0] = id;
			peca[1][1] = id;
			peca[0][1] = id;
			peca[0][2] = id;

			//Inicial  State
			
			Tx[0] = 0; Tx[1] = 1;
			Ty[0] = -1; Ty[1] = 0;

			break;
		case (int)'J':		//T(x,y) = (y,-x)

			//Inicial  State
			
			peca[0][1] = id;
			peca[1][1] = id;
			peca[2][1] = id;
			peca[3][1] = id;
			peca[3][0] = id;

			//Inicial  State
		
			Tx[0] = 0; Tx[1] = 1;
			Ty[0] = -1; Ty[1] = 0;

			break;
		case (int)'L':		//T(x,y) = (y,-x)

			//Inicial  State
			
			peca[0][0] = id;
			peca[1][0] = id;
			peca[2][0] = id;
			peca[3][0] = id;
			peca[3][1] = id;

			//Inicial  State
		
			Tx[0] = 0; Tx[1] = 1;
			Ty[0] = -1; Ty[1] = 0;

			break;
		case (int)'T':		//T(x,y) = (y,-x)

			//Inicial  State
			
			peca[0][0] = id;
			peca[1][0] = id;
			peca[2][0] = id;
			peca[1][1] = id;

			//Inicial  State
			
			Tx[0] = 0; Tx[1] = 1;
			Ty[0] = -1; Ty[1] = 0;

			break;
		case (int)'O':

			//Inicial  State
			
			peca[0][0] = id;
			peca[1][0] = id;
			peca[0][1] = id;
			peca[1][1] = id;

			//Inicial  State
			
			Tx[0] = 1; Tx[1] = 0;
			Ty[0] = 0; Ty[1] = 1;

			break;
	
	}


	TransformaForma(peca, Tx , Ty, r/90);

	// Verifica se eh possivel adicionar peca

	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++){
			if(peca[j][i] == id){
				if(c+i>=numColunas || c+i < 0) return false;
				else if(l-j < 0) return false;
				else if(l==-1) return false;
				else if(get(c+i,l-j)!= ' ') return false;
			}
		}

	// Salva peca no jogo
	
	SalvaForma(peca, c, l, id);

	return true;


}

void Tetris::SalvaForma(char (&Forma) [5][5], int c, int l , char id){

	char** NewJogo = new char* [5];

	int EspacosEmBranco[5] = {0,0,0,0,0};
	int Alturas[5] = {0,0,0,0,0};

	// Descobre os espacos em branco acima de cada coluna de Forma

	for(int i=0;i<5;i++)
		for(int j=0;j<5 && Forma[j][i] == ' ';j++)
			EspacosEmBranco[i]++;

	// Define as alturas de cada coluna

	bool ChangeAltura = false;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++)
			if(Forma[j][i] == id) ChangeAltura = true;

		if(ChangeAltura){
			Alturas[i] = l+1-EspacosEmBranco[i];
			NewJogo[i] = new char [ Alturas[i] ];
			ChangeAltura = false;
		}
	}

	// Preenche cada coluna nova com os pixels antigos 

	for(int i=0;i<5;i++)
		for(int j=0;j<Alturas[i];j++)
			NewJogo[i][j] = get(i+c,j);

	// Salva os pixels da Forma para as Colunas Novas

	bool FirstPixel = false;
	for(int i=0;i<5;i++)
		for(int j=Alturas[i]-1, k=0 ; k<5 && j>Alturas[i]-6; k++)
			if(Forma[k][i]==id){
			       	NewJogo[i][j] = Forma[k][i];
				j--;
			}

	// Salva as colunas em jogo

	char* AuxColuna = NULL;

	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++)
			if(Forma[j][i] == id) ChangeAltura = true;

		if(ChangeAltura){
			AuxColuna = jogo[i+c];
			jogo[i+c] = NewJogo[i];
			NewJogo[i] = AuxColuna;
			alturas[i+c] = Alturas[i];
			ChangeAltura = false;
		}
	}

	delete AuxColuna;	


}


void Tetris::TransformaForma(char (&Forma) [5][5], int Tx[2], int Ty[2], int times){ 		//e.g Forma, {0,1} , {1,0} , 270/90

	if(times <= 0) return;

	char FormaAux [5][5];
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			FormaAux[i][j] = ' ';

	int deslX = 0;		// Desloca a peca caso esteja fora da Matris Forma
	int deslY = 0;

	for(int i=0;i<5;i++)	// Verifica se eh necessario deslocar a peca
		for(int j=0;j<5;j++){
			if(Forma[i][j] != ' ' && (  Tx[0]*i + Tx[1]*j < deslX )) deslX =  Tx[0]*i + Tx[1]*j;
			if(Forma[i][j] != ' ' && (  Ty[0]*i + Ty[1]*j < deslY )) deslY =  Ty[0]*i + Ty[1]*j;	
		}

	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if(Forma[i][j] != ' ') FormaAux[ Tx[0]*i+Tx[1]*j + (-1)*deslX ][ Ty[0]*i+Ty[1]*j + (-1)*deslY ] = Forma[i][j] ; // Rotate Piece


	for(int i=0;i<5;i++) // Salva a Forma
		for(int j=0;j<5;j++)
			Forma[i][j] = FormaAux[i][j];

	TransformaForma( Forma, Tx, Ty , times-1);

}

	

