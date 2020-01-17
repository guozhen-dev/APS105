#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
struct {
	char name[10];
	char tolerance[15];
}colors[13];
const double eps = 1e-5;
int find_value(const char input){
	char index[13]="kbroeguvywls";
	for (int i = 0; i < 12; i++){
		if ( index[i] == input || index[i] == input + 32 ){
			return i;
		}
	}
	return -1;
}
int val_proc(double value){	
	if (log(value)/log(10) >= 6-eps){
		value *= 1e-6;
		printf("%.2lf MOhms ",(double)value);
		return 0;
	} else if (log(value)/log(10) >= 3.0-eps ){
		value *= 1e-3;
		printf("%.2lf KOhms ",(double)value);
		return 0;
	}else {
		printf("%.2lf Ohms ",(double)value);
		return 0;
	}

	return -1;
}
int main(int argc, char const *argv[]){

	strcpy(colors[0].name,"Black");
	strcpy(colors[1].name,"Brown");
	strcpy(colors[1].tolerance,"+/- 1.00%");
	strcpy(colors[2].name,"Red");
	strcpy(colors[2].tolerance,"+/- 2.00%");
	strcpy(colors[3].name,"Orange");
	strcpy(colors[4].name,"Yellow");
	strcpy(colors[5].name,"Green");
	strcpy(colors[5].tolerance,"+/- 0.50%");
	strcpy(colors[6].name,"Blue");
	strcpy(colors[6].tolerance,"+/- 0.25%");
	strcpy(colors[7].name,"Violet");
	strcpy(colors[7].tolerance,"+/- 0.10%");
	strcpy(colors[8].name,"Grey");
	strcpy(colors[8].tolerance,"+/- 0.05%");
	strcpy(colors[9].name,"White");
	strcpy(colors[10].name,"Gold");
	strcpy(colors[10].tolerance,"+/- 5.00%");
	strcpy(colors[11].name,"Silver");
	strcpy(colors[11].tolerance,"+/- 10.00%");
	long long value1 = 0;	
	char a[4] = {0,};
	printf("Please enter the 1st band of resistor 1: \n");
	scanf("%c",&a[0]);getchar();
	printf("Please enter the 2nd band of resistor 1: \n");
	scanf("%c",&a[1]);getchar();
	printf("Please enter the multiplier band of resistor 1:\n");
	scanf("%c",&a[2]);getchar();
	printf("Please enter the tolerance band of resistor 1:\n");
	scanf("%c",&a[3]);getchar();
	value1 = 10*find_value(a[0])+find_value(a[1]);
	value1 *= pow(10,find_value(a[2]));
	char b[4] = {0,};
	long long value2 = 0;
	printf("Please enter the 1st band of resistor 2: \n");
	scanf("%c",&b[0]);getchar();
	printf("Please enter the 2nd band of resistor 2: \n");
	scanf("%c",&b[1]);getchar();
	printf("Please enter the multiplier band of resistor 2: \n");
	scanf("%c",&b[2]);getchar();
	printf("Please enter the tolerance band of resistor 2: \n" );
	scanf("%c",&b[3]);getchar();
	value2 = 10*find_value(b[0])+find_value(b[1]);
	value2 *= pow(10,find_value(b[2]));
	printf("Colour bands for resistor 1: \n");
	if (find_value(a[0])<0 || find_value(a[0])>9){
		printf("Invalid colour for the 1st band of resistor 1. Exiting the program...\n");
		return 0;
	}
	if (find_value(a[1])<0 || find_value(a[1])>9){
		printf("Invalid colour for the 2nd band of resistor 1. Exiting the program...\n");
		return 0;
	}
	if (find_value(a[2])==-1 || find_value(a[2]) == 8 || find_value(a[2]) == 9){
		printf("Invalid colour for the multiplier of resistor 1. Exiting the program...\n");
		return 0;
	}
	if (find_value(a[3])==3 || find_value(a[3])==4 || find_value(a[3])==9 ){
		printf("Invalid colour for the tolerance of resistor 1. Exiting the program...\n");
		return 0;
	}
	printf("%s %s %s %s\n",colors[find_value(a[0])].name,colors[find_value(a[1])].name,colors[find_value(a[2])].name,colors[find_value(a[3])].name);
	printf("Colour bands for resistor 2: \n");
	if (find_value(b[0])<0 || find_value(b[0])>9){
		printf("Invalid colour for the 1st band of resistor 2. Exiting the program...\n");
		return 0;
	}
	if (find_value(b[1])<0 || find_value(b[1])>9){
		printf("Invalid colour for the 2nd band of resistor 2. Exiting the program...\n");
		return 0;
	}
	if (find_value(b[2])==-1 || find_value(b[2]) == 8 || find_value(b[2]) == 9){
		printf("Invalid colour for the multiplier of resistor 2. Exiting the program...\n");
		return 0;
	}
	if (find_value(b[3])==3 || find_value(b[3])==4 || find_value(b[3])==9 ){
		printf("Invalid colour for the tolerance of resistor 2. Exiting the program...\n");
		return 0;
	}
	printf("%s %s %s %s\n",colors[find_value(b[0])].name,colors[find_value(b[1])].name,colors[find_value(b[2])].name,colors[find_value(b[3])].name);
	printf("Value in ohms of resistor 1: " );val_proc((double)value1);printf("%s\n", colors[find_value(a[3])].tolerance);
	printf("Value in ohms of resistor 2: " );val_proc((double)value2);printf("%s\n", colors[find_value(b[3])].tolerance);
	printf("The Equivalent in series is ");val_proc(value1+value2); printf("\n");
	printf("The Equivalent in parallel is ");val_proc((double)value1*value2/(double)(value2+value1));printf("\n");
	return 0;
}
