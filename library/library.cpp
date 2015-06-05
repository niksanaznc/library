#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <conio.h>

using namespace std;

bool logged = false;
bool admin = false;

void book_read(string book)
{
	string line;
	ifstream file(book);
	if(file)
		{
			while(getline(file , line))
				{
					cout<<line<<endl;
				}
			file.close();
		}
}

void write_info(string filename , string bookname)
{
	char sentence[1000];
	ofstream book(filename);
	
	cout<<"Author : ";
	book<<"Author : ";
	cin.getline(sentence , 1000);
	book<<sentence<<endl;
	
	book<<"Title : ";
	book<<bookname<<endl;

	cout<<"Genre : ";
	book<<"Genre : ";
	cin.getline(sentence , 1000);
	book<<sentence<<endl;

	cout<<"Short description : ";
	book<<"Short description : ";
	cin.getline(sentence , 1000);
	book<<sentence<<endl;

	cout<<"Year : ";
	book<<"Year : ";
	cin.getline(sentence , 1000);
	book<<sentence<<endl;

	cout<<"Keywords : ";
	book<<"Keywords : ";
	cin.getline(sentence , 1000);
	book<<sentence<<endl;

	cout<<"Rating : ";
	book<<"Rating : ";
	cin.getline(sentence , 1000);
	book<<sentence<<endl;

	cout<<"Number : ";
	book<<"Number : ";
	cin.getline(sentence , 1000);
	book<<sentence<<endl;

	book.close();
}

void books_add()
{
	char title[100];
	string dir = "D:/lib/books/" , end = ".txt";
	cout<<"Enter book title : ";
	cin.ignore();
	cin.getline(title , 100);
	string filename = dir + title + end;
	string bookname = title;
	write_info(filename , bookname);
}

int remove(const char* filename);

void books_remove()
{
	char title[100];
	cout<<"Which book would you like to remove? ";
	cin.ignore();
	cin.getline(title , 100);
	string del = title;
	string dir = "D:/lib/books/" + del + ".txt";
	if(remove(dir.c_str()) == 0)
		cout<<"Book successfully removed!"<<endl;
	else
		cout<<"Such book does not exist!"<<endl;
}

void books_all()
{
	string line , dir = "D:/lib/books/" , searchPattern = "*.txt";
	string fullSearchPath = dir + searchPattern;

	WIN32_FIND_DATA FindData;
	HANDLE hFind;

	hFind = FindFirstFile(fullSearchPath.c_str() , &FindData);

	if(hFind == INVALID_HANDLE_VALUE)
		{
			cout<<"Error!"<<endl;
		}
	cout<<endl;
	do
		{
			string filePath = dir + FindData.cFileName;
			ifstream in(filePath.c_str());
			if(in)
				{
					int count = 1;
					while(getline(in , line))
						{
							if(count == 1 || count == 2 || count == 3 || count == 8)
								{
									cout<<line<<endl;
								}
							count++;
						}
					cout<<endl;
				}
		}
	while(FindNextFile(hFind , &FindData) > 0);
}

void books_info()
{
	string num , line , fullCrit;
	cout<<"Enter desired book personal number : ";
	cin>>num;
	fullCrit = "Number : " + num;

	string dir = "D:/lib/books/" , searchPattern = "*.txt";
	string fullSearchPath = dir + searchPattern;

	WIN32_FIND_DATA FindData;
	HANDLE hFind;

	hFind = FindFirstFile( fullSearchPath.c_str(), &FindData);

	if(hFind == INVALID_HANDLE_VALUE)
	{
		cout<<"Error"<<endl;
	}
	do
	{
		string filePath = dir + FindData.cFileName;
		ifstream in (filePath.c_str());
		if( in )
		{

			while(getline(in , line))
			{
				if(line.find(fullCrit) != string::npos)
				{
					book_read(filePath.c_str());	
					cout<<endl;
				}

			}
		}
	}
	while(FindNextFile(hFind , &FindData) > 0);
	
}

