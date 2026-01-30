#include <stdio.h>
#include <string.h>
#include <time.h> 

void audit_password(const char* wordlist_path, const char* user_input) {
    printf("Starting audit using: %s\n", wordlist_path);
    
    FILE* file = fopen(wordlist_path, "r");
    if (!file) {
        printf("Error: Could not find the wordlist file at %s\n", wordlist_path);
        printf("Check if the path is correct and the file exists.\n");
        return;
    }

    char buffer[256];
    int is_compromised = 0;
    long line_count = 0;
    

    clock_t start_time = clock();

    while (fgets(buffer, sizeof(buffer), file)) {
        line_count++;
        
       
        buffer[strcspn(buffer, "\r\n")] = 0; 

        
        if (strcmp(buffer, user_input) == 0) {
            is_compromised = 1;
            break;
        }
    }

  
    clock_t end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    if (is_compromised) {
        printf("\n[!] SECURITY ALERT: This password was found in the wordlist!\n");
        printf("Found on line: %ld\n", line_count);
    } else {
        printf("\n[+] SUCCESS: Password not found in the wordlist after checking %ld lines.\n", line_count);
    }

    printf("Search completed in %.4f seconds.\n", time_taken);

    fclose(file);
}

int main() {
    char user_password[256];
    
    
    const char* my_path = "/home/noxbot/Desktop/rockyou.txt";
    
    printf("--- Cybersecurity Password Auditor ---\n");
    printf("Enter a password to check: ");
    
   
    if (scanf("%255s", user_password) == 1) {
        audit_password(my_path, user_password);
    }

    printf("\nPress Enter to exit...");
    getchar(); 
    getchar(); 
    
    return 0;
}
