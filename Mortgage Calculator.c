#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double totalInterest(double loanAmount, double interestRate, double termYears){
    double monthlyPayment;
    double monthlyInterestRate = interestRate / (12 * 100);
    double termMonths = termYears * 12.0;
    double interestSum = 0.0;
    double totalBalance = loanAmount;
    double interest, principal;
   
    //-------------Monthly payment formula---------------------
    monthlyPayment = loanAmount * monthlyInterestRate * pow(1+monthlyInterestRate, termMonths) / (pow(1+monthlyInterestRate, termMonths) - 1);
   
    //------------Total interest-----------------------
    //Outer loop represents years
    for(int i = 0; i < termYears; i++){
        //Inner loop represents months
        for(int j = 0; j < 12; j++){
            interest = totalBalance * monthlyInterestRate;
            principal = monthlyPayment - interest;
            totalBalance -= principal;
            interestSum += interest;
        }
    }
   
    //Return the total interest that is accumulated
    return interestSum;
}


void outputShortFormat(double loanAmount, double interestRate, double termYears){
    double monthlyPayment;
    double monthlyInterestRate = interestRate / (12 * 100);
    double termMonths = termYears * 12.0;
    double interestSum = totalInterest(loanAmount, interestRate, termYears);
    double totalBalance = loanAmount;
    double interest, principal;
   
    //-------------Monthly payment---------------------
    monthlyPayment = loanAmount * monthlyInterestRate * pow(1+monthlyInterestRate, termMonths) / (pow(1+monthlyInterestRate, termMonths) - 1);
   
    //------------Total interest-----------------------
    //Outer loop represents years
    for(int i = 0; i < termYears; i++){
        //Inner loop represents months
        for(int j = 0; j < 12; j++){
            interest = totalBalance * monthlyInterestRate;
            principal = monthlyPayment - interest;
            totalBalance -= principal;
        }
    }
   
    //----------------Print statements--------------------
    printf("\n-------------------------------------\n");
    printf("%23s", "LOAN TERMS");
    printf("\n-------------------------------------\n");
    printf("Loan Amount: %*.2lf\n", 21, loanAmount);
    printf("Interest Rate: %*.2lf%%\n", 18, interestRate);
    printf("Term: %*.2lf years", 22, termYears);
    printf("\n-------------------------------------\n");
    printf("\nMonthly payment is: %*.2lf\n", 14, monthlyPayment);
    printf("Total Interest is: %*.2lf\n", 15, interestSum);
    printf("Total amount paid is: %*.2lf", 12, interestSum + loanAmount);

}

void outputAmortized(double loanAmount, double interestRate, double termYears){
    double monthlyPayment;
    double monthlyInterestRate = interestRate / (12 * 100);
    double termMonths = termYears * 12.0;
    double interestSum = 0.0;
    double principalSum = 0.0;
    double totalBalance = loanAmount;
    double interest, principal;
    int month = 1;
   
    //-------------Monthly payment---------------------
    monthlyPayment = loanAmount * monthlyInterestRate * pow(1+monthlyInterestRate, termMonths) / (pow(1+monthlyInterestRate, termMonths) - 1);
   
    //------------Total interest-----------------------
    //Outer loop represents years
    for(int i = 0; i < termYears; i++){
        printf("\n-----------------------------------------------------------------\n");
        printf("%4s%7s%10s%11s%9s  |%10s%11s", "Year", "Month", "Interest", "Principal", "Balance", "INTEREST", "PRINCIPAL");
        printf("\n-----------------------------------------------------------------\n");
        //Inner loop represents months
        for(int j = 0; j < 12; j++){
            interest = totalBalance * monthlyInterestRate;
            principal = monthlyPayment - interest;
            totalBalance -= principal;
            interestSum += interest;
            principalSum += principal;
            //Print the year in the first month's row
            if (j == 0) {
                printf("%4d%7d%10d%11d%9d  |%10d%11d\n", i+1, month, (int) interest, (int) principal, (int) totalBalance, (int) interestSum, (int) principalSum);
            } else {
                printf("%11d%10d%11d%9d  |%10d%11d\n", month, (int) interest, (int) principal, (int) totalBalance, (int) interestSum, (int) principalSum);
            }
            month++;
        }
    }
   
}

