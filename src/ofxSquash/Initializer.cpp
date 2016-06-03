#include "Initializer.h"

#include "ofMain.h"
#include <squash/squash.h>

namespace ofxSquash {
	//----------
	void initialize() {
		static bool initialized = false;
		if (!initialized) {
			string pluginDir = getPluginDir();
			
			pluginDir = ofToDataPath(pluginDir, true);

			if (!ofDirectory(pluginDir).exists()) {
				pluginDir = getPluginOriginDir();
			}
			
			ofStringReplace(pluginDir, "\\", "/");

			if (ofDirectory(pluginDir).exists()) {
				cout << "found plugins folder at: " << pluginDir << endl;
			}
			else {
				cout << "error: didn't find plugins folder!" << pluginDir << endl;
			}

			squash_set_default_search_path(pluginDir.c_str());
			initialized = true;
		}
	}

	//----------
	string getPluginDir() {
		return "plugins/squash";
	}

	//----------
	string getPluginOriginDir() {
		string platform, arch = sizeof(void*) == 8 ? "x64" : "x86";
#if defined(_MSC_VER)
		platform = "vs";
#elif defined(__MACOSX_CORE__)
		platform = "osx";
#endif
		return "../../../../ofxSquash/libs/squash/bin/" + platform + "/" + arch + "/plugins/squash/";
	}
}