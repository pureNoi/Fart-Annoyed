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
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float DeltaTime);
	void DrawWall();
	void DrawBrickArray();
	void DrawPaddle();
	void DrawBall();
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
	static constexpr float BrickSpreadingAreaSizeX = 500.0f;
	static constexpr float BrickSpreadingAreaSizeY = 200.0f;
	static constexpr float BrickSpreadingAreaOffsetX = (Graphics::ScreenWidth - BrickSpreadingAreaSizeX) / 2.0f;
	static constexpr float BrickSpreadingAreaOffsetY = 100.0f;
	static constexpr float WallThickness = 20.0f;
	static constexpr Color WallColor = Colors::LightGray;
	static constexpr float PaddleWidth = 200.0f;
	static constexpr float PaddleHeight = 20.0f;
	static constexpr float PaddleStartPositionX = (Graphics::ScreenWidth - PaddleWidth) / 2.0f;
	static constexpr float PaddleStartPositionY = 550.0f;
	static constexpr float PaddleMovingSpeed = 480.0f;
	static constexpr Color PaddleColor = Colors::Red;
	static constexpr float BallStartPositionX = PaddleStartPositionX + PaddleWidth / 2.0f;
	static constexpr float BallStartPositionY = PaddleStartPositionY;
	static constexpr float BallStartSpeedX = 300.0f;
	static constexpr float BallStartSpeedY = -300.0f;
	static constexpr float BallRadius = 10.0f;
	static constexpr Color BallColor = Colors::Yellow;
	static constexpr float DeltaTime = 1.0f / 60.0f;
	static constexpr float BrickWidth = BrickSpreadingAreaSizeX / BricksRowNum;
	static constexpr float BrickHeight = BrickSpreadingAreaSizeY / BricksColumeNum;

	Ball PlayerBall;
	Paddle PlayerPaddle;
	Brick BrickArray[BrickNum];
	Color ColorArray[ColorsNum] = {Colors::Blue, Colors::Cyan, Colors::Gray, Colors::Green, Colors::Magenta};
	/********************************/
	/*  User Variables              */
	/********************************/
};