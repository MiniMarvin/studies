import random

for i in range(1, 100):
    print("1 " + str(i))

quit()

arr = [0]*10000
for i in arr:
    i = 0

for i in range(10000):
    u = (int) (random.random()*10)
    u = u%2 + 1
    k = (int) (random.random()*10000)
    if(u == 1 and arr[k] == 0):
        arr[k] = 1
        print(str(u) + " " + str(k))
        pass
    elif u != 1:
        print(str(u) + " " + str(k))
        pass
    
    