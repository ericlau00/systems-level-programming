#include <stdio.h>
#include <stdlib.h>

int main()
{
    //part i
    unsigned int i = 261;
    int *p = &i;
    char *c = &i;

    printf("part ii\n");
    printf("\taddress: %p, value: %u\n", p, *p);
    printf("\taddress: %p, value: %u\n", c, *c);

    printf("\npart iii\n");
    printf("\ti as a hex: %x\n", i);
    printf("\ti as a uint: %u\n", i);

    printf("\npart iv\n");
    int byte;
    for (byte = 0; byte < sizeof(unsigned int); byte++)
    {
        printf("\tbyte %hhu\n", c + byte);
    }
    printf("\ti: %u\n", i);

    printf("\npart v\n");
    for (byte = 0; byte < sizeof(unsigned int); byte++, c++)
    {
        printf("\taddress: %p\n", c);
        printf("\ti as a hex: %x\n", i);
        printf("\ti as a uint: %u\n", i);
    }

    printf("\n\tpost modification bytes\n");
    for (byte = 0; byte < sizeof(unsigned int); byte++)
    {
        printf("\tbyte %hhu\n", c + byte);
    }

    printf("\npart vi\n");
    for (byte = 0; byte < sizeof(unsigned int); byte++, p++)
    {
        printf("\taddress: %p\n", p);
        printf("\ti as a hex: %x\n", i);
        printf("\ti as a uint: %u\n", i);
    }

    printf("\n\tpost modification bytes\n");
    for (byte = 0; byte < sizeof(unsigned int); byte++)
    {
        printf("\tbyte %hhu\n", p + byte);
    }
    return 0;
}
