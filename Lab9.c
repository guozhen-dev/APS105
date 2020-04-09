#include "rawRecipes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// #define FILE 
struct recipe{
	char * name;
	char * ing[100];
	int ingcnt;
} rlist[30];
struct ingredient{
	char * name;
	char * rec[30];
	int reccnt;
} ilist[100];

struct ingredient * find (char * str){
	for (int i = 0 ; i < 100 ; i++){
		if (ilist[i].name == NULL) return NULL ; 
		if (ilist[i].name == str) return &ilist[i];
	}
}
struct ingredient * lookup (char str[]){
	for (int i = 0 ; i < 100 ; i++){
		if (ilist[i].name == NULL) return NULL ; 
		if(strcmp(str,ilist[i].name)==0) return &ilist[i];
	}
}
struct ingredient * ranked_ilist[100];
int cmp (const void * a, const void * b){
	char *x = (*(struct ingredient **)a)->name;
	char *y = (*(struct ingredient **)b)->name;
	return strcmp(x,y);
}
void rank(){
	int size = 0;
	while(ilist[size].name){
		ranked_ilist[size] = &ilist[size];
		size++;
	}
	printf("size = %d\n", size);
	qsort(ranked_ilist,size,sizeof(ranked_ilist[0]),cmp);
	for (int i = 0 ; i< size ; i++){
		printf("%d: %s\n",i,ranked_ilist[i]->name+1 );
	}
}
int main(int argc, char const *argv[]){
	#ifdef FILE
	freopen("in","r",stdin);
	#endif
	int p = -1,rindex=-1,iindex=-1;
	char * now_rec = NULL;
	while (rawRecipes[++p]){
		// printf("%s %p\n", rawRecipes[p], rawRecipes[p]);
		if (rawRecipes[p][0]=='0'){
			rlist[++rindex].name = rawRecipes[p];
			now_rec = rawRecipes[p];

		}else if(rawRecipes[p][0]=='1'){
			rlist[rindex].ing[rlist[rindex].ingcnt++] = rawRecipes[p];
			struct ingredient * location = find(rawRecipes[p]);
			if (!location){
				ilist[++iindex].name = rawRecipes[p];
				location = &ilist[iindex];
			}
			location -> rec[(location->reccnt)++] = now_rec;
		}
	}

	while (1){
	printf("\n\nEnter a command by letter\n1. List all Recipes\n2. Print a Recipe\n3. List All Recipes with a given ingredient\n4. List All Ingredients in alphabetical order\n5. Exit the program\nGive input:");
	int CH;
	scanf("%d",&CH);
	if (CH == 1){
		for (int i = 0 ; i < 24; i++){
			printf("Recipe #%d: %s\n", i+1, rlist[i].name+1 );
		}
	}else if (CH==2){
		printf("Give the number of the recipe (1-24):");
		int num;
		scanf ("%d",&num);
		num --;
		printf("%s\n",rlist[num].name+1);
		for (int t = 0 ; t < rlist[num].ingcnt; t++){
			printf("%s\n",rlist[num].ing[t]+1);
		}
	}else if (CH == 3){
		printf("Give the name of the ingredient:");
		char input[100]={'1',};
		getchar();
		gets(input+1);
		struct ingredient * location = lookup(input);
		// printf("%d\n", location->reccnt);
		for (int i=0 ; i < location->reccnt ; i++){
			// printf("%d\n",i );
			printf("%s\n", location->rec[i]+1 );
		}
	}else if (CH == 4){
		printf("ALL INGREDIENTS\n");
		rank();
	}else if (CH == 5){
		exit(0);
	}
}
	return 0;
}