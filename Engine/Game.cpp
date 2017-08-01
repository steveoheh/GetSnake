/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 2,2 }),
	goal(rng, brd, snake)

	//Test Test Test
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if(wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		Started = true;
	}

	if (!gameIsOver && Started==true)
	{

		if (wnd.kbd.KeyIsPressed(VK_UP) && direction != 's')
		{
			delta_loc = { 0,-1 };
			direction = 'w';
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN) && direction != 'w')
		{
			delta_loc = { 0,1 };
			direction = 's';
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT) && direction != 'd')
		{
			delta_loc = { -1,0 };
			direction = 'a';
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && direction != 'a')
		{
			delta_loc = { 1,0 };
			direction = 'd';
		}
		
		++snakeMoveCounter;
	
		if (snakeMoveCounter >= snakeMovePeriod)
		{
			snakeMoveCounter = 0;
			const Location next = snake.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) ||  snake.IsInTile(next))
			{
				gameIsOver = true;
			}

			else
			{
				const bool eating = next == goal.GetLocation();

				if (eating)
				{
					snake.Grow();
					
				}

				snake.Moveby(delta_loc);
				if (eating)
				{
					goal.Respwan(rng, brd, snake);
				}
			}
		}
		++snakeSpeedupCounter;

		if (snakeSpeedupCounter >= snakeSpeedupPeriod)
		{
			snakeSpeedupCounter = 0;
		
			// returns the max of snakemoveperiod - 1 OR the min (value 4)
			snakeMovePeriod = std::max(snakeMovePeriod-1, snakeMovePeriodmin);
			
		}
	}
}

void Game::ComposeFrame()
{
	if (!Started)
	{
		SpriteCodex::DrawTitle(290, 225, gfx);
	}
	else
	{
		
		snake.Draw(brd);
		goal.Draw(brd);
		brd.DrawBorder();
		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(350, 265, gfx);
		}
	}
}
