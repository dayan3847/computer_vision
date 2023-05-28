import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    print('original_corners_fix.txt')
    data_original_corners = np.loadtxt('original_corners_fix.txt', delimiter=' ')
    data_iK_original_corners = np.loadtxt('iK_original_corners_fix.txt', delimiter=' ')

    plt.figure()
    # plt.plot(data_original_corners[:, 0], data_original_corners[:, 1], 'o', label='original_corners', color='yellow')
    plt.plot(data_iK_original_corners[:, 0], data_iK_original_corners[:, 1], 'o', label='iK_original_corners',
             color='blue')
    plt.legend()
    plt.show()
