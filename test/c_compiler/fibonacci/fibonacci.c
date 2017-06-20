int main()
{
    int t1 = 0, t2 = 1, nextTerm = 0, n;

    n = 7;

    // displays the first two terms which is always 0 and 1
    nextTerm = t1 + t2;

    while(nextTerm <= n)
    {
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }
    return nextTerm;
}
