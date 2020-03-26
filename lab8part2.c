#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lab8part2lib.h"
//#define DDEBUG
//#define FILE
//#define DEBUG

struct available_move{
	char *list;
	int size;
};
struct node{
	char x;
	char y;
	int value;
};
void prt_mapp(char mapp[][26], int n);
void init_move(char mapp[][26], int n);
void config_board(char mapp[][26], char che, char xx, char yy );
bool oper_board(char mapp[][26], int n , char che, int xx, int yy );
bool point_in_bound(int n , int r, int w );
int check_legal_direction(char mapp[][26], int n, int row, int col, char che, int d_row, int d_col);
bool check_vaild(char mapp[][26], int n, char che , char xx, char yy );
struct available_move generate_vaild(char mapp[][26], char che, int n );
void print_possible_move(char c, char * ans);
void flip(char mapp[][26], int n, int row, int col, char che, int d_row, int d_col);
int comp_oper_board(char mapp[][26],int n , char che,int depth);
int count_valid(char mapp[][26], char che, int n );
void final(char mapp[][26],int n );
struct node get_max(char mapp[][26],int n ,char che, struct available_move avail,int depth);
struct node get_min(char mapp[][26],int n , char che , struct available_move avail,int depth);
char opposite(char a ){
	return a=='B'?'W':'B';
}

char computer;
const int predict_depth = 4;
int main(int argc, char const *argv[]){
	#ifdef FILE 
	freopen("in","r",stdin);
	#endif
	bool is_computers_turn;
	char mapp[26][26],cc;
	memset(mapp,'U',sizeof(mapp));
	int N;
	printf("Enter the board dimension: \n");
	scanf("%d",&N);
	init_move(mapp,N);
	printf("Computer plays (B/W): \n");
	scanf(" %c",&cc);
	char hc = cc=='B'?'W':'B';
	computer = cc;
	prt_mapp(mapp,N);
	is_computers_turn= cc=='B'?1:0;
	while(true){
		char this_turn = is_computers_turn?cc:hc;
		char next_turn = is_computers_turn?hc:cc;
		if(!count_valid(mapp,this_turn,N) ){
			if (count_valid(mapp,next_turn,N)){
				printf("%c player has no valid move.\n",this_turn);
				is_computers_turn = !is_computers_turn;
				continue;
			}else {
				final(mapp,N);
				break;
			}
		}
		if(is_computers_turn){
			#ifdef DDEBUG
			printf("Computer chance\n");
			#endif
			comp_oper_board(mapp,N,cc,predict_depth);
		}else {
			int xx=0, yy=0;
			printf("Enter move for colour %c (RowCol): \n", hc);
			getchar();
			xx = getchar();
			yy = getchar();
			// findSmarterMove(mapp, N, hc, &xx, &yy);
			// printf("Testing AI move (row, col): %c%c\n", xx + 'a', yy + 'a');
			// xx+='a';
			// yy+='a';

			if(check_vaild(mapp,N,hc,xx,yy)){
				oper_board(mapp,N,hc,xx,yy);
			}else {
				printf("Invalid move.\n");
				printf("%c player wins.\n", cc);
				break; 
			}
		}
		is_computers_turn = !is_computers_turn;
		prt_mapp(mapp,N);
	}
	

	return 0;
}


