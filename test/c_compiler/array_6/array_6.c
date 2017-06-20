int main()
{
    int n[ 10 ];
     int i;

     for ( i = 1; i < 10; i++ ) {
        n[ i-1+1-1 ] = i + 100;
     }

     return n[3]&&n[2];

}
