import numpy as np

def f(x,y):
	return y

def g1(x):
	return x**3

def g2(x):
	return x**3

def g3(y):
	return 0

def g4(y):
	return 1

def poisson(xl, xr, yb, yt, M, N):
	m = M + 1
	n = N + 1
	mn = m * n
	h = (xr - xl) / M
	h2 = h * h
	k = (yt - yb) / N
	k2 = k * k
	x = [i * h + xl for i in range(0,M+1)]
	y = [i * h + yb for i in range(0,N+1)]
	A = np.zeros((mn, mn))
	b = np.zeros((mn))
	for i in range(1,m-1):
		for j in range(2,n):
			A[i + (j - 1) * m, i-1 + (j-1) * m] = A[i + (j-1) * m, i + 1 + (j-1) * m] = 1 / h2
			A[i + (j - 1) * m, i + (j - 1) * m] = -2 / h2 - 2 / k2
			A[i + (j - 1) * m, i + (j - 2) * m] = A[i + (j - 1) * m, i + j * m] = 1 / k2
			b[i + (j - 1) * m] = f(x[i], y[j-1])
	for i in range(m):
		j = 1
		A[i + (j - 1) * m, i + (j - 1) * m] = 1
		b[i + (j - 1) * m] = g1(x[i])
		j = n
		A[i + (j-1) * m, i + (j-1) * m] = 1
		b[i + (j - 1) * m] = g2(x[i])
	for j in range(2,n):
		i = 0
		A[i + (j - 1) * m, i + (j - 1) * m] = 1
		b[i + (j - 1) * m] = g3(y[j-1])
		i = m-1
		A[i + (j - 1) * m, i + (j - 1) * m] = 1
		b[i + (j - 1) * m] = g4(y[j-1])
	v = np.linalg.solve(A, b)
	w = np.reshape(v, (m, n))
	return w

n = 9
m = 9

W = poisson(0,1,0,1,n,m)
h1 = 1.0 / n
h2 = 1.0 / m
for i in range(6):
	for j in range(6):
		print(i * h1, j * h2, W[i][j])
