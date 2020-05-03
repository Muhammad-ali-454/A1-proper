#include <stdio.h>
#include <string.h>
//This program can encrypt and decrypt both the rail fence and the two level rail fence algorithm.
//The menu system is pretty straight forward.

void railFenceEncryption(char *message, char *cipherText, int length, int A);
void railFenceDecryption(char *message, char *deCipherText, int length, int A);
void twoLevelRailFence(char *message, char *cipherText, int length, int A, int B, int dir);


int main() {
//output???
        char output[1024];
        for(int i = 0; i < 1024; i++){
            output[i] = 0;
        }

        //Opens the file containing the text
        FILE * input;
        input = fopen("cipherText.txt", "r");
        if(input == NULL){
            perror("fopen()");
            return 1;
        }
        //Gets the length of text stored in file
        fseek(input, 0, SEEK_END);//Go to end
        size_t length = ftell(input);//Read the length and store it in variable length
        fseek(input, 0, SEEK_SET);//Go to start

        int i = 0;
        char c;
        char msg[length];
        for(i = 0; i < length; i++){//initialize msg array
            msg[i] = 0;
        }
        i = 0;
        //reading the text
        fscanf(input, "%c", &c);
        while(!feof(input) && i < length){
            msg[i++] = c;
            fscanf(input, "%c", &c);
        }
        msg[i] = 0;

        //menu
        int choice = 0;
        int key = 0, key1 = 0;
        printf("Welcome to the Encryption and Decryption Algorithms!\nPLease choose:\n1 for Rail Fence Encryption\n2 for Rail Fence Decryption\n3 for 2-level rail fence selection\n");
        scanf("%d", &choice);

        if(choice == 1){
            printf("Please input a key to encrypt with. Must be above 1!\n");
            scanf("%d", &key);
            railFenceEncryption(msg, output, 0, key);
            //printf("%s\n", output);
        }else if(choice == 2){
            printf("Please input a key to decrypt with. Must be above 1!\n");
            scanf("%d", &key);
            railFenceDecryption(msg, output, 0, key);
            //printf("%s\n", output);
        }else if(choice == 3){
            int decision = 0;
            printf("Please input Key A (Rails) & Key B (Secondary Height). A must be bigger than B and B must be more than 1!\n");
            scanf("%d %d", &key, &key1);
            printf("Please enter 0 for encryption or 1 for decryption!\n");
            scanf("%d", &decision);
            twoLevelRailFence(msg, output, 0, key, key1, decision);
            //printf("%s\n", output);
        }else{
            printf("Please input a valid choice");

        }
        return 0;
}

