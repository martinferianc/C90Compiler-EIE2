const signed* f(){
  return -1;
}

int main()
{
  const unsigned int i = f();
  return i;
}