void books_find()
{
	string line , crit , crit2 , fullCrit;
	char name[100];
	cout<<"Search by author , title or tag : ";
	cin>>crit2;
	cout<<"Enter search criteria : ";
	cin.ignore();
	cin.getline(name , 100);
	crit = name;
	cout<<endl;
	if(crit2 == "Author" || crit2 == "author")
		fullCrit = "Author : " + crit;
	else if(crit2 == "Title" || crit2 == "title")
		fullCrit = "Title : " + crit;

	string dir = "D:/lib/books/" , searchPattern = "*.txt";
	string fullSearchPath = dir + searchPattern;
	
	WIN32_FIND_DATA FindData;
	HANDLE hFind;

	hFind = FindFirstFile( fullSearchPath.c_str(), &FindData);

	if(hFind == INVALID_HANDLE_VALUE)
	{
		cout<<"Error"<<endl;
	}

	do
	{
		string filePath = dir + FindData.cFileName;
		ifstream in (filePath.c_str());
		if( in )
		{
			int count = 1;
			while(getline(in , line))
			{
				if(crit2 == "Tag" || crit2 == "tag")
				{
					if(line.find(crit) != string::npos && count == 6)
					{
						book_read(filePath.c_str());	
						cout<<endl;
					}
				}
				else 
				{
					if(line.find(fullCrit) != string::npos)
					{
						book_read(filePath.c_str());	
						cout<<endl;
					}
				}
				count++;
			}
		}
	}
	while(FindNextFile(hFind , &FindData) > 0);

}

void books_sort()
{
	string line , crit , fullCrit;
	cout<<"Sort by year or rating : ";
	cin>>crit;
	cout<<endl;
	string dir = "D:/lib/books/" , searchPattern = "*.txt";
	string fullSearchPath = dir + searchPattern;

	if(crit == "year" || crit == "Year")
		{
			for(int i = 2015 ; i > 201 ; i--)
				{
					string str;
					ostringstream convert;
					convert << i;
					str = convert.str();

					fullCrit = "Year : " + str;
					WIN32_FIND_DATA FindData;
					HANDLE hFind;

					hFind = FindFirstFile( fullSearchPath.c_str(), &FindData);

					if(hFind == INVALID_HANDLE_VALUE)
						{
							cout<<"Error"<<endl;
						}

					do
						{
							string filePath = dir + FindData.cFileName;
							ifstream in (filePath.c_str());
							if( in )
								{

									while(getline(in , line))
										{
											if(line.find(fullCrit) != string::npos)
												{
													book_read(filePath.c_str());	
													cout<<endl;
												}

										}
								}
						}
					while(FindNextFile(hFind , &FindData) > 0);
					
				}
		}
	else if(crit == "Rating" || crit == "rating")
	{
		for(double i = 6 ; i > 0 ; i--)
		{
			string str;          
			ostringstream convert;   
			convert << i;      
			str = convert.str(); 

	
			fullCrit = "Rating : " + str;
			WIN32_FIND_DATA FindData;
			HANDLE hFind;

			hFind = FindFirstFile( fullSearchPath.c_str(), &FindData);

			if(hFind == INVALID_HANDLE_VALUE)
				{
					cout<<"Error"<<endl;
				}

			do
				{
					string filePath = dir + FindData.cFileName;
					ifstream in (filePath.c_str());
					if( in )
						{

							while(getline(in , line))
								{
									if(line.find(fullCrit) != string::npos)
										{
											book_read(filePath.c_str());	
											cout<<endl;
										}

								}
						}
				}
			while(FindNextFile(hFind , &FindData) > 0);
		}
		}
}

void users_create()
{
	bool exist = true;
	string name; 
	string dir = "D:/lib/users/" , end=".txt";
	while(exist)
		{
			cout<<"Enter username : ";
			cin>>name;
			string username = dir + name + end;
			ifstream in (username.c_str());
			if( in )
				{
					cout<<"username already exist!"<<endl;
					name.clear();
					in.close();
				}
			else
				exist = false;
		}
	string username = dir + name + end;
	string pass;
	ofstream user(username);
	cout<<"Enter password : ";
   char c;
   c = _getch();
   while(c != 13)
	 {
		  if(c != '\b')
			 {
				 pass.push_back(c);
				 cout << '*';
				 c = _getch();
			 }
		 else
			{
				 cout<<endl;
				 cout<<"Enter password : ";
				 c = _getch();
				 pass.clear();
		    }
	   
	 }
    cout<<endl;
	user<<pass;
	user<<endl;
	user.close();
}

