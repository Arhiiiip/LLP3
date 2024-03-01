import pandas as pd

def check_str_quotes(s):
	for i in range(2, len(s)-1):
		if(s[i] == "'"):
			print(s)
			return 1
	return 0

def spaceless_str(s):
	rets = ""
	for i in s:
		if(i != " " and i != "."):
			rets += i
	return rets


ccode_id = {}

data1 = pd.read_csv("export.csv")
outfile = open("out.txt", "w+")
data2 = pd.read_csv("export(1).csv")

print(data1)
print(data2)

size_of_data1 = data1.shape[0]
size_of_data2 = data2.shape[0]

id1 = 0

nbrackets = 0

for i in range(size_of_data1):
	line = data1.loc[i]

	ccode_id[line[0]] = id1
	id1+=1

	
	query = "add_vertex(\'vertex\', \'smth\', "
	for j in range(0, 6):
		
		if j == 0:
			nbrackets += check_str_quotes(line[j])
			query += spaceless_str(line[j])
			query += ", 'smth', "
			continue
		if j == 1:
			query += str(line[j])
			query += ", 'smth', "
			continue
		if j == 2:
			query += str(line[j])
			query += ", 'smth', "
			continue
		if j == 3:
			query += str(line[j])
			query += ", 'smth', "
			continue						
		if j == 4:
			nbrackets += check_str_quotes(line[j])
			query += spaceless_str(line[j])
			query += ", 'smth', "
			continue
		if j == 5:
			nbrackets += check_str_quotes(line[j])
			query += spaceless_str(line[j])
			query += ");\n"
			continue
	outfile.write(query)
	#print(query)
print(nbrackets)
nbrackets = 0

for i in range(size_of_data2):
	line = data2.loc[i]

	query = "add_vertex(\'vertex\', \'vid\', "
	for j in range(0, 6):
		
		if j == 0:
			query += str(ccode_id[line[j]])
			query += ", 'smth', "
			continue
		if j == 1:
			nbrackets += check_str_quotes(line[j])
			query += spaceless_str(line[j])
			query += ", 'smth', "
			continue
		if j == 2:
			query += str(line[j])
			query += ", 'smth', "
			continue
		if j == 3:
			query += str(line[j])
			query += ", 'smth', "
			continue						
		if j == 4:
			query += str(line[j])
			query += ", 'smth', "
			continue
		if j == 5:
			nbrackets += check_str_quotes(line[j])
			query += spaceless_str(line[j])
			query += ");\n"
			continue
	outfile.write(query)
	#print(query)

print(nbrackets)
