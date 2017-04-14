from datetime import date

def diff_dates(date1, date2):
    return abs(date2-date1).days

def diff_days(date1, date2):
    d1 = datetime.strptime(date1, "%d/%m/%Y")
    d2 = datetime.strptime(date2, "%d/%m/%Y")
    return abs((date2 - date1).days)

def main():
	for i in range(5000):
		a=raw_input()
		ar = map(int, a.split("/"))
		b=raw_input()
		br = map(int, b.split("/"))
	    #d1 = date(2013,1,1)
	    #d2 = date(2013,9,13)
		try:
			d1 = date(ar[2],ar[1],ar[0])
			d2 = date(br[2],br[1],br[0])
			pass
		except Exception, e:
			print(i)
			print(a)
			print(b)
			raise
		else:
			pass
		finally:
			pass

		result1 = diff_dates(d2, d1)
		#result1 = diff_days(d2, d1)
		#print '{} days between {} and {}'.format(result1, d1, d2)
		print('{}'.format(result1))

main()