#ifndef INCLUDED_QW_H
#define INCLUDED_QW_H

#include "spawn_button.h"
#include "mouse.h"
#define INIT(Name) qw :: Name :: Init(w)

#define QW_INIT \
	INIT(SpawnButton); INIT(Toglable); INIT(Mouse)


#endif // !INCLUDED_QW_H
