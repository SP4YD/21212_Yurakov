#pragma once

#ifndef BLOCKS_H
#define BLOCKS_H

struct Block;

const int PatternBlock1[4][4]=
{
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
};

const int PatternBlock2[4][4]=
{
    {0,0,1,0},
    {0,0,1,0},
    {0,1,1,0},
    {0,0,0,0}
};

const int PatternBlock3[4][4]=
{
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0},
    {0,0,0,0}
};

const int PatternBlock4[4][4]=
{
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,0,0}
};

const int PatternBlock5[4][4]=
{
    {0,0,1,0},
    {0,1,1,0},
    {0,1,0,0},
    {0,0,0,0}
};

const int PatternBlock6[4][4]=
{
    {0,1,0,0},
    {0,1,1,0},
    {0,1,0,0},
    {0,0,0,0}
};

const int PatternBlock7[4][4]=
{
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0}
};

Block Block1;
Block Block2;
Block Block3;
Block Block4;
Block Block5;
Block Block6;
Block Block7;


#endif // BLOCKS_H
