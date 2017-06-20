int main(){
  int l;
  int* p;
  int* d;
  l = 123;
  p = &l;
  {
    p = &l;
    {
      *d = 5;
      return l;
    }
  }
}
