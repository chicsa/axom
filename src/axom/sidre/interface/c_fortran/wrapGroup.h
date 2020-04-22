// wrapGroup.h
// This is generated code, do not edit
//
// Copyright (c) 2017-2020, Lawrence Livermore National Security, LLC and
// other Axom Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: (BSD-3-Clause)
/**
 * \file wrapGroup.h
 * \brief Shroud generated wrapper for Group class
 */
// For C users and C++ implementation

#ifndef WRAPGROUP_H
#define WRAPGROUP_H

#include "typesSidre.h"
#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#include "axom/sidre/core/SidreTypes.hpp"
#else
#include <stdbool.h>
#include <stddef.h>
#include "axom/sidre/interface/SidreTypes.h"
#endif

// splicer begin class.Group.CXX_declarations
// splicer end class.Group.CXX_declarations

#ifdef __cplusplus
extern "C" {
#endif

// splicer begin class.Group.C_declarations
// splicer end class.Group.C_declarations

SIDRE_IndexType SIDRE_Group_get_index(SIDRE_Group* self);

const char* SIDRE_Group_get_name(const SIDRE_Group* self);

void SIDRE_Group_get_name_bufferify(const SIDRE_Group* self, char* SHF_rv,
                                    int NSHF_rv);

void SIDRE_Group_get_path_bufferify(const SIDRE_Group* self, char* SHF_rv,
                                    int NSHF_rv);

void SIDRE_Group_get_path_name_bufferify(const SIDRE_Group* self, char* SHF_rv,
                                         int NSHF_rv);

SIDRE_Group* SIDRE_Group_get_parent(const SIDRE_Group* self,
                                    SIDRE_Group* SHC_rv);

size_t SIDRE_Group_get_num_groups(const SIDRE_Group* self);

size_t SIDRE_Group_get_num_views(const SIDRE_Group* self);

SIDRE_DataStore* SIDRE_Group_get_data_store(const SIDRE_Group* self,
                                            SIDRE_DataStore* SHC_rv);

bool SIDRE_Group_has_view(const SIDRE_Group* self, const char* path);

bool SIDRE_Group_has_view_bufferify(const SIDRE_Group* self, const char* path,
                                    int Lpath);

bool SIDRE_Group_has_child_view(const SIDRE_Group* self, const char* name);

bool SIDRE_Group_has_child_view_bufferify(const SIDRE_Group* self,
                                          const char* name, int Lname);

SIDRE_IndexType SIDRE_Group_get_view_index(const SIDRE_Group* self,
                                           const char* name);

SIDRE_IndexType SIDRE_Group_get_view_index_bufferify(const SIDRE_Group* self,
                                                     const char* name,
                                                     int Lname);

const char* SIDRE_Group_get_view_name(const SIDRE_Group* self,
                                      SIDRE_IndexType idx);

void SIDRE_Group_get_view_name_bufferify(const SIDRE_Group* self,
                                         SIDRE_IndexType idx, char* SHF_rv,
                                         int NSHF_rv);

SIDRE_View* SIDRE_Group_get_view_from_name(SIDRE_Group* self, const char* path,
                                           SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_get_view_from_name_bufferify(SIDRE_Group* self,
                                                     const char* path,
                                                     int Lpath,
                                                     SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_get_view_from_index(SIDRE_Group* self,
                                            const SIDRE_IndexType idx,
                                            SIDRE_View* SHC_rv);

SIDRE_IndexType SIDRE_Group_get_first_valid_view_index(const SIDRE_Group* self);

SIDRE_IndexType SIDRE_Group_get_next_valid_view_index(const SIDRE_Group* self,
                                                      SIDRE_IndexType idx);

SIDRE_View* SIDRE_Group_create_view_empty(SIDRE_Group* self, const char* path,
                                          SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_empty_bufferify(SIDRE_Group* self,
                                                    const char* path, int Lpath,
                                                    SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_type(SIDRE_Group* self,
                                              const char* path, int type,
                                              SIDRE_IndexType num_elems,
                                              SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_type_bufferify(SIDRE_Group* self,
                                                        const char* path,
                                                        int Lpath, int type,
                                                        SIDRE_IndexType num_elems,
                                                        SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_shape(SIDRE_Group* self,
                                               const char* path, int type,
                                               int ndims,
                                               SIDRE_IndexType* shape,
                                               SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_shape_bufferify(SIDRE_Group* self,
                                                         const char* path,
                                                         int Lpath, int type,
                                                         int ndims,
                                                         SIDRE_IndexType* shape,
                                                         SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_into_buffer(SIDRE_Group* self,
                                                const char* path,
                                                SIDRE_Buffer* buff,
                                                SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_into_buffer_bufferify(SIDRE_Group* self,
                                                          const char* path,
                                                          int Lpath,
                                                          SIDRE_Buffer* buff,
                                                          SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_type_and_buffer(SIDRE_Group* self,
                                                         const char* path,
                                                         int type,
                                                         SIDRE_IndexType num_elems, SIDRE_Buffer* buff,
                                                         SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_type_and_buffer_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type,
  SIDRE_IndexType num_elems, SIDRE_Buffer* buff, SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_shape_and_buffer(SIDRE_Group* self,
                                                          const char* path,
                                                          int type, int ndims,
                                                          SIDRE_IndexType* shape, SIDRE_Buffer* buff,
                                                          SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_shape_and_buffer_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type, int ndims,
  SIDRE_IndexType* shape, SIDRE_Buffer* buff, SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_external(SIDRE_Group* self,
                                             const char* path,
                                             void* external_ptr,
                                             SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_external_bufferify(SIDRE_Group* self,
                                                       const char* path,
                                                       int Lpath,
                                                       void* external_ptr,
                                                       SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_type_external(SIDRE_Group* self,
                                                       const char* path,
                                                       int type,
                                                       SIDRE_IndexType num_elems, void* external_ptr,
                                                       SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_type_external_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type,
  SIDRE_IndexType num_elems, void* external_ptr, SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_shape_external(SIDRE_Group* self,
                                                        const char* path,
                                                        int type, int ndims,
                                                        SIDRE_IndexType* shape,
                                                        void* external_ptr,
                                                        SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_from_shape_external_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type, int ndims,
  SIDRE_IndexType* shape, void* external_ptr, SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_and_allocate_nelems(SIDRE_Group* self,
                                                        const char* path,
                                                        int type,
                                                        SIDRE_IndexType num_elems,
                                                        SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_and_allocate_nelems_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type,
  SIDRE_IndexType num_elems, SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_and_allocate_shape(SIDRE_Group* self,
                                                       const char* path,
                                                       int type, int ndims,
                                                       SIDRE_IndexType* shape,
                                                       SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_and_allocate_shape_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type, int ndims,
  SIDRE_IndexType* shape, SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_scalar_int(SIDRE_Group* self,
                                               const char* path, int value,
                                               SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_scalar_bufferify_int(SIDRE_Group* self,
                                                         const char* path,
                                                         int Lpath, int value,
                                                         SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_scalar_long(SIDRE_Group* self,
                                                const char* path, long value,
                                                SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_scalar_bufferify_long(SIDRE_Group* self,
                                                          const char* path,
                                                          int Lpath, long value,
                                                          SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_scalar_float(SIDRE_Group* self,
                                                 const char* path, float value,
                                                 SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_scalar_bufferify_float(SIDRE_Group* self,
                                                           const char* path,
                                                           int Lpath,
                                                           float value,
                                                           SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_scalar_double(SIDRE_Group* self,
                                                  const char* path,
                                                  double value,
                                                  SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_scalar_bufferify_double(SIDRE_Group* self,
                                                            const char* path,
                                                            int Lpath,
                                                            double value,
                                                            SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_string(SIDRE_Group* self, const char* path,
                                           const char* value,
                                           SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_create_view_string_bufferify(SIDRE_Group* self,
                                                     const char* path,
                                                     int Lpath,
                                                     const char* value,
                                                     int Lvalue,
                                                     SIDRE_View* SHC_rv);

void SIDRE_Group_destroy_view(SIDRE_Group* self, const char* path);

void SIDRE_Group_destroy_view_bufferify(SIDRE_Group* self, const char* path,
                                        int Lpath);

void SIDRE_Group_destroy_view_and_data_name(SIDRE_Group* self,
                                            const char* path);

void SIDRE_Group_destroy_view_and_data_name_bufferify(SIDRE_Group* self,
                                                      const char* path,
                                                      int Lpath);

void SIDRE_Group_destroy_view_and_data_index(SIDRE_Group* self,
                                             SIDRE_IndexType idx);

SIDRE_View* SIDRE_Group_move_view(SIDRE_Group* self, SIDRE_View* view,
                                  SIDRE_View* SHC_rv);

SIDRE_View* SIDRE_Group_copy_view(SIDRE_Group* self, SIDRE_View* view,
                                  SIDRE_View* SHC_rv);

bool SIDRE_Group_has_group(SIDRE_Group* self, const char* path);

bool SIDRE_Group_has_group_bufferify(SIDRE_Group* self, const char* path,
                                     int Lpath);

bool SIDRE_Group_has_child_group(SIDRE_Group* self, const char* name);

bool SIDRE_Group_has_child_group_bufferify(SIDRE_Group* self, const char* name,
                                           int Lname);

SIDRE_IndexType SIDRE_Group_get_group_index(const SIDRE_Group* self,
                                            const char* name);

SIDRE_IndexType SIDRE_Group_get_group_index_bufferify(const SIDRE_Group* self,
                                                      const char* name,
                                                      int Lname);

const char* SIDRE_Group_get_group_name(const SIDRE_Group* self,
                                       SIDRE_IndexType idx);

void SIDRE_Group_get_group_name_bufferify(const SIDRE_Group* self,
                                          SIDRE_IndexType idx, char* SHF_rv,
                                          int NSHF_rv);

SIDRE_Group* SIDRE_Group_get_group_from_name(SIDRE_Group* self,
                                             const char* path,
                                             SIDRE_Group* SHC_rv);

SIDRE_Group* SIDRE_Group_get_group_from_name_bufferify(SIDRE_Group* self,
                                                       const char* path,
                                                       int Lpath,
                                                       SIDRE_Group* SHC_rv);

SIDRE_Group* SIDRE_Group_get_group_from_index(SIDRE_Group* self,
                                              SIDRE_IndexType idx,
                                              SIDRE_Group* SHC_rv);

SIDRE_IndexType SIDRE_Group_get_first_valid_group_index(const SIDRE_Group* self);

SIDRE_IndexType SIDRE_Group_get_next_valid_group_index(const SIDRE_Group* self,
                                                       SIDRE_IndexType idx);

SIDRE_Group* SIDRE_Group_create_group(SIDRE_Group* self, const char* path,
                                      SIDRE_Group* SHC_rv);

SIDRE_Group* SIDRE_Group_create_group_bufferify(SIDRE_Group* self,
                                                const char* path, int Lpath,
                                                SIDRE_Group* SHC_rv);

void SIDRE_Group_destroy_group_name(SIDRE_Group* self, const char* path);

void SIDRE_Group_destroy_group_name_bufferify(SIDRE_Group* self,
                                              const char* path, int Lpath);

void SIDRE_Group_destroy_group_index(SIDRE_Group* self, SIDRE_IndexType idx);

SIDRE_Group* SIDRE_Group_move_group(SIDRE_Group* self, SIDRE_Group* grp,
                                    SIDRE_Group* SHC_rv);

void SIDRE_Group_print(const SIDRE_Group* self);

bool SIDRE_Group_is_equivalent_to(const SIDRE_Group* self, SIDRE_Group* other);

void SIDRE_Group_save(const SIDRE_Group* self, const char* file_path,
                      const char* protocol);

void SIDRE_Group_save_bufferify(const SIDRE_Group* self, const char* file_path,
                                int Lfile_path, const char* protocol,
                                int Lprotocol);

void SIDRE_Group_load_0(SIDRE_Group* self, const char* file_path,
                        const char* protocol);

void SIDRE_Group_load_0_bufferify(SIDRE_Group* self, const char* file_path,
                                  int Lfile_path, const char* protocol,
                                  int Lprotocol);

void SIDRE_Group_load_1(SIDRE_Group* self, const char* file_path,
                        const char* protocol, bool preserve_contents);

void SIDRE_Group_load_1_bufferify(SIDRE_Group* self, const char* file_path,
                                  int Lfile_path, const char* protocol,
                                  int Lprotocol, bool preserve_contents);

void SIDRE_Group_load_external_data(SIDRE_Group* self, const char* file_path);

void SIDRE_Group_load_external_data_bufferify(SIDRE_Group* self,
                                              const char* file_path,
                                              int Lfile_path);

bool SIDRE_Group_rename(SIDRE_Group* self, const char* new_name);

bool SIDRE_Group_rename_bufferify(SIDRE_Group* self, const char* new_name,
                                  int Lnew_name);

#ifdef __cplusplus
}
#endif

#endif  // WRAPGROUP_H