/*
*inputs/outputs: The inputs are: the pointer to the message which is read for encryption, cipherText pointer displays the worked output, length is not used in my program and is just there to meet spec, A variable holds the key.
*return value: void
*function operation: Encrypts text using the rail fence cipher algorithm
*function limitation: The key has to be an integer and be more than 1
*/
void railFenceEncryption(char *message, char *cipherText, int length, int A) {
        // Declaring the "rail" grid with appropriate size.
        char grid[A][strlen(message)]; //string length is columns and number of rails is rows
        int i = 0, j = 0;

        printf("Key is: %d\n", A);

        //creating empty grid
        for(i = 0; i < A; i++){
            for(j = 0; j < strlen(message); j++){
                grid[i][j] = 0;
            }
        }

        int cnt = 0;
        j = 0; //initialize the variable again so that previous value doesn't affect loop
        //filling the grid with message
        if (A > 1){
        while(j < strlen(message)){
            if(cnt % 2 == 0) // Even count will initiate the "top to bottom" algorithm ie the first for loop, therefore when odd the "else" algorithm will run.
            {
                for(i = 0; i < A && j < strlen(message); i++){ // Fill top to bottom for X amount of rails then exit loop.
                    grid[i][j] = message[j]; // Fill in the text.
                    j++;
                }
            }
            else
            {
                for(i = A-2; i > 0 && j < strlen(message); i--){ // Fill in the array bottom to top leaving the letter in the last rail
                    grid[i][j] = message[j]; // Fill in the text.
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
    }else{
    printf("Please input a valid key");
    }
        return;
}

/*
*inputs/outputs: The inputs are: the pointer to the message which is read for decryption, cipherText pointer displays the worked output, length is not used in my program and is just there to meet spec, A variable holds the key.
*return value: void
*function operation: Decrypts text using the rail fence cipher algorithm
*function limitation: The key has to be an integer and be more than 1
*/
void railFenceDecryption(char *message, char *deCipherText, int length, int A){
        char grid[A][strlen(message)]; //string length is columns and number of rails is rows
        int i = 0, j = 0;

        printf("Key is: %d\n", A);

        //creating empty grid
        for(i = 0; i < A; i++){
            for(j = 0; j < strlen(message); j++){
                grid[i][j] = 0;
            }
        }

        int cnt = 0;
        j = 0;
        //filling the grid with -1 in place of the encrypted text indexes
        if (A > 1){
        while(j < strlen(message)){
            if(cnt % 2 == 0)
            {
                for(i = 0; i < A && j < strlen(message); i++)
                {
                    grid[i][j] = -1;
                    j++;
                }
            }
            else
            {
                for(i = A-2; i > 0 && j < strlen(message); i--)
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
                for(i = 0; i < A && j < strlen(message); i++)
                {
                    deCipherText = grid[i][j];
                    printf("%c", deCipherText);
                    j++;
                }
            }
            else{
                for(i = A-2; i > 0 && j < strlen(message); i--)
                {
                    deCipherText = grid[i][j];
                    printf("%c", deCipherText);
                    j++;
                }
            }
            cnt++;
        }
    }else{
    printf("Please input a valid key");
    }
return;
}
/*
*inputs/outputs: The inputs are: the pointer to the message which is read for encryption or decryption, cipherText pointer displays the worked output, length is not used in my program and is just there to meet spec, A and B variables hold the key.
*return value: void
*function operation: Encrypts and Decrypts text using the 2 level rail fence cipher algorithm
*function limitation: A is more than B and B is more than 1
*/
void twoLevelRailFence(char *message, char *cipherText, int length, int A, int B, int dir){
        // Declaring the "rail" grid with appropriate size.
        char grid[A][strlen(message)]; //string length is columns and number of rails is rows
        int i = 0, j = 0;

        //creating empty grid
        for(i = 0; i < A; i++){
            for(j = 0; j < strlen(message); j++){
                grid[i][j] = 0;
            }
        }
        printf("Key A(Rails) is: %d\nKey B(Height) is: %d\n", A, B);

        int cnt = 0;
        j = 0;
        if(A > B && B > 1){//only gonna work if conditions are met

            if(dir == 0){ //encryption

                while(j < strlen(message)){

            if(cnt % 2 == 0) // Even count will initiate the "top to bottom" algorithm ie the first for loop, therefore when odd the "else" algorithm will run.
            {
                //Fills 0 rails to A-1 rails
                for(i = 0; i < A && j < strlen(message); i++){ // Fill top to bottom for X amount of rails then exit loop.
                    grid[i][j] = (int)message[j]; // Fill in the text.
                    j++;
                }
                //Fill from A-2 rail up to B rail
                for(i = A-2; i > ((A-1) - B)  && j < strlen(message); i--){ //(A-2) (leave the last letter from bottom), ((A-1) - B)(Go up to height)
                    grid[i][j] = (int)message[j]; // Fill in the text.
                    j++;
                }
            }
            else
            {
                // Fill from B+1 rail back down to A-1 rail
                for(i = ((A-B) + 1); i < (A-1) && j < strlen(message); i++){
                    grid[i][j] = (int)message[j]; // Fill in the text.
                    j++;
                }
                // Fill in the array bottom to top
                for(i = A-1; i > 0 && j < strlen(message); i--){
                    grid[i][j] = (int)message[j]; // Fill in the text.
                    j++;
                }
            }
                cnt++;
        }

            //printing out cipher text by reading left to right; top to bottom.
            for(i = 0; i < A; i++){
                for(j = 0; j < strlen(message); j++){
                    if(grid[i][j] != 0){ // Where not zero in grid print the message
                        cipherText = grid[i][j];
                        printf("%c", cipherText);
                    }
                }
            }


    }else if(dir == 1){//decrypt

        if(A > B && B > 1){ //only gonna work if conditions are met

                while(j < strlen(message)){
            //same algorithm as encryption but instead of filling with message, it fills with -1 at the correct indexes
            if(cnt % 2 == 0) // Even count will initiate the "top to bottom" algorithm ie the first for loop, therefore when odd the "else" algorithm will run.
            {

                for(i = 0; i < A && j < strlen(message); i++){
                    grid[i][j] = -1; // Fill in the text.
                    j++;
                }
                for(i = A-2; i > ((A-1) - B) && j < strlen(message); i--){
                    grid[i][j] = -1; // Fill in the text.
                    j++;
                }
            }
            else
            {

                for(i = ((A-B) + 1); i < (A-1) && j < strlen(message); i++){
                    grid[i][j] = -1; // Fill in the text.
                    j++;
                }

                for(i = A-1; i > 0 && j < strlen(message); i--){
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
                    if(grid[i][j] != 0){//where grid is non zero fill with message
                        grid[i][j] = (int)message[k];
                        k++;
                }
            }
        }
        cnt = 0;
        j = 0;
        while(j < strlen(message)){
            //Reads the message not top to bottom left to right rather according to algorithm
            if(cnt % 2 == 0) // Even count will initiate the "top to bottom" algorithm ie the first for loop, therefore when odd the "else" algorithm will run.
            {

                for(i = 0; i < A && j < strlen(message); i++){
                    cipherText = grid[i][j];
                    printf("%c", cipherText);
                    j++;
                }
                for(i = A-2; i > ((A-1) - B) && j < strlen(message); i--){
                    cipherText = grid[i][j];
                    printf("%c", cipherText);
                    j++;
                }
            }
            else
            {

                for(i = ((A-B) + 1); i < (A-1) && j < strlen(message); i++){
                    cipherText = grid[i][j];
                    printf("%c", cipherText);
                    j++;
                }

                for(i = A-1; i > 0 && j < strlen(message); i--){
                    cipherText = grid[i][j];
                    printf("%c", cipherText);
                    j++;
                }
            }
                cnt++;
        }
    }

//writing to file???
    //writing the decrypted text to a file
    //FILE * output;
    //output = fopen("decryptedText2Level.txt", "w");
    //fprintf(output, );
    //fclose(output);


        }else{
                printf("Wrong input, please input either 0 for encryption or 1 for decryption");
        }
return;
    }else{
    printf("Please input the valid keys");
    }
}
