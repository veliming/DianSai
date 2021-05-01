from math import sin, pi,floor

mylog = open('sin.h', mode = 'a',encoding='utf-8')
COL = 0
for i in range(1,51):
    print("const uint16_t Sin" + str(i) + "[]={",file=mylog)
    j = round(2000/i)
    for k in range(0, j):
        print("%4d,"%(round((sin((k/j)*2*pi)+1)*1860+188)),file=mylog,end='')
        COL = COL + 1
        if COL == 10:
            COL = 0
            print('\n',file=mylog,end='')
    COL = 0
        # if k+1 < (j+1)/4:
        #     print(str( round((sin((k/j)*2*pi)+1)*2048) )+ ",",file=mylog)
        # if k+1 >= (j+1)/4 and k+1 < (j+1)/2:
        #     print(str( round((sin((   floor((j+1)/2)-k   /j)*2*pi)+1)*2048) )+ ",",file=mylog)
        # if k+1 >= (j+1)/2 and k+1 < (j+1)*3/4:
        #     print(str( round((sin((k/j)*2*pi)+1)*2048) )+ ",",file=mylog)
        # if k+1 >= (j+1)*3/4:
        #     print(str( round((sin((   floor((j+1)*3/2)-k            /j)*2*pi)+1)*2048) )+ ",",file=mylog)
    print("};",file=mylog)

# print("const uint16_t *Sin[]={",file=mylog)
# for i in range(1,51):
#     print("Sin" + str(i) + ",",file=mylog)
# print("};",file=mylog)
mylog.close()
