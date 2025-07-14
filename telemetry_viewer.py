import socket
import json
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import for 3D


def main(host="0.0.0.0", port=7000):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((host, port))

    plt.ion()
    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")
    ax.set_xlabel("X (m)")
    ax.set_ylabel("Y (m)")
    ax.set_zlabel("Z (m)")

    rocket_plot, = ax.plot([0], [0], [0], "ro", label="Rocket")
    body_plots = {}
    ax.legend()

    while True:
        data, _ = sock.recvfrom(65535)
        try:
            telem = json.loads(data.decode())
        except json.JSONDecodeError:
            continue

        pos = telem.get("position", {})
        rocket_plot.set_data([pos.get("x", 0)], [pos.get("y", 0)])
        rocket_plot.set_3d_properties([pos.get("z", 0)])

        for body in telem.get("bodies", []):
            name = body.get("name", "body")
            if name not in body_plots:
                body_plots[name], = ax.plot([body.get("x", 0)],
                                             [body.get("y", 0)],
                                             [body.get("z", 0)],
                                             "bo", label=name)
                ax.legend()
            else:
                plot = body_plots[name]
                plot.set_data([body.get("x", 0)], [body.get("y", 0)])
                plot.set_3d_properties([body.get("z", 0)])

        ax.relim()
        ax.autoscale_view()
        plt.draw()
        plt.pause(0.001)


if __name__ == "__main__":
    main()
