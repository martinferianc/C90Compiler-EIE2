int main()
{
    char c = 'd';
    c = c<<3;
    char b = 's';
    c = b +c;
    return sizeof(c) + c;
}
