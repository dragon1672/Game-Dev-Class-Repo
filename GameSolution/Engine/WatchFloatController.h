#pragma once

#include <sstream>
#include <Qt/qlabel.h>
#include <Qt/qstring.h>

namespace DebugMenuControllers {
	struct WatchFloatController {
		const char * title;
		float * data;
		QLabel label;
		inline void init(const char * name, float * toWatch) {
			title = name;
			data = toWatch;
			update();
		}
		inline void update() {
			std::stringstream ss;
			ss << title << ": " << *data;
			label.setText(QString( ss.str().c_str() ));
		}
	};
}