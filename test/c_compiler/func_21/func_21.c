int l(){
  return 12;
}


int f(int p){
  if (p<=14){
    return 1;
  } else {
    return 10 + l();
  }
}

int main(){
    int a;
    a = 200;
    for (a = 0; a<123; a++){
      a+= f(a);
      int b;
      while (a<20){
        ++a;
      }
    }
    return a;
}
