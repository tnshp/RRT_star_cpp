import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import os 
import numpy as np

def plot_points(x_values, y_values, connections = [], obstacles = [], path =[]):
    fig, ax = plt.subplots()

    x_path = []
    y_path = []
    for i in path:
        x_path.append(x_values[int(i)])
        y_path.append(y_values[int(i)])


    ax.scatter(x_values, y_values, color='blue', marker='.')
    ax.scatter(x_values[0], y_values[0], color='yellow', marker='o')
    for i in range(int(len(obstacles)/ 2)):
        # Define the coordinates and dimensions of the rectangular area to shade
        x_min, x_max = obstacles[2*i][0], obstacles[2*i + 1][0]
        y_min, y_max = obstacles[2*i][1], obstacles[2*i + 1][1]
        width = x_max - x_min
        height = y_max - y_min

        # Create a Rectangle patch and add it to the plot to shade the area
        rect = patches.Rectangle((x_min, y_min), width, height, linewidth=1, edgecolor='none', facecolor='red', alpha=0.3)
        ax.add_patch(rect)

    for connection in connections:
        x1, y1 = x_values[connection[0]], y_values[connection[0]]
        x2, y2 = x_values[connection[1]], y_values[connection[1]]
        ax.plot([x1, x2], [y1, y2], color='gray', linewidth=1)

    ax.plot(x_path,y_path, color = 'red', linewidth = 5)
    ax.set_xlabel('X-axis')
    ax.set_ylabel('Y-axis')
    ax.set_title('Plotting Points')

    plt.grid(False)
    plt.show()

script_dir = os.path.dirname(os.path.relpath(__file__))
point_path = os.path.join(script_dir, "RRT_star_points.txt")
obs_path = os.path.join(script_dir, 'RRT_star_environment.txt')

df = pd.read_csv(point_path, header= None)
obstacles_data = pd.read_csv(obs_path, header=None)

data = df.values
X = df.iloc[:,0].values
Y = df.iloc[:,1].values
idx = df.iloc[:,2].values

obstacles = obstacles_data.iloc[2:, :].values

#np.insert(X, 0, 150)
#p.insert(Y,0, 150)
print(data)
print(data.shape)

connections = [(0,1)]
for i in range(1,len(idx) - 1):
    x = (i  , int(idx[i]))
    connections.append(x )
 

current_point = 300
prev_point = 0
    

path = []
while(current_point != -1):
    path.append(current_point)
    #print(current_point)
    current_point = idx[int(current_point)]

x_path = []
y_path = []
for i in path:
    x_path.append(X[int(i)])
    y_path.append(Y[int(i)])


#print(path)
#print(df)

if __name__ == "__main__":
    # Sample data for x and y coordinates of points
    # Call the plot_points function to plot the points
   plot_points(X,Y, obstacles = obstacles, connections=connections, path=path) 