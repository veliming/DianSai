from math import sin, pi,floor

mylog = open('sin.h', mode = 'a',encoding='utf-8')
COL = 0
print("const uint16_t sin[]={",file=mylog)
for i in range(0,1680):
    print("%4d"%round( (sin((i/1680)*2*pi)+1)*1840+188 ),file=mylog,end=',')
    COL = COL + 1
    if COL == 10:
        COL = 0
        print('\n',file=mylog,end='')
print("};",file=mylog)

# 500K -> 5000
# 