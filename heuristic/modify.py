header = open("head.txt", "r")
head = header.read()
header.close()

files = dict()
lengths = dict()
length = []
for i in range(1, 101):

	index = 2 * i - 1
	pad = str(index).zfill(3)
	origin_name = "instance" + pad + ".gr"


	f1 = open(origin_name, "r")

	outfile_content = head + f1.read()

	files[pad] = outfile_content
	l = len(outfile_content)
	lengths[l] = pad
	length.append(l)


	f1.close()

length.sort()

cnt = 0

mapping = open("mapping.txt", "w")
for l in length:
	pad = lengths[l]
	to_name = "ins_"+str(cnt)+".gr"
	f2 = open(to_name, "w")

	print >> f2, files[pad]
	print >> mapping, cnt, pad
	cnt += 1
	f2.close()

mapping.close()
