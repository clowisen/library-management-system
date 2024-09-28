#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

class Library{
    public:
    void addBook(string name, int pages, string price);
    void removeBook();
    void getAllBook();
    void searchBook();
};


void Library::addBook(string name, int pages, string price){
    ofstream write("books.dat", ios::app);
    write << name << endl;
    write << pages << endl;
    write << price << endl;
    write.close();
    cout << "Book added." << endl;
}

void Library::removeBook(){
    string name;

    cin.ignore();

    tryagain:
    cout << "Enter the book name: ";
    getline(cin, name);

    ifstream read("books.dat");
    string data;

    vector<string>lines;
    vector<string>newlines;


    int checker = 0;
    bool exist = false;
    bool checkExist = false;

    while(getline(read,data)){
        lines.push_back(data);
    }

    read.close(); 

    for (int i = 0; i < lines.size(); i++)
    {
        if (checker == 0)
        {
            if(name != lines[i]){
                newlines.push_back(lines[i]);
                exist = true;
            }
            else{
                checkExist = true;
            }
            checker++;
        }
        else if(checker == 1){
            if(exist == true){
                newlines.push_back(lines[i]);
            }
            checker++;
        }
        else if(checker == 2){
            if(exist == true){
                newlines.push_back(lines[i]);
                exist = false;
            }
            checker = 0;
        }
    }

    if(checkExist == true){
        ofstream write("books.dat");
        if(write.is_open()){
            for (int k = 0; k < newlines.size(); k++)
            {
                write << newlines[k] << endl;
            }
        }
        cout << "Book deleted." << endl;
        write.close();
    }
    else{
        cout << "Book not exist." << endl;
        goto tryagain;
    }

    
}

void Library::getAllBook(){

    ifstream read("books.dat");
    string data;

    int checker = 0;

    while (getline(read, data))
    {
        if (checker == 0)
        {
            cout << "--------------------------" << endl;
            cout << "Book name: " << data << endl;
            checker++;
        }
        else if(checker == 1){
            cout << "Pages: " << data << endl;
            checker++;
        }
        else if(checker == 2){
            cout << "Price: " << data << endl;
            cout << "--------------------------" << endl;
            checker = 0;
        }
        
    }

    read.close(); 
}

void Library::searchBook(){

    string name;

    cin.ignore();

    tryagain:
    cout << "Enter the book name: ";
    getline(cin, name);

    ifstream read("books.dat");
    string data;

    int checker = 0;
    bool exist = false;

    while (getline(read, data))
    {
        if (checker == 0)
        {
            if(name == data){
                cout << "--------------------------" << endl;
                cout << "Book name: " << data << endl;
                exist = true;
            }
            checker++;
        }
        else if(checker == 1){
            if(exist == true){
                cout << "Pages: " << data << endl;
            }
            checker++;
        }
        else if(checker == 2){
            if(exist == true){
                cout << "Price: " << data << endl;
                cout << "--------------------------" << endl;
                break;
            }
            checker = 0;
        }
        
    }

    if(exist == false){
        cout << "Book not exist." << endl;
        goto tryagain;
    }

    read.close(); 
}

int main(){

    Library lib;
    int choice;
    main:
    cout << "Welcome to Library Management System" << endl;
    cout << "1) Add Book" << endl;
    cout << "2) Remove Book" << endl;
    cout << "3) Get All Books" << endl;
    cout << "4) Search Book" << endl;
    cout << "5) Quit" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if(choice == 1){
        string name, price;
        int pages;
        cin.ignore();
        cout << "Book Name: ";
        getline(cin, name);
        cout << "Pages: ";
        cin >> pages;
        cin.ignore();
        cout << "Price: ";
        getline(cin, price);
        lib.addBook(name, pages, price);
        goto main;
    }

    else if(choice == 2){
        lib.removeBook();
        goto main;
    }

    else if(choice == 3){
        lib.getAllBook();
        goto main;
    }

    else if(choice == 4){
        lib.searchBook();
        goto main;
    }
    else if(choice == 5){
        cout << "Exiting..." << endl;
        system("pause");
    }
}