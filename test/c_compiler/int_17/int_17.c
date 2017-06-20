int main(){
  int j = 10;
  int i = 2;
  i &= 20 + j;
  i |= 20 + i + i;
  ++i;
  i++;
  --i;
  i--;
  return i;
}
