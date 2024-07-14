
def main():
	record = {}
	with open("output.txt", "r") as f:
		for line in f:
			tokens = line.split()
			if len(tokens) == 0:
				continue
			philo_no = int(tokens[1])
			if tokens[2] == "is" and tokens[3] == "eating":
				if philo_no in record:
					record[philo_no] += 1
				else:
					record[philo_no] = 1

	for i in sorted(record.keys()):
		print("Philo", i, "ate", record[i], "times")

if __name__ == '__main__':
	main()