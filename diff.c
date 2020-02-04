#include<bits/stdc++.h>
using namespace std;
int main(){
    int i;
  for (i=1;;i++){
        system("sleep 1 ");
	printf("The result of No. %d Case is:  ",i);
        system("./data");
        system("./std");
        system("./test");
        if (system("diff std.out test.out")){
            printf("Wrong Answer\n");
            return 0;
        }
        else printf("Accepted\n");
    }
    return 0;
}

