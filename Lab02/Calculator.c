// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"




// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double AbsoluteValue(double operand1);
double FahrenheitToCelsius(double operand1);
double Tangent(double operand1);
//add more prototypes here
double Subtract(double operand1, double operand2);
double Divide(double operand1, double operand2);
double CelsiusToFahrenheit(double operand1);
double Average(double operand1, double operand2);
double Round(double operand1);

void CalculatorRun(void)
{
    char g;                //
    char gg;            //garbage char
    double result;
    double operand1;
    double operand2;
   
   printf("\n\nWelcome to Duo's calculator program! Compiled at %s %s\n",__DATE__, __TIME__);
    
   while (1){
   
    printf("Enter a mathematical operation to perform (*,/,+,-,m,a,c,f,t,q,r): ");
    scanf(" %c",&g);
    if (g != '*' && g != '/' && g != '+' && g != '-' && g != 'm' && g != 'a' && g != 'c' && g != 'f' && g != 't' && g != 'q' && g != 'r')  //g != '*'&& g!='/'
    {
        g = 0;
        
    }
    if (g == 'q')// g == q
    {
      return;  
    }
    if (g != 0)
    {
       printf("Enter the first operand:");
       scanf(" %lf",&operand1);
       if (g == '*' || g == '/'|| g == '+' || g == '-' || g == 'm')
       {
           printf("Enter the second operand:");
           scanf(" %lf",&operand2);
           if (g == 'm')
               {
                   result = Average(operand1, operand2);
                   printf("Result of Average(%lf and %lf):%lf\n",operand1, operand2, result);
               }
           else if (g == '+')
           {
               result = Add(operand1, operand2);
           }
           else if (g == '-')
               {
                   result = Subtract(operand1, operand2);
               }
           else if (g == '*')
               {
                   result = Multiply(operand1, operand2);
               }
           else if (g == '/')
               {
                   result = Divide(operand1, operand2);
               }
            if (g != 'm')
               {
                   printf("Result of (%lf %c %lf):%lf\n",operand1, g, operand2, result);
               }
           
       }
       if (g == 'a' || g == 'c' || g == 'f' || g == 't' || g == 'r')
       {
           if (g == 'a')
           {
               result = AbsoluteValue(operand1);
               printf("Result of AbsoluteValue(%lf)is:%lf\n", operand1, result);
           }
           else if (g == 'c')
           {
               result = FahrenheitToCelsius(operand1);
               printf("Result of FahrenheitToCelsius(%lf)is:%lf\n", operand1, result);
           }
           else if (g == 'f')
           {
               result = CelsiusToFahrenheit(operand1);
               printf("Result of CelsiusToFahrenheit(%lf)is:%lf\n", operand1, result);
           }
           else if (g == 't')
           {
               result = Tangent(operand1);
               printf("Result of Tangent(%lf)is:%lf\n", operand1, result);
           }
           else if (g == 'r')
           {
               result = Round(operand1);
               if (operand1 == 0)
               {
                   printf("Error, not a valid operand\n");
               }
               else
               {
                   printf("Result of Round(%lf)is:%lf\n", operand1, result);
               }
               
           }
       }
      
       
    }
    else 
    {
        printf("Error, not a valid operator\n");
        
    }
   }
   
}




/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2)
{
    double result = operand1 + operand2;
    return result;
    
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2)
{
	double result = operand1 - operand2;
    return result;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2)
{
    double result = operand1 * operand2;
    return result;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
	double result = operand1 / operand2;
    return result;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand1)
{
    double result;
    if (operand1 < 0)
    {
        double result = operand1 * -1;
     
    }
    else
    {
        double result = operand1;
        
    }
    return result;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand1)
{
    double result = (5.0 / 9.0)*(operand1 - 32.0);
    return result;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand1)
{
   double result =  32.0 + (operand1 * 9.0) / 5.0;
   return result;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{
   double result = (operand1 + operand2) / 2.0;
   return result; 
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand1)
{
    double operand = operand1 / M_PI;
    double result = tan(operand);
    return result;
    
}
/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand1) //if its negative and +0.5 then make it a int so 
{
    double result;
    if (operand1 > 0)
    {
        
        int operand = operand1 + 0.5;
        
         result = operand;
        
    }
    else 
    {
       
        int operand = operand1 - 0.5;
        
        result = operand;
        
    }
    return result;
}


