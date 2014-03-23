#include <stdio.h>
int strcmp(const char* pStr1, const char* pStr2) {
  if (!pStr1 && !pStr2) {
    return 0;
  }
  else if (!pStr1) {
    return -1;
  }
  else if (!pStr2) {
    return 1;
  }
  else {
#if 0
    while(*pStr1 && *pStr2) {
      if (*pStr1 > *pStr2) {
        return 1;
      }
      else if (*pStr1 < *pStr2) {
        return -1;
      }
      ++pStr1;
      ++pStr2;
    }
    if (*pStr1) {
      return 1;
    }
    else if(*pStr2) {
      return -1;
    }
    else {
      return 0;
    }
#endif
    int rv = 0;
    while((rv = (*pStr1 - *pStr2) ) && *pStr1 && *pStr2) {
      ++pStr1;
      ++pStr2;
    }
    if (rv > 0) {
      rv = 1;
    }
    else if (rv < 0) {
      rv = -1;
    }
    else {}
    return rv;
  }
}

char* strcpy(char* pDst, const char* pSrc) {
  if (!pSrc || !pDst) {
    return nullptr;
  }
  char* pTmp = pDst;
  while((*pTmp++ = *pSrc++) != '\0');
  return pDst;
}

int strlen(const char* pStr) {
  int len = 0;
  if (!pStr) {
    return len;
  }
  while(*pStr++ != '\0') {
    ++len;
  }
  return len;
}

char* strcat(char* pLeftStr, const char* pRightStr) {
#if 0
  while(*pLeftStr++ != '\0');
  --pLeftStr;
#endif
  char* pTmp = pLeftStr;
  while(*pTmp) {
    ++pTmp;
  }
  while((*pTmp++ = *pRightStr++) );
  return pLeftStr;
}

int main(int /*argc*/, char */*argv*/[])
{
  char* p1 = "abc";
  char* p2 = "abc";
  const char str1[] = "abc";
  const char str2[] = "abc";
  const char* pStr1 = "abc";
  const char* pStr2 = "abc";
  printf("p1 address: 0x%x, p2 address: 0x%x, p1 == p2: %d\n", (int)p1, (int)p2, (int)(p1 == p2) );
  printf("str1 address:0x%x, str2 address: 0x%x, str1 == str2: %d\n", (int)str1, (int)str2, (int)(str1 == str2) );
  printf("pStr1 address: 0x%x, pStr2 address: 0x%x, pStr1 == pStr2: %d\n", (int)pStr1, (int)pStr2, int(pStr1 == pStr2) );
  char* pDst = new char[2048];
  printf("current destination string:%s\n", strcpy(pDst, "dst is") );
  printf("dst string len: %d, str2 len: %d\n", strlen(pDst), strlen(str2) );
  printf("current string cmp pStr2: %d\n", strcmp(pDst, pStr2) );
  printf("new concatenation string: %s\n", strcat(pDst, pStr2) );
  delete pDst;
  return 0;
}
