"""
    @file        speedUpdate.py
    @author      Mowibox (Ousmane THIONGANE)
    @brief       Function to modify robot's speed regarding the distance from an obstacle
    @version     1.0
    @date        2024-04-28
    
"""

import matplotlib.pyplot as plt
from numpy import exp

dist_threshold = 310 # mm
tau = 25

def speedUpdate(min_distance, dist_threshold, tau):
    if 20 <= min_distance <= dist_threshold:
        return 0.0
    elif min_distance > dist_threshold:
        return float(1-exp(-(min_distance-dist_threshold)/tau))
    else:
        return
    

X = [i for i in range(750)]
S = [speedUpdate(i, dist_threshold, tau) for i in range(750)]

plt.plot(X, S, "g-")
plt.xlim(200, 550)
plt.title(f"speedUpdate function with distance threshold at {dist_threshold} and $\\tau = {tau}$")
plt.ylabel("speed_factor")
plt.xlabel("min_distance (mm)")
plt.grid()
plt.show()