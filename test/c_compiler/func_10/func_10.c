int f (int d, int p){
  return d;
}

int main(){
  int a = 5;
  a = f(a,7) + f(a,9);
  return a;
}
