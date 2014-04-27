
int findDuplicateNumIn1000(int (&a)[1000]) {
  int duplicate = a[0];
  for (int i = 1; i < 1000; ++i) {
    duplicate ^= (a[i]^i);
  }
  return duplicate;
}
