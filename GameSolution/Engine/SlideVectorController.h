#pragma once

#include <Qt/qlabel.h>
#include "LinkedSlider.h"
#include <glm/glm.hpp>

namespace DebugMenuControllers {
	struct SlideVectorController {
		QLabel label;
		LinkedSlider xSlider;
		LinkedSlider ySlider;
		LinkedSlider zSlider;
		glm::vec3 * data;
		inline void init(const char * name, glm::vec3 * toWatch, float lowRange, float highRange) {
			data = toWatch;
			label.setText(name);
			updateModeltoGUI();
			xSlider.setMin(lowRange);	xSlider.setMinimumWidth(30);	xSlider.setMax(highRange);
			ySlider.setMin(lowRange);	ySlider.setMinimumWidth(30);	ySlider.setMax(highRange);
			zSlider.setMin(lowRange);	zSlider.setMinimumWidth(30);	zSlider.setMax(highRange);
		}
		inline void updateGUItoModel() {
			// not required
		}
		inline void updateModeltoGUI() {
			xSlider.setBoundValue(&data->x);
			ySlider.setBoundValue(&data->y);
			zSlider.setBoundValue(&data->z);
		}
	};
}