int fibonacci(int x){
  if (x<=1){
    return 1;
  } else {
    return fibonacci(x-1) + fibonacci(x-2);
  }
}


int main(){
    int i;
    i = fibonacci(7);
    return i;
}
