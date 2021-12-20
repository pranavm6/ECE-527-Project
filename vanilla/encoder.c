#include <encoder.h>
#include <utility.h>
#include <field.h>

/*Creates generator polynomial (x-a)(x-a^2)... where a is generator of GF(256)*/
u32 create_generator_polynomial()
{
    int i,j,k;

    u32 m1[N-K+1] = {0};
    u32 m2[N-K+1] = {0};

    m1[0] = get_alogx()[1];
    m2[0] = get_alogx()[2];

    m1[1] = 1;
    m2[1] = 1;

    for(k=0; k<N-K-1; k++)
    {
        u32 mult[N-K+1] = {0};
        for(i=0; i<=N-K; i++)
        {
            for(j=0; j<=N-K; j++)
            {
                if(m1[i]>0 && m2[j]>0)
                {
                    mult[i+j] = add(mult[i+j],multiply(m1[i],m2[j]));
                }
            }
        }

        for(i=0; i<=N-K; i++)
        {
            m1[i] = mult[i];
        }

        m2[1] = get_alogx()[3+k];

        polynomial_print(m1,N-K+1);
    }
    return 1;
}

/*Encodes data by multiplying with generator polynomial. Current implementation is the BCH-view of Reed Solomon codes and encoding is NOT systematic*/
u32 encode(u32 encoded[N],u32 data[K])
{
    int i,j;
    for(i=0; i<K; i++)
    {
        for(j=0; j<=N-K; j++)
        {
            encoded[i+j] = add(encoded[i+j],multiply(data[i],g16[j]));
        }
    }
}

int main()
{
    create_generator_polynomial();
}
