#ifndef PAINTTYPE_H_
#define PAINTTYPE_H_
#include <vector>
#include "datatype.h"
namespace umity {

struct Bit {
	pixeltype y, x;
	char ch;
	Bit(pixeltype y, pixeltype x, char ch);
};

using Bitmap = std::vector<Bit>;

enum class PaintableType {ch, rec, bm};

class Paintable {
	Vec diff;
	int colpr;
	public:
	Paintable();
	void setdiff(Vec nd);
	Vec getdiff();
	void setcolpr(int cp);
	int getcolpr();
	virtual ~Paintable();
	virtual PaintableType gettype() const = 0;
};

class Ch: public Paintable {
	public:
	char ch;
	Ch(char ch);
	PaintableType gettype() const override;
};

class Rec: public Paintable {
	public:
	char ch;
	pixeltype het, wid;
	Rec(char ch, pixeltype het, pixeltype wid);
	PaintableType gettype() const override;
};

class Bm: public Paintable {
	public:
	Bitmap z;
	Bm(Bitmap z);
	PaintableType gettype() const override;
};
}
#endif
