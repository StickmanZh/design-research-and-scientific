import numpy as np
import tkinter as tk
import os

def main():
    window = tk.Tk()
    window.mainloop()

if __name__ == "__main__":
    global reader, writer
    reader = open('are-female-hurricanes-deadlier-than-male-hurricanes/data/data.txt', 'r')
    main()
    reader.close()
