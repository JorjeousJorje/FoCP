from EulerSolver import EulerSolver

import numpy as np
import matplotlib.pyplot as plt
import pyqtgraph as pg
from matplotlib.widgets import Slider
from itertools import chain

def analytical_solution(t: np.ndarray, cond: tuple):
    alpha: float = cond[1] + cond[0]
    beta: float = -2 * cond[1] - cond[0]
    u: np.ndarray = 2 * alpha * np.exp(-t) + beta * np.exp(-1000 * t)
    v: np.ndarray = -alpha * np.exp(-t) - beta * np.exp(-1000 * t)
    return np.stack([u, v])


def main():
    t = np.linspace(0, 10, 1000)
    mat = np.array([
        [998., 1998.],
        [-999., -1999.],
    ])
    cond = [1., 1.]
    sols = EulerSolver.solve_explicit(t, mat, np.asfarray(cond)), EulerSolver.solve_implicit(t, mat, np.asfarray(cond)), analytical_solution(t, np.asfarray(cond))

    fig, axes = plt.subplots(1, 3)
    fig.subplots_adjust(bottom=0.25)
    fig.set_size_inches(14, 8)
    ut_lines = []
    vt_lines = []
    uv_lines = []


    axes[0].set_title("u(v)")
    axes[1].set_title("u(t)")
    axes[2].set_title("v(t)")


    uv_lines.append(axes[0].plot(sols[0][0], sols[0][1], label="implicit", color='r')[0])
    uv_lines.append(axes[0].plot(sols[1][0], sols[1][1], label="explicit", color='cyan')[0])
    uv_lines.append(axes[0].plot(sols[2][0], sols[2][1], label="ground truth", color='black')[0])
    
    ut_lines.append(axes[1].plot(t, sols[0][0], label="implicit", color='r')[0])
    ut_lines.append(axes[1].plot(t, sols[1][0], label="explicit", color='cyan')[0])
    ut_lines.append(axes[1].plot(t, sols[2][0], label="ground truth", color='black')[0])


    vt_lines.append(axes[2].plot(t, sols[0][1], label="implicit", color='r')[0])
    vt_lines.append(axes[2].plot(t, sols[1][1], label="explicit", color='cyan')[0])
    vt_lines.append(axes[2].plot(t, sols[2][1], label="ground truth", color='black')[0])

    ax_time = plt.axes([0.25, 0.15, 0.65, 0.03])
    ax_cond_u = plt.axes([0.25, 0.1, 0.65, 0.03])
    ax_cond_v = plt.axes([0.25, 0.05, 0.65, 0.03])

    allowed_n = np.concatenate([range(10, 100, 10), range(100, 1000 + 1, 100), range(1000, 10000 + 1, 1000)])
    allowed_cond = [0.1, 0.5, 1.0, 1.5, 2.0, 3.0]

    slider_cond_u = Slider(
        ax_cond_u, "u cond", min(allowed_cond), max(allowed_cond),
        valinit=1., valstep=allowed_cond,
        color='red'
    )
    slider_cond_v = Slider(
        ax_cond_v, "v cond", min(allowed_cond), max(allowed_cond),
        valinit=1., valstep=allowed_cond,
        color='blue'
    )
    
    slider_n = Slider(
        ax_time, "N", 10, 10000,
        valinit=1000, valstep=allowed_n,
        color="green"
    )

    def update(val):
        t = np.linspace(0, 10., slider_n.val)
        cond[0] = slider_cond_u.val
        cond[1] = slider_cond_v.val

        sols = EulerSolver.solve_explicit(t, mat, np.asfarray(cond)), EulerSolver.solve_implicit(t, mat, np.asfarray(cond)), analytical_solution(t, np.asfarray(cond))
        x_datas = [
            t,t,t, 
            t,t,t, 
            sols[0][0], sols[1][0],sols[2][0]
            ]
        y_datas = [
            sols[0][0],sols[1][0], sols[2][0], 
            sols[0][1],sols[1][1], sols[2][1], 
            sols[0][1],sols[1][1], sols[2][1]
            ]

        for line, x, y in zip(chain(ut_lines, vt_lines, uv_lines), x_datas, y_datas):
            line.set_xdata(x)
            line.set_ydata(y)
        
        fig.canvas.draw_idle()

    for ax in axes:
        ax.legend()

    slider_cond_u.on_changed(update)
    slider_cond_v.on_changed(update)
    slider_n.on_changed(update)

    plt.show()
    
if __name__ == "__main__":
    main()