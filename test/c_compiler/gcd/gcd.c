int main()
{
    int n1, n2, i, gcd;

    n1 = 40;
    n2 = 50;

    for(i=1; ((i <= n1) && (i <= n2)); ++i)
    {
        if(n1%i==0 && n2%i==0)
            gcd = i;
    }

    return gcd;

}
