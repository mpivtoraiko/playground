#from typing import TypeAlias

import copy
from enum import IntEnum

class Dims(IntEnum):
    R: int = 0
    C: int = 1

#type Board = list[list[Board | None]]  # since 3.12
type Cell = tuple[int, int]
type Board = dict[Cell, None] # map of queen locations (for fast lookup)


class Problem:
    
    def __init__(self, board_size: int): #, queens: list[Cell] | None):
        self.board_size: int = board_size
        # self.board: Board = {}  
        # if queens is not None:
        #     for cur_cell in queens:
        #         self.board[cur_cell] = None

    def __search(self, board: Board, offset: str) -> int:
        ''' Runs through the branch-and-bound search looking for ways to add n queens 
            to the board. Returns the number of queens it was able to place. 
        '''
        #print(f"{offset}board: {list(board.keys())}")
        solutions = [] # an accumulator for the number of solutions at this level
        # place a queen where we can and branch out to add another queen
        for row_idx in range(self.board_size):
            for col_idx in range(self.board_size):
                cur_cell = (row_idx, col_idx)
                if cur_cell in board:
                    continue # cell taken already, can't add

                # check if this cell is shootable from the existing queen locations
                if self.__cell_in_danger(board, cur_cell):
                    continue # it's shootable, can't add

                # this cell is feasible, so we place a queen there and explore the new
                # board arrangement
                board[cur_cell] = None # add the queen
                #print(f"{offset}adding {cur_cell}")
                val = self.__search(copy.deepcopy(board), offset + "  ")
                if len(val) == 0: 
                    # no further solutions found with this board, this is a leaf
                    # node, so count it as a final arrangement
                    solutions.append(list(board.keys()))
                    #print(f"{offset}now solutions: {solutions}")
                else:
                    solutions += val

                # we explored the cur_cell placement, now remove it, so we explore others
                board.pop(cur_cell)

        #print(f"{offset}returning {len(solutions)} solutions")
        return solutions


    def search(self) -> int:
        board = {}
        solutions = self.__search(board, "")
        print(f"Found {len(solutions)} solutions:")
        # for cur_sol in solutions:
        #     print(*cur_sol)


    def test_cell(self, cell: Cell) -> bool:
        return self.__cell_in_danger(cell)

    def __check_limits(self, cell: Cell) -> bool:
        if cell[Dims.R] < 0 or cell[Dims.R] >= self.board_size or \
           cell[Dims.C] < 0 or cell[Dims.C] >= self.board_size:
           return False
        return True

    def __cell_in_danger(self, board: Board, cell: Cell) -> bool:
        ''' Checks if a particular cell is shootable for any of the existing queens.
        '''
        if not self.__check_limits(cell):
            return False

        for cur_queen in board.keys():
            if cur_queen[Dims.R] == cell[Dims.R] or cur_queen[Dims.C] == cell[Dims.C] or \
               abs(cur_queen[Dims.R] - cell[Dims.R]) == abs(cur_queen[Dims.C] - cell[Dims.C]):
               return True
        return False


class NQueens:
    def __init__(self, board_size: int):
        self.board_size: int = board_size
        #self.num_queens = self.board_size ^ 2
        #self.root_node = Board(board_size, None)

    def solve(self):
        root_node = Board(self.board_size, None)
        num_queens: int = root_node.search()
        

def test_tree_node() -> None:
    problem: Problem = Problem(10)#, [(4, 4)])
    board: Board = {(4, 4): None}
    cell_list: list[Cell] = [(0, 0), (2, 3), (5, 5), (0, 8), (0, 9), (0, 7), (7, 5), (3, 2), (4, 4), (10, 20)]
    for cur_cell in cell_list:
        print(f"{cur_cell}: {problem.test_cell(cur_cell)}")


if __name__ == "__main__":
    #test_tree_node()

    problem: Problem = Problem(6)
    problem.search()
