# Save and run as generate_test_03.py in your terminal
import os

num_v = 1000
num_nodes_in_ring = 999  # Node 999 will be isolated

adj = {i: set() for i in range(num_v)}

for i in range(num_nodes_in_ring):
    prev_node = (i - 1 + num_nodes_in_ring) % num_nodes_in_ring
    next_node = (i + 1) % num_nodes_in_ring
    cross_node = (i + 500) % num_nodes_in_ring
    
    adj[i].add(prev_node)
    adj[i].add(next_node)
    adj[i].add(cross_node)

# Count unique undirected edges
total_edges = sum(len(neighbors) for neighbors in adj.values()) // 2

os.makedirs("assignment_01/testcases", exist_ok=True)
filepath = "assignment_01/testcases/bfs_test_03.txt"

with open(filepath, "w") as f:
    f.write(f"{num_v} {total_edges}\n")
    for u in range(num_v):
        neighbors = sorted(list(adj[u]))
        degree = len(neighbors)
        if degree == 0:
            f.write(f"{u} 0\n")
        else:
            neighbors_str = " ".join(map(str, neighbors))
            f.write(f"{u} {degree} {neighbors_str}\n")
    f.write("SOURCE 0\n")

print(f"Successfully generated {filepath} with {num_v} vertices and {total_edges} edges.")