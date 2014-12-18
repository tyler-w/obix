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

#ifndef _MODULE_H
#define _MODULE_H

#include <libxml2/libxml/tree.h>

/**
 * Structure containing a dynamic oBIX module.
 */
struct obix_module {
	char *module_config_path;
	xmlNode *module_config;
	obix_module_operations *funcs;
	void *_private;
	void *_handle;
};

/**
 * Structure containing function pointers to the implementations inside the dynamically
 * loaded modules.
 */
struct obix_module_operations {
	int (*obix_module_init)(struct obix_module *module);
	void (*obix_server_destroy)(struct obix_module *module);
	
	int (*obix_server_read)(struct obix_module *module);
	int (*obix_server_write)(struct obix_module *module, const char *uri);
	int (*obix_server_invoke)(struct obix_module *module, const char *uri, const xmlNode *params);
};

int obix_module_load(const char *lib_path, const char *conf_path, struct obix_module **out_module);
int obix_module_unload(struct obix_module *module);

#endif
