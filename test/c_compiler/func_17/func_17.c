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

int main(){
    int a;
    a = 200;
    return d(123+21,5) + f(20);
}
