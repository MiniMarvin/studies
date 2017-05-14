import random

a = random.randint(1, 3)

for x in xrange(1,1000):
	a = random.randint(1, 3)
	#print(str(a))
	if(a == 1):
		b = 'a'
		a = random.randint(1, 10000)
		print(b + ' ' + str(a))
	elif(a == 2):
		b = 'r'
		a = random.randint(1, 10000)
		print(b + ' ' + str(a))
	else:
		b = 'p'
		print(b)
	pass
