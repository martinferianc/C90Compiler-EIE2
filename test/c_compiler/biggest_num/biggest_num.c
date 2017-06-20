int main()
{
    int n1 = 10;
    int n2 = 20;
    int n3 = 30;

    if(n1>=n2 && n1>=n3)
        return n1;
    else if (n2>=n1 && n2>=n3)
        return n2;
    else
        return n3;

    return 0;
}
