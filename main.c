#include <stdio.h>
#include <string.h>

void railFenceEncryption(char *message, char *cipherText, int length, int A);
void railFenceDecryption(char *message, char *deCipherText, int length, int A);
void twoLevelRailFence(char *message, char *cipherText, int length, int A, int B, int dir);


int main() {
        char output[1024];
        //railFenceEncryption("This is a test message", output, 0, 5);
        //printf("%s\n", output);
        //railFenceDecryption("T aseghsi  etmsaeist s", output, 0, 3);
        //printf("%s\n", output);
        twoLevelRailFence("This is a test message", output, 0, 11, 5, 0);
        printf("%s\n", output);
}

void railFenceEncryption(char *message, char *cipherText, int length, int A) {
        // Declare the "rail" grid with appropriate size.
        // Choice of row/col order in indexing is arbitrary
        char grid[A][strlen(message)]; //string length is columns and number of rails is rows
        int i = 0, j = 0;

        for(i = 0; i < A; i++){ //creating empty grid
            for(j = 0; j < strlen(message); j++){
                grid[i][j] = 0;
            }
        }
/*
        for(i = 0; i < A; i++){ //testing the grid
            for(j = 0; j < strlen(message); j++){
                 printf("%c", grid[j][i]);
            }
            printf("\n");
        }
*/
        int cnt = 0;
        j = 0;
        //filling the grid with message
        if (A > 1){
        while(j < strlen(message)){
            if(cnt % 2 == 0) // Even count will initiate the "top to bottom" algorithm ir the first for loop, therefore when odd the "else" algorithm will run.
            {
                for(i = 0; i < A; i++){ // Fill top to bottom for X amount of rails then exit loop.
                    grid[i][j] = (int)message[j]; // Fill in the text.
                    j++;
                }
            }
            else
            {
                for(i = A-2; i > 0; i--){ // Fill in the array bottom to top in between the letter in the top most and the bottom most rails
                    grid[i][j] = (int)message[j]; // Fill in the text.
                    j++;
                }
            }
            cnt++;
        }

        //printing the encrypted message

        for(i = 0; i < A; i++){
            for(j = 0; j < strlen(message); j++){
                    if(grid[i][j] != 0){ // Where not zero in grid print the message
                        cipherText = grid[i][j];
                        printf("%c", cipherText);
                    }
            }
        }
    }
        return;
}

void railFenceDecryption(char *message, char *deCipherText, int length, int A){
        char grid[A][strlen(message)]; //string length is columns and number of rails is rows
        int i = 0, j = 0;

        for(i = 0; i < A; i++){ //creating empty grid
            for(j = 0; j < strlen(message); j++){
                grid[i][j] = 0;
            }
        }
/*
        for(i = 0; i < A; i++){ //testing the grid
            for(j = 0; j < strlen(message); j++){
                 printf("%c", grid[j][i]);
            }
            printf("\n");
        }
*/
        int cnt = 0;
        j = 0;
        //filling the grid with -1 in place of the encrypted text rails
        while(j < strlen(message)){
            if(cnt % 2 == 0)
            {
                for(i = 0; i < A; i++)
                {
                    grid[i][j] = -1;
                    j++;
                }
            }
            else
            {
                for(i = A-2; i > 0; i--)
                {
                    grid[i][j] = -1;
                    j++;
                }
            }
            cnt++;
        }

        //filling grid with message
        int k = 0;
        for(i = 0; i < A; i++){
            for(j = 0; j < strlen(message); j++){
                    if(grid[i][j] != 0){
                        grid[i][j] = (int)message[k];
                        k++;
                }
            }
        }

        //printing the message out line by line, top to bottom.
        cnt = 0;
        j = 0;
        while(j < strlen(message)){
            if(cnt % 2 == 0)
            {
                for(i = 0; i < A; i++)
                {
                    deCipherText = grid[i][j];
                    printf("%c", deCipherText);
                    j++;
                }
            }
            else{
                for(i = A - 2; i > 0; i--)
                {
                    deCipherText = grid[i][j];
                    printf("%c", deCipherText);
                    j++;
                }
            }
            cnt++;
        }
        printf("\n");
return;
}

