import matplotlib.pyplot as plt
import numpy as np

male_data = [4, 3, 7, 1, 15, 5, 2, 0, 1, 12, 5, 0, 21, 3, 15, 62, 10, 3, 1, 0, 56, 1, 10, 8, 25, 15, 1, 52, 5]
female_data = [2, 1, 0, 60, 20, 20, 0, 200, 15, 1, 0, 22, 50, 0, 46, 3, 3, 5, 37, 3, 75, 6, 3, 15, 3, 256, 22, 0, 2, 0, 117, 1, 21, 5, 0, 21, 3, 4, 8, 5, 3, 1, 13, 3, 6, 9, 8, 26, 3, 8, 2, 3, 51, 7, 5, 1, 1, 62, 5, 1, 84, 41, 159]

box_plot_data = [female_data, male_data]
plt.boxplot(box_plot_data, labels = ['Female Hurricane Names', 'Male Hurricane Names'])
plt.show()