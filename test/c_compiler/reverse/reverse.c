int main()
{
    int n, reversedNumber = 0, remainder;

    n = 100;

    while(n != 0)
    {
        remainder = n%10;
        reversedNumber = reversedNumber*10 + remainder;
        n /= 10;
    }

    return reversedNumber;
}
