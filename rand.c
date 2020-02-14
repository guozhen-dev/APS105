#include <cstdio>
#include<cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
int main(int argc, char *argv[]){
		srand(time(0));
		cout<<(rand()%40000)/1000.0 <<' ';
		cout<<(rand()%40000)/1000.0 <<' ';
		cout<<(rand()%40000)/1000.0 <<' ';
		cout<<(rand()%40000)/1000.0 <<' ';
}	
		 
