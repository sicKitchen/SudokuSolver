//
//  main.cpp
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
//-------------------------------------------------------
// XXX
//=======================================================
int main(int argc, char *argv[]) {
    string puzzle;
    //string puzzle = argv[1];
    cin >> puzzle;
    
    //int puzzleLength = puzzle.length();
    //std::cout << puzzleLength << "\n";
    if (puzzle.length() != 9*9 || !all_of(puzzle.begin(), puzzle.end(),[](char ch) {
        return ch == '.' || ('1' <= ch && ch <= '9');
    })) {
        cerr << "bogus puzzle!" << endl;
        exit(1);
    }
    //for (int i =  0; i<puzzleLength; i++) {
    //    std::cout << puzzle[i];
    //}
    //std::cout << "\n";
    
    // XXX
    SudokuGrid board = SudokuGrid(puzzle);
    prettyPrint(board);
    
    //board.setPencil(0, 0, 5);
    
    
    //board.autoPencil(board);
    board.solveSudoku(board);
    //std::cout<<"//----------------------\n\n";
    prettyPrint(board);
    
    return 0;
}

//=============================================================
void prettyPrint(SudokuGrid board){
    for (int i = 0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (j<9) {
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










