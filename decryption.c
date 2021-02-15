#include <stdio.h>

#include <time.h> //used for the random generation 

#include <stdlib.h> //used for system("cls")

#define SIZE 4 //allows the whole program to use this SIZE 


//this defines the struct code_counter that will be altered in the counting function
struct code_counter 
{

  int correct_code;
  int wrong_code;

};


//function declaration
int newMenu(int * codeArray, int * randArray); 

void enterCode(int * codeArray);

void randGen(int * randArray);

bool match(int * empty_Array, int *access_code);

void counting(struct code_counter * ,int * empty_array, int *access_code);

int Encrypt(int * codeArray, int * empty_Array);

void decrypt(int * codeArray);

int exiting();




int main() {
    
    int codeArray[SIZE] = {0}; //array for code entered by user 

    int randArray[SIZE] = {0}; //array for randomly generated code
  
    int empty_Array[SIZE] = {0}; //array to store the encrypted array to be used in the counting function

    int access_code[SIZE] = {4,5,2,3}; //this is the correct code 

    char answer; //holds the inputted answer by the user 

    struct code_counter correct; 
  
    //These will be incremented in counting later
    correct.correct_code = 0; 
    correct.wrong_code = 0;   

    int newMenuAnswer = 0;  
  
    int encrypt_func_value = 0;
  
    int exit1 = 2;
  
    int encrypted = 0;
    
    

    do {
    
        printf("\n************************************Menu**************************************\n");
        printf("[1] Enter 1 to choose between a randomly generated code or a user entered code\n");
        printf("[2] Enter 2 to encrypt the code\n");
        printf("[3] Enter 3 to check if the encrypted code is correct\n");
        printf("[4] Enter 4 to decrypt the code\n");
        printf("[5] Enter 5 to display the amount of times the encrypted code is right or wrong\n");
        printf("[6] Enter 6 to exit\n");
   
        scanf("%1s", & answer);
    
        switch (answer) {
            case '1':
                encrypt_func_value = 0;//sets encrypt_func_value to 0 so that only encrypted codes can be matched with the access_code
       
                encrypted = 0; //resets encrypted so that a new code can be encrypted 
        
                newMenuAnswer = newMenu(codeArray, randArray); //holds the return value of newMenu function while also calling the function
                break;
            
            case '2':
        
                //if statement is used instead of switch statement due to the use of && 
                if (newMenuAnswer == 1 && encrypted == 0) 
                {
                    encrypt_func_value = Encrypt(randArray, empty_Array); //holds the return value of the randomly generated encrypt function while also calling the function
                    encrypted = 1; //sets encrypted to 1 so that the code cannot be encrypted twice 
                } 
      
                else if (newMenuAnswer == 2 && encrypted == 0) 
                {
                    encrypt_func_value = Encrypt(codeArray, empty_Array); //holds the return value of the manually entered encrypt function while also calling the function
                    encrypted = 1; //sets encrypted to 1 so that the code cannot be encrypted twice 
                } 
                
                else if(encrypted == 1)
                {      
                    printf("The code has already been encrypted"); //printed if the code has already been encrypted 
                }
                
                else 
                {
                    printf("The code has not been entered"); //printed if no code has been entered
                }
                break;
                
            case '3':
                match(empty_Array,access_code);
                //this checks whether option 2 has been chosen or not
                switch(encrypt_func_value)
                {
                    case 2:
                        if (match(empty_Array,access_code) == true) 
                        {
                            printf("Correct Code Entered");
                        }     
                
                        else if(match(empty_Array,access_code) == false)
                        {
                            printf("Wrong Code Entered");
                        }
                        break;
                   
                    default:
                        printf("The code has not been encrypted");
                        for(int i = 0;i<SIZE;i++)
                        {
                            *(empty_Array+i) = 0; //sets the encrypted array to 0 so that option 5 cannot say that the answer is correct due to old contents left in this array 
                        }
                        break;
                }
                break;
                
            case '4':
                //only decrypts the function if it has already been encrypted 
                if (newMenuAnswer == 1 && encrypt_func_value == 2) 
                {   
                    decrypt(randArray); //decrypts the random code 
                } 
                else if (newMenuAnswer == 2 && encrypt_func_value == 2) 
                {
                    decrypt(codeArray); //decrypts the entered code
                }    
                else 
                {
                    printf("The code has not been encrypted");
                }
                break;
    
            case '5':
                counting(&correct,empty_Array,access_code); //this counts the amount of times a correct or wrong answer is given 
                break;

            case '6':
                exit1 = exiting(); //holds the return value for the exit function
            break;
    
        default:
            system("cls"); //clears the screen so that certain entered characters do not make the menu print multiple times 
            printf("Thats invalid\n");
            break;

        }

    } while (exit1 != 0); //this menu loops around as long as the y key is not pressed in the exiting() function.If it is 0 is returned.

printf("Goodbye\n");
printf("Press Enter to exit"); 
getchar(); 
return 0;

}





