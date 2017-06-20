int main()
{
    int n;
    int count = 0;

    n = 1204;

    while(n != 0)
    {
        n /= 10;
        ++count;
    }

    return count;
}
