int main(){
  int j = 10, z = 120;
  int i = 2;
  i &= 20 + j;
  i |= 20 + i + z;
  return i;
}
