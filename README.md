# 🖥️ Linux Resource Monitor - Visual Panel

An open-source project to **visualize real-time system resource usage** on **Linux**.  
This monitor provides a clear and detailed overview of system activity: **CPU**, **GPU**, **RAM**, **disks**, **network**, and more.

---

## 🎯 Objective

Build a **visual panel** (CLI or simple GUI) to:
- Display **per-core CPU usage**
- Show **GPU load** (NVIDIA/AMD - planned support)
- Monitor **RAM** and **swap** usage
- Track **network** activity (upload / download)
- View **disk** status (usage and I/O)
- And more to come: temperature, processes, system alerts, etc.

---

## 🚀 Installation

```bash
git clone https://github.com/bosota-the-boron/ui/
cd linux-resource-monitor
make
./panel

```
🛠️ Usage

Run the executable ./panel in your terminal to launch the monitoring interface.

The program displays:

    Total CPU usage as a percentage bar

    Per-core CPU usage bars with live updating every 0.5 seconds

Use Ctrl+C to quit the program.
🧩 How It Works

    Reads CPU statistics from /proc/stat on Linux.

    Calculates CPU usage by comparing CPU time counters at two intervals.

    Uses ncurses for a responsive, colored text interface.

    Visualizes CPU load with horizontal bars, where the length and color indicate usage intensity.

📂 Code Structure

    main.c
    The program entry point. Initializes the UI, reads CPU stats periodically, computes usage, and updates the display.

    processor.c / processor.h
    Functions to parse /proc/stat and calculate CPU usage percentages, both total and per-core.

    ui.c / ui.h
    Manages the terminal UI with ncurses, including bar rendering, colors, and screen refreshing.

📝 Development Notes

    CPU stats are cumulative counters, so usage is calculated based on the difference between two reads.

    Total CPU usage displayed is the average of all cores’ usages, ensuring intuitive results.

    The UI uses green bars to represent active CPU time visually.

    Designed to be lightweight and extendable for monitoring additional system resources.

🤝 Contribution

Contributions, bug reports, and feature requests are welcome!
Please open an issue or submit a pull request on GitHub.
🛠️ Usage

Run the executable ./panel in your terminal to launch the monitoring interface.

The program displays:

    Total CPU usage as a percentage bar

    Per-core CPU usage bars with live updating every 0.5 seconds

Use Ctrl+C to quit the program.
🧩 How It Works

    Reads CPU statistics from /proc/stat on Linux.

    Calculates CPU usage by comparing CPU time counters at two intervals.

    Uses ncurses for a responsive, colored text interface.

    Visualizes CPU load with horizontal bars, where the length and color indicate usage intensity.

📂 Code Structure

    main.c
    The program entry point. Initializes the UI, reads CPU stats periodically, computes usage, and updates the display.

    processor.c / processor.h
    Functions to parse /proc/stat and calculate CPU usage percentages, both total and per-core.

    ui.c / ui.h
    Manages the terminal UI with ncurses, including bar rendering, colors, and screen refreshing.

📝 Development Notes

    CPU stats are cumulative counters, so usage is calculated based on the difference between two reads.

    Total CPU usage displayed is the average of all cores’ usages, ensuring intuitive results.

    The UI uses green bars to represent active CPU time visually.

    Designed to be lightweight and extendable for monitoring additional system resources.

🤝 Contribution

Contributions, bug reports, and feature requests are welcome!
Please open an issue or submit a pull request on GitHub.

📜 License

This project is licensed under the MIT License — see the LICENSE file for details.
🙏 Acknowledgments

Thanks to the open-source community and all contributors for supporting Linux system monitoring tools!

---

If you want, I can also help you generate a `Makefile` or add sections on building from source, troubleshooting, or examples. Just ask!


