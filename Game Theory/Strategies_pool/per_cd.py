if memory == None:
	memory = 0
	coop = 1
else:
	if memory == 0:
		coop = 1
	else:
		coop = 0

memory = (memory + 1) % 2