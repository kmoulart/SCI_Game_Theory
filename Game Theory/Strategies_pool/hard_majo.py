if last_move == None:
	memory = 1
	last_move = 0

if last_move == 0:
	memory -= 1
else:
	memory += 1

if memory > 0:
	coop = 0
else:
	coop = 1