/*The following encoder implements Reed-Solomon Code: RS(144,128) where symbol size is 1 byte. The code can correct upto 8 errors that are NOT known ahead of time*/
#include <decoder.h>

/*Evaluate encoded polynomial at powers of GF(256) generator*/
u32 calculate_syndromes(u32 encoded[N])
{
    int i,j;
    for(j=0; j<N-K; j++)
    {
        syndromes[j] = encoded[0];
        u32 x_term = get_alogx()[j+1]; 
        for(i=1; i<N; i++)
        {
            syndromes[j] = add(syndromes[j],multiply(encoded[i],x_term));
            x_term = multiply(x_term,get_alogx()[j+1]);
        }
    }
    return 1;
}

/*Guess (n-k)/2 error locations out of n. Current implementation is dummy and considers first n-k/2 symbols as errors*/
u32 guess_errors(u32 guessed_errors[N])
{
    int i;
    for(i=0; i<(N-K)/2; i++)
    {
        guessed_errors[i] = 1;
    }

    for(i=(N-K)/2; i<N; i++)
    {
        guessed_errors[i] = 0;
    }
}

/*Checks whether all syndromes are zero or not after receiving data from Xilinx decoder. If yes, decoding is successful else do full RS decoding*/
u32 verify_errors(u32 encoded[N])
{
    calculate_syndromes(encoded);

    for(int i =0; i<N-K; i++)
    {
        if(syndromes[i]!=0)
        {
            return 0;
        }
    }
    return 1;
}

