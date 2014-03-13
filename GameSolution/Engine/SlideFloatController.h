#pragma once

#include <Qt/qlabel.h>
#include "LinkedSlider.h"

namespace DebugMenuControllers {
	struct SlideFloatController {
		QLabel label;
		float * data;
		LinkedSlider slider;
		inline void init(const char * name, float * toWatch) {
			data = toWatch;
			label.setText(name);
			updateModeltoGUI();
		}
		inline void updateGUItoModel() {
			// not required
		}
		inline void updateModeltoGUI() {
			slider.setBoundValue(data);
		}
	};
}