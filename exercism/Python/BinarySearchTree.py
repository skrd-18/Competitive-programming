from dataclasses import dataclass
from typing import Optional


@dataclass
class Node:
    value: int
    left: Optional["Node"] = None
    right: Optional["Node"] = None

    def preorder(self, node=None) -> None:
        if node is None:
            node = self  # Start from the current node if no node is passed

        # Debugging output to verify the traversal is called
        print(f"Visiting Node: {node.value}")

        if node.left:
            self.preorder(node.left)
        if node.right:
            self.preorder(node.right)


# Construct the binary tree
root = Node(1)
root.left = Node(2)
root.right = Node(3)
root.left.left = Node(4)
root.left.right = Node(5)

# Debugging print for tree structure
print("Tree Root:", root.value)
print("Tree Left Child:", root.left.value)
print("Tree Right Child:", root.right.value)

# Perform preorder traversal
print("\nPreorder Traversal:")
root.preorder()
