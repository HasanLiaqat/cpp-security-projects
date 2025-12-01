#include<iostream>
#include<ctime>
#include<fstream>
#include<string>

int mod ( int a, int b)
{
	while ( a>=b )
	{
		a = a - b;
	}
	
	return a;
}

int range ( int r )
{
	while ( r<2 || r>49 )
	{
		if ( r<2 )
		r = r + 50;
		
		else if ( r>49 )
		r = r - 50;
	}
	
	return r;
}

bool isprime ( int n )
{
	if ( n<=1 )
	return false;
	
	for ( int i=2; i<=n/2; i++)
	{
		if ( mod (n, i) == 0 )
		return false;
	}
	
	return true;
}

int range2 ( int r )
{
	while ( r<0 || r>50 )
	{
		if ( r<0 )
		r = r + 51;
		
		else if ( r>50 )
		r = r - 51;
	}
	
	return r;
}

int modpower ( int base, int exp, int p )
{
	int z = 1;
	
	for ( int i=0; i<exp; i++)
	{
		z = mod ( z*base, p );
	}
	
	return z;
}

char encrypt ( char c, int key )
{
	return c ^ key;
}

char decrypt ( char c, int key )
{
	return c ^ key;
}

using namespace std;
int main()
{
	srand ( time(NULL) );
	int prime;
	
	while (true)
	{
		int r = rand();
		int num = range(r); 
		
		if ( num<=2 )			// WE BASICALLLY SKIP 2 BECAUSE G CAN'T BE GENERATED THEN
		continue;
		
		if ( isprime (num) )
		{
			prime = num;
			break;
		}
	}
	
	cout<<"\nDynamically generated prime number ( < 50 ) is: "<<prime<<endl;
	
	int G;
	
	for ( int i=2; i<prime; i++)
	{
		bool visit[50] = {false};		// ALL INDEXES ARE AT FALSE NOW
		bool isRoot = true;
		
		int value=1;
		
		for ( int j=1; j<=prime-1; j++ )
		{
			value = value * i;
			value = mod ( value, prime );
			
			if ( visit[value] )		// CHECKING IF NUMBER REPEATS, THEN ITS NOT PRIMITIVE ROOT
			{
				isRoot = false;
				break;
			}
			
			visit[value] = true;
		}
		
		if (isRoot)
		{
			G = i;
			break;
		}

	}
	
	cout<<"Primitive Root G is "<<G<<endl;	
	
	srand ( time(NULL) );
	
	int a = range2 ( rand() );			// KEY IS IN BTW 0-50 AS PRIME NUMBERS ARE BELOW 50
	int b = range2 ( rand() ); 			// MORE LARGER KEYS WOULD REDUCE EFFICIENCY OF PROGRAM
	
	cout<<endl;
	cout<<"Sender Private Key ( 0-50 ): "<<a<<endl;
	cout<<"Reciever Private Key ( 0-50 ): "<<b<<endl;
	
	int A = modpower ( G, a, prime );
	int B = modpower ( G, b, prime );		// PUBLIC KEY = G^a % prime
	
	cout<<endl;
	cout<<"Sender Public Key: "<<A<<endl;
	cout<<"Reciever Public Key: "<<B<<endl;
	
	int SK1 = modpower ( B, a, prime );
	int SK2 = modpower ( A, b, prime );		// SHARED KEY FORMULA AND IT IS SAME FOR BOTH PARTIES
	
	cout<<endl;
	cout<<"Sender Shared Key: "<<SK1<<endl;
	cout<<"Reciever Shared Key: "<<SK2<<endl;
	
	int key = SK1;					// WE CAN ALSO WRITE SK2 AS BOTH ARE SAME
	
	char ch;
	string text;
	
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
