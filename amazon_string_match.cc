//http://www.mitbbs.com/article_t1/JobHunting/32633319_0_1.html
#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>
//http://www.mitbbs.com/article/JobHunting/32812761_0.html
/*
   public boolean isMultiple(String s) {
        if(s==null || s.length()==0)
            return true;
        int maxInterval = 1;
        HashMap<Character, Integer> map = new HashMap<Character, Integer>();
        char[] chs = s.toCharArray();
        for(int i=0; i<chs.length; i++){
            if(!map.containsKey(chs[i]))
                map.put(chs[i], i);
            else{
                int pre = map.get(chs[i]);
                if(maxInterval<(i-pre)){
                    maxInterval = i-pre;
                }
                map.put(chs[i], i);
            }
        }
        int length = chs.length;
        if(maxInterval==1){
            if(length%2==0 && length/2>1)
                return true;
            for(int i=3; i*i<=length; i+=2){
                if(length%i==0 && length/i>1)
                    return true;
            }
            return false;
        }
        if(length%maxInterval!=0)
            return false;
        List<String> list = new ArrayList<String>();
        for(int i=0; i<length; i+=maxInterval)
            list.add(s.substring(i, i+maxInterval));
        if(list.size()==1)
            return false;
        String pre = list.get(0);
        for(String str : list){
            if(!pre.equals(str))
                return false;
        }
        return true;
    }

bool isMultiple(const std::string& s) {
// wrong as below
  if(s.length()==0)
    return true;
  int maxInterval = 1;
  std::unordered_map<char, int> map;
  for(int i=0; i< s.length(); i++){
    const auto mapIter = map.find(s[i]);
    if(mapIter == map.end())
      map.insert(std::pair<char, int>(s[i], i));
    else{
      int pre = mapIter->second;
      if(maxInterval<(i-pre)){
        maxInterval = i-pre;
      }
      map.insert(std::pair<char, int>(s[i], i));
    }
  }
  int length = s.length();
  if(maxInterval==1){
    if(length%2==0 && length/2>1)
      return true;
    for(int i=3; i*i<=length; i+=2){
      if(length%i==0 && length/i>1)
        return true;
    }
    return false;
  }
  if(length%maxInterval!=0)
    return false;
  std::vector<std::string> list;
  for(int i=0; i<length; i+=maxInterval)
    list.push_back(s.substr(i, maxInterval));
  if(list.size()==1)
    return false;
  std::string pre = list[0];
  for(std::string str : list){
    if(pre != str)
      return false;
  }
  return true;
}
*/

/*
Test case:
"abcabcabcab" // false
"bcdbcdbcde" //false
"abcdabcd" //true
"xyzxy" //false
"aaaaaaaaaaaaaaaaaaaaa" //true
"bcdbcdbcdbcdbcdbc" //fasle
"aaaaabaaaa" //false

bcdbcdbcdebcdbcdbcde //true
*/

bool isRepeatMatch(const std::string& cmpString) {
  std::string repeater;
  int repeaterPtr = 0;
  bool matched = true;
  for (auto strIter = cmpString.begin(); strIter != cmpString.end(); ++strIter)
  {
    const char ch = *strIter; 
    if (repeater.empty() ) {
      repeater.append(1, ch);
    }
    else if (repeater[repeaterPtr] == ch) {
      repeaterPtr = ++repeaterPtr%repeater.size();
    }
    else if (repeaterPtr != 0) {
      matched = false;
      break;
    }
    else {
      repeater.append(1, ch);
    }  
  }
  if (repeater.size() == 1 || repeater.size() == cmpString.size() ) {
    matched = false;
  }
  return matched;
}

