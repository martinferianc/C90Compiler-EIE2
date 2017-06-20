int main()
{
  int i, j, temp;
  int a[5];
  a[0] = 2;
  a[1] = -2;
  a[3] = 7;
  a[4] = 8;
  a[2] = 9;
   for (i = 0; i < (5 - 1); ++i)
   {
        for (j = 0; j < 5 - 1 - i; ++j )
        {
             if (a[j] > a[j+1])
             {
                  temp = a[j+1];
                  a[j+1] = a[j];
                  a[j] = temp;
             }
        }
   }
   return a[1];

}
