#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_string(char arr[]);
void copy_string();
void concatenate_string();
void compare_string();
void find_char();

int main()
{
    printf("DO NOW\n");
    char *s = "hello";
    char s1[10] = "hello";
    printf("s points to: %p\n", s);
    printf("s1 points to: %p\n", s1);
    printf("address of \"hello\": %p\n", &"hello");

    copy_string();
    concatenate_string();
    compare_string();
    find_char();
    return 0;
}

void print_string(char arr[])
{
    int i;
    for (i = 0; arr[i] != '\0'; i++)
    {
        printf("%c", arr[i]);
    }
    printf("\n");
}

void copy_string()
{
    printf("\nSTRCPY");
    printf("\npre strcpy\n");
    char src[] = "source";
    printf("src points to: %p\n", src);
    printf("src value: ");
    print_string(src);

    char dest[] = "destintation";
    printf("dest points to: %p\n", dest);
    printf("dest value: ");
    print_string(dest);

    printf("\npost strcpy\n");
    strcpy(dest, src);
    printf("src points to: %p\n", src);
    printf("src value: ");
    print_string(src);
    printf("dest points to: %p\n", dest);
    printf("dest value: ");
    print_string(dest);
}

void concatenate_string()
{
    printf("\nSTRCAT");
    printf("\npre concatenate\n");
    char kit[] = "kit";
    printf("src value: ");
    print_string(kit);

    char kat[6] = "kat"; //this has to be size 6 because destination has to have enough space to contain both dest and src
    printf("dest value: ");
    print_string(kat);

    printf("\npost concatenate\n");
    strcat(kat, kit);
    printf("src value: ");
    print_string(kit);
    printf("dest value: ");
    print_string(kat);
}

void compare_string()
{
    printf("\nSTRCMP\n");
    char s2[] = "abc";
    char s3[] = "aby";
    printf("This should be less than 0: %d\n", strcmp(s2, s3));

    s2[2] = 'y';
    printf("This should be equal to 0: %d\n", strcmp(s2, s3));

    s2[2] = 'z';
    printf("This should be greater than 0: %d\n", strcmp(s2, s3));
}

void find_char() {
    printf("\nSTRCHR\n");
    char test[] = "test";
    printf("test points to: %p\n", test);
    printf("pointer of first occurance of t: %p\n", strchr(test, 't'));
    printf("pointer of first occurance of e: %p\n", strchr(test, 'e'));
    printf("pointer of first occurance of s: %p\n", strchr(test, 's'));
    printf("pointer of first occurance of a: %p\n", strchr(test, 'a'));
}