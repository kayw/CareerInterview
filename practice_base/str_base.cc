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
  }
}
