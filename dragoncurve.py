from turtle import *
color('red')
rule=['f','x']
prev=['f','x']
ans=[]
x_app = ['x','+','y','f','+']
y_app = ['-','f','x','-','y']

for iter in range(7):
    ans = []
    for i in prev:
        if(i=='x'):
            ans+=x_app
        elif(i=='y'):
            ans+=y_app
        else:
            ans.append(i)
    prev = ans

#print(ans)

for i in range(0,len(ans)):
    if(ans[i] == '+'):
        right(90)
    elif(ans[i] == '-'):
        left(90)
    elif(ans[i] == 'f'):
        forward(20)

done()