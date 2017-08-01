#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{


}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int off_x = x + borderWidth+borderPadding;
	const int off_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim(loc.x*dimension + off_x+cellPadding, loc.y*dimension + off_y+cellPadding, dimension-cellPadding*2, dimension-cellPadding*2, c);

}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

int Board::GetDimension() const
{
	return dimension;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	if (loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;

	const int bottom = top + (2 * borderPadding) + (2 * borderWidth) + (dimension*height);
	const int right = left + (2 * borderPadding) + (2 * borderWidth) + (dimension*width);

	//TOP
	gfx.DrawRect(left, top, right, top + borderWidth, borderColor);
	//LEFT
	gfx.DrawRect(left, top+borderWidth, left+borderWidth, bottom-borderWidth, borderColor);
	//RIGHT
	gfx.DrawRect(right-borderWidth, top+borderWidth, right, bottom - borderWidth, borderColor);
	//BOTTOM
	gfx.DrawRect(left, bottom-borderWidth, right, bottom, borderColor);

}
