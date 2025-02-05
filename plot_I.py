import numpy as np
import matplotlib.pyplot as plt



d = {}
with open("I_bifurcation") as file:
    for line in file:
        key, *value = map(float, line.split())
        d[key] = value


plt.title("Bifurcation with changing I.")
for key in d:
    plt.scatter([key]*len(d[key]), d[key], c = 'black', s = 1)

plt.xlabel("I value")
plt.ylabel("interspike intervals")

plt.savefig("I_bif.png")