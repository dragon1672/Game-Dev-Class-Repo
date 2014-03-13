#pragma once

#include <QtGui\qcheckbox.h>

namespace DebugMenuControllers {
	struct BoolToggleController {
		QCheckBox checkBox;
		bool * dataBound;

		inline void init(const char * name, bool * toWatch) {
			checkBox.setText(name);
			dataBound = toWatch;
			updateModeltoGUI();
		}
		inline void updateGUItoModel() {
			*dataBound = checkBox.isChecked();
		}
		inline void updateModeltoGUI() {
			checkBox.setChecked(*dataBound);
		}
	};
}