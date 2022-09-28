#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<time.h>
using namespace std;

void PrintMessage(string message, bool PrintTop=true, bool PrintBottom=true) // we used bool to hide or show borders
{
    if (PrintTop)
    {
        cout<<"+---------------------------------+"<<endl;
        cout<<"|";
    }
    else
    {
        cout<<"|";
    }
    bool front=true;
    for(int i=message.length(); i<33;i++)  //33 will display the "-" width
    {
        if(front)
        {
            message=" "+message;  // to add space in front of string
        }
        else
        {
            message= message + " ";  // to add space in back of string
        }
        front=!front;  // to achieve space we have to make it false
    }
    cout<<message.c_str();

     if (PrintBottom)
    {
        cout<<"|"<<endl;
        cout<<"+---------------------------------+"<<endl;
    }
    else
    {
        cout<<"|"<<endl;
    }
}
void DrawHangman(int guessCount=0)
{
    if(guessCount >= 1)
        PrintMessage("|",false, false); // the top and bottom borders will not print 
    else
        PrintMessage("",false,false);

    if(guessCount >= 2)
        PrintMessage("|",false, false); // the top and bottom borders will not print 
    else
        PrintMessage("",false,false);
    
    if(guessCount >= 3)
        PrintMessage("O",false, false); // the top and bottom borders will not print 
    else
        PrintMessage("",false,false);

    if(guessCount == 4)
        PrintMessage("/  ",false, false); // the top and bottom borders will not print 

    if(guessCount == 5)
        PrintMessage("/| ",false, false); // the top and bottom borders will not print 

    if(guessCount >= 6)
        PrintMessage("/|\\",false, false); // the top and bottom borders will not print 
    else
    {
        PrintMessage("",false,false);
    }

    if(guessCount >= 7)
        PrintMessage("|",false, false); // the top and bottom borders will not print 
    else
        PrintMessage("",false,false);

    if(guessCount == 8)
        PrintMessage("/",false, false); // the top and bottom borders will not print 
    
    if(guessCount >= 9)
        PrintMessage("/ \\",false, false); // the top and bottom borders will not print 
    else
        PrintMessage("",false,false);
 
    
    
}

void PrintLetters(string input, char from, char to)  // to print letters "from" starts from 1st and "to" ends
{
    string s;
    for(char i=from;i<=to;i++)
    {
        if(input.find(i)==string::npos) //we used npos cause if "find" returns "string" it means it didnt find the character
        {
            s +=i; 
            s +=" ";
        } 
        else
        s += "  "; // if it contains letter then we'll add an empty space
    }
    PrintMessage(s, false, false);

}

void PrintAvailableLetters(string taken) // the letters that are taken will not be printed  
{
    PrintMessage("Available Letters");
    PrintLetters(taken,'A','M');
    PrintLetters(taken,'N','Z');
}

bool PrintWordAndCheckWin(string word, string guessed)
{
    bool won = true;
    string s;
    for(int i=0; i<word.length();i++)
    {
        if(guessed.find(word[i])==string::npos) // if string does not containt the character
        {
            won=false;
            s += "_ ";
        }
        else
        {
            s +=word[i];
            s +=" ";
        }
    }
    PrintMessage(s,false); //the PrintTop is automatically set to true
    return won;

}

string LoadRandomWord(string path)
{
    int lineCount=0;
    string word;
    vector<string> v;  //used vector as the array is dynamic
    ifstream reader(path);
    if(reader.is_open())
    {
        while(std::getline(reader, word)) //will input the lines and sort them
        v.push_back(word); 

        int randomLine = rand()%v.size(); // will give the range from 0 to number of lines

        word=v.at(randomLine);
        reader.close();   
    }
    return word;    


}

int TriesLeft(string word, string guessed)
{
    int error=0;
    for(int i=0;i<guessed.length();i++)
    {
        if(word.find(guessed[i])==string::npos)
        error++;
    }
    return error;
}
int main()
{   
    srand(time(0));
    string guesses;
    string WordToGuess;
    WordToGuess = LoadRandomWord("word.txt"); ;
    int tries =0;
    bool win=false;
    do
    {
         
        PrintMessage("HANG MAN");
        DrawHangman(tries); 
        PrintAvailableLetters(guesses);
        PrintMessage("Guess The Word");
        win = PrintWordAndCheckWin(WordToGuess, guesses);

        if(win)
        break;

        char x; //if the user hasnt won we will load the character from the user
        cout<<">";cin>>x;
        if(guesses.find(x)==string::npos)
        guesses +=x;

        tries=TriesLeft(WordToGuess, guesses);

    } while (tries<10);
    if (win)
    PrintMessage("YOU WON");
    else{
        PrintMessage("GAME OVER");
    }
    
    
    return 0;
}