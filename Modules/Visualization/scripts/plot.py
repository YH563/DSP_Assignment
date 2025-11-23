import matplotlib.pyplot as plt
import numpy as np

class PlotManager:
    def __init__(self):
        self.fig = None
        self.axes = None
        self.current_subplot = 0
        self.title = "Default Title"

    # 创建子图
    def create_subplots(self, rows, cols):
        self.fig, self.axes = plt.subplots(rows, cols, figsize=(12, 8))
        if rows * cols > 1:
            self.axes = self.axes.flatten()
        else:
            self.axes = [self.axes]
        self.current_subplot = 0

    # 设置标题
    def set_title(self, title: str):
        self.title = title

    # 单独绘图
    def plot(self, data, color=None, label=None, sub_title=None):
       if self.axes is not None and self.current_subplot < len(self.axes):
           ax = self.axes[self.current_subplot]
           ax.clear()
           ax.plot(data, color=color, label=label)
           ax.legend(loc="upper right")
           ax.grid()
           ax.set_title(sub_title if sub_title is not None else "")
           self.current_subplot += 1
    
    # 展示绘图结果
    def show(self):
        if self.fig is not None:
            self.fig.suptitle(self.title, y=0.08)
            plt.tight_layout()
            plt.subplots_adjust(bottom=0.15)
            plt.show()
