if memory == None:
	memory = 0
	last_move = 1

if last_move == 0:
	memory = 1
	coop = 0
else:
	if memory > 0:
		memory = 0
		coop = 0
	else:
		coop = 1