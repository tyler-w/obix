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

#include "log_utils.h"
#include "ptask.h"
#include "xml_utils.h"
#include "xml_config.h"
#include "module.h"
#include "obix_request.h"
#include "xml_storage.h"
#include "server.h"

static const char *doc = "<?xml version=\"1.0\"?>"
"<obj href=\"/obix/deviceRoot/test\" name=\"test device\">"
"	<str href=\"test1\" val=\"test1\" />"
"</obj>";


void obix_module_destroy(struct obix_module *module)
{
	
}

int mod_test_invoke(const struct obix_module *module, const obix_request_t *request, const char *uri, const xmlNode *params)
{
	return 0;
}

int mod_test_write(const struct obix_module *module, const obix_request_t *request, const char *uri, const xmlNode *params)
{
	return 0;
}

int mod_test_read(const struct obix_module *module, const obix_request_t *request, const char *uri)
{
	/**
	 * test read
	 */
	return 0;
}

int obix_module_start(struct obix_module *module)
{
	struct obix_module_operations *ops = (struct obix_module_operations *)malloc(sizeof(struct obix_module_operations));
	if (ops == NULL) {
		log_error("Could not allocate enough memory for the module implementation.");
		return -1;
	}

	ops->obix_server_read = &mod_test_read;
	ops->obix_server_write = &mod_test_write;
	ops->obix_server_invoke = &mod_test_invoke;
	ops->obix_module_destroy = &obix_module_destroy;

	module->funcs = ops;
	
	
	xmlDoc *xmldoc = xmlReadMemory(doc, strlen(doc), NULL, NULL, 0);
	xmlNode *node = xmlDocGetRootElement(xmldoc);
	xmlChar *href = xml_valid_node_href(node, NULL);
	xmlNode *returnNode;
	int r;

	if ((r = obix_server_device_add(node, &returnNode, href, 1)) != 0) {
		log_error("Module %s failed to add device: %s", module->module_path, obix_server_error_msg(r).msgs);
	}
	
	xmlFreeDoc(xmldoc);
	
	/**
	 * test read
	 */
	return 0;
}