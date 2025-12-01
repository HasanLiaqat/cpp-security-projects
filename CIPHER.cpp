#include<iostream>
#include<fstream>
#include<string>
#include<ctime>

using namespace std;

char encrypt(char ch, int key)
{
	if ( ch >= 'A' && ch<= 'Z' )
	{
		ch = ch + key;
		if ( ch > 'Z' )
		{
			ch = ch - 'Z' + 'A' - 1;		
		}	
	}
	
	else if ( ch >= 'a' && ch<= 'z' )
	{
		ch = ch + key;
		if ( ch > 'z' )
		{
			ch = ch - 'z' + 'a' - 1;		
		}	
	}
	
	return ch;
}	
	
char decrypt(char ch, int key)
{
	if ( ch >= 'A' && ch<= 'Z' )
	{
		ch = ch - key;
		if ( ch < 'A' )
		{
			ch = ch + 'Z' - 'A' + 1;		
		}	
	}
	
	else if ( ch >= 'a' && ch<= 'z' )
	{
		ch = ch - key;
		if ( ch < 'a' )
		{
			ch = ch + 'z' - 'a' + 1;		
		}	
	}
	
	return ch;	
	
}
int main()
{
	int key;
	char ch;
	string text;
	
	srand ( time (NULL) );
	
	key = rand();
	
	while ( key > 25 )
	{
		key = key - 26;
	}
	
	cout<<"Dynamically generated key is: "<<key<<endl;
	
	ofstream fout ("input.txt");
	
	cout<<"\nEnter the text to be encrypted ( Press Enter when done ): ";
	getline(cin, text);
	
	fout<<text;
	fout.close();
	
	ifstream fin ("input.txt");
	ofstream foutE ("encrypt.txt"); 
	
	if (!fin || !foutE)
	{
		cout<<"Error in opening files."<<endl;
		return 0;
	}
	
	while ( fin.get(ch) )
	{
		foutE<<encrypt(ch, key);
	}
	
	fin.close();
	foutE.close();
	
	cout<<"Encrypted Successfully"<<endl;
	
	ifstream finD ("encrypt.txt");
	ofstream foutD ("decrypt.txt");
	
	while ( finD.get(ch) )
	{
		foutD<<decrypt(ch, key);
	}
	
	finD.close();
	foutD.close();
	
	cout<<"Decrypted Successfully"<<endl;
	
	return 0;
	
}
