﻿#include "BoardLayout.h"

const char BoardLayout::AsciiBoard[Height][Width] = 
{
	"                              ",
	" ^------------>^---------->^- ",
	" |............||............| ",
	" |.^-->.^--->.||.^--->.^-->.| ",
	" |#|  |.|   |.||.|   |.|  |#| ",
	" |.<--v.<---v.<v.<---v.<--v.| ",
	" |..........................| ",
	" |.^-->.^>.^------>.^>.^-->.| ",
	" |.<--v.||.<-->^--v.||.<--v.| ",
	" |......||....||....||......| ",
	" <---->.|<--> || ^--v|.^----v ",
	"      |.|^--v <v <-->|.|      ",
	"      |.||          ||.|      ",
	"      |.|| ^--~~--> ||.|      ",
	"  ----v.<v |      | <v.<----  ",
	" r     .   |      |   .     l ",
	"  ---->.^> |      | ^>.^----  ",
	"      |.|| <------v ||.|      ",
	"      |.||          ||.|      ",
	"      |.|| ^------> ||.|      ",
	" ^----v.<v <-->^--v <v.<----> ",
	" |............||............| ",
	" |.^-->.^--->.||.^--->.^-->.| ",
	" |.<->|.<---v.<v.<---v.|^-v.| ",
	" |#..||................||..#| ",
	" <->.||.^>.^------>.^>.||.^-v ",
	" ^-v.<v.||.<-->^--v.||.<v.<-> ",
	" |......||....||....||......| ",
	" |.^----v<-->.||.^--v<---->.| ",
	" |.<--------v.<v.<--------v.| ",
	" |..........................| ",
	" <--------------------------v ",
	"                              "
};