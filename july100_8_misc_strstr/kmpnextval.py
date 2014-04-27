#list=('g','c','a','g','a','g','a','g')
list=('a','b','c','a','b','c','a','a')
pre=[-1]
k = -1
for q in range(1, len(list)):
    while(k>-1 and list[k+1] != list[q]):
        k = pre[k]
    if(list[k+1] == list[q]):
        k = k+1
    pre.append(k)

for a in pre:
    print a

print "nextval"
pre=[-1]
k = -1
m = len(list)
i = 0
while(i <m):
    while (k > -1 and list[i] != list[k]):
      k =pre[k];
    i= i+1
    if(i == m):
      break
    k=k+1
    if (list[i] == list[k]):
        pre.append(pre[k])
    else:
        pre.append(k)

for a in pre:
    print a

print "next"
#http://www.cnblogs.com/10jschen/archive/2012/08/19/2646120.html
#http://www.slyar.com/blog/kmp-next-nextval.html
i = 0
j = -1
pre=[-1]
while(i < m):
    if(j==-1 or list[i] == list[j]):
        i = i+1
        j = j+1
        pre.append(j)
    else:
        j = pre[j]
for a in pre:
    print a
