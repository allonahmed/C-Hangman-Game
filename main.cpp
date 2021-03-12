#include <iostream>
#include <stdlib.h> // to use srand
#include <time.h> // to use time
#include <sstream> //to use stringstream for int convers
#include <string>
#include <curses.h> // to use to clear screen
#include <vector> //for wordbank

using namespace std;
//https://codereview.stackexchange.com/questions/51461/hangman-game-with-hard-coded-word-or-phrase
string phrases[] = {"Neville Longbottom", "America Chavez", "My Hero Academia", "All of Me", "All American", "Macbook pro laptop","Frank Grillo","Dog", "Mexico", "Taj Mahal", "Abraham Lincoln", "Spanish", "Frankenstien", "Star Trek", "World War", "Waterfalls", "Batman", "Lady Death", "Cheetah", "Goldie", "James Bond", "Writings on the Wall"  };
string category[] = {"Fantasy Characters", "Marvel Super Heroes","Anime Titles", "John Legend Song", "Drama Television", "Technology", "Actors", "Pets", "Country", "Landmarks", "Historical Figures", "Languages", "Monsters", "Science Fiction", "Non-Fiction", "Nature", "Dc Super Heroes", "Marvel Super Villians", "Dc Super Villians", "Nissan Altima", "Secret Agent", "Sam Smith Song"};
string boardBlank = ""; //
vector<char> wordBank;


// int sizeOfArr = 3;
int error=0; // this will represent the ammount of wrong choices the player has made
//Hangman Game Application
void welcomeGame()
{
  cout << "-------------------------------------------\n";
  cout << "- Hello, Welcome to the C++ Hangman Game! -\n";
  cout << "-------------------------------------------\n";
}
void hangManBoard(int); // function prototype

void rules(){
  char choice;
  cout << "Would you like to see the rules of Hangman? (type y for yes/n for no): ";
  cin >> choice;
  if (choice=='y')
  {
    cout << "print rules\n";
  }
}

int randInd(){ // random function to randomly generate our phrase and category
  srand(time(NULL));
  return rand()%22;
}
int x = randInd();

//function that converts strings to lowercase for error handling
string toLower(string a)
{
  string toL = "";
  for (int i = 0; i < a.size(); i+=1)
  {
    if (a[i]>='A' && a[i] <= 'Z')
    {
      toL += a[i] + 32; //dont put only equal sign, setting it equal to that value, ADD!
    }
    else 
      toL += a[i];
  }
  return toL;
}

void generateBoardString(string n) // create the blank spots of the string //& is used for reference within parameters for string //immutable
{
  string boardS = "";
  n = toLower(n); // converts the string to lowercase, if not used..only lowercase letters will be counted...not the uppercase
  // string boardP = "";
  for (int i = 0; i < n.size(); i++)
  {
    if (n[i] >='a' && n[i] <='z')
    {
      boardS += "_";
    }
    else if( n[i]==' '){
      boardS += " ";
    }
  }
  boardBlank = boardS;
}

void addBank(char letter)
{
  wordBank.push_back(letter);
}

bool checkLetter( char letter, string &boardBlank)
{
  addBank(letter);
  for (int i = 0; i < boardBlank.size(); i++)
  {
    if (letter == boardBlank[i])
    {
      return true;
    }
  }
  return false;
}

void createBank()
{
  cout << "\n********************************************\n WORD BANK: ";
  for (int i = 0; i < wordBank.size(); i++)
  {
    cout << wordBank[i] << " ";
  }
  cout << "\n********************************************\n";
}

void updatePhrase(string phrases, string &boardBlank, char letter)
{
  for (int i = 0; i < phrases.size(); i++)
  {
    if(phrases[i] == letter)
    {
      boardBlank[i] = letter;
    }
  }
}
bool winnerTrue(string boardBlank, string phrases)
{
  string l = toLower(phrases);
  return boardBlank==l;
}

