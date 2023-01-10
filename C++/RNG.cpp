#include <iostream>
using std::rand;
using std::cout;

int D6()
{
    return (rand()%6)+1;
}

// RNG >= lo and <= hi; lo and hi are > 0 
// NOTE: srand(time(0))
int RandomNumber(int lo, int hi)
{
    // Return invalid if: hi<lo, lo<1, or hi>100
    if(hi<lo || lo<0 || hi<1)
        return -1;

    // Difference between hi and lo
    int diff = hi-lo; 

    // Random num generated
    int num = rand()%(diff+1)+lo;

    // Return random num if it's less or equal to 100
    return num;
}

int main()
{
    srand(time(0));
    cout << RandomNumber(0,6);
    return 0;
}