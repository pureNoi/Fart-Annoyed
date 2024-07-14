/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	void DrawBrickArray();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	static constexpr int BricksRowNum = 8;
	static constexpr int BricksColumeNum = 8;
	static constexpr int ColorsNum = 5;
	static constexpr int BrickNum = BricksColumeNum * BricksRowNum;
	static constexpr int BrickSpreadingAreaSizeX = 500;
	static constexpr int BrickSpreadingAreaSizeY = 200;
	static constexpr int BrickSpreadingAreaOffsetX = (Graphics::ScreenWidth - BrickSpreadingAreaSizeX) / 2;
	static constexpr int BrickSpreadingAreaOffsetY = 100;
	const float BrickWidth = BrickSpreadingAreaSizeX / BricksRowNum;
	const float BrickHeight = BrickSpreadingAreaSizeY / BricksColumeNum;
	Brick BrickArray[BrickNum];
	Color ColorArray[ColorsNum] = {Colors::Blue, Colors::Cyan, Colors::Gray, Colors::Green, Colors::Magenta};
	/********************************/
	/*  User Variables              */
	/********************************/
};