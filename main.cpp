#include "SDL.h"
#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
#include "Matrix.h"
#include "BinaryImage.h"

using namespace std;

//Reads .txt file 
double* readTXT(char *fileName, int sizeR, int sizeC);

//Makes .pgm image file
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);

//bool to check if txt files have been read
bool File_has_read = true;

int main(int argc, char* args[])
{
	bool fine = false;
	int startR = 0, startC = 0, goalR = 0, goalC = 0;
	//M = Rows and N = columns in the image,
	int M = 20; int N = 30;

	//initals pointer for file
	double* inputf = 0;

	char* inputFileName = "C:\\Users\\Sinjun\\Documents\\visual studio 2013\\Projects\\Assessment 2\\layout.txt";
	inputf = readTXT(inputFileName, M, N);

	if (File_has_read)//check the that text files where both read
	{
		//save layout to matrix
		Matrix layout(M, N, inputf);

		//layout.Output_Matrix(M, N);//outmatrix to chec that layout is saved

		//get start location		
		do{
			cout << "Enter start row location: \nRange 0-19\n";
			cin >> startR;
			cout << "Enter start column location: \nRange 0-29\n";
			cin >> startC;
			int x = layout.get(startR, startC);
			if (x == 0)
				fine = true;
			else
				cout << "not a valid location, Causes - wall there or out of range\nTry agian \n";
			system("pause");
		} while (!fine);
		fine = false;
		//get goal location
		do{
			cout << "Enter goal row location:\nRange 0-19\n";
			cin >> goalR;
			cout << "Enter goal column location: \nRange 0-29\n";
			cin >> goalC;
			int x = layout.get(goalR, goalC);
			if (x == 0)
				fine = true;
			else
				cout << "not a valid location, Causes - wall there or out of range\nTry agian \n\n";
			system("pause");
		} while (!fine);
		//Start SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Quit SDL
		SDL_Quit();
		
	}
	system("pause");
	delete[] inputf;
	return 0;
}


	// Read .txt file with image of size RxC, and convert to an array of doubles
	double* readTXT(char *fileName, int sizeR, int sizeC)
	{
		double* data = new double[sizeR*sizeC];
		int i = 0;
		ifstream myfile(fileName);
		if (myfile.is_open())
		{
			while (myfile.good())
			{
				if (i > sizeR*sizeC - 1) break;
				myfile >> *(data + i);

				i++;
			}
			myfile.close();
		}

		else
		{
			cout << "Unable to open file at loaction:" << endl << fileName << endl << endl;
			File_has_read = false;
		}

		return data;
	}
