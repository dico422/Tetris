#ifndef __Tetris_h__
#define __Tetris_h__

#include <iostream>

class Tetris{
	public:

		Tetris(int l);
		Tetris(const Tetris&);
		~Tetris();

		void TransformaForma(char (&Forma) [5][5], int [2] ,int [2] , int);
		void TransformaColuna(int c , int l, char* Forma);
		void SalvaForma(char (&Forma) [5][5], int c, int l, char id);

		char get(int c, int l) const;

		void removeColuna(int c);
		void removeLinhasCompletas();
		void removeLinha(int);

		int getNumColunas() const{ return numColunas;}
		int getAltura(int c) const{ return alturas[c];}
		int getAltura() const;

		bool adicionaForma(int c, int l, char id, int r);

		Tetris& operator= (const Tetris&);


	private:
		
		char** jogo;
		int numColunas;
		int* alturas;

		void constroi(int);
		void destroi();

};

#endif