/*
发信人: purp (小狗狗， 仅次于狼), 信区: JobHunting
标  题: Re: 我也发一道A家的电面题，不难，但是跪了。。。。
发信站: BBS 未名空间站 (Sun Oct 26 19:38:30 2014, 美东)

这题用KMP吧。检查preprocess部分生产的array l 就可以了。如果是valid case.
preprocessing array 必然满足下面的几个条件：
1. l[n-1] 必须是最大值 (这个没必要专门检查,只要3满足就成);
2. s[0,...,n-l[n-1])就是repeating pattern;
3. l[n-1]/(length of the repeating pattern) >= 1;
4. l[n-1] % (length of the repeating pattern) == 0.

比如：
"abcabcabc" -> [0, 0, 0, 1, 2, 3, 4, 5, 6]
"abcdabcd"-> [0, 0, 0, 0, 1, 2, 3, 4]
几个false cases:
"bcdbcdbcdebcdbcdbcd" -> [0, 0, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 7,
8, 9]
"ababeabab"-> [0, 0, 1, 2, 0, 1, 2, 3, 4]

code 如下：
public static boolean isMultiple(String s){
        if(s == null || s.length() == 0) {
            throw new IllegalArgumentException("Bad input: input string
cannot be null or empty!");
        }
        int n = s.length();
        if(n < 4) {
            return false; //since the short string needs to have a length >=
2 and repeat at least once
        }
        int[] l = new int[n];
        int j = 0;
        l[0] = 0;
        for(int i = 1; i < n; i++) {
            while(j > 0 && s.charAt(i) != s.charAt(j)) {
                j = l[j-1];
            }
            if(s.charAt(i) == s.charAt(j)) {
                j++;
            }
            l[i] = j;
        }
        System.out.println(Arrays.toString(l));
        int len = n-l[n-1];
        return len > 1 && l[n-1]/len >= 1 && l[n-1]%len == 0;
    }
*/
// http://www.mitbbs.com/article/JobHunting/32654547_0.html
// http://www.mitbbs.com/article/JobHunting/32634011_0.html
/*

贴一个 O(n) 解法， java code 用了KMP 里的prefix function. 思路是前面有人提到
的 topcoder连接里讲解的。    
public boolean checkRepetition(String s) {
        int m = s.length();
        if(m<4) return false;
        for(int i=1;i<m;i++) {
            if(s.charAt(i)!=s.charAt(i-1)) break;
            if(i==m-1) return false;
        }
        int[] pattern = prefixFunction(s);       
        int p = pattern[m];
        while(p>1) {
            if(p%(m-p)==0) return true;
            p=pattern[p];
        }
        return false;
    }

   
    public int[] prefixFunction(String p) {
        int m = p.length();
        int [] next = new int[m+1];
        next[0]=next[1]=0;
        int k=0;
        for(int q = 2;q<=m;q++) {
            while(k>0 && p.charAt(q-1)!=p.charAt(k))
                k=next[k];
            if(p.charAt(k)==p.charAt(q-1))
                k=k+1;
            next[q] = k;
        }
        return next;
    }
*/   
bool isMultiple(const std::string& s) {
  int len = s.length();
  if (len < 4) {
    return false;
  }
  std::vector<int> l(len, 0);
  int j = 0;
  for (int i = 1; i < len; i++) {
    while(j > 0 && s[i] != s[j]) {
      j = l[j-1];
    }
    if (s[i] == s[j]) {
      j++;
    }
    l[i] = j;
  }
  for (int li : l) {
    printf("%d", li);
  }
  printf("\n");
  int p = l[len-1];
  while(p>1) {
    if (p%(len-p) == 0) {
      return true;
    }
    p = l[p-1];
  }
  return false;
}

int main(int /*argc*/, char */*argv*/[]) {
  std::vector<std::string> tests;
  tests.push_back("abcabad");
  tests.push_back("xyz");
  tests.push_back("abcdabcd");
  tests.push_back("abcdaabcd");
  tests.push_back("aaaaaaa");
  tests.push_back("abaaba");//FAILED with two pointer/solved with KMP

  for (auto vecIter = tests.begin(); vecIter != tests.end(); ++vecIter) {
    printf("%s ", vecIter->c_str());
    //if (isRepeatMatch(*vecIter) ) {
    if (isMultiple(*vecIter)) {
      printf("TRUE\n");
    }
    else {
      printf("FALSE\n");
    }
  }
  return 0;
}

//see also
//http://leetcode.com/2011/05/longest-substring-without-repeating-characters.html
