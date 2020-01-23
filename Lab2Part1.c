//Name : Guozhen Ding (1005760749)
/*
 * Lab Submission for APS105H1 
 * Input : The daily rate and the rental period 
 * Output : The total charge and days of free by using the given charge method 
 * Assumption : All the input from the user is vaild
 */

#include <stdio.h>
#define TAX 1.13
#define freeRate 4

int main(int argc, char const *argv[]){
    //init the variables 
    double dailyRate, totalCharge;
    int rentDays, paidCircles;

    //Get input from the user
    printf("Enter the daily rate: ");
    scanf("%lf",&dailyRate);
    printf("Enter the rental period (in days): \n");
    scanf("%d",&rentDays);

    //Do the calculations 
    paidCircles = rentDays / freeRate;
    totalCharge = TAX*(paidCircles * (freeRate-1) * dailyRate + ( rentDays % freeRate ) * dailyRate);
    
    //Output the result 
    printf("Your total free day(s) in this rental is: %d\n",paidCircles);
    printf("The total charge including taxes is: %.2lf\n",totalCharge);
    
    return 0;
}
