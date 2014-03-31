def sum(tab):
	result = 0
	for index, i in enumerate(tab):
		result += i
	return result

if last_move == None:
	memory = [1, 1]
	last_move = 1

if last_move + sum(memory) >= 2:
	coop = 0
else:
	coop = 1

memory[0] = memory[1]
memory[1] = last_move