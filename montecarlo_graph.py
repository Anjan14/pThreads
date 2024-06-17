import matplotlib.pyplot as plt

# Data for Time vs. Number of Threads
threads = [1, 2, 4, 8]
time_for_threads = [0.001681, 0.000897, 0.000538, 0.000644]

# Data for Time vs. Number of Sample Points (example data)
sample_points = [200000, 400000, 800000, 1600000]
time_for_samples = [0.000188, 0.000509, 0.000522, 0.000970]

# Plot Time vs. Number of Threads
plt.figure(figsize=(10, 5))
plt.plot(threads, time_for_threads, marker='o', linestyle='-', color='b')
plt.title('Time vs. Number of Threads')
plt.xlabel('Number of Threads')
plt.ylabel('Time (seconds)')
plt.grid(True)
plt.savefig('time_vs_threads.png')
plt.show()

# Plot Time vs. Number of Sample Points
plt.figure(figsize=(10, 5))
plt.plot(sample_points, time_for_samples, marker='o', linestyle='-', color='r')
plt.title('Time vs. Number of Sample Points')
plt.xlabel('Number of Sample Points')
plt.ylabel('Time (seconds)')
plt.grid(True)
plt.savefig('time_vs_samples.png')
plt.show()