
        set(relative_file_name "sbom/qtdeclarative-6.8.3.spdx")
        set(document_dir_paths D:/Exam_Project/qtcharts-build/qt_sbom;$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX};D:/0/Qt/6.8.3/llvm-mingw_64)
        list(JOIN document_dir_paths "\n" document_dir_paths_per_line)
        foreach(document_dir_path IN LISTS document_dir_paths)
            set(document_file_path "${document_dir_path}/${relative_file_name}")
            if(EXISTS "${document_file_path}")
                break()
            endif()
        endforeach()
        if(NOT EXISTS "${document_file_path}")
            message(FATAL_ERROR "Could not find external SBOM document ${relative_file_name}"
                " in any of the document dir paths: ${document_dir_paths_per_line} "
            )
        endif()
        file(SHA1 "${document_file_path}" ext_sha1)
        file(READ "${document_file_path}" ext_content)

        if(NOT "${ext_content}" MATCHES "[\r\n]DocumentNamespace:")
            message(FATAL_ERROR "Missing DocumentNamespace in ${document_file_path}")
        endif()

        string(REGEX REPLACE "^.*[\r\n]DocumentNamespace:[ \t]*([^#\r\n]*).*$"
                "\\1" ext_ns "${ext_content}")

        string(APPEND QT_SBOM_EXTERNAL_DOC_REFS "
ExternalDocumentRef: DocumentRef-qtdeclarative ${ext_ns} SHA1: ${ext_sha1}")

        
