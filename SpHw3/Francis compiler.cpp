#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define TABLE_NUM 4
#define TABLE_SIZE 100  

using namespace std;    

fstream outfile ;

struct identiferType {
	string identifier ;
	int subroutine ;
	int type ;
	int pointer ;
};

string table[TABLE_NUM][TABLE_SIZE] ; 

void int2str( int i, string &str) {
	stringstream ss ;
	ss << i ;
	str = ss.str();
}   

void readTable( int total ) {
	fstream file ;
	int i = 1, j = 0;
	while ( i <= total ) {
		string input ;
		string num ;
		int2str( i, num ) ;
		string tableName = "Table" + num + ".table" ;
		//cout << tableName << "\n" ;
		file.open( tableName.c_str(), ios::in);
		while ( !file.eof()) {
			getline(file,input,' ');
			getline(file,input,'\n');
			table[i-1][j] = input ;
			//cout << table[i-1][j] << "\n" ;
			j++ ;
		}
		j = 0 ;
		i++ ;
		file.close() ;
	}
}

void hash( string insert, int i ){
	int total = 0;
	int hvalue = 0 ;
	char ascii[100]  ;
	
	for ( int j = 0 ; j < sizeof(insert) ; j++ ){
	
		strcpy ( ascii,insert.c_str() ) ;
		total = ascii[j] + total ;
	}

	hvalue = total%100 ;
	
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
	outfile << "(" << i+1 << "," << hvalue << ")" ; 
	//cout << "(" << i+1 << " , " << hvalue << " )" ;

}

void splitStr2Vec(string s, vector<string>& buf){
	string token ;
	for ( int i = 0 ; i < s.size() ; i++ ){

		if ( s[i] == ' ' || s[i] == '\t' ){
			if ( !token.empty() ) {
				buf.push_back(token);
				token = "";
			}
		}
		else if ( s[i] == '[' || s[i] == ']' || s[i] == ',' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == ':' || s[i] == ';' || s[i] == '?' || s[i] == '(' || s[i] == ')' || s[i] == '↑' || s[i] == '=' ) {
			if ( !token.empty() ) buf.push_back(token);
			//cout << s[i] << "\n" ;
			token = s[i] ;
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

void findTable( vector<string>token ) {
	int intable = 0 ;
	string TOP ;
	
	for( int i = 0 ; i < token.size() ; i++ ){			
		for( int j = 0 ; j < TABLE_NUM ; j++ ){			
			for( int k = 0 ; k < TABLE_SIZE ; k++ ){
				TOP = token[i] ;
				transform(TOP.begin(), TOP.end(), TOP.begin(), ::toupper ) ;					
				if ( strcmp( TOP.c_str(), table[j][k].c_str() ) == 0 ){		
					outfile << "(" << j+1 << "," << k+1 << ")"; 
					//cout << "( " << j+1 << ", " << k+1 << " )";
					intable = 1 ;
				}
			}		
		}
			
		if ( intable == 0 ) { 
			
			if ( token[i].at(0) == 48 || token[i].at(0) == 49 || token[i].at(0) == 50 || token[i].at(0) == 51 || token[i].at(0) == 52 || token[i].at(0) == 53 || 
					token[i].at(0) == 54 || token[i].at(0) == 55 || token[i].at(0) == 56 || token[i].at(0) == 57 ) {		
				for ( int j = 0 ; j < token[i].size() ; j++ ) {
					if ( token[i].at(j) == 46 ) {
						hash( token[i], 3) ;
						break ;
					}
					else if ( j == token[i].size()-1 ) {
						hash( token[i], 2) ;
					}
				}
			}
			else { 		
				hash( token[i], 4 ) ;	
			}
				
		}
		intable = 0 ;
	}
	outfile << "\n" ;
	//cout << "\n" ;
		
} 

bool checkId ( string str ) {
	for( int j = 0 ; j < 2 ; j++ ){			
		for( int k = 0 ; k < TABLE_SIZE ; k++ ){
			TOP = str ;
			transform(TOP.begin(), TOP.end(), TOP.begin(), ::toupper ) ;					
			if ( strcmp( TOP.c_str(), table[j][k].c_str() ) == 0 ){		
				return false ;
			}
		}
	}
	if ( str.at(0) == '0' || str.at(0) == '1' || str.at(0) == '2' || str.at(0) == '3' || str.at(0) == '4' || str.at(0) == '5' || str.at(0) == '6' || str.at(0) == '7' || str.at(0) == '8' || str.at(0) == '9' )	return false ;
	return true ;	
}

void syntaxAnalysis( vector<string>token ) {
	int i = 0 ;
	if ( token[i] == "PROGRAM" ) {
		
		if ( checkId( token[i+1] ) ) {
			if ( )
		}
		else {
			cout << "Syntax Error" ;
			return 0 ;
		}
	}
}

int main() {
	
	for( int i = 0 ; i < TABLE_NUM ; i++ ){
		for( int j = 0 ; j < TABLE_SIZE ; j++ ){
				table[i][j] = "empty" ;
				//cout << table[i][j] << "\n" ;
		}
	}  //初始化 

	readTable(2);

	string input;
	
	string fileName ;
	string inFileName ;
	string outFileName ;
	fstream file ;
	
	
	vector<string>token ;
	
	cout << "Input a file\n" ;
	cin >> fileName ;
	inFileName = fileName + ".txt" ;
	outFileName = fileName + "_output.txt" ;
	file.open( inFileName.c_str() ,ios::in );
	outfile.open(outFileName.c_str() ,ios::out);
	while ( !file.eof()) {
		getline(file,input,'\n');
		outfile << input << '\n' ; //寫檔 
		//cout << input << '\n' ; //試印 
		
		splitStr2Vec(input, token) ;
		
		/*for( int i = 0 ; i < token.size() ; i++ ){
			cout << token[i] << "\n" ;
		}  //切token試印 */
		
		
		/*
		findTable( token ) ;
		token.clear() ;
		*/
		syntaxAnalysis(token) ;
		
	}
	


	file.close();
	outfile.close();
	
	cout << "Success\n" ;
		
}
