#include "SDL.h"
#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
#include "Matrix.h"
#include "BinaryImage.h"
#include "DoublyLinkedList.h"

using namespace std;

//Reads .txt file 
double* readTXT(char *fileName, int sizeR, int sizeC);

//Makes .pgm image file
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);

//bool to check if txt files have been read
bool File_has_read = true;

//manhattan
double manhattan(double, double, double, double);

//euclid
double euclid(double, double, double, double);

int main(int argc, char* args[])
{
	//The images setup
	SDL_Surface* hello = NULL;
	SDL_Surface* screen = NULL;
	//setup blocksize
	int Blocksize = 0;
	//checker
	bool fine = false;
	//R & C of current and goal
	double currentR = 0, currentC = 0, goalR = 0, goalC = 0;
	//M = Rows and N = columns in the image,
	int M = 20; int N = 30;
	//set up lists
	DoublyLinkedList<double> Openlist;
	DoublyLinkedList<double> close;
	//initals pointer for file
	double* inputf = 0;

	//store file location
	char* inputFileName = "C:\\Users\\Sinjun\\Documents\\visual studio 2013\\Projects\\Assessment 2\\layout.txt";
	inputf = readTXT(inputFileName, M, N);

	if (File_has_read)//check that text files was read
	{
		//save layout to matrix
		Matrix layout(M, N, inputf);

		layout.Output_Matrix(M, N);//output matrix to check that layout is saved

		do{
		//get blocksize
		cout << "Enter the block size of the screen, recomended 20, range 20-40\n";
		cin >> Blocksize;
		//validate blocksize
		if (Blocksize > 19 && Blocksize < 41){
			fine = true;
			break;
		}
		cout << "Blocksize input is out of range\n";

	} while (!fine);
	fine = false;
		//get start location		
		do{
			cout << "Enter start row location: \nRange 0-19\n";
			cin >> currentR;
			cout << "Enter start column location: \nRange 0-29\n";
			cin >> currentC;
			int x = layout.get(currentR, currentC);
			//validate start loaction
			if (x == 0)
				fine = true;
						 else{
				cout << "not a valid location, Causes - wall there or out of range\nTry agian \n";
				system("pause");
			}
		} while (!fine);
		fine = false;

		//get goal location
		do{
			cout << "Enter goal row location:\nRange 0-19\n";
			cin >> goalR;
			cout << "Enter goal column location: \nRange 0-29\n";
			cin >> goalC;
			int x = layout.get(goalR, goalC);
			//validate goal loaction
			if (x == 0)
				fine = true;			
			else{
				cout << "not a valid location, Causes - wall there or out of range\nTry agian \n\n";
				system("pause");
			}
		} while (!fine);
		
		//Start SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Set up screen
		screen = SDL_SetVideoMode(N*Blocksize, M*Blocksize, 32, SDL_SWSURFACE);
	
		//Apply image to screen
		SDL_BlitSurface(hello, NULL, screen, NULL);

		//make and rec object
		SDL_Rect Rectangle;
		//set rec height
		Rectangle.h = Blocksize;
		//set rec weight
		Rectangle.w = Blocksize;

		//def a a colour
		Uint32 White = SDL_MapRGB(screen->format, 255, 255, 255);//traversable colour
		Uint32 Green = SDL_MapRGB(screen->format, 0, 204, 0);//start colour
		Uint32 Red = SDL_MapRGB(screen->format, 255, 0, 0);//goal colour
		Uint32 blue = SDL_MapRGB(screen->format, 51, 51, 255);//trail colour
		//hold increass value
		double temi=0, temj = 0;

		//outputs the layout of the text file onto the screen.
		for (int i = 0; i < M; i++){
			for (int j = 0; j < N; j++){
				Rectangle.y = temi;
				Rectangle.x = temj;
				if (layout.get(i, j) == 0){
					SDL_FillRect(screen, &Rectangle, White);
					//SDL_Flip(screen);
				}
				else{
					NULL;
				}
				temj += Blocksize;
			}
			temj = 0;
			temi += Blocksize;
		}
		//set up start block colour
		Rectangle.y = currentR* Blocksize;
		Rectangle.x = currentC*Blocksize;
		SDL_FillRect(screen, &Rectangle, Green);

		//set up goal colour
		Rectangle.y = goalR*Blocksize;
		Rectangle.x = goalC*Blocksize;
		SDL_FillRect(screen, &Rectangle, Red);
		//Update Screen
		SDL_Flip(screen);
		//--------------------------------------------------------------------------------------------------------------------
		if(currentC == goalC && currentC == goalR)
		{
			cout<<"Goal found";
		}
		else
		{
			close.InsertFront(currentR - 1, currentR + 1, currentC - 1, currentC + 1, NULL, manhattan(currentR, currentC, goalR, goalC));
		}


		//--------------------------------------------------------------------------------------------------------------------
		//Pause
		//SDL_Delay(2000);

		//Free the loaded image
		SDL_FreeSurface(hello);


		SDL_Event event;
		bool gameRunning = true;
		while (gameRunning)
		{
			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					gameRunning = false;
				}
			}
		}

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

	//manhattan
	double manhattan(double Str, double Stc, double Gor, double Goc)
	{
		double H = 0;

		H = ((Str - Gor)) + ((Stc - Goc)) * 10;

		if (H < 0)
			H = H*-1;//remove negative values
		return H;
	}
	//euclid
	double euclid(double Str, double Stc, double Gor, double Goc)
	{
		double H = 0;
		H = (sqrt(((Str - Gor)*(Str - Gor)) + ((Stc - Goc)*(Stc - Goc)))) * 10;
		return H;
	}