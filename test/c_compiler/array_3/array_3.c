int main()
{
    int i;
    int arr[5];

    arr[0] = 2;
    arr[1] = -2;
    arr[3] = 7;
    arr[4] = 8;
    arr[2] = 9;

    for(i = 1; i < 5; ++i)
    {
       if(arr[0] < arr[i]){
           arr[0] = arr[i];
         }
    }
    return arr[0];
}
