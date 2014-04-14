from random import randint

n = 1000000

def random_char():
    return chr(randint(ord('A'), ord('Z')))

id = 0

def create_test(s1, s2):
    global id
    id += 1
    f = open("friends.in." + str(id), "w")
    f.write(s1 + "\n")
    f.close()
    f = open("friends.out." + str(id), "w")
    f.write(s2 + "\n")
    f.close()
    

for i in range(5):
    s = ""
    for j in range(n):
        s += random_char()
    q = s
    s = s+s
    u = random_char()
    k = randint(0, n)
    s = s[:k] + u + s[k:]
    create_test(s, q)
    
create_test("A"*2000000, "IMPOSSIBLE")
create_test("A"*2000001, "A"*1000000)
create_test("ABC"*600000+"A", "NOT UNIQUE")
create_test("ABC"*600000+"B", "ABC"*300000)
create_test("A"+"ABC"*600000, "ABC"*300000)
create_test("A"*555555+"B"*555555+"A"*555555, "IMPOSSIBLE")
