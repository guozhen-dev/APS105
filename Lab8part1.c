#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#define DDEBUG
//#define FILE
//#define DEBUG

void prt_mapp(char mapp[][26], int n);
void init_move(char mapp[][26], int n);
void config_board(char mapp[][26], char che, char xx, char yy );
bool oper_board(char mapp[][26], int n , char che, int xx, int yy );
bool point_in_bound(int n , int r, int w );
int check_legal_direction(char mapp[][26], int n, int row, int col, char che, int d_row, int d_col);
bool check_vaild(char mapp[][26], int n, char che , char xx, char yy );
char * generate_vaild(char mapp[][26], char che, int n );
void print_possible_move(char c, char * ans);
void flip(char mapp[][26], int n, int row, int col, char che, int d_row, int d_col);
void comp_oper_board(char mapp[][26],int n , char che);
int count_valid(char mapp[][26], char che, int n );
void final(char mapp[][26],int n );

int main(int argc, char const *argv[])
{
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
			comp_oper_board(mapp,N,cc);
		}else {
			char xx, yy;
			printf("Enter move for colour %c (RowCol): \n", hc);
			getchar();
			xx = getchar();
			yy = getchar();
			if(check_vaild(mapp,N,hc,xx,yy)){
				oper_board(mapp,N,hc,xx,yy);
			}else {
				printf("Invalid move.\n");
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
char * generate_vaild(char mapp[][26], char che, int n ){
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
					if (num=check_legal_direction(mapp,n,i,j,che,k,l)) {
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
	return ret;
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
void comp_oper_board(char mapp[][26],int n , char che){
	char * available = generate_vaild(mapp,che , n );
	#ifdef DEBUG
	print_possible_move(che, available);
	#endif
	int cnt = 0 ;
	int max = -1, max_cnt = 0;
	while (*(available+3*cnt)){
		if (*(available+3*cnt+2) > max){
			max_cnt = cnt;
			max = *(available+3*cnt+3);
		}
		cnt ++;
	}
	oper_board(mapp,n,che,*(available+3*max_cnt),*(available+3*max_cnt+1));
	printf("Computer places %c at %c%c.\n", che, *(available+3*max_cnt),*(available+3*max_cnt+1));
}
void final(char mapp[][26],int n ){
	int B,W = B = 0;
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