/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-05 12:29:54 
 * @Last Modified by: Stephane.Lejeune
 * @Last Modified time: 2016-12-05 13:25:56
 */

#ifndef _INPUT_HPP
#define _INPUT_HPP_

#include <iostream>
#include <stdio.h>
#include <Keyboard.hpp>

class DataBase {};

class Input
{
public:
    int InputLeftArrowKey();
    int InputRightArrowKey();
    int InputUpArrowKey();
    int InputDownArrowKey();
    int InputEscKey();

   private:
    DataBase    &_db;

public:
    Input(DataBase &);
    void    update(void); 
};

#endif /* !_INPUT_HPP_ */