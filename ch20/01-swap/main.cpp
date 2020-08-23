//Utterly useless program that uses a function template
//      -- from _C++20 for Lazy Programmers_

template <typename T, typename U>
void mySwap (T& arg1, U& arg2)
{
    T temp = arg2; arg2 = arg1; arg1 = temp;
}

int main ()
{
    int    i = 10  , j = 20  ;
    double m =  0.5, n =  1.5;
        
    mySwap (i, j);
    mySwap (m, n);
    mySwap (i, n); // You'll get a warning abt loss of data 
                   //   as always, but it'll work 

    return 0;
}
