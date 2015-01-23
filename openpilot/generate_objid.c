
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>


enum {
	FIELDTYPE_INT8 = 0,
	FIELDTYPE_INT16,
	FIELDTYPE_INT32,
	FIELDTYPE_UINT8,
	FIELDTYPE_UINT16,
	FIELDTYPE_UINT32,
	FIELDTYPE_FLOAT32,
	FIELDTYPE_ENUM
};


char fieldtype_names[][16] = {
	"int8",
	"int16",
	"int32",
	"uint8",
	"uint16",
	"uint32",
	"float",
	"enum"
};

char fieldtype_ptypes[][2] = {
	"i",
	"i",
	"i",
	"i",
	"i",
	"i",
	"f",
	"i"
};

uint8_t fieldtype_size[] = {
	1,
	2,
	4,
	1,
	2,
	4,
	4,
	1
};

char fieldtype_tnames[][16] = {
	"int8_t",
	"int16_t",
	"int32_t",
	"uint8_t",
	"uint16_t",
	"uint32_t",
	"float",
	"uint8_t"
};

uint32_t updateHash_int(uint32_t value, uint32_t hash) {
	return (hash ^ ((hash<<5) + (hash>>2) + value));
}

uint32_t updateHash_str(uint8_t *value, uint32_t hash) {
	int n;
	uint32_t hashout = hash;
	for (n = 0; n < strlen(value); ++n) {
		hashout = updateHash_int(value[n], hashout);
	}
	return hashout;
}

void trim(char *input) {
	char *dst = input, *src = input;
	char *end;
	while (isspace((unsigned char)*src)) {
		++src;
	}
	end = src + strlen(src) - 1;
	while (end > src && isspace((unsigned char)*end)) {
		*end-- = 0;
	}
	if (src != dst) {
		while ((*dst++ = *src++));
	}
}

void parseParamsGetAttr (xmlDocPtr doc, xmlNodePtr cur, char *attrName, char *attrValue) {
	xmlAttrPtr attribute = NULL;
	for (attribute = cur->properties; attribute != NULL; attribute = attribute->next){
		if (!(xmlStrcasecmp(attribute->name, (const xmlChar *)attrName))) {
			xmlChar *content = xmlNodeListGetString(doc, attribute->children, 1);
			strcpy(attrValue, (char *)content);
			xmlFree(content);
			trim(attrValue);
			return;
		}
	}
	attrValue[0] = 0;
}

int main (int argc, char *argv[]) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlNodePtr cur2;
	xmlNodePtr cur3;
	xmlNodePtr cur4;
	xmlParserCtxtPtr ctxt;
	char object_name[128];
	char object_name_uc[128];
	char attrValue[1024];
	uint32_t hash = 0;
	int n = 0;
	int nn = 0;
	ctxt = xmlNewParserCtxt();
	if (ctxt == NULL) {
		fprintf(stderr, "Failed to allocate parser context\n");
		return;
	}
	doc = xmlCtxtReadFile(ctxt, argv[1], NULL, XML_PARSE_DTDVALID);
	if (doc == NULL) {
		printf("mavlink: Document parsing failed: %s\n", argv[1]);
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		printf("mavlink: Document is Empty!!!\n");
		return;
	}
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((xmlStrcasecmp(cur->name, (const xmlChar *)"object")) == 0) {
			parseParamsGetAttr(doc, cur, "name", attrValue);
			hash = updateHash_str(attrValue, 0);
			strcpy(object_name, attrValue);
			strcpy(object_name_uc, attrValue);
			for (n = 0; n < strlen(object_name_uc); n++) {
				object_name_uc[n] = toupper(object_name_uc[n]);
			}

			char f_struct_name[1024];
			sprintf(f_struct_name, "openpilot/uavobject_struct.h", object_name);
			FILE *f_struct = fopen(f_struct_name, "w");

			char f_otypes_name[1024];
			sprintf(f_otypes_name, "openpilot/uavobject_otypes.h");
			FILE *f_otypes = fopen(f_otypes_name, "w");

			char f_options_name[1024];
			sprintf(f_options_name, "openpilot/uavobject_options.h");
			FILE *f_options = fopen(f_options_name, "w");

			char f_defs_name[1024];
			sprintf(f_defs_name, "openpilot/uavobject_defs.h");
			FILE *f_defs = fopen(f_defs_name, "w");

			char f_ids_name[1024];
			sprintf(f_ids_name, "openpilot/uavobject_ids.h");
			FILE *f_ids = fopen(f_ids_name, "w");

			char f_comment_name[1024];
			sprintf(f_comment_name, "openpilot/uavobject_comment.h");
			FILE *f_comment = fopen(f_comment_name, "w");

			char f_examples_name[1024];
			sprintf(f_examples_name, "openpilot/uavobject_examples.h");
			FILE *f_examples = fopen(f_examples_name, "w");

			char f_examplessend_name[1024];
			sprintf(f_examplessend_name, "openpilot/uavobject_examplessend.h");
			FILE *f_examplessend = fopen(f_examplessend_name, "w");


			fprintf(f_comment, " Object: %s\n", object_name);
			fprintf(f_struct, "typedef struct {\n");

			fprintf(f_examplessend, "\n");
			fprintf(f_examplessend, "void UAVT_%s_Send (UAVT_%sData *data) {\n", object_name, object_name);
			fprintf(f_examplessend, "	uint8_t buf[256];\n");
			fprintf(f_examplessend, "	uint8_t len = 0;\n");

			fprintf(f_examples, "case %s_OBJID: {\n", object_name_uc);
			fprintf(f_examples, "	UAVT_%sData *data = (UAVT_%sData *)buf;\n", object_name, object_name);
//			fprintf(f_examples, "	memcpy(&Openpilot%s, data, sizeof(UAVT_%sData));\n", object_name, object_name);
			fprintf(f_examples, "	SDL_Log(\"uavtalk: <-%s\\n\");\n", object_name);

			parseParamsGetAttr(doc, cur, "settings", attrValue);
			if (strcmp(attrValue, "true") == 0) {
				hash = updateHash_int(1, hash);
			} else {
				hash = updateHash_int(0, hash);
			}
			parseParamsGetAttr(doc, cur, "singleinstance", attrValue);
			if (strcmp(attrValue, "true") == 0) {
				hash = updateHash_int(1, hash);
			} else {
				hash = updateHash_int(0, hash);
			}

			cur2 = cur->xmlChildrenNode;
			while (cur2 != NULL) {
				if ((xmlStrcasecmp(cur2->name, (const xmlChar *)"description")) == 0) {
					xmlChar *key;
					key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
					if (key != NULL) {
						fprintf(f_comment, " Comment: %s\n", (char *)key);
						xmlFree(key);
					}
				}
				cur2 = cur2->next;
			}

			int size_n = 0;
			for (size_n = 8; size_n > 0; size_n--) {
				cur2 = cur->xmlChildrenNode;
				while (cur2 != NULL) {
					if ((xmlStrcasecmp(cur2->name, (const xmlChar *)"field")) == 0) {
						char fieldname[128];
						char fieldname_uc[128];
						char typename[128];
						int elements = 0;
						int type_n = 0;
						parseParamsGetAttr(doc, cur2, "type", typename);
						for (type_n = 0; type_n < FIELDTYPE_ENUM; type_n++) {
							if (strcmp(typename, fieldtype_names[type_n]) == 0) {
								break;
							}
						}
						if (fieldtype_size[type_n] == size_n) {
							parseParamsGetAttr(doc, cur2, "name", fieldname);
							for (n = 0; n < strlen(fieldname); n++) {
								fieldname_uc[n] = toupper(fieldname[n]);
								fieldname_uc[n + 1] = 0;
							}
							uint8_t enum_start = 0;
							uint8_t type_start = 0;
							hash = updateHash_str(fieldname, hash);
							parseParamsGetAttr(doc, cur2, "elements", attrValue);
							if (attrValue[0] != 0) {
								elements = atoi(attrValue);
								hash = updateHash_int(elements, hash);
								if (elements > 1) {
									if (strcmp(typename, "enum") == 0) {
										fprintf(f_struct, "	%s %s[%i];\t// %s\n", fieldtype_tnames[type_n], fieldname, elements, fieldtype_names[type_n]);
										for (nn = 0; nn < elements; nn++) {
											fprintf(f_examples, "	SDL_Log(\"uavtalk: 	%s[%i]: %%%s (%%s)\\n\", data->%s[%i], UAVT_%s%sOption[data->%s[%i]]);\n", fieldname, nn, fieldtype_ptypes[type_n], fieldname, nn, object_name, fieldname, fieldname, nn);
//fprintf(f_examplessend, "	// data->%s[%i] = 0;\n", fieldname, nn);
fprintf(f_examplessend, "	len = openpilot_add_%ibyte(buf, len, data->%s[%i]);\n", size_n, fieldname, nn);
										}
									} else {
										fprintf(f_struct, "	%s %s[%i];\n", fieldtype_tnames[type_n], fieldname, elements);
										for (nn = 0; nn < elements; nn++) {
											fprintf(f_examples, "	SDL_Log(\"uavtalk: 	%s[%i]: %%%s\\n\", data->%s[%i]);\n", fieldname, nn, fieldtype_ptypes[type_n], fieldname, nn);
//fprintf(f_examplessend, "	// data->%s[%i] = 0;\n", fieldname, nn);
fprintf(f_examplessend, "	len = openpilot_add_%ibyte(buf, len, data->%s[%i]);\n", size_n, fieldname, nn);
										}
									}
								} else {
									if (strcmp(typename, "enum") == 0) {
										fprintf(f_struct, "	%s %s;\t// %s\n", fieldtype_tnames[type_n], fieldname, fieldtype_names[type_n]);
										fprintf(f_examples, "	SDL_Log(\"uavtalk: 	%s: %%%s (%%s)\\n\", data->%s, UAVT_%s%sOption[data->%s]);\n", fieldname, fieldtype_ptypes[type_n], fieldname, object_name, fieldname, fieldname);
									} else {
										fprintf(f_struct, "	%s %s;\n", fieldtype_tnames[type_n], fieldname);
										fprintf(f_examples, "	SDL_Log(\"uavtalk: 	%s: %%%s\\n\", data->%s);\n", fieldname, fieldtype_ptypes[type_n], fieldname);
									}
//fprintf(f_examplessend, "	// data->%s = 0;\n", fieldname);
fprintf(f_examplessend, "	len = openpilot_add_%ibyte(buf, len, data->%s);\n", size_n, fieldname);
								}
							} else {
								elements = 0;
								char element_name[128];
								int on = 0;
								parseParamsGetAttr(doc, cur2, "elementnames", attrValue);
								for (n = 0; n < strlen(attrValue); n++) {
									if (attrValue[n] == ',') {
										if (type_start == 0) {
											fprintf(f_otypes, "typedef struct {\n");
											type_start = 1;
										}
										trim(element_name);
										fprintf(f_otypes, "	%s %s;\n", fieldtype_tnames[type_n], element_name);
										if (strcmp(typename, "enum") == 0) {
											fprintf(f_examples, "	SDL_Log(\"uavtalk: 	%s.%s: %%%s (%%s)\\n\", data->%s.%s, UAVT_%s%sOption[data->%s]);\n", fieldname, element_name, fieldtype_ptypes[type_n], fieldtype_ptypes[type_n], fieldname, element_name, fieldname);
										} else {
											fprintf(f_examples, "	SDL_Log(\"uavtalk: 	%s.%s: %%%s\\n\", data->%s.%s);\n", fieldname, element_name, fieldtype_ptypes[type_n], fieldname, element_name);
										}

//fprintf(f_examplessend, "	// data->%s.%s);\n", fieldname, element_name);
fprintf(f_examplessend, "	len = openpilot_add_%ibyte(buf, len, data->%s.%s);\n", size_n, fieldname, element_name);

										elements++;
										on = 0;
									} else {
										element_name[on] = attrValue[n];
										on++;
										element_name[on] = 0;
									}
								}
								if (on > 0) {
									if (type_start == 0) {
										fprintf(f_otypes, "typedef struct {\n");
										type_start = 1;
									}
									trim(element_name);
									fprintf(f_otypes, "	%s %s;\n", fieldtype_tnames[type_n], element_name);
									if (strcmp(typename, "enum") == 0) {
										fprintf(f_examples, "	SDL_Log(\"uavtalk: 	%s.%s: %%%s (%%s)\\n\", data->%s.%s, UAVT_%s%sOption[data->%s]);\n", fieldname, element_name, fieldtype_ptypes[type_n], fieldtype_ptypes[type_n], fieldname, element_name, fieldname);
									} else {
										fprintf(f_examples, "	SDL_Log(\"uavtalk: 	%s.%s: %%%s\\n\", data->%s.%s);\n", fieldname, element_name, fieldtype_ptypes[type_n], fieldname, element_name);
									}


//fprintf(f_examplessend, "	// data->%s.%s);\n", fieldname, element_name);
fprintf(f_examplessend, "	len = openpilot_add_%ibyte(buf, len, data->%s.%s);\n", size_n, fieldname, element_name);

									elements++;
								}
								if (elements == 0) {
									elements = 1;
								}
								hash = updateHash_int(elements, hash);
								if (elements == 1) {
									if (strcmp(typename, "enum") == 0) {
										fprintf(f_struct, "	%s %s;\t// %s\n", fieldtype_tnames[type_n], fieldname, fieldtype_names[type_n]);
										fprintf(f_examples, "	SDL_Log(\"uavtalk: 	%s: %%%s (%%s)\\n\", data->%s, UAVT_%s%sOption[data->%s]);\n", fieldname, fieldtype_ptypes[type_n], fieldname, object_name, fieldname, fieldname);
									} else {
										fprintf(f_struct, "	%s %s;\n", fieldtype_tnames[type_n], fieldname);
										fprintf(f_examples, "	SDL_Log(\"uavtalk: 	%s: %%%s\\n\", data->%s);\n", fieldname, fieldtype_ptypes[type_n], fieldname);
									}
								} else {
									fprintf(f_struct, "	UAVT_%s%sType %s;\t// %s[%i]\n", object_name, fieldname, fieldname, fieldtype_names[type_n], elements);
								}
							}
							hash = updateHash_int(type_n, hash);
							if (strcmp(typename, "enum") == 0) {
								fprintf(f_options, "char UAVT_%s%sOption[][32] = {\n", object_name, fieldname);
								parseParamsGetAttr(doc, cur2, "options", attrValue);
								char option_name[128];
								char option_name_uc[128];
								int option_n = 0;
								int on = 0;
								for (n = 0; n < strlen(attrValue); n++) {
									if (attrValue[n] == ',') {
										trim(option_name);
										fprintf(f_options, "	\"%s\",\n", option_name);
										hash = updateHash_str(option_name, hash);
										for (nn = 0; nn < strlen(object_name); nn++) {
											option_name_uc[nn] = toupper(option_name[nn]);
											option_name_uc[nn + 1] = 0;
										}
										if (enum_start == 0) {
											fprintf(f_defs, "enum {\n");
											enum_start = 1;
										}
										fprintf(f_defs, "	%s_%s_%s = %i,\n", object_name_uc, fieldname_uc, option_name_uc, option_n);
										option_n++;
										on = 0;
									} else {
										option_name[on] = attrValue[n];
										on++;
										option_name[on] = 0;
									}
								}
								if (on > 0) {
									trim(option_name);
									fprintf(f_options, "	\"%s\",\n", option_name);
									hash = updateHash_str(option_name, hash);
									for (nn = 0; nn < strlen(object_name); nn++) {
										option_name_uc[nn] = toupper(option_name[nn]);
										option_name_uc[nn + 1] = 0;
									}
									if (enum_start == 0) {
										fprintf(f_defs, "enum {\n");
										enum_start = 1;
									}
									fprintf(f_defs, "	%s_%s_%s = %i,\n", object_name_uc, fieldname_uc, option_name_uc, option_n);
									option_n++;
								}

								cur3 = cur2->xmlChildrenNode;
								while (cur3 != NULL) {
									if ((xmlStrcasecmp(cur3->name, (const xmlChar *)"options")) == 0) {
										cur4 = cur3->xmlChildrenNode;
										while (cur4 != NULL) {
											if ((xmlStrcasecmp(cur4->name, (const xmlChar *)"option")) == 0) {
												xmlChar *key;
												key = xmlNodeListGetString(doc, cur4->xmlChildrenNode, 1);
												if (key != NULL) {
													fprintf(f_options, "	{\"%s\"},\n", (char *)key);
													hash = updateHash_str((char *)key, hash);
													fprintf(f_struct, "		// %s\n", (char *)key);
													xmlFree(key);
												}
											}
											cur4 = cur4->next;
										}
									}
									cur3 = cur3->next;
								}
								fprintf(f_options, "};\n");
								fprintf(f_options, "\n");
								if (enum_start == 1) {
									fprintf(f_defs, "	%s_%s_LASTITEM = %i,\n", object_name_uc, fieldname_uc, option_n);
									fprintf(f_defs, "}\n");
									fprintf(f_defs, "\n");
								}
							}
							if (type_start == 1) {
								fprintf(f_otypes, "} UAVT_%s%sType;\n", object_name, fieldname);
								fprintf(f_otypes, "\n");
							}
						}
					}
					cur2 = cur2->next;
				}
			}
			fprintf(f_struct, "} UAVT_%sData;\n", object_name);
			fprintf(f_ids, "#define %s_OBJID 0x%x \n", object_name_uc, hash & 0xFFFFFFFE);

			fprintf(f_examplessend, "	openpilot_send(buf, %s_OBJID, 0x22, len);\n", object_name_uc, hash & 0xFFFFFFFE);
			fprintf(f_examplessend, "}\n");
			fprintf(f_examplessend, "\n");

			fprintf(f_examples, "	break;\n");
			fprintf(f_examples, "}\n");

			fclose(f_comment);
			fclose(f_ids);
			fclose(f_defs);
			fclose(f_options);
			fclose(f_otypes);
			fclose(f_struct);
			fclose(f_examples);

		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return 0;
}


