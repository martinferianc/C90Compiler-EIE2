int main(){
  int i = 0;
  int j = 0;
  while((i < 10)||(i%3 == 7)){
    j = 0 ; // initialization
    while((j < 10)||(j<20)){
      j++;
    }
  i++;
  }
  return i+j;
}
