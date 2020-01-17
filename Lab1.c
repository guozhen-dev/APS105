//Name : Guozhen Ding (1005760749)
//Purpose : Practice on simple computation
#include <stdio.h>
inline int read(){//快读
    int x=0,sign=1;
    char c=getchar();
    while(c>'9'||c<'0'){    //判断符号
        if(c=='-') sign=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){      //转换数
        x=x*10+c-'0';
        c=getchar();
    }
    return x*sign;
}
int main(int argc, char const *argv[]){
	int inputNumber1, inputNumber2, inputNumber3; //init the variables
	printf("Enter First Number: ");
	// scanf("%d",&inputNumber1);
	inputNumber1 = read();
	printf("Enter Second Number: ");
	// scanf("%d",&inputNumber2);
	inputNumber2 = read();
	printf("Enter Third Number: ");
	// scanf("%d",&inputNumber3); //read in the three numbers
	inputNumber3 = read();
	printf("Sum: %d \n", inputNumber1 + inputNumber2 + inputNumber3);// calc and print the sum
	printf("First negated: %d \n", -1 * inputNumber1 ); //calc and print the neg of number 1
	printf("After Number 2: %d \n", inputNumber2 + 1 );//calc and print the next number of number 2
	printf("Product of Number 2 and Number 3: %d \n", inputNumber2 * inputNumber3 ); // calc and print the n2 * n3
	return 0; 
}