void GAMEWINNER(string phrases)
{
  if (winnerTrue(boardBlank, phrases))
  {
    cout << "\nYOU WON THE GAME CONGRATULATIONS!\n";
  }
}
char toCharLower(char letter)
{
  if (letter>='A' && letter <= 'Z')
  {
    return letter+32;
  }
  else
  {
    return letter;
  }
}
bool findLetterInBank(char letter)
{
  for (int i = 0; i < wordBank.size(); i++)
  {
    if( letter == wordBank[i])
    {
      return true;
    }
  }
  return false;
}

void pickLetter(string &boardBlank)
{
  char letter;
  string phr = toLower(phrases[x]);
  while((winnerTrue(boardBlank, phr) == false) && error!=6)
  {
    cout << "Enter a letter! : ";
    cin >> letter;
    letter = toCharLower(letter);
    while (findLetterInBank(letter)){
      cout << "\nYou already picked that letter! Try again: ";
      cin >> letter;
      letter = toCharLower(letter);
    }
    system("clear");
    if(checkLetter(letter,phr) == true)
    {
      updatePhrase(phr, boardBlank, letter);
      hangManBoard(error);
      // system("clear");2
    }
    else
    {
      error++;
      hangManBoard(error);
    }
  }
}

void displayPhrase(string &boardBlank)
{
  for (int i = 0; i < boardBlank.size(); i+=1)
  {
    cout << boardBlank[i] << " ";
  }
}

void Game(){
  welcomeGame(); // first thing to show up on console
  // rules();
 // segmentation means out of bounds
  generateBoardString(phrases[randInd()]);
  hangManBoard(error);
    // generates random 
  cout << "\n\n";
  pickLetter(boardBlank);
}

int main()
{
  Game();
}

void hangManBoard(int error)
{
  
  if (error==0)
  {
    cout << "     |--------|     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << " ------------------ \n\n" << endl;
    displayPhrase(boardBlank);
    cout << "\n\nCategory: " << category[x] << endl;
  }
  else if (error==1)
  {
   
    cout << "     |--------|     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |       / \\     " << endl;
    cout << "     |       \\ /     " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << " ------------------ \n\n" << endl;
    cout << boardBlank << "\n";
    cout << "\nCategory: " << category[x] << endl;
  }
  else if( error == 2)
  {

    cout << "     |--------|     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |       / \\     " << endl;
    cout << "     |       \\ /     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |        |      " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << " ------------------ \n\n" << endl;
    cout << boardBlank << "\n";
    cout << "\nCategory: " << category[x] << endl;
  }
  else if( error ==3)
  {

    cout << "     |--------|     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |       / \\     " << endl;
    cout << "     |       \\ /     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |        |      " << endl;
    cout << "     |       /      " << endl;
    cout << "     |      /       " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << " ------------------ \n\n" << endl;
    cout << boardBlank << "\n";
    cout << "\nCategory: " << category[x] << endl;
  }
    else if( error ==4)
  {

    cout << "     |--------|     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |       / \\     " << endl;
    cout << "     |       \\ /     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |        |      " << endl;
    cout << "     |       / \\    " << endl;
    cout << "     |      /   \\    " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << " ------------------ \n\n" << endl;
    cout << boardBlank << "\n";
    cout << "\nCategory: " << category[x] << endl;
  }
  else if( error ==5)
  {

    cout << "     |--------|     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |       / \\     " << endl;
    cout << "     |       \\ /     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |       /|     " << endl;
    cout << "     |      / |      " << endl;
    cout << "     |       / \\    " << endl;
    cout << "     |      /   \\    " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << " ------------------ \n\n" << endl;
    cout << boardBlank << "\n";
    cout << "\nCategory: " << category[x] << endl;
  }
  else if( error ==6)
  {

    cout << "     |--------|     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |       / \\     " << endl;
    cout << "     |       \\ /     " << endl;
    cout << "     |        |     " << endl;
    cout << "     |       /|\\    " << endl;
    cout << "     |      / | \\     " << endl;
    cout << "     |       / \\    " << endl;
    cout << "     |      /   \\    " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << "     |              " << endl;
    cout << " ------------------ \n\n" << endl;
    cout << boardBlank << "\n";
    cout << "\nCategory: " << category[x] << endl;
    cout << "YOU LOSE\n";
  }

  createBank();
  GAMEWINNER(phrases[x]);
}