int main(){
  int* i;
  int* p;
  int l = 20;
  int d = 7;
  i = &d;
  p = i;
  *p = 123;
  return d+d+l + *p + *i;
}
