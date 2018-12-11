import random
def generaterandomnumber(times):
    id = str(random.randint(1,9))
    for i in range(1, times):
        id += str(random.randint(0,9))
    return int(id)

#f = open("./fft-and-ifft/test.data", "w")
f = open("./test.data", "w")

for i in range(8,11):
    for j in range(40):
        a = generaterandomnumber(pow(2,i) - 16)
        b = generaterandomnumber(pow(2,i) - 259)
        c = a * b
        f.write(str(a)+"\t")
        f.write(str(b)+"\t")
        f.write(str(c)+"\t")
        f.write("\n")
f.close()

