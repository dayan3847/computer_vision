import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    data_original_corners = np.loadtxt('./data/originalCornersMat.txt', delimiter=' ')
    data_iK_original_corners = np.loadtxt('./data/iK_originalCornersMat.txt', delimiter=' ')

    plt.figure()
    plt.plot(data_original_corners[:, 0], data_original_corners[:, 1], label='original_corners', color='yellow')
    plt.plot(data_original_corners[:, 0], data_original_corners[:, 1], 'o', label='original_corners', color='red')
    plt.plot(data_iK_original_corners[:, 0], data_iK_original_corners[:, 1], label='iK_original_corners', color='blue')
    plt.plot(data_iK_original_corners[:, 0], data_iK_original_corners[:, 1], 'o', label='iK_original_corners',
             color='black')
    plt.legend()
    plt.grid()
    plt.axis('equal')
    plt.show()