void login()
{
	if(logged)
		{
			cout<<"You are already logged in!"<<endl;
		}
	else
	{
		string line , user , pass;
		cout<<"Enter username : ";
		cin>>user;
		cout<<"Enter password : ";
		char c;
	    c = _getch();
	    while(c != 13)
		 {
		  if(c != '\b')
			 {
				 pass.push_back(c);
				 cout << '*';
				 c = _getch();
		     }
		 else
			 {
				 cout<<endl;
				 cout<<"Enter password : ";
				 c = _getch();
				 pass.clear();
			 }	
	   
		 }
		cout<<endl;
		string path = "D:/lib/users/";
		string end = ".txt";
		string fullPath = path + user + end;
		ifstream in (fullPath.c_str());
			if( in )
				{
					while(getline(in , line))
						{
							if(line.find(pass) != string::npos)
								{
									cout<<"Welcome "<<user<<" !"<<endl;
									logged = true;
									if(user == "admin")
										admin = true;
									else
										admin = false;
								}	
							else
								cout<<"Wrong username or password!"<<endl;
						}
				}
			else
				cout<<"Wrong username or password!"<<endl;
	}
	
}

void logout()
{
	logged = false;
}

void users_remove()
{
	char user[100];
	cout<<"Which user would you like to remove? ";
	cin.ignore();
	cin.getline(user , 100);
	string del = user;
	if(del == "admin")
		cout<<"User admin cannot be deleted!"<<endl;
	else
		{
			string dir = "D:/lib/users/" + del + ".txt";
			if(remove(dir.c_str()) == 0)
				cout<<"User successfully removed!"<<endl;
			else
				cout<<"Such user does not exist!"<<endl;
		}
}

void help()
{
	cout<<"Press 1 for help."<<endl;
	cout<<"Press 2 to log in."<<endl;
	cout<<"Press 3 to exit."<<endl;
}

int main()
{
	int k;
	cout<<"Welcome to the library!"<<endl;
	do
	{
	if(logged && admin)
		{
			cout<<"Press 1 to create users."<<endl;
			cout<<"Press 2 to remove users."<<endl;
			cout<<"Press 3 to create books."<<endl;
			cout<<"Press 4 to remove books."<<endl;
			cout<<"Press 5 for exit."<<endl;
			do
				{
					cout<<"Enter command : "<<endl;
					cin>>k;
					switch(k)
						{
							case 1 : users_create(); break;
							case 2 : users_remove(); break;
							case 3 : books_add(); break;
							case 4 : books_remove(); break;
							case 5 : return 0;
						}
				}
			while(cin);
		}
	else if(logged)
		{
			cout<<"Press 1 to view all books."<<endl;
			cout<<"Press 2 to find books."<<endl;
			cout<<"Press 3 to view the books sorted."<<endl;
			cout<<"Press 4 to view a book."<<endl;
			cout<<"Press 5 to create books."<<endl;
			cout<<"Press 6 to remove books."<<endl;
			cout<<"Press 7 to create users."<<endl;
			cout<<"Press 8 to remove users."<<endl;
			cout<<"Press 9 to log out."<<endl;
			do
				{
					cout<<"Enter command : "<<endl;
					cin>>k;
					switch(k)
						{
							case 1 : books_all(); break;
							case 2 : books_find(); break;
							case 3 : books_sort(); break;
							case 4 : books_info(); break;
							case 5 : books_add(); break;
							case 6 : books_remove(); break;
							case 7 : users_create(); break;
							case 8 : users_remove(); break;
							case 9 : logout(); break;
						}
				}
			while(logged && cin);
		}
	else
		{
			cout<<"Press 1 for help."<<endl;
			cout<<"Press 2 to log in."<<endl;
			cout<<"Press 3 to exit."<<endl;
			do
				{
					cout<<"Enter command : "<<endl;
					cin>>k;
					switch(k)
						{
							case 1 : help(); break;
							case 2 : login(); break;
							case 3 : return 0;
						}
				}
			while(!logged && cin);
		}
	}
	while(cin);
	return 0;
}

