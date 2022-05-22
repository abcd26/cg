from turtle import *
color('red')
rule=['r','f','l','l','f','r']
prev=['r','f','l','l','f','r']
ans=[]
for iter in range(4):
    ans = []
    for i in prev:
        if(i=='f'):
            ans+=rule
        else:
            ans.append(i)
    prev = ans

print(ans)

for i in range(0,len(ans)):
    if(ans[i] == 'r'):
        right(45)
    elif(ans[i] == 'f'):
        forward(20)
    elif(ans[i] == 'l'):
        left(45)

done()