void twoLevelRailFence(char *message, char *cipherText, int length, int A, int B, int dir){
        // Declare the "rail" grid with appropriate size.
        // Choice of row/col order in indexing is arbitrary
        char grid[A][strlen(message)]; //string length is columns and number of rails is rows
        int i = 0, j = 0;

        for(i = 0; i < A; i++){ //creating empty grid
            for(j = 0; j < strlen(message); j++){
                grid[i][j] = '.';
            }
        }
        printf("A: %d\nB: %d\n", A, B);

        int cnt = 0;
        j = 0;
        if(dir == 0){ // encryption

            if(A > B && B > 1){ //only gonna work if conditions are met

                while(j < strlen(message)){

            if(cnt % 2 == 0) // Even count will initiate the "top to bottom" algorithm ie the first for loop, therefore when odd the "else" algorithm will run.
            {
                //Fills 0 index to A rails
                for(i = 0; i < A && j < strlen(message); i++){ // Fill top to bottom for X amount of rails then exit loop.
                    grid[i][j] = (int)message[j]; // Fill in the text.
                    printf("%c - ", (int)message[j]);
                    j++;
                    printf("going down:%d, %d\n", i, j);
                }
                for(i = A-2; i > ((A-1) - B)  && j < strlen(message); i--){ //Fill from A rail up to B rail
                    grid[i][j] = (int)message[j]; // Fill in the text.
                    printf("%c - ", (int)message[j]);
                    j++;
                    printf("going up to b: %d, %d\n", i, j);
                }
            }
            else
            {
                //try i = B; i <= A
                for(i = ((A-B) + 1); i < (A-1) && j < strlen(message); i++){ // Fill from B rail back down to A rail
                    grid[i][j] = (int)message[j]; // Fill in the text.
                    printf("%c - ", (int)message[j]);
                    j++;
                    printf("going down to A: %d, %d\n", i, j);
                }

                for(i = A-1; i > 0 && j < strlen(message); i--){ // Fill in the array bottom to top in between the letter in the top most and the bottom most rails
                    grid[i][j] = (int)message[j]; // Fill in the text.
                    printf("%c - ", (int)message[j]);
                    j++;
                    printf("going back to top: %d, %d\n", i, j);
                }
            }
                cnt++;
        }

            for(i = 0; i < A; i++){ //testing the grid
                for(j = 0; j < strlen(message); j++){
                 printf("%c", grid[i][j]);
            }
            printf("\n");
        }
        //printing out cipher text by reading left to right; top to bottom.
/*
            for(i = 0; i < A; i++){
                for(j = 0; j < strlen(message); j++){
                    if(grid[i][j] != 0){ // Where not zero in grid print the message
                        cipherText = grid[i][j];
                        printf("%c", cipherText);
                    }
                }
            }
*/
        }
    }else if(dir == 1){

        if(A > B && B > 1){ //only gonna work if conditions are met

                while(j < strlen(message)){

            if(cnt % 2 == 0) // Even count will initiate the "top to bottom" algorithm ir the first for loop, therefore when odd the "else" algorithm will run.
            {
                //Fills 0 index to A rails
                for(i = 0; i < A && j < strlen(message); i++){ // Fill top to bottom for X amount of rails then exit loop.
                    grid[i][j] = -1; // Fill in the text.
                    j++;
                }
                for(i = A-2; i < ((A-B) -1)  && j < strlen(message); i--){ //Fill from A rail up to B rail
                    grid[i][j] = -1; // Fill in the text.
                    j++;
                }
            }
            else
            {
                //try i = B; i <= A
                for(i = A-(B-1); i < B && j < strlen(message); i++){ // Fill from B rail back down to A rail
                    grid[i][j] = -1; // Fill in the text.
                    j++;
                }

                for(i = A-1; i > 0 && j < strlen(message); i--){ // Fill in the array bottom to top in between the letter in the top most and the bottom most rails
                    grid[i][j] = -1; // Fill in the text.
                    j++;
                }
            }
                cnt++;
        }

            //filling grid with message
        int k = 0;
        for(i = 0; i < A; i++){
            for(j = 0; j < strlen(message); j++){
                    if(grid[i][j] != 0){
                        grid[i][j] = (int)message[k];
                        k++;
                }
            }
        }

        cnt = 0;
        j = 0;
        while(j < strlen(message)){

            if(cnt % 2 == 0) // Even count will initiate the "top to bottom" algorithm ir the first for loop, therefore when odd the "else" algorithm will run.
            {
                //Fills 0 index to A rails
                for(i = 0; i < A && j < strlen(message); i++){ // Fill top to bottom for X amount of rails then exit loop.
                    cipherText = grid[i][j];
                    printf("%c", cipherText);
                    j++;
                }
                for(i = A-2; i < ((A-B) -1)  && j < strlen(message); i--){ //Fill from A rail up to B rail
                    cipherText = grid[i][j];
                    printf("%c", cipherText);
                    j++;
                }
            }
            else
            {
                //try i = B; i <= A
                for(i = A-(B-1); i < B && j < strlen(message); i++){ // Fill from B rail back down to A rail
                    cipherText = grid[i][j];
                    printf("%c", cipherText);
                    j++;
                }

                for(i = A-1; i > 0 && j < strlen(message); i--){ // Fill in the array bottom to top in between the letter in the top most and the bottom most rails
                    cipherText = grid[i][j];
                    printf("%c", cipherText);
                    j++;
                }
            }
                cnt++;
        }
    }else{
    printf("Wrong input, please input either 0 for encryption or 1 for decryption");
    }
return;
    }
}
