
int factorial(int i){
  if (i<=1){
    return 1;
  } else {
    return i* factorial(i-1) + 1;
  }
}

int main(){
  int d = factorial(6);
  return d;
}
