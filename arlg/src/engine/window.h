#ifndef WINDOW_H_
#define WINDOW_H_
#include <curses.h>
#include <string>
#include <vector>
#include "datatype.h"
#include "painttype.h"

namespace umity {

pixeltype const Nlines = 25, Ncols = 80, Status = 3;
char const Corner = '+', Beam = '-', Pillar = '|';

using std::string;
using std::vector;

class Window final{
	WINDOW* win;
	vector<vector<dptype>> depbuf; // The depth buffer
	public:
	Window();
	~Window();
	// printstatus(line, content, st) will print content to the status line starting
	//     from (line, st)
	//     if the content is too long or the line is out of range, returns true
	//     otherwise return false
	bool printstatus(pixeltype const line, string content, pixeltype const st = 0);
	// draw(ch, ps) draws a char to the screen
	//     if the position is out of range, do nothing
	void draw(Ch ch, Pos ps);
	// draw(rec, ps) draws a rectangle to the screen
	//     if some part of the rectangle is out of range, then they are not drawn
	void draw(Rec rec, Pos ps);
	// draw(bm, ps) draws a bitmap to the screen
	//     if some part of the rectangle is out of range, then they are now drawn
	void draw(Bm bm, Pos ps);
	// refresh() refreshes current screen
	void refresh();
	// frushdepbuf() reset depbuf to be all zero.
	void frushdepbuf();
	// cls() cleans the screen but not refreshes it.
	void cls();
	// getkey() returns a key collected from the keyboard
	int getkey();
};

}
#endif
