int main()
{
    int number, originalNumber, remainder, result = 0;

    number = 120;

    originalNumber = number;

    while (originalNumber != 0)
    {
        remainder = originalNumber%10;
        result += remainder*remainder*remainder;
        originalNumber /= 10;
    }

    if(result == number)
        return 1;
    else
        return 0;

    return 0;
}
