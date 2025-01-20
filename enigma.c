#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define NUM_ROTORS 8


/* Array of rotors */
const char* enigma_rotors[NUM_ROTORS+1] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ", //0
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ", //1
    "AJDKSIRUXBLHWTMCQGZNPYFVOE", //2
    "BDFHJLCPRTXVZNYEIWGAKMUSQO", //3
    "ESOVPZJAYQUIRHXLNFTGKDCMWB", //4
    "UKLBEPXWJVFZIYGAHCMTONDRQS", //5
    "JPGVOUMFYQBENHZRDKASXLICTW", //6
    "NZJHGRCXMYSWBOUFAIVLPEKQDT", //7
    "FKQHTLXOCBJSPDZRAMEWNIUYGV"  //8
};


/* A help print function to printf 2D-array for testing*/
void printf2d(int **arr, int num){
    printf("The result is : \n");
    for (int i =0; i< num; i++){
        for(int j =0; j< ALPHABET_SIZE; j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    printf ("\n");
}

/* A help function to check if the char is alphabet*/
int isLetter(char a){
    if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')){
        return 1;
    }
    return 0;
}

/*
 * Convert a space-separated string of rotor indices into
 * an integer array of rotor indices
 *
 * @param rotor_ind_str   Space-separated string of rotor indices
 * @param num_rotors      Number of rotors provided in the string
 * @return                Integer array of rotor indices
 */
int* parse_rotor_indices(char* rotor_ind_str, int num_rotors) {
    // TODO
    if (num_rotors > NUM_ROTORS){
        printf("The rotors number is worng.\n");
        exit(1); // For testing. return -1 does not work. error in num_rotors
    }
    int* temp = malloc(num_rotors * sizeof(int));
    if (temp == NULL){
        return NULL; //Failed to allocte memory for some reason.
    }

    int i = 0; 
    int j = 0; // index for result int array.

    while(rotor_ind_str[i] != '\0'){
        if (rotor_ind_str[i] !=' '){
            temp[j] = rotor_ind_str[i] - '0'; //char to int
            j++;
        }
        i++;
    }
    return temp;
}

/*
 * Create a 2D array of integers where
 * each row represents a rotor
 *
 * @param rotors          Integer array of rotor indices
 * @param num_rotors      Number of rotors provided
 * @return                2D array where each row represents a rotor
 */
int** set_up_rotors(int* rotors, int num_rotors) {
    // TODO
    if (num_rotors > NUM_ROTORS){
        printf("The rotors number is worng.\n");
        return NULL;
    }
    int** rotNo = (int**)malloc(num_rotors * sizeof(int*));
    if (rotNo == NULL){
        return NULL;
    }

    for (int i = 0; i< num_rotors; i++){
        rotNo[i] = (int*)malloc(ALPHABET_SIZE * sizeof(int));

        for(int j = 0; j < ALPHABET_SIZE; j++){
            rotNo[i][j] = enigma_rotors[rotors[i]][j] - 65;
        }
    }
    return rotNo;
}


/*
 * Rotate each rotor to the right by the
 * given number of rotations
 *
 * @param rotor_config   2D array of rotors
 * @param rotations      Number of rotations
 * @param num_rotors     Number of rotors provided
 */
void rotate_rotors(int** rotor_config, int rotations, int num_rotors) {
    // TODO
    if (rotations >= ALPHABET_SIZE) {
        rotations = rotations % ALPHABET_SIZE; //get the number of rotates
    }
    if (num_rotors > NUM_ROTORS){
        printf("The rotors number is worng.\n");
        exit(1); //For testing. num number error
    }
    
    //printf("The rotations is %d.\n", rotations);

    for(int i = 0;i<num_rotors;i++){
        for(int j =0; j <rotations; j++){
            int temp;
            temp = rotor_config[i][ALPHABET_SIZE-1];

            for (int k = 0; k<= ALPHABET_SIZE; k++){
                rotor_config[i][ALPHABET_SIZE-k] = rotor_config[i][ALPHABET_SIZE-k-1];
            }
            rotor_config[i][0] = temp;
        }
    }
}

/*
 * Encrypt the given message
 *
 * @param message        Message to encrypt
 * @param rotor_config   2D array of rotors
 * @param num_rotors     Number of rotors provided
 * @return               Encrypted message
 */
char* encrypt(char *message, int** rotor_config, int num_rotors) {
    // TODO
    if (num_rotors > NUM_ROTORS){
        printf("The rotors number is worng.\n");
        exit(1); //For testing.
    }


    for (int i = 0; i< num_rotors; i++){

        for (int j = 0; message[j] != '\0'; j++){

            // call the help function to check
            if(isLetter(message[j])){ 
                // lowercase to upper
                if(message[j]>= 'a' && message[j] <= 'z') {
                    message[j] = message[j] - ('a' - 'A');
                }
                int index = message[j] - 'A'; //char message to int
                message[j] = rotor_config[i][index] + 'A'; //int to ascii char
            }
        }
    }
    return message;
}

/*
 * Decrypt the given message
 *
 * @param message        Message to decrypt
 * @param rotor_config   2D array of rotors
 * @param num_rotors     Number of rotors provided
 * @return               Decrypted message
 */
char* decrypt(char *message, int** rotor_config, int num_rotors) {
    // TODO
    if (num_rotors > NUM_ROTORS){
        printf("The rotors number is worng.\n");
        exit(1);
    }

    for (int i = 0; i < num_rotors; i++){

        for(int j =0; message[j] != '\0'; j++){

            if(isLetter(message[j])){
                if(message[j]>= 'a' && message[j] <= 'z') {
                    message[j] = message[j] - ('a' - 'A');
                }
                int index;
                for(int k = 0; k< ALPHABET_SIZE; k++){
                    //find the corresponding index
                    index = message[j] - 'A';
                    if(rotor_config[i][k] == index){ 
                        index = k;
                        message[j] = 'A' + index; //update char in message
                        break;
                    }
                }

            }
        }
    }
    return message;
}

/*
 * Format of command line input:
 * ./enigma e "JAVA" 3 "1 2 4" 0
 * 
 *    e    - mode (e for encrypt, d for decrypt)
 * "JAVA"  - message
 *    3    - number of rotors to use
 * "1 2 4" - indices of rotors to use
 *    0    - number of rotations of the rotors
 */
int main(int argc, char* argv[]) {
    // TODO
    if (argc != 6) {
        printf("Command format error. Please follow ./enigma mode message number_rotors indices_rotors number_rotations.\n");
        return -1;
    }

    char *mode = argv[1];
    char *message = argv[2];
    int num_rotors= atoi(argv[3]); //char to int
    char *indices_rotors = argv[4];
    int num_rotations = atoi(argv[5]);
    
    int *indicesNumber = parse_rotor_indices(argv[4], num_rotors);
    int **rotos2d = set_up_rotors(indicesNumber,num_rotors);
    rotate_rotors(rotos2d, num_rotations, num_rotors);


    if (strcmp(mode,"d") == 0){ 
        printf("Decrypted message: %s\n", decrypt(message, rotos2d, num_rotors));

    }else if(strcmp(mode,"e") == 0){
        printf("Encrypted message: %s\n", encrypt(message, rotos2d, num_rotors));

    }else{
        printf("Mode command error.\n");
        return -1;
    }
    free(indicesNumber);
    for (int i = 0; i < num_rotors; i++) {
        free(rotos2d[i]);
    }
    free(rotos2d);
}
