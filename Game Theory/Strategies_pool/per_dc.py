if memory == None:
	memory = 0
	coop = 0
else:
	if memory == 0:
		coop = 0
	else:
		coop = 1

memory = (memory + 1) % 2