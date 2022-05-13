#include "idrawable.h"
#include <utility>
namespace umity {

IDrawable::IDrawable(unique_ptr<Paintable> image): image{std::move(image)} {}

IDrawable::~IDrawable() {}

unique_ptr<Paintable>& IDrawable::getimage() {
	return image;
}

unique_ptr<Paintable> const& IDrawable::getimage() const {
	return image;
}
}
