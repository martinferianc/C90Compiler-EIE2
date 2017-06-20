int main(){
  int j = 10;
  int i = 2;
  i += (i + j);
  i -= 4 * i;
  i <<= (7+i);
  i >>= 3 ^ 5;
  return i;
}
