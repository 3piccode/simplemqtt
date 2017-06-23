# Track memory leak

from collections import defaultdict
from gc import get_objects

test1 = defaultdict(int);
test2 = defaultdict(int);

for i in get_objects():
    test1[type(i)] += 1

# leak
leakage = [[x] for x in range(100)

for i in get_objects():
    test2[type(i)] += 1

#debug leak
print([(i, test2[i] - test1[i]) for i in after if test2[i] - test1[i]])
