import numpy as np
import matplotlib.pyplot as plt


def plot_mat(mat: np.ndarray, label: str, color: str):
    plt.plot(mat[:, 0], mat[:, 1], color=color)
    plt.plot(mat[1:, 0], mat[1:, 1], 'o', label=label, color=color, markersize=3)
    # plot the first point in green
    plt.plot([mat[0, 0]], [mat[0, 1]], 'h', label=f'{label} first', color=color, markersize=10)


if __name__ == '__main__':
    data_original_corners_m = np.loadtxt('./data/originalCornersM.txt', delimiter=' ')
    data_iK_original_corners_m = np.loadtxt('./data/iK_originalCornersM.txt', delimiter=' ')

    i_frame_corners_m = np.loadtxt('./data/iFrameCornersM.txt', delimiter=' ')
    i_frame_corners_canonical_m = np.loadtxt('./data/iFrameCornersCanonicalM.txt', delimiter=' ')
    i_frame_corners_canonical_cartesian_m = np.loadtxt('./data/iFrameCornersCanonicalCartesianM.txt', delimiter=' ')

    plt.figure()

    plot_mat(data_original_corners_m, 'original_corners_m', 'red')
    plot_mat(data_iK_original_corners_m, 'iK_original_corners_m', 'blue')

    # plot_mat(i_frame_corners_m, 'i_frame_corners_m', 'gray')
    plot_mat(i_frame_corners_canonical_m, 'i_frame_corners_canonical_m', 'orange')
    plot_mat(i_frame_corners_canonical_cartesian_m, 'i_frame_corners_canonical_cartesian_m', 'green')

    plt.legend()
    plt.grid()
    plt.axis('equal')
    plt.show()
