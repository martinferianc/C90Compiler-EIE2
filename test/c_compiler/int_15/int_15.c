int main(){
  int j = 10;
  int i = 2;
  i += (i + j);
  i -= 4 * i;
  i <<= (7+i);
  i >>= 3 ^ 5;
  i *= ((i + j) >> 3)/7;
  i /= 3;
  return i;
}