void outputExtraMonthly(double loanAmount, double interestRate, double termYears, double extraPayment){
    double monthlyPayment;
    double monthlyInterestRate = interestRate / (12 * 100);
    double termMonths = termYears * 12.0;
    double interestSum = 0.0;
    double principalSum = 0.0;
    double totalBalance = loanAmount;
    double interest, principal;
    int month = 1;
    int monthsRemaining;
   
    //-------------Monthly payment---------------------
    monthlyPayment = loanAmount * monthlyInterestRate * pow(1+monthlyInterestRate, termMonths) / (pow(1+monthlyInterestRate, termMonths) - 1);
   
    //------------Total interest-----------------------
    //Outer loop represents years
    for(int i = 0; i < termYears; i++){
        printf("------------------------------------------------------------------------\n");
        printf("%4s%7s%10s%11s%9s  |%10s%11s%7s", "Year", "Month", "Interest", "Principal", "Balance", "INTEREST", "PRINCIPAL", "EXTRA");
        printf("\n------------------------------------------------------------------------\n");
        //Inner loop represents months
        for(int j = 0; j < 12; j++){
            //If balance is paid off, break out from loop and report the statistics
            if(totalBalance < 0) {
                monthsRemaining = termMonths - month + 1;
                printf("The payments are finished %d months (%.1f years) earlier!\n", monthsRemaining, monthsRemaining / 12.0);
                printf("The interest saving is: %d\n", (int) (totalInterest(loanAmount, interestRate, termYears) - interestSum));
                break;
            }
            //Otherwise, continue with the arithmetic, adding the extra payement to what is deducted from the total balance
            interest = totalBalance * monthlyInterestRate;
            principal = monthlyPayment - interest;
            totalBalance -= (principal + extraPayment);
            interestSum += interest;
            principalSum += principal;
            //Print the year in the first month's row
            if (j == 0) {
                printf("%4d%7d%10d%11d%9d  |%10d%11d%7d\n", i+1, month, (int) interest, (int) principal, (int) totalBalance, (int) interestSum, (int) principalSum, (int) extraPayment);
            } else {
                printf("%11d%10d%11d%9d  |%10d%11d%7d\n", month, (int) interest, (int) principal, (int) totalBalance, (int) interestSum, (int) principalSum, (int) extraPayment);
            }
            month++;
        }
        if(totalBalance < 0) {
                break;
            }
    }
   
}

