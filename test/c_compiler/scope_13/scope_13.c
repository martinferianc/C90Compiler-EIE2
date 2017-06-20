

int main()
{
  int i = 3;
  {
    int i = 4;
    {
      int i = 2;
    }
  }
  return i;
}