int newMenu(int * codeArray, int * randArray) 
{
    char newAnswer; //holds the result of the user entered answer
  
    printf("[1] Enter 1 to randomly generate a code\n");
    printf("[2] Enter 2 to enter a 4 digit code");
    scanf("%1s", & newAnswer);
    
    switch(newAnswer)
    {
        case '1': 
            randGen(randArray);
            return 1;
     
        case '2': 
            enterCode(codeArray);
            return 2;
    
        default:
            system("cls");
            printf("Thats invalid\n");
    }
}





void randGen(int * randArray) 
{
    //this ensures that the randomly generated numbers are not always the same by changing the seed along with the changing of the internal clock
    srand(time(NULL)); 
    int randomNumber;

    for (int i = 0; i < SIZE; i++) 
    {
        randomNumber = rand() % 9; //picks a random number between 0-9 
        *(randArray + i) = randomNumber; //each element is entered into the array 
        printf("%d", *(randArray + i));
    }
    

}





void enterCode(int * codeArray) 
{
    printf("Enter a new code:");
    for (int i = 0; i < SIZE; i++) 
    {
        scanf("%d", (codeArray + i));
    }    
    

}





int Encrypt(int * codeArray, int * empty_Array) 
{
    int temp, temp1, temp2, temp3 = 0;
    //this swaps the 1st and 3rd element and the 2nd and 4th element while adding one to each element
    temp =  *(codeArray + 0) + 1;
    temp1 = *(codeArray + 2) + 1;
    temp2 = *(codeArray + 1) + 1;
    temp3 = *(codeArray + 3) + 1;
    *(codeArray + 2) = temp;
    *(codeArray + 0) = temp1;
    *(codeArray + 1) = temp3;
    *(codeArray + 3) = temp2;

    //if an element equals to 10 it changes to 0
    for (int i = 0; i < SIZE; i++) 
    {
        if ( *(codeArray + i) == 10) 
        {
            *(codeArray + i) = 0;
        }
    
        *(empty_Array + i) = *(codeArray + i); //empty array now equals the entered/random array to be used in other functions such as match
        printf("%d", *(codeArray + i));
        
    }

    return 2;
}





bool match(int * empty_Array, int *access_code) 
{
    
    //this checks whether the encrypted array equals to the actual array 
    for (int i = 0; i < SIZE; i++) 
    {
        if ( *(empty_Array + i) != *(access_code + i)) 
        {
            return false;
        }

    }
    //if they are all the same true is returned outside of the for loop 
    return true;
}





void counting(struct code_counter * correct,int * empty_Array, int *access_code) 
{
    int wrong = 0;
  
    for (int i = 0; i < SIZE; i++) 
    {
        if (*(empty_Array + i) != *(access_code + i)) 
        {
            wrong++;
        }
    }
    //wrong iterates through 4 times and adds 1 each time the element is false. This means if wrong is greater than or equal to 1 the array is not fully true
    if (wrong >= 1)
    {
        correct->wrong_code++; //increments wrong_code
    }
    
    else
    {
        correct->correct_code++; //increments correct_code
    }

    printf("You got %d correct", correct->correct_code);
    printf("You got %d wrong", correct->wrong_code);
}





void decrypt(int * codeArray) 
{
    int swap, swap1, swap2, swap3 = 0;
       //swaps the 1st and 3rd element and the 2nd and 4th element  while taking one away from each element
    swap =  *(codeArray + 0) - 1;
    swap1 = *(codeArray + 2) - 1;
    swap2 = *(codeArray + 1) - 1;
    swap3 = *(codeArray + 3) - 1;
    *(codeArray + 2) = swap;
    *(codeArray + 0) = swap1;
    *(codeArray + 1) = swap3;
    *(codeArray + 3) = swap2;

    //changes an element to 9 if it equals -1
    for (int i = 0; i < SIZE; i++) 
    {
        if ( * (codeArray + i) == -1) 
        {
            *(codeArray + i) = 9;
        }
    
        printf("%d", *(codeArray + i));
    }

}





int exiting() 
{
    char answering;
    printf("Would you like to exit?y/n\n");
    scanf("%1s", & answering);
    flushall();
    //if the answer is y then the program exits otherwise if it is n it stays going 
    switch (answering) 
    {
        case 'y':
            return 0;
            break;
        case 'Y':
            return 0;
            break;
        case 'n':
            printf("You can continue");
            return 1;
            break;
         case 'N':
            printf("You can continue");
            return 1;
            break;
        default:
            printf("Please enter y or n");
            return 2;
            break;
    }
}
