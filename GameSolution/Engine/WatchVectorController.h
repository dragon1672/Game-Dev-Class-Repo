#pragma once

#include <Qt/qlabel.h>
#include <sstream>
#include <glm/glm.hpp>

namespace DebugMenuControllers {
	struct WatchVectorController {
		const char * title;
		QLabel label;
		glm::vec3 * data;
		inline void init(const char * name, glm::vec3 * toWatch) {
			title = name;
			data = toWatch;
			label.setText(name);
			update();
		}
		inline void update() {
			std::stringstream ss;
			ss << title << ": {" << data->x << ", " << data->y << ", " << data->z << ", }";
			label.setText(QString( ss.str().c_str() ));
		}
	};
}