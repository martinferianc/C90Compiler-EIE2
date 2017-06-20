int d(int p,int k){
  if (p<=1){
    return 1;
  } else {
    return d(p-1,k);
  }
}

int f(int p){
  if (p<=1){
    return 1;
  } else {
    return d(p-1,p);
  }
}

int m(){
  return 7;
}

int main(){
    int a;
    a = 200;
    return d(123+21,a) + f(a) + m();
}
