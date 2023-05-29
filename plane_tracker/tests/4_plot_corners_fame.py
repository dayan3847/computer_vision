import numpy as np
import matplotlib.pyplot as plt


def plot_mat(mat: np.ndarray, label: str, *color: str):
    plt.plot(mat[:, 0], mat[:, 1], color=color[0])
    plt.plot(mat[1:, 0], mat[1:, 1], 'o', label=label, markersize=3, color=color[1] if len(color) > 1 else color[0])
    plt.plot([mat[0, 0]], [mat[0, 1]], 'h', label=f'{label} first', markersize=10,
             color=color[2] if len(color) > 2 else color[0])


if __name__ == '__main__':
    data_original_corners_m = np.loadtxt('./data/originalCornersM.txt', delimiter=' ')

    i_frame_corners_m = np.loadtxt('./data/f/iFrameCornersM.txt', delimiter=' ')
    i_frame_i_k_corners_m = np.loadtxt('./data/f/iFrame_iK_cornersM.txt', delimiter=' ')

    plt.figure()

    plot_mat(data_original_corners_m, 'original_corners_m', 'red')

    # plot_mat(i_frame_corners_m, 'i_frame_corners_m', 'gray')
    plot_mat(i_frame_i_k_corners_m, 'i_frame_i_k_corners_m', 'orange')

    plt.legend()
    plt.grid()
    plt.axis('equal')
    plt.show()
