if last_move == None:
	memory = [1, 1]
	last_move = 1

if memory[0] > 0:
	coop = 1
	memory[0] -= 1
else:
	if last_move == 0 or memory[1] == 0:
		coop = 0
	else:
		coop = 1

memory[1] = last_move