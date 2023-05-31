import numpy as np
import matplotlib.pyplot as plt


def plot_mat(mat: np.ndarray, label: str, *color: str):
    plt.plot(mat[:, 0], mat[:, 1], color=color[0])
    plt.plot(mat[1:, 0], mat[1:, 1], 'o', label=label, markersize=3, color=color[1] if len(color) > 1 else color[0])
    plt.plot([mat[0, 0]], [mat[0, 1]], 'h', label=f'{label} first', markersize=10,
             color=color[2] if len(color) > 2 else color[0])


if __name__ == '__main__':
    data_original_corners_m = np.loadtxt('./data/originalCornersM.txt', delimiter=' ')
    corners_found_meter = np.loadtxt('./data/f/corners_found_meter.txt', delimiter=' ')

    plt.figure()

    plot_mat(data_original_corners_m, 'original_corners_m', 'red')
    plot_mat(corners_found_meter, 'corners_found_meter', 'orange')

    plt.legend()
    plt.title('Esquinas detectadas premultiplicadas por iK')
    plt.xlabel('meter')
    plt.ylabel('meter')
    plt.grid()
    plt.axis('equal')
    plt.show()
