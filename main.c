#include <stdio.h>
#include <string.h>

void railFenceEncryption(char *message, char *cipherText, int length, int A);
void railFenceDecryption(char *message, char *deCipherText, int length, int A);

int main() {
        char output[1024];
        railFenceEncryption("This is a test message", output, 0, 3);
        printf("%s\n", output);
        railFenceDecryption("", output, 0, 2);
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
        while(j < strlen(message)){
            if(cnt % 2 == 0)
            {
                for(i = 0; i < A; i++){
                    grid[i][j] = (int)message[j];
                    j++;
                }
            }
            else
            {
                for(i = A-2; i > 0; i--){
                    grid[i][j] = (int)message[j];
                    j++;
                }
            }
            cnt++;
        }

        //printing the encrypted message

        for(i = 0; i < A; i++){ //testing the grid
            for(j = 0; j < strlen(message); j++){
                    if(grid[i][j] != 0){
                        cipherText = grid[i][j];
                        printf("%c", cipherText);
                    }
            }
        }
        return;
}

void railFenceDecryption(char *message, char *deCipherText, int length, int A){






return;
}
