int f(int x, int y){
  if ((x==0) || (y==0))
    return 1;
  else
    return f(x-1+x,y-1)+1;
}


int main(){
    int i;
    i = f(f(20,10),f(1,1)) + f(1,2);
    return i;
}
