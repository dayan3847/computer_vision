import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    K = np.loadtxt('./data/K.txt', delimiter=' ')
    iK = np.loadtxt('./data/iK.txt', delimiter=' ')

    print('K:', K)
    print('iK:', iK)
