#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define DEBUG
#define FILE

void prt_mapp(char mapp[][26], int n);
void init_move(char mapp[][26], int n);
void config_board(char mapp[][26], char che, char xx, char yy );
bool oper_board(char mapp[][26], int n , char che, int xx, int yy );
bool point_in_bound(int n , int r, int w );
bool check_vaild(char mapp[][26], char che , char xx, char yy );
char * generate_vaild(char mapp[][26], char che, int n );
void print_possible_move(char c, char * ans);
void flip(char mapp[][26], int n, int row, int col, char che, int d_row, int d_col);

int main(int argc, char const *argv[]){
	#ifdef FILE
	freopen("in","r",stdin);
	#endif

	printf("Enter the board dimension: \n");
	char mapp[26][26];
	memset(mapp,'U',sizeof(mapp));
	int N;
	scanf("%d",&N);
	init_move(mapp, N);
	prt_mapp(mapp, N);
	printf("Enter board configuration: \n");
	char che,xx,yy ;
	scanf(" %c %c %c",&che, &xx, &yy);
	while ( che != '!' && xx!='!' && yy !='!'){
		config_board(mapp,che,xx,yy);
		scanf(" %c %c %c",&che, &xx, &yy);
	}
	prt_mapp(mapp,N);

	char * ans_W = generate_vaild(mapp,'W',N);
	char * ans_B = generate_vaild(mapp,'B',N);
	print_possible_move('W',ans_W);
	print_possible_move('B',ans_B);
	free(ans_W);
	free(ans_B);


	printf("Enter a move: \n");
	scanf(" %c %c %c", &che,&xx,&yy);
	if (oper_board(mapp,N,che,xx,yy)) {
		printf("Valid move.\n");
		prt_mapp(mapp,N);
	}else {
		printf("Invalid move.\n");
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
void config_board(char mapp[][26],char che, char xx, char yy){
	mapp[xx-'a'][yy-'a'] = che;
}
inline bool point_in_bound(int n , int r, int w ){
	#ifdef DEBUG
	printf("checking %d %d %d\n",n,r,w );
	#endif
	return (r>=0 && w>=0 && r<n && w<n);
}
bool check_legal_direction(char mapp[][26], int n, int row, int col, char che, int d_row, int d_col){
	if (mapp[row][col] == mapp[row + d_row ][col + d_col] ) {
		#ifdef DEGUG
		printf("not vaild\n");
		#endif
		return false;
	}
	int cnt = 1;
	bool is_vaild = 0;
	if(point_in_bound(n,row +d_row ,col + d_col)&& mapp[row +d_row ][col + d_col] == che) return false;
	while(point_in_bound(n  ,  row + cnt*d_row  ,  col + cnt*d_col)){

		if (mapp[row + cnt*d_row ][col + cnt*d_col]=='U') {
			#ifdef DEBUG
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
	return is_vaild;
}
char * generate_vaild(char mapp[][26], char che, int n ){
	char * ret = (char *) malloc(sizeof(char) * 2 * 26 * 26);
	int cnt = 0 ;
	memset(ret,0,sizeof(char) * 2 * 26 * 26);
	for (int i = 0 ; i < n ; i++){
		for (int j = 0 ; j < n; j++){
			if(mapp[i][j] != 'U') continue;
			bool checked_vaild = false;
			for (int  k = -1; k <=1 && !checked_vaild; k++){
				for (int l = -1 ; l <=1 ; l++){
					if ( (!k) && (!l) ) continue;
					#ifdef DEBUG
					printf("%d %d %d %d\n",i,j,k,l );
					#endif
					if (check_legal_direction(mapp,n,i,j,che,k,l)) {
						checked_vaild = true;
						#ifdef DEBUG
						printf("correct:%d %d\n", i,j);
						#endif
						break;
					}
				}
			}
			if (checked_vaild){
				*(ret+2*cnt) =(char)'a'+i;
				*(ret+2*cnt++ + 1) =(char)'a'+j;
				#ifdef DEBUG
				printf("Added\n");
				#endif
			}
		}
	}
	#ifdef DEBUG
	printf("cnt = %d\n", cnt);
	#endif
	return ret;
}
void print_possible_move(char c,char * ans){
	printf("Available moves for %c:\n",c);
	int cnt = 0 ;
	#ifdef DEBUG
	printf ("%p\n",ans);
	#endif
	while (*(ans+2*cnt)){
		printf("%c%c\n",*(ans+2*cnt),*(ans+2*cnt+1));
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
			#ifdef DEBUG
			printf("checking move of %d %d %c %d %d\n",xx,yy,che,i,j);
			#endif
			if ((!i) && (!j)) continue;
			if (check_legal_direction(mapp,n,xx,yy,che,i,j)){
				#ifdef DEBUG
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