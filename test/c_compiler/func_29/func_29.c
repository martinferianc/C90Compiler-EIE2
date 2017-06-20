
int g(int x);
int l();


int f(int x, int y){
  if ((x==0) || (y==0))
    return 1;
  else
    return f(x-1+x,y-1)+1 + g(x);
}

int g(int x){
  return x + l();
}

int l(){
  return 7;
}


int main(){
    int i;
    i = f(2,3) + f(1,2);
    return i;
}