void prt_mapp(char mapp[][26], int n){
	printf("  ");
	for(register int i= 0 ; i < n ; i++){
		printf("%c",'a'+i);
	}
	puts("");
	for (register int i = 0 ; i < n ; i++){
		printf("%c ", 'a'+ i);
		for (register int j = 0 ; j < n ; j++){
			printf("%c",mapp[i][j]);
			// if(mapp[i][j]=='U') printf(" ");
			// if(mapp[i][j]=='B') printf("X");
			// if(mapp[i][j]=='W') printf("O");
		}
		puts("");
	}
}
void init_move(char mapp[][26], int n){
	mapp[n/2-1][n/2-1] = mapp[n/2][n/2] = 'W';
	mapp[n/2-1][n/2] = mapp[n/2][n/2-1] = 'B';
}
inline bool point_in_bound(int n , int r, int w ){
	#ifdef DDEBUG
	printf("checking %d %d %d\n",n,r,w );
	#endif
	return (r>=0 && w>=0 && r<n && w<n);
}
int check_legal_direction(char mapp[][26], int n, int row, int col, char che, int d_row, int d_col){
	if (mapp[row][col] == mapp[row + d_row ][col + d_col] ) {
		#ifdef DDEBUG
		printf("not vaild\n");
		#endif
		return false;
	}
	int cnt = 1;
	bool is_vaild = 0;
	if(point_in_bound(n,row +d_row ,col + d_col)&& mapp[row +d_row ][col + d_col] == che) return 0;
	while(point_in_bound(n  ,  row + cnt*d_row  ,  col + cnt*d_col)){

		if (mapp[row + cnt*d_row ][col + cnt*d_col]=='U') {
			#ifdef DDEBUG
			printf("breaking\n");
			#endif
			break;
		}
		if (mapp[row + cnt*d_row ][col + cnt*d_col]==che){
			is_vaild = true ;
			break ;
		}
		cnt ++;
	}
	return is_vaild?cnt:0;
}
struct available_move generate_vaild(char mapp[][26], char che, int n ){
	char * ret = (char *) malloc(sizeof(char) * 3 * 26 * 26);
	int cnt = 0 ;
	memset(ret,0,sizeof(char) * 3 * 26 * 26);
	for (int i = 0 ; i < n ; i++){
		for (int j = 0 ; j < n; j++){
			if(mapp[i][j] != 'U') continue;
			bool checked_vaild = false;
			int num=0;
			for (int  k = -1; k <=1 && !checked_vaild; k++){
				for (int l = -1 ; l <=1 ; l++){
					if ( (!k) && (!l) ) continue;
					#ifdef DDEBUG
					printf("%d %d %d %d\n",i,j,k,l );
					#endif
					if ((num=check_legal_direction(mapp,n,i,j,che,k,l)) != 0) { // '=' in purpose dont't change !!!!! 
						checked_vaild = true;
						#ifdef DDEBUG
						printf("correct:%d %d\n", i,j);
						#endif
						break;
					}
				}
			}
			if (checked_vaild){
				*(ret+3*cnt) =(char)'a'+i;
				*(ret+3*cnt + 1) =(char)'a'+j;
				*(ret+3*cnt++ + 2) =num;
				#ifdef DDEBUG
				printf("Added\n");
				#endif
			}
		}
	}
	#ifdef DDEBUG
	printf("cnt = %d\n", cnt);
	#endif
	struct available_move ret_pack;
	ret_pack.list = ret;
	ret_pack.size = cnt;
	return ret_pack;
}
int count_valid(char mapp[][26], char che, int n ){
	int cnt = 0 ;
	for (int i = 0 ; i < n ; i++){
		for (int j = 0 ; j < n; j++){
			if(mapp[i][j] != 'U') continue;
			bool checked_vaild = false;
			for (int  k = -1; k <=1 && !checked_vaild; k++){
				for (int l = -1 ; l <=1 ; l++){
					if ( (!k) && (!l) ) continue;
					#ifdef DDEBUG
					printf("%d %d %d %d\n",i,j,k,l );
					#endif
					if (check_legal_direction(mapp,n,i,j,che,k,l)) {
						checked_vaild = true;
						#ifdef DDEBUG
						printf("correct:%d %d\n", i,j);
						#endif
						break;
					}
				}
			}
			if (checked_vaild){
				cnt++;
			}
		}
	}
	#ifdef DDEBUG
	printf("cnt = %d\n", cnt);
	#endif
	return cnt;
}
void print_possible_move(char c,char * ans){
	printf("Available moves for %c:\n",c);
	int cnt = 0 ;
	#ifdef DDEBUG
	printf ("%p\n",ans);
	#endif
	while (*(ans+3*cnt)){
		printf("%c%c\n",*(ans+3*cnt),*(ans+3*cnt+1));
		cnt ++;
	}
	return;
}
bool oper_board(char mapp[][26], int n, char che, int xx, int yy ){
	xx-='a';
	yy-='a';
	bool is_vaild = false;
	for (int i = -1 ; i <=1 ; i++){
		for (int j = -1 ; j <= 1 ; j++){
			#ifdef DDEBUG
			printf("checking move of %d %d %c %d %d\n",xx,yy,che,i,j);
			#endif
			if ((!i) && (!j)) continue;
			if (check_legal_direction(mapp,n,xx,yy,che,i,j)){
				#ifdef DDEBUG
				printf("checked move of %d %d %c %d %d\n",xx,yy,che,i,j);
				#endif
				flip(mapp, n, xx,yy,che,i,j);
				is_vaild = true;
		}
		}
	}
	return is_vaild;
}
void flip(char mapp[][26], int n, int row, int col, char che, int d_row, int d_col){
	mapp[row][col]=che;
	int cnt = 1 ;
	while (point_in_bound(n,row+cnt*d_row,col+cnt*d_col)){
		if (mapp[row+cnt*d_row][col+cnt*d_col]!=che){
			mapp[row+cnt*d_row][col+cnt*d_col]=che;
		}else{
			break;
		}
		cnt++;
	}
	return;
}
int evaluate(char mapp[][26], int n, int che){
	int table[8][8] ={{500,-25,10,5,5,10,-25,500},
 					{-25,-45,1,1,1,1,-45,-25},
 					{10,1,3,2,2,3,1,10},
 					{5,1,2,1,1,2,1,5},
 					{5,1,2,1,1,2,1,5},
 					{10,1,3,2,2,3,1,10},
 					{-25,-45,1,1,1,1,-45,-25},
 					{500,-25,10,5,5,10,-25,500}};
	int B = 0 , W = 0 ;
	for(int i = 0; i < n ; i++){
		for (int j = 0 ; j < n ; j++){
			if (mapp[i][j]=='B') B+=table[i][j];
			if (mapp[i][j]=='W') W+=2*table[i][j];
		}
	}
	int delta = B-W+20*count_valid(mapp,'B',n)-20*count_valid(mapp,'W',n);
	// printf("%d\n",delta );
	return computer=='B'?delta:-delta;
}

