//
//  solvessudoku.cpp
//  SudokuSolver
//
//  Created by Spencer Kitchen on 2/5/16.
//  Copyright © 2016 Spencer Kitchen. All rights reserved.
//
#include <string>
#include <iostream>
#include <algorithm>
#include "SudokuGrid.h"

using namespace std;
void prettyPrint(SudokuGrid board);
//=======================================================
int main(int argc, char *argv[]) {
    string puzzle;
    //string puzzle = argv[1];                    // for xcode
    cin >> puzzle;
    
    // provided by assignment
    if (puzzle.length() != 9*9 || !all_of(puzzle.begin(), puzzle.end(),[](char ch) {
        return ch == '.' || ('1' <= ch && ch <= '9');
    })) {
        cerr << "bogus puzzle!" << endl;
        exit(1);
    }
    SudokuGrid board = SudokuGrid(puzzle);      // make board
    prettyPrint(board);                         // print board
    std::cout<<"\n";
 
    board.deduce(board);                        // deduce board
    prettyPrint(board);                         // print deduce
    std::cout<<"\n";
   
    if (board.solveSudoku(board) == true) {
        prettyPrint(board);                     // print solved board
    }else
        printf("I did not solve this puzzle");
    
    return 0;
}
//=============================================================
// prints out the board in a sudoku format
//
void prettyPrint(SudokuGrid board){
    for (int i = 0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (j<9) {
                if (board.number(i, j) == 0) {
                    std::cout <<". ";
                } else
                    std::cout <<board.number(i, j)<<" ";
            }
            if (j==2 || j==5 ) {
                std::cout <<"| ";
            }
        }
        std::cout <<"\n";
        if (i == 2 || i == 5) {
            std::cout <<"------+-------+------\n";
        }
    }
}
//----------------------------------------------------


