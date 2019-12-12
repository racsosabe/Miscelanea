import numpy as np
import scipy.integrate

def f(x):
	return 1 + x

def solve(n):
	h = 1 / n
	F = np.zeros((n-1,1))
	for ii in range(n-1):
		F[ii] = scipy.integrate.quad(lambda x: (1 + x) * (x - ii * h + h) / h , ii * h - h, ii * h)[0] + scipy.integrate.quad(lambda x : (1 + x) * (- (x - ii * h - h) / h), ii * h, ii * h + h)[0]
	k = 1
	K = np.zeros((n-1,n-1))
	for ii in range(n-1):
		K[ii,ii] = 2 * k / h
	for ii in range(n-2):
		K[ii, ii+1] = -k / h
		K[ii+1, ii] = -k / h
	u = np.linalg.solve(K,F)
	return u

n = 10
x = [0 + i * (1.0 / n) for i in range(n+1)]
w = solve(n)
u = [0]
for _ in w:
	u.append(_[0])
u.append(0)
for i in range(len(x)):
	print(x[i], u[i])