/*

*/
int comp_oper_board(char mapp[][26],int n , char che,int depth ){
	if (depth==0) return evaluate(mapp,n,computer);
	struct available_move available = generate_vaild(mapp, che, n);
	struct node decision = get_max(mapp,n,che,available,depth);
	printf("Computer places %c at %c%c.\n", che, decision.x ,decision.y);
	oper_board(mapp, n, che, decision.x, decision.y);
	return 0;
}
void final(char mapp[][26],int n ){
	int B=0,W = 0;
	for (int i = 0; i < n ; i++ ){
		for(int j = 0 ; j < n ; j++){
			if (mapp[i][j]=='B') B++;
			if (mapp[i][j]=='W') W++;
		}
	}
	if (B>W){
		puts("B player wins.");
	}else if (B<W){
		puts("W player wins.");
	}else{
		puts("Tie.");
	}
}

bool check_vaild(char mapp[][26], int n, char che , char xx, char yy ){
	xx-='a';
	yy-='a';
	for (int i = -1 ; i <= 1 ; i++){
		for (int j = -1 ; j <= 1 ; j++){
			if(!i && !j) continue;
			if(check_legal_direction(mapp,n,xx,yy,che,i,j)) return true;
		}
	}
	return false;
}
struct node get_max(char mapp[][26],int n , char che , struct available_move avail,int depth){
	if (!depth){
		struct node ret ;
		ret.x = 0 ;
		ret.y = 0 ;
		ret.value = evaluate(mapp, n,che);
		return ret;
	}
	struct node ret ;
	int max = -0x7fffff;
	int max_index = 0;
	for (int i = 0 ; i < avail.size ; i++){
		char cp_mapp[26][26];
		memcpy(cp_mapp,mapp,sizeof(cp_mapp));
		oper_board(cp_mapp,n,che,*(avail.list+3*i), *(avail.list + 3*i + 1 ) );
		struct available_move available = generate_vaild(cp_mapp,opposite(che),n);
		int value = get_min(cp_mapp,n,che,available,depth-1).value;
		if (value > max){
			max = value;
			max_index = i ;
		}
	}
	ret.x=*(avail.list+3*max_index);
	ret.y=*(avail.list+3*max_index+1);
	ret.value = max;
	return ret ;
}
struct node get_min(char mapp[][26],int n , char che , struct available_move avail,int depth){
	if (!depth){
		struct node ret ;
		ret.x = 0 ;
		ret.y = 0 ;
		ret.value = evaluate(mapp, n,che);
		return ret;
	}
	struct node ret ;
	int min = 0x7fffff;
	int min_index = 0;
	for (int i = 0 ; i < avail.size ; i++){
		char cp_mapp[26][26];
		memcpy(cp_mapp,mapp,sizeof(cp_mapp));
		oper_board(cp_mapp,n,che,*(avail.list+3*i), *(avail.list + 3*i + 1 ) );
		struct available_move available = generate_vaild(cp_mapp,opposite(che),n);
		int value = get_max(cp_mapp,n,che,available,depth-1).value;
		if (value < min){
			min = value;
			min_index = i ;
		}
	}
	ret.x=*(avail.list+3*min_index);
	ret.y=*(avail.list+3*min_index+1);
	ret.value = min;
	return ret ;
}
