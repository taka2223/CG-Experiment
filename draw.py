import matplotlib.pyplot as plt

x1 = [5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
yDDA = [0.015421, 0.045512, 0.10467, 0.191734, 0.346649, 0.540821, 0.738749, 0.903885, 1.08745, 1.29382, 1.51789]
yBrese = [0.015533, 0.04742, 0.108773, 0.2011, 0.354793, 0.562825, 0.778136, 0.956008, 1.15537, 1.37628, 1.62307]

x2 = [10, 100, 300, 500, 700, 900]
y1 = [0.009089, 0.015915, 0.037266, 0.055925, 0.081818, 0.09398]

plt.rcParams['font.sans-serif'] = ['KaiTi']
plt.subplot(121)
plt.plot(x1, yDDA, label='time DDA', linewidth=3, color='r', marker='o', markerfacecolor='blue', markersize=12)
plt.plot(x1, yBrese, label='time Breseham', linewidth=3, color='g', marker='*', markerfacecolor='blue', markersize=12)
plt.xlabel('直线数量 单位：k ')
plt.ylabel('消耗时间 单位:s')
plt.legend()
plt.title("DDA 与 Breseham 算法的比较")

plt.subplot(122)
plt.plot(x2, y1, label='time with different Δx', linewidth=3, color='r', marker='o', markerfacecolor='blue',
         markersize=12)
plt.xlabel('x坐标的差值')
plt.ylabel("消耗时间")
plt.title("不同的ΔX与扫描转换时间的关系")
plt.show()
