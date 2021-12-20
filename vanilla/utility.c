#include <utility.h>

/*Utility function to print polynomials from coefficient array in a human-readable format*/
u32 polynomial_print(u32 *a, u32 LEN)
{
    int i;
    for(i=LEN-1; i>=0; i--)
    {
        if(a[i]!=0)
        {
            if(i==0)
            {  
                printf("%d",a[i],i);    
            }
            else
            {
                if(a[i]!=1)
                {
                    printf("%dx^%d+ ",a[i],i);
                }
                else
                {
                    printf("x^%d+ ",i);
                }
            }
        }
    }
    printf("\n");
}