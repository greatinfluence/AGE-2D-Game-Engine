#include "window.h"
namespace umity {
Window::Window() {
	depbuf.resize(Nlines - Status);
	for(auto& z: depbuf) z.resize(Ncols);
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_BLUE, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_RED, COLOR_GREEN);
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
	cbreak();
	noecho();
	win = newwin(Nlines, Ncols, 0, 0);
	keypad(win, TRUE);
	nodelay(win, TRUE);
	for(pixeltype i = 1; i < Nlines - Status - 1; ++ i) {
		mvwaddch(win, i, 0, Pillar);
		mvwaddch(win, i, Ncols - 1, Pillar);
	}
	mvwaddch(win, 0, 0, Corner);
	for(pixeltype i = 1; i < Ncols - 1; ++ i) {
		waddch(win, Beam);
	}
	waddch(win, Corner);
	mvwaddch(win, Nlines - Status - 1, 0, Corner);
	for(pixeltype i = 1; i < Ncols - 1; ++ i) {
		waddch(win, Beam);
	}
	waddch(win, Corner);
	refresh();
}

Window::~Window() {
	delwin(win);
	endwin();
}

bool Window::printstatus(pixeltype const line, std::string content, pixeltype const st) {
	if(line >= Status) return true;
	wmove(win, Nlines - Status + line, st);
	if(content.length() >= Ncols) {
		for(pixeltype i = 0; i < Ncols - st; ++ i)
			waddch(win, content[i]);
	}
	else {
		for(auto x: content)
			waddch(win, x);
	}
	if(content.length() + st >= Ncols) {
		return printstatus(line + 1, content.substr(Ncols));
	}
	return false;
}

void Window::draw(Ch ch, Pos ps) {
	ps = ps + ch.getdiff();
	pixeltype y = getpixeltype(ps.y), x = getpixeltype(ps.x);
	if(y <= 0 || x <= 0 || y >= Nlines - Status - 1 ||
		x >= Ncols - 1 || depbuf[y][x] > ps.dep)
	{
		// The char is out of range, don't bother draw it
		return;
	}
	depbuf[y][x] = ps.dep;
	auto col = ch.getcolpr();
	if(! col) mvwaddch(win, y, x, ch.ch);
	else {
		wattron(win, COLOR_PAIR(col));
		mvwaddch(win, y, x, ch.ch);
		wattroff(win, COLOR_PAIR(col));
	}
}

void Window::draw(Rec rec, Pos ps) {
	ps = ps + rec.getdiff();
	pixeltype y = getpixeltype(ps.y), x = getpixeltype(ps.x);
	if(y >= Nlines - Status - 1 || x >= Ncols - 1) {
		// The rectangle is out of range, don't bother draw it
		return;
	}
	if(y <= 0) {
		if(y + rec.het <= 1) {
			// The rectangle is out of range
			return;
		}
		rec.het = rec.het + y - 1;
		y = 1;
		ps.y = 1.0;
	}
	if(y + rec.het >= Nlines - Status) {
		rec.het = Nlines - Status - y - 1;
	}
	if(x <= 0) {
		if(x + rec.wid <= 1) {
			// The rectangle is out of range
			return;
		}
		rec.wid = rec.wid + x - 1;
		x = 1;
		ps.x = 1.0;
	}
	if(x + rec.wid >= Ncols) {
		rec.wid = Ncols - x - 1;
	}
	// Draw the rectangle
	Ch ch{rec.ch};
	ch.setcolpr(rec.getcolpr());
	ps.x = (postype)x;
	ps.y = (postype)y;
	for(pixeltype i = 0; i < rec.het; ++ i, ++ ps.y) {
		for(pixeltype j = 0; j < rec.wid; ++ j, ++ ps.x) {
			draw(ch, ps);
		}
		ps.x -= rec.wid;
	}
}

void Window::draw(Bm bm, Pos ps) {
	ps = ps + bm.getdiff();
	ps.y = (postype)getpixeltype(ps.y);
	ps.x = (postype)getpixeltype(ps.x);
	for(auto bit: bm.z) {
		ps.y += (postype)bit.y, ps.x += (postype)bit.x;
		Ch wd{bit.ch};
		wd.setcolpr(bm.getcolpr());
		draw(wd, ps);
		ps.y -= (postype)bit.y, ps.x -= (postype)bit.x;
	}
}

void Window::refresh() {wrefresh(win);}

void Window::frushdepbuf() {
	for(auto& z: depbuf) for(auto& x: z) x = 0;
}

void Window::cls() {
	for(pixeltype i = 1; i < Nlines - Status - 1; ++ i) {
		wmove(win, i, 1);
		for(pixeltype j = 1; j < Ncols - 1; ++ j) {
			waddch(win, ' ');
		}
	}
}

int Window::getkey() {return wgetch(win);}
}