void outputExtraYearly(double loanAmount, double interestRate, double termYears, double extraPayment){
    double monthlyPayment;
    double monthlyInterestRate = interestRate / (12 * 100);
    double termMonths = termYears * 12.0;
    double interestSum = 0.0;
    double principalSum = 0.0;
    double totalBalance = loanAmount;
    double interest, principal;
    int month = 1;
    int monthsRemaining;
   
    //-------------Monthly payment---------------------
    monthlyPayment = loanAmount * monthlyInterestRate * pow(1+monthlyInterestRate, termMonths) / (pow(1+monthlyInterestRate, termMonths) - 1);
   
    //------------Total interest-----------------------
    //Outer loop represents years
    for(int i = 0; i < termYears; i++){
        printf("------------------------------------------------------------------------\n");
        printf("%4s%7s%10s%11s%9s  |%10s%11s%7s", "Year", "Month", "Interest", "Principal", "Balance", "INTEREST", "PRINCIPAL", "EXTRA");
        printf("\n------------------------------------------------------------------------\n");
        //Inner loop represents months
        for(int j = 0; j < 12; j++){
            //Extra payment is only made in the month of december, as per project requirements
            if(j != 11) {
                if(totalBalance < 0) {
                    monthsRemaining = termMonths - month + 1;
                    printf("The payments are finished %d months (%.1f years) earlier!\n", monthsRemaining, monthsRemaining / 12.0);
                    printf("The interest saving is: %d\n", (int) (totalInterest(loanAmount, interestRate, termYears) - interestSum));
                    break;
                }
                interest = totalBalance * monthlyInterestRate;
                principal = monthlyPayment - interest;
                totalBalance -= principal;
                interestSum += interest;
                principalSum += principal;
                //Print the year in the first month's row
                if (j == 0) {
                    printf("%4d%7d%10d%11d%9d  |%10d%11d%7d\n", i+1, month, (int) interest, (int) principal, (int) totalBalance, (int) interestSum, (int) principalSum, 0);
                } else {
                    printf("%11d%10d%11d%9d  |%10d%11d%7d\n", month, (int) interest, (int) principal, (int) totalBalance, (int) interestSum, (int) principalSum, 0);
                }
            } else {
                if(totalBalance < 0) {
                    monthsRemaining = termMonths - month + 1;
                    printf("The payments are finished %d months (%.1f years) earlier!\n", monthsRemaining, monthsRemaining / 12.0);
                    printf("The interest saving is: %d\n", (int) (totalInterest(loanAmount, interestRate, termYears) - interestSum));
                    break;
                }
                interest = totalBalance * monthlyInterestRate;
                principal = monthlyPayment - interest;
                totalBalance -= (principal + extraPayment);
                interestSum += interest;
                principalSum += principal;
                //Print the year in the first month's row
                if (j == 0) {
                    printf("%4d%7d%10d%11d%9d  |%10d%11d%7d\n", i+1, month, (int) interest, (int) principal, (int) totalBalance, (int) interestSum, (int) principalSum, (int) extraPayment);
                } else {
                    printf("%11d%10d%11d%9d  |%10d%11d%7d\n", month, (int) interest, (int) principal, (int) totalBalance, (int) interestSum, (int) principalSum, (int) extraPayment);
                }
            }
            month++;
        }
        if(totalBalance < 0) {
                break;
            }
    }
   
}


int main()
{
    double loanAmount;
    double interestRate;
    double termYears;
    double extraPayment;
    int n = -1;
   
    //Do-while loop used to create a menu
    do {
    printf("%23s", "\n\nMORTGAGE CALCULATOR\n");
    printf("Navigate using the following choices: \n");
    printf("1.\t Short Format\n");
    printf("2.\t Amortized Format\n");
    printf("3.\t Early monthly payments\n");
    printf("4.\t Early yearly payments\n");
    printf("5.\t Quit\n");
    scanf("%d", &n);
    
    //User is given different options to help navigate the program. Each number represents a menu choice
    if(n == 1){
        system("clear");
        printf("Enter loan amount: ");
        scanf("%lf", &loanAmount);
        printf("\nEnter interest rate: ");
        scanf("%lf", &interestRate);
        printf("\nEnter term years: ");
        scanf("%lf", &termYears);
       
        outputShortFormat(loanAmount, interestRate, termYears);
   
    }else if(n == 2){
        system("clear");
        printf("Enter loan amount: ");
        scanf("%lf", &loanAmount);
        printf("\nEnter interest rate: ");
        scanf("%lf", &interestRate);
        printf("\nEnter term years: ");
        scanf("%lf", &termYears);
       
        outputAmortized(loanAmount, interestRate, termYears);
   
    } else if(n == 3){
        system("clear");
        printf("Enter loan amount: ");
        scanf("%lf", &loanAmount);
        printf("\nEnter interest rate: ");
        scanf("%lf", &interestRate);
        printf("\nEnter term years: ");
        scanf("%lf", &termYears);
        printf("\nEnter extra montly payment: ");
        scanf("%lf", &extraPayment);
       
        outputExtraMonthly(loanAmount, interestRate, termYears, extraPayment);
   
    } else if(n == 4){
        system("clear");
        printf("Enter loan amount: ");
        scanf("%lf", &loanAmount);
        printf("\nEnter interest rate: ");
        scanf("%lf", &interestRate);
        printf("\nEnter term years: ");
        scanf("%lf", &termYears);
        printf("\nEnter extra montly payment: ");
        scanf("%lf", &extraPayment);
       
        outputExtraYearly(loanAmount, interestRate, termYears, extraPayment);
    }
       
    } while (n != 5);
   
    return 0;
}