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

#include "module.h"
#include <string.h>
#include "log_utils.h"

static struct obix_module *obix_module_create(const char *lib_path, const char *conf_path)
{
	struct obix_module *module = NULL;

	if ((module = (struct obix_module *)malloc(sizeof(struct obix_module))) == NULL) {
		return NULL;
	}

	memset(module, 0, sizeof(struct obix_module));

	if ((module->module_config_path = strdup(lib_path)) == NULL) {
		log_error("Could not allocate enough memory for lib_path"); 
		goto config_path_failed;
	}

	return module;

config_path_failed:
	free(module);

	return NULL;
}

static void obix_module_destroy(struct obix_module *module)
{
	if (module == NULL) {
		return;
	}

	free(module->module_config_path);
}

int obix_module_load(const char* lib_path, const char* conf_path, obix_module** out_module)
{
	if (lib_path == NULL
		|| conf_path == nullptr) {

	}
}

int obix_module_unload(obix_module* module)
{

}