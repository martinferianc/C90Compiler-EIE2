int d(int p,int k){
  if (p<=1){
    return 1;
  } else {
    return d(p-1,k);
  }
}

int main(){
    int a;
    a = 200;
    return d(123+21,5);
}
