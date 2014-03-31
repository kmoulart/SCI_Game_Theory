if last_move == None:
	memory = [0,1]
	last_move = 1

if memory[1] != last_move:
	if last_move == 1:
		memory[0] += 5
	else:
		memory[0] -= 5

if memory[0] < 0:
	coop = 0
else:
	coop = 1