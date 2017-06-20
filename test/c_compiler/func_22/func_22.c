int l(){
  return 12;
}


int f(int p, int d){
  if (p<=14){
    return 1;
  } else {
    return 10 + l() + d;
  }
}

int main(){
    int a;
    a = 200;
    int b;
    for (a = 0; a<123; a++){
      a+= f(a,7);
      b = f(-2,-3);
      while (a<20){
        ++a;
        break;
      }
    }
    return a+b;
}
