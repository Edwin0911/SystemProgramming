#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;


string table[7][200] ;

fstream outfile ;


void hash( string insert, int i ){
	int total = 0;
	int hvalue = 0 ;
	char ascii[100]  ;
	
	for ( int j = 0 ; j < sizeof(insert) ; j++ ){
	
		strcpy ( ascii,insert.c_str() ) ;
		total = ascii[j] + total ;
	}

	hvalue = total%100 ;
	//cout << i << "\n" << hvalue << "\n" ;
	
	//cout << table[i][hvalue] << "\n" ;
	
	if ( strcmp( table[i][hvalue].c_str(),"empty" ) != 0  ) {

		table[i][hvalue] = insert ;
	}
	
	else {

		while ( strcmp( table[i][hvalue].c_str(),"empty" ) != 0  ) {

			hvalue++ ;
			if ( hvalue == 100 ) 
				hvalue = 0 ;
			if ( strcmp( table[i][hvalue].c_str(),"empty" ) == 0 )  {	
				table[i][hvalue] = insert ;
				break ;
			
			}
		} 

	}
	//outfile << "(" << i+1 << "," << hvalue << ")" ; 印座標 
	//cout << "(" << i+1 << " , " << hvalue << " )" ;

}

void splitStr2Vec(string s, vector<string>& buf)
{
	string token ;
	for ( int i = 0 ; i < s.size() ; i++ ){
		if ( s[0] == ';')
			i++ ;
		if ( s[i] == ' ' || s[i] == '\t' ){
			if ( !token.empty() ) {
				buf.push_back(token);
				token = "";
			}
		}
		else if ( s[i] == '[' || s[i] == ']' || s[i] == ',' || s[i] == '+'  || s[i] == '*' || s[i] == '/' || s[i] == ':' || s[i] == ';' || s[i] == '?' || s[i] == '(' || s[i] == ')' ) {
			if ( !token.empty() ) buf.push_back(token);
			//cout << s[i] << "\n" ;
			token = s[i] ;
			buf.push_back(token);
			token = "";
		}
		
		else if ( s[i] == '-'  ) {
			if ( !token.empty() ) buf.push_back(token);
			//cout << s[i] << "\n" ;
			token = "- " ;
			buf.push_back(token);
			token = "";
		}
		
		else if ( s[i] == '\''  ) {
			if ( !token.empty() ) buf.push_back(token);
			//cout << s[i] << "\n" ;
			token = s[i] ;
			buf.push_back(token);
			token = "";
			i++ ;
			while ( s[i] != '\'' ) {
				token = token.append( s, i, 1 ) ;
				i++ ;
			}
			buf.push_back(token);
			
			token = "\'" ;
			buf.push_back(token);
			i++ ;
			token = "";
		}
		
		else if ( i == s.size()-1 ) {
			token = token.append( s, i, 1 ) ;
			buf.push_back(token);
		}
		else {
			token = token.append( s, i, 1 ) ;
		}
	}
}

int main() {
	
	string input ;
	
	int intable = 0 ;
	
	for( int i = 0 ; i < 7 ; i++ ){
		for( int j = 0 ; j < 200 ; j++ ){
				table[i][j] = "empty" ;
				//cout << table[i][j] << "\n" ;
		}
	}  //初始化 

	int i = 0 ;

	fstream file1;
	file1.open("Table1.table",ios::in);
	while ( !file1.eof()) {
		getline(file1,input,' ');
		getline(file1,input,'\n');
		table[0][i] = input ;
		//cout << table[0][i] << "\n" ;
		i++ ;

	}
	file1.close();
	
	i = 0 ;
	fstream file2;
	file2.open("Table2.table",ios::in);
	while ( !file2.eof()) {
		getline(file2,input,' ');
		getline(file2,input,'\n');
		table[1][i] = input ;
		i++ ;
	}

	file2.close();
	
	i = 0 ;
	fstream file3;
	file3.open("Table3.table",ios::in);
	while ( !file3.eof()) {
		getline(file3,input,' ');
		getline(file3,input,'\n');
		table[2][i] = input ;
		i++ ;
	}

	file3.close();
	
	i = 0 ;
	fstream file4;
	file4.open("Table4.table",ios::in);
	while ( !file4.eof()) {
		getline(file4,input,' ');
		getline(file4,input,'\n');
		table[3][i] = input ;
		i++ ;
	}

	file4.close();

	/*for( int i = 0 ; i < 200 ; i++ ){		
		cout << table[3][i] << "\n" ;		
	}*/ 
	
	int hvalue = 0 ;
	int total = 0 ;
	char ascii[100]  ;
	string TOP ;
	
	int length = 0 ;
	string fileName ;
	string inFileName ;
	string outFileName ;
	fstream file;
	
	vector<string>token;
	
	int line = 5 ;
	cout << "Input a file\n" ;
	cin >> fileName ;
	inFileName = "x86" + fileName + ".txt" ;
	outFileName = "input" + fileName + "_output.txt" ;
	file.open( inFileName.c_str() ,ios::in );
	outfile.open(outFileName.c_str() ,ios::out);
	outfile << "Line\tLocation\tObject Code\t\tSource Statement\n" ;
	while ( !file.eof()) {
		getline(file,input,'\n');
		outfile << line << "\t" << input << "\n"  ; //寫檔 
		line = line+5 ;
		//cout << input << '\n' ; //試印 
		/* 
		//transform(input.begin(), input.end(), input.begin(), ::toupper ) ;
		splitStr2Vec(input, token) ;
		
		/*for( int i = 0 ; i < token.size() ; i++ ){
			cout << token[i] << "\n" ;
		}  //切token試印 
		
		
		
		for( int i = 0 ; i < token.size() ; i++ ){			
			for( int j = 0 ; j < 7 ; j++ ){			
				for( int k = 0 ; k < 100 ; k++ ){
					TOP = token[i] ;
					transform(TOP.begin(), TOP.end(), TOP.begin(), ::toupper ) ;					
					if ( strcmp( TOP.c_str(), table[j][k].c_str() ) == 0 ){		
						//outfile << "(" << j+1 << "," << k+1 << ")"; 印座標  
						//cout << "( " << j+1 << ", " << k+1 << " )";
						intable = 1 ;
					}
				}		
			}
			
			if ( intable == 0 ) { 
				if ( token[i+1] == "\'" && i+1 != token.size() ) {
				
					hash( token[i], 6 ) ;
					
				}
				else if ( token[i].at(0) == 48 || token[i].at(0) == 49 || token[i].at(0) == 50 || token[i].at(0) == 51 || token[i].at(0) == 52 || token[i].at(0) == 53 || 
				token[i].at(0) == 54 || token[i].at(0) == 55 || token[i].at(0) == 56 || token[i].at(0) == 57 ) {
					
						hash( token[i], 5) ;
						
				}
	
				else { 
					
					hash( token[i], 4 ) ;
					
				}
				
			}
			intable = 0 ;
		}
		outfile << "\n" ;
		//cout << "\n" ;
		
		
		token.clear() ;
		*/
		
	}
	


	file.close();
	outfile.close();
	
	cout << "Success!\n" ;
		
}
	         
