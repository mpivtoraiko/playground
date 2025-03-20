# Write a function which can transform a BST into a tree which looks like a linked list
#
#        2            ----->     1
#  1         3                        2
#                                          3
#

from typing import Final
from collections import deque


class Node:
    def __init__(self, value: int):
        self.value: int = value
        self.left: Node = None
        self.right: Node = None

    def print(self):
        left_val: str = "None"
        if self.left is not None:
            left_val = str(self.left.value)

        right_val: str = "None"
        if self.right is not None:
            right_val = str(self.right.value)
        print(f"{self.value}: {left_val}, {right_val}")


class Tree:
    def __init__(self):
        self.root: Node = None
        self.queue = deque()

    def insert(self, value: int) -> None:
        if self.root is None:
            self.root = Node(value)
        else:
            self.__insert(self.root, value)

    def print(self) -> None:
        print(f"depth: {self.get_depth()}")
        self.__print_node(self.root)

    def get_depth(self) -> int:
        if self.root is None:
            return 0
        return self.__get_depth(self.root, 1)

    def in_order(self) -> None:
        self.__in_order(self.root)

    def in_order2(self) -> None:
        self.__in_order2(self.root)

    def pre_order(self) -> None:
        self.__pre_order(self.root)

    def post_order(self) -> None:
        self.__post_order(self.root)

    def bfs(self) -> None:
        if self.root is not None:
            self.queue.append(self.root)

        iter_cnt = 0        
        while(True):
            if not self.__bfs():
                break
            iter_cnt += 1
        print(f"done in {iter_cnt} iter")


    # private
    def __insert(self, node: Node, value: int) -> None:
        assert node is not None
        if value < node.value:
            if node.left:
                self.__insert(node.left, value)
            else:
                node.left = Node(value)
        else:
            if node.right:
                self.__insert(node.right, value)
            else:
                node.right = Node(value)

    def __get_depth(self, node: Node, depth: int) -> int:
        if node is None:
            return depth
        return max(
            self.__get_depth(node.left, depth + 1),
            self.__get_depth(node.right, depth + 1),
        )

    def __print_node(self, node: Node):
        left_val: str = "None"
        if node.left is not None:
            left_val = node.left.value

        right_val: str = "None"
        if node.right is not None:
            right_val = node.right.value

        print(f"{node.value}: {left_val}, {right_val}")
        
        if node.left is not None:
            self.__print_node(node.left)

        if node.right is not None:
            self.__print_node(node.right)



    def __in_order(self, node) -> None:
        if node is None:
            return

        self.__in_order(node.left)
        node.print()
        self.__in_order(node.right)


    def __in_order2(self, node) -> None:
        if node is None:
            return

        self.__in_order2(node.right)
        node.print()
        self.__in_order2(node.left)

    def __pre_order(self, node) -> None:
        if node is None:
            return

        node.print()
        self.__pre_order(node.left)
        self.__pre_order(node.right)

    def __post_order(self, node) -> None:
        if node is None:
            return

        self.__post_order(node.left)
        self.__post_order(node.right)
        node.print()


    def __bfs(self) -> None:
        if len(self.queue) == 0:
            return False

        cur_node: Node = self.queue.popleft()
        cur_node.print()
        if cur_node.left is not None:
            self.queue.append(cur_node.left)
        if cur_node.right is not None:
            self.queue.append(cur_node.right)
        return True

# def reorder_tree(cur_node):

#     left_successor = cur_node.successors[0]
#     if left_successor.successors[0] is not None:
#         reorder_tree(left_successor)

#     if left_successor.successors[0] is None and \
#        left_successor.successors[1] is None):
#        left_successor.successors[1] = cur_node

# right_successor = cur_node.successors[1]


if __name__ == "__main__":
    input: list[int] = [5, 2, 3, 0, 4, 7, 3, 2, 1]

    tree: Tree = Tree()
    for cur_val in input:
        tree.insert(cur_val)

    #tree.print()
    #tree.in_order2()
    #tree.pre_order()
    #tree.post_order()
    tree.bfs()
