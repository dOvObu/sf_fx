#ifndef INCLUDED_QW_H
#define INCLUDED_QW_H

#include "spawn_button.h"
#include "field_of_choice.h"
#include "fonts_provider.h"
#include "textures_provider.h"
#include "ui/i_ui_item.h"
#include "mouse.h"
#include "app.h"
#define INIT(Name) qw :: Name :: Init(w)

#define QW_INIT \
	sf::RenderWindow w{{ 800,600 }, "T_T"}; \
	w.setFramerateLimit(60); \
	qw::TexturesProvider::LoadTextures("resources/img"); \
	qw::FontsProvider::LoadFonts("resources/fonts"); \
		INIT(App); INIT(SpawnButton); INIT(Toglable); INIT(Mouse); INIT(FieldOfChoice); INIT(IUiItem)


#endif // !INCLUDED_QW_H
