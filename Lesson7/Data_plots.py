import numpy as np
import matplotlib.pyplot as plt

#%%
file1 = "Vector_end.txt"
file2 = "Vector_middle.txt"
file3 = "Deque_end.txt"
file4 = "Deque_middle.txt"

#%%
Data1 = np.loadtxt(file1)
Data2 = np.loadtxt(file2)
Data3 = np.loadtxt(file3)
Data4 = np.loadtxt(file4)

#%%
Nve = Data1[:, 0]
Ve = Data1[:, 1]

Nvm = Data2[:, 0]
Vm = Data2[:, 1]

Nde = Data3[:, 0]
De = Data3[:, 1]

Ndm = Data4[:, 0]
Dm = Data4[:, 1]

#%%
fig, ax = plt.subplots()
ax.scatter(Nve, Ve)
plt.title("Vector to end", fontsize = 12)
plt.show()

#%%
fig, ax = plt.subplots()
ax.scatter(Nde, De)
plt.title("Deque to end", fontsize = 12)
plt.show()

#%%
fig, ax = plt.subplots()
ax.scatter(Nvm, Vm)
plt.title("Vector in the middle", fontsize = 12)
plt.show()

#%%
fig, ax = plt.subplots()
ax.scatter(Ndm, Dm)
plt.title("Deque in the middle", fontsize = 12)
plt.show()

