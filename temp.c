#include <stdio.h>
#include <string.h>

void audit_password(const char* wordlist_path, const char* user_input) {
    FILE* file = fopen(wordlist_path, "r");
    if (!file) {
        printf("Error: Could not find the wordlist file at %s\n", wordlist_path);
        return;
    }

    char buffer[256];
    int is_compromised = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = 0; 

        if (strcmp(buffer, user_input) == 0) {
            is_compromised = 1;
            break;
        }
    }

    if (is_compromised) {
        printf("[!] SECURITY ALERT: This password is in the common wordlist!\n");
    } else {
        printf("[+] SUCCESS: Password not found in the common wordlist.\n");
    }

    fclose(file);
}

int main() {
    char user_password[256];
    
    
    printf("Enter a password to audit: ");
   
    scanf("%255s", user_password);

    audit_password("rockyou.txt", user_password);

    return 0;
}