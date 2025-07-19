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
git clone https://github.com/your-username/linux-resource-monitor.git
cd linux-resource-monitor
make
./monitor
