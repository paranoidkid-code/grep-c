#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_whole_word(const char *buffer, const char *match, size_t keyword_len) {
    if (match > buffer) {
        unsigned char before = (unsigned char)*(match - 1);
        if (isalnum(before) || before == '_') {
            return 0;
        }
    }
    unsigned char after = (unsigned char)*(match + keyword_len);
    if (isalnum(after) || after == '_') {
        return 0;
    }
    return 1;
}

void to_lower_case(char *str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        printf("Usage: grep <keyword> <filename> [flags]\n");
        return 1;
    }

    int whole_word = 0, ignore_case = 0;
    const char *keyword = NULL;
    const char *filename = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0) {
            whole_word = 1;
        } else if (strcmp(argv[i], "-i") == 0) {
            ignore_case = 1;
        } else if (keyword == NULL) {
            keyword = argv[i];
        } else if (filename == NULL) {
            filename = argv[i];
        }
    }

    if (keyword == NULL || filename == NULL) {
        printf("Usage: grep <keyword> <filename> [flags]\n");
        return 1;
    }

    size_t keyword_len = strlen(keyword);
    if (keyword_len >= 1024) {
        fprintf(stderr, "Error: Keyword exceeds maximum supported length.\n");
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file '%s'\n", filename);
        return 1;
    }

    char search_keyword[1024];
    strncpy(search_keyword, keyword, sizeof(search_keyword) - 1);
    search_keyword[sizeof(search_keyword) - 1] = '\0';
    if (ignore_case) {
        to_lower_case(search_keyword);
    }

    char buffer[1024], search_buffer[1024];
    int line_number = 1;
    int found = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        strncpy(search_buffer, buffer, sizeof(search_buffer) - 1);
        search_buffer[sizeof(search_buffer) - 1] = '\0';

        if (ignore_case) {
            to_lower_case(search_buffer);
        }

        char *match = search_buffer;
        while ((match = strstr(match, search_keyword)) != NULL) {
            if (!whole_word || is_whole_word(search_buffer, match, keyword_len)) {
                printf("Found in Line %d: \033[31m%s\033[0m", line_number, buffer);
                found = 1;
                break;
            }
            match += 1; // Advance to continue searching the remainder of the line
        }
        line_number++;
    }

    if (found == 0) {
        printf("\nUnable to find '%s' inside file '%s'\n", keyword, filename);
    }

    fclose(file);
    return 0;
}