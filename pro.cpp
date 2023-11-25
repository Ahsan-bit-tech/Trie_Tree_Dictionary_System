#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std ; 
struct Node
{
    char ch ; 
    Node*next[97];
    bool endline = false;
};
class  trietree
{
private:
    Node* root ;
    Node* current;
    int char_index;
public:
    trietree();
    void insert(string ,string);
    void Loading();
    bool Search( string);
    void AddWord();
    bool deletion(string);
    void update_word(string);
    
//    ~ trietree()
//    {
//        root= NULL;
//        delete root;
//    }
};
trietree:: trietree()
{
    root = new Node; //for constructor build a new root node which is empty
    root->ch = '\0'; //root contain empty data
    root->next[97] ;
    
}

 void trietree:: insert(string word,string meaning) //insertion
{
    current = root;
    for(int i = 0; i < word.length(); i++) //insert of word
    {
            if(word[i] > 96) //convert all the lowercase to upercase
            {
                word[i]-=32; //minus 32 as small to big letter differ by 32
            }
                char_index =word[i]; //char ascii of the words is pass to index
            if(current->next[char_index]==NULL) //if node -> next -> is NULL
            {
                current->next[char_index]=new Node;  //create a node which was created
                current->next[char_index]->ch =word[i];
                current->endline = false; // the node of array saved the ascii of the word char
            }
            current=current->next[char_index];//jump to next node
          
    }
          current->endline =true;// the end letter will return true
    for (int i = 0; i < meaning.length(); i++)
    {
         if(meaning[i] > 96)//convert all the lowercase to upercase
    {
        meaning[i]-=32; //minus 32 as small to big letter differ by 32
    }
      char_index =meaning[i];//char ascii of the words is pass to index
     if(current->next[char_index]==NULL) //if node -> next -> is NULL
     {
         current->next[char_index]=new Node;  //create a new node
         current->next[char_index]->ch =meaning[i];
         current->endline = false;// the node of array saved the ascii of the word char
     }
     current=current->next[char_index];//jump to  node which was created
    }
   
     current->endline = true; // the end letter will return true 
}
bool trietree::Search(string word)
{
    current = root ;//search starts from the root
    for(int i = 0 ; i <word.length();i++) // lower to upercase
    {
          if(word[i] > 96)
            {
                word[i]-=32;
            }
        char_index = word[i];
    if(current->next[char_index] == NULL) //if node->array(ascii) == NULL 
         {
         return false; 
         break; //stop the triversal
         }
    if(current->next[char_index]->ch == word[i])//if the node contain char at array(ascii of char ) == char to the word
        {
            current = current->next[char_index]; //jump to next node
        }
    }
    
    return current->endline; //if true the word  is formed as the last char is true
}
void trietree::Loading()
{
    ifstream in ; //read from the file
    string s1,s2; 
     in.open("Dictionary.txt");//open the file
     cout<<"\n\t\t\t\t“Dictionary is loading” "<<endl; 
     while(in.eof()==0) // read until the end of the line 
     { 
           in >> s1 ;
           in >> s2 ;
           insert(s1,s2); //insert those words to the trie tree
     }
     in.close();
   
}
void trietree::AddWord()
{
    string wordl , meaningl;
     cout<<"enter the word u want to add"<<endl;
     cin.ignore();
     getline(cin,wordl);
      if(!Search(wordl))//if the searching is true
    {
       cout <<"the word does not found "<<endl;
        cout<<"enter its meaning"<<endl;
       getline(cin,meaningl);
        ofstream out("Dictionary.txt", ios::app); //write the word and meaning
        out << wordl <<"\t" <<meaningl<<endl; //write the words in the dictionary
        out.close ();
         insert(wordl,meaningl);
         cout <<"word=>>"<<wordl <<"\t meaning==>>"<<meaningl<<endl<<endl;
    }
    else
    {   
     cout <<"“Word already exist”\n"<<endl;
    }   
    if(Search(wordl))
    {
        cout<<"word now exist in the library \n"<<endl;
    }
    else
    {
        cout<<"error the word was not inserted\n"<<endl;
    }
}
bool trietree::deletion(string word) //same as the search function for understanding go to search function
{
    
    current = root ;
    for(int i = 0 ; i <word.length();i++)
    {
          if(word[i] > 96)
            {
                word[i]-=32;
            }
        char_index = word[i];
    if(current->next[char_index] == NULL)
         {
         return false;
         break;
         }

    if(current->next[char_index]->ch == word[i])
        {
            current = current->next[char_index];
        }
    }  
    return current->endline=false;  // the differ from search function as the last word will become false and the word will no longer in the trie tree
}
void trietree::update_word(string word)
{
    if(Search(word)) //if the word is found 
    {
        string meaning;
        deletion(word); //deletion the word for updating
        cout<<"enter its meaning"<<endl;
        getline(cin,meaning); // the new word u want to update and its meaning is taken by user
         ofstream out("Dictionary.txt", ios::app);
        out << word <<"\t" <<meaning<<endl;
        out.close ();
         insert(word,meaning); //insert the updating words in the  trie tree
         cout <<"word=>>"<<word <<"\t meaning==>>"<<meaning<<endl<<endl;
    }
    else
    {
        cout<<"word is not found"<<endl;
    }

}
int main()
{
    trietree t1;
     string word;
    cout <<"loading .."<<endl;
    sleep(1);
    cout <<"loading ..."<<endl;
    sleep(1);
    cout <<"loading ...."<<endl;
    sleep(2);
    t1.Loading();
   
    int options;
    char op;
    do
    {
        cout <<"\t\t\tSEARCH PAGE "<<endl;
        cout <<"\tEnter 1 : for searching a word"<<endl;
        cout <<"\tEnter 2 : for adding  a word in the dictionary"<<endl;
        cout <<"\tEnter 3 : for deletion "<<endl;
        cout <<"\tEnter 4 : for updating  a word"<<endl;
        cout <<"\tEnter 5 : to exit"<<endl;
        cout <<"Enter ur choice == ";
        cin>>options;
        switch (options)
        {
        case 1:
        {
            string word;
            cin.ignore();
            cout<<"enter the word u want to Search = ";
            getline(cin,word);
            if(t1.Search(word))
            {
                // meaning;
                cout<<"the word found"<<endl;
            }
            else
            {
                cout<<"“Word not found”"<<endl;
            }
        }
            break;
        case 2:
        {
            t1.AddWord();
        }
        break;
        case 3:
        {
            cin.ignore();
            cout<<"enter the word u want to delete"<<endl;
            getline(cin,word);
            char input;
            cout <<"“Do you want to delete word”(y/n)"<<endl;
            cout <<"For YES enter (y)\t"<<"For NO enter(n)"<<endl;
            cin>>input;
            switch (input)
            {
                case 'y':
                    {  
                        t1.deletion(word);
                    }
                    break;
                
                case 'n':
                    break;
                default:
                    {
                        cout<<"Invalid output"<<endl;
                    }
                    break;     
            }
            break;
        }
        case 4:
        {
            cin.ignore();
            cout<<"word u want to update in the tree"<<endl;
            getline (cin,word);
            t1.update_word(word);
        }
        case 5 :
        cout<<"program shutdown"<<endl;
        break;
        default:
        cout<<"Invalid Output"<<endl;
            break;
        }
        cout <<"if want to close the dictionary program \t=>=>=>"<<"Press n"<<endl;
        cout <<"to check for another word \t\t\t=>=>=>"<<"Press y"<<endl;
        cout<<"enter the option (y/n) == ";
        cin>>op;
        if(op=='n')
        {
            cout<<"terminate program"<<endl;
            break;
        }
        if(op=='y')
        {
            continue;
        }
    } while (options==5 or op =='y');
    return 0;
}