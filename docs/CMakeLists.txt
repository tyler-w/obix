#
# Copyright NEXTDC LTD. 2014
# 


# Default doc directory
IF(NOT PROJECT_DOC_DIR)
    SET(PROJECT_DOC_DIR "/usr/share/doc" CACHE PATH "Install dir for docs")
ENDIF(NOT PROJECT_DOC_DIR)

IF(NOT PROJECT_DOC_DIR_SUFFIX)
    SET(PROJECT_DOC_DIR_SUFFIX "obix-doc")
ENDIF(NOT PROJECT_DOC_DIR_SUFFIX)

SET(INSTALL_DOCS CODING_GUIDELINES.md HISTORY.md WATCH.md XML_DB_MANAGEMENT.md)
INSTALL(FILES ${INSTALL_DOCS}
    DESTINATION "${PROJECT_DOC_DIR}/${PROJECT_DOC_DIR_SUFFIX}")

