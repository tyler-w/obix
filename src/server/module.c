/* *****************************************************************************
 * Copyright (c) 2014 Tyler Watson <tyler.watson@nextdc.com>
 *
 * This file is part of oBIX.
 *
 * oBIX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * oBIX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with oBIX.  If not, see <http://www.gnu.org/licenses/>.
 *
 * *****************************************************************************/

#include <string.h>
#include <dlfcn.h>
#include "module.h"
#include "log_utils.h"

static struct obix_module *obix_module_create(const char *lib_path, const char *conf_path)
{
	struct obix_module *module = NULL;

	if ((module = (struct obix_module *)malloc(sizeof(struct obix_module))) == NULL) {
		return NULL;
	}

	memset(module, 0, sizeof(struct obix_module));

	if ((module->module_config_path = strdup(conf_path)) == NULL) {
		log_error("Could not allocate enough memory for lib_path");
		goto config_path_failed;
	}

	if ((module->module_path = strdup(lib_path)) == NULL) {
		log_error("Could not allocate enough memory for module_path");
		goto module_path_failed;
	}

	return module;
module_path_failed:
	free(module->module_config_path);

config_path_failed:
	free(module);

	return NULL;
}

static void obix_module_destroy(struct obix_module *module)
{
	if (module == NULL) {
		return;
	}

	free(module->module_path);
	free(module->module_config_path);
	if (module->_dlhandle != NULL) {
		dlclose(module->_dlhandle);
	}
	free(module);
}

int obix_module_load(const char *lib_path, const char *conf_path, struct obix_module **out_module)
{
	struct obix_module *module = NULL;
	char *dlError = NULL;
	*out_module = NULL;
	
	if (lib_path == NULL || conf_path == NULL) {
		return -1;
	}

	if ((module = obix_module_create(lib_path, conf_path)) == NULL) {
		log_error("obix_module_create failed: memory error");
		return -1;
	}

	if ((module->_dlhandle = dlopen(module->module_path, RTLD_LAZY)) == NULL) {
		log_error("dlopen of %s failed: %s", module->module_path, dlerror());
		goto dlopen_failed;
	}

	obix_module_main_t main_func = dlsym(module->_dlhandle, OBIX_MODULE_FUNC_START);
	if ((dlError = dlerror()) != NULL) {
		log_error("oBIX module %s has no %s entry point", module->module_path, 
				  dlError);
		goto dlopen_failed;
	}

	/**
	 * TODO: Parse module configuration file.
	 * 
	 * The module's configuration doc pointer should point to a valid doc before
	 * the entry point function is called.
	 */
	if (main_func(module) < 0) {
		log_error("oBIX module %s failed to initialize.");
		goto dlopen_failed;
	}

	*out_module = module;
	return 0;

dlopen_failed:
	obix_module_destroy(module);

	return -1;
}
