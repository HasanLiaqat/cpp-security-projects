#include<iostream>
#include<fstream>
#include<string>
#include<ctime>

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

int gcd ( int a, int b )
{
	while ( b != 0 )
	{
		int temp = b;
		b = mod ( a, b);
		a = temp;	
	}
	
	return a;
}

using namespace std;
int main()
{
	srand ( time(NULL) );
	int p;
	int q;
	
	while (true)
	{
		int r = rand();
		int num = range(r); 
		
		if ( isprime (num) )
		{
			p = num;
			break;
		}
	}
	
	while (true)
    	{
		int r = rand();
		int num = range(r);
		
		if ( isprime(num) && num != p )  	// BOTH PRIME ARE NOT EQUAL
		{
		    q = num;
		    break;
		}
    	}
	
	cout<<"\nDynamically generated p is: "<<p;
	cout<<"\nDynamically generated q is: "<<q<<endl;
	
	int n;
	n = p * q;
	
	cout<<"\nValue of n is: "<<n;
	
	int fi;
	fi = ( p-1 ) * ( q-1 );
	
	cout<<"\nValue of fi is: "<<fi;
	
	int e = 2;				// BCZ e IS ALWAYS GREATER THAN 1
	
	while ( e < fi )
	{
		if ( gcd ( e, fi ) == 1 )
		break;
		
		e++;
	}
	
	cout<<"\nSelected e is: "<<e<<endl;
	
	int d=1;				// HERE ( d * e ) mod fi == 1
	
	while ( true )
	{
		if ( mod ( d * e, fi) == 1 )
		break;
		
		d++;
	}
	
	cout<<"Selected d is: "<<d<<endl;
	
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
	
	while (fin.get(ch))
	{
	    int m = (int)ch;   

	    int z = 1;
	    for (int i = 1; i <= e; i++)
	    {
		z = mod(z * m, n);
	    }
	    	
	    foutE<<z;  
	}
	
	fin.close();
	foutE.close();
	
	cout<<"Encrypted Successfully"<<endl;
	

	
	
	return 0;
} 
