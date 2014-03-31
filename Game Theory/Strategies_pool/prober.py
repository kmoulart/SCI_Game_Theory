# memory[0] = global state (0 = DCC, 1 = tit_for_tat, 2 = all_d)
# memory[1] = state for dcc
# memory[1] = nb coop in move 2 and 3 from opponent

if memory == None:
	memory = [0, 0, 0]
	last_move = 1

if memory[0] == 0:
	if memory[1] == 0:
		coop = 0
	else:
		coop = 1

	memory[1] = memory[1] + 1
	
	if memory[1] > 1:
		memory[2] += last_move

	if memory[1] == 3:
		if memory[2] == 2:
			memory[0] = 2
		else:
			memory[0] = 1

else:
	if memory[0] == 2: # all d
		coop = 0
	else:
		if memory[0] == 1: # tit_for_tat
			coop = last_move