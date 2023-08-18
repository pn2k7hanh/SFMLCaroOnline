#include <SFML/Graphics/Texture.hpp>
#include "images.h"

#include "texture.h"

bool isInitTexture = false;
namespace Tex {
	sf::Texture up, down, left, right, upleft, upright, downleft, downright, box, boxx, boxxs, boxo, boxos;
}

void InitTexture()
{
	if (isInitTexture) return;
	if (!isInitImage) InitImage();

	Tex::up.loadFromImage(Board, sf::IntRect(u.x, u.y, u.w, u.h));
	Tex::down.loadFromImage(Board, sf::IntRect(d.x, d.y, d.w, d.h));
	Tex::left.loadFromImage(Board, sf::IntRect(l.x, l.y, l.w, l.h));
	Tex::right.loadFromImage(Board, sf::IntRect(r.x, r.y, r.w, r.h));
	Tex::upleft.loadFromImage(Board, sf::IntRect(ul.x, ul.y, ul.w, ul.h));
	Tex::upright.loadFromImage(Board, sf::IntRect(ur.x, ur.y, ur.w, ur.h));
	Tex::downleft.loadFromImage(Board, sf::IntRect(dl.x, dl.y, dl.w, dl.h));
	Tex::downright.loadFromImage(Board, sf::IntRect(dr.x, dr.y, dr.w, dr.h));
	Tex::box.loadFromImage(Board, sf::IntRect(bx.x, bx.y, bx.w, bx.h));
	Tex::boxx.loadFromImage(BoxX, sf::IntRect(x.x, x.y, x.w, x.h));
	Tex::boxxs.loadFromImage(BoxX, sf::IntRect(xs.x, xs.y, xs.w, xs.h));
	Tex::boxo.loadFromImage(BoxO, sf::IntRect(o.x, o.y, o.w, o.h));
	Tex::boxos.loadFromImage(BoxO, sf::IntRect(os.x, os.y, os.w, os.h));

	isInitTexture = true;
}