from turtle import *
color('red', 'yellow')
begin_fill()
rule=['f','-','g','-','g']
prev=rule.copy()
ans=[]
rule1=['f','-','g','+','f','+','g','-','f']
rule2=['g','g']
for iter in range(4):
    ans = []
    for i in prev:
        if(i=='f'):
            ans+=rule1
        elif(i=='g'):
            ans+=rule2
        else:
            ans.append(i)
    prev = ans

print(ans)

for i in range(0,len(ans)):
    if(ans[i] == '+'):
        right(120)
    elif(ans[i] == 'f' or ans[i]=='g'):
        forward(20)
    elif(ans[i] == '-'):
        left(120)


end_fill()
done()