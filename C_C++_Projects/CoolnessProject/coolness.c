//will compute the coolness equation for asgn2
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//function that takes in float values for variables V and T needed in the coolness equation

void coolnessEq(float T, float V) {

    float coolness = 35.74 + (0.6215 * T) - (35.75 * pow(V, 0.16)) + (0.4275 * T * pow(V, 0.16));
	//creating final var coolness that has value of the final equation needed using math lib	
	//float coolness = 35.74 + (0.6215 * T) - (35.75 * pow(V, 0.16)) + (0.4275 * T * pow(V, 0.16));
    //printing with correct formatting using tabs and rounding to a single decimal place 
    printf("%.1f\t%.1f\t%.1f\n", T, V, coolness);
}

int main(int argc, char *argv[]) {

	//adressing the too many args case
	 if (argc > 3) {
		 //should print desired error message and return 1 
        printf("Usage: %s [temperature] [wind speed]\n", argv[0]);
        return 1;
    }



//addressing the out of bounds error message	 
 if (argc == 2 || argc == 3) {

	 //considering when the amount of arguements passed are correct for 1,2 args
        float T = atof(argv[1]);
        float V = 0.0;
	//will default v as 0 but then later update it when the if statement does not execute.
        if (argc == 3) {
		//since the statement executes then the value for v becomes the arguement provided by the user
            V = atof(argv[2]);
        }
        
        // Check if arguments are out of bounds
        if (T < -99 || T > 50 || (argc == 3 && V < 0.5)) {

		//printing exact error message as it appears on HW 
            printf("Error: Coolness. Acceptable input values are -99<=T<=50 and 0.5<=V.\n");
            return 1;
        }
    }


//first checking to see if thenumber of arguements are satisfied 
//checking for no args
    if (argc == 1) {
        // Implement the logic for no arguments here
	//printf("you ahve no inputs");
		printf("Temp\tWind\tCoolness\n");

		for (float T = -10; T <= 40; T += 10) {
		//T from -10 to 40 in steps of 10, and V from 5 to 15 in steps of 5
            for (float V = 5; V <= 15; V += 5) {

                coolnessEq(T, V);

            }
	    //in order to get the new line on each iteration of new numbers but not at the end of 40
	      if (T < 40) {

		      //printing the needed new line
            printf("\n");
        }

        }
    }
   
   //checking for a singular arguement
    else if (argc == 2) {
 

	    // creating float value T from the arguement passed by the user
	     float T = atof(argv[1]);

            //printing header colums for formating using tabs
	     printf("Temp\tWind\tCoolness\n");
	   //here there must be a for loop that incriments by 5 starting from 5 and ending at 15 calling the function on each iteration
		//declaring a float V that will incriment 3 times 
	     for (float V = 5; V <= 15; V += 5) {

            coolnessEq(T, V);

        }
	    //coolnessEq(T, V); 
           //printf("you have 1 input");

    } 
    //checking for 2 arguements
    
    else if (argc == 3) {
        //have to convert arguements to floats for both variables
        float T = atof(argv[1]);
        float V = atof(argv[2]);
       //test to run the values of the arguements 
	//printf(" T=%f and V=%f.\n", T, V);
	//using print statement with tabs for correct spacing needed and output format
	printf("Temp\tWind\tCoolness\n");
	//calling the function created to calculate the equation
	coolnessEq(T, V); 
	//this will ensure the program has correct output.
    }

    //printf("program ran to the end")
    return 0;
}
