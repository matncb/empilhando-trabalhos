# graph for data generated in ex1/src/data_gen.c

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

import scienceplots
plt.style.use(['science', 'notebook', 'grid'])

# Read data from CSV file
data = pd.read_csv('data.csv', delimiter=' ')
n_values = data['n']
recursive_times = data['recursive_time']
iterative_times = data['iterative_time']

def plot_recusive_time():
    plt.figure(figsize=(10, 6))
    plt.plot(n_values, recursive_times, marker='o', ls = '', label='Recursive Time', color='blue')

    plt.xlabel('n (factorial Number)')
    plt.ylabel('Execution Time (seconds)')

    plt.title('factorial Recursive Execution Time')
    plt.legend()

    plt.savefig('graphics/factorial_recursive_times.png')
    plt.close()

def plot_iterative_time():
    plt.figure(figsize=(10, 6))
    plt.plot(n_values, iterative_times, marker='o', ls= '', label='Iterative Time',
                color='orange')
    
    plt.xlabel('n (factorial Number)')
    plt.ylabel('Execution Time (seconds)')

    plt.title('factorial Iterative Execution Time')
    plt.legend()

    plt.savefig('graphics/factorial_iterative_times.png')
    plt.close()

def plot_normal_scale():
    # Plotting
    plt.figure(figsize=(10, 6))
    plt.plot(n_values, recursive_times, marker='o', ls = '', label='Recursive Time', color='blue')
    plt.plot(n_values, iterative_times, marker='o', ls= '', label='Iterative Time',
                color='orange')

    plt.xlabel('n (factorial Number)')
    plt.ylabel('Execution Time (seconds)')
    plt.title('factorial Execution Time Comparison')
    plt.legend()

    plt.savefig('graphics/factorial_times.png')
    plt.close()

def plot_log_scale():
    # Plotting
    plt.figure(figsize=(10, 6))
    plt.plot(n_values, recursive_times, marker='o', ls = '', label='Recursive Time', color='blue')
    plt.plot(n_values, iterative_times, marker='o', ls= '', label='Iterative Time',
                color='orange')

    plt.yscale('log')  # Use logarithmic scale for y-axis
    plt.xlabel('n (factorial Number)')
    plt.ylabel('Execution Time (seconds, log scale)')
    plt.title('factorial Execution Time Comparison')
    plt.legend()

    plt.savefig('graphics/log_factorial_times.png')
    plt.close()

plot_iterative_time()
plot_recusive_time()
plot_normal_scale()
plot_log_scale()