#ifndef IDRAWABLE_H_
#define IDRAWABLE_H_
#include "painttype.h"
#include "window.h"
#include <memory>
namespace umity {

using std::unique_ptr;

class IDrawable {
	unique_ptr<Paintable> image;
	public:
	IDrawable(unique_ptr<Paintable> image);
	IDrawable(IDrawable&&) = default;
	virtual ~IDrawable();
	unique_ptr<Paintable>& getimage();
	unique_ptr<Paintable> const& getimage() const;
};
}
#endif
