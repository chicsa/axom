// wrapGroup.cpp
// This is generated code, do not edit
//
// Copyright (c) 2017-2020, Lawrence Livermore National Security, LLC and
// other Axom Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: (BSD-3-Clause)
#include "wrapGroup.h"
#include <cstring>
#include <string>
#include "axom/sidre/core/Buffer.hpp"
#include "axom/sidre/core/DataStore.hpp"
#include "axom/sidre/core/Group.hpp"
#include "axom/sidre/core/View.hpp"
#include "axom/sidre/interface/SidreTypes.h"

// splicer begin class.Group.CXX_definitions
// splicer end class.Group.CXX_definitions

extern "C" {


// helper function
// Copy src into dest, blank fill to ndest characters
// Truncate if dest is too short.
// dest will not be NULL terminated.
static void ShroudStrCopy(char* dest, int ndest, const char* src, int nsrc)
{
  if (src == NULL)
  {
    std::memset(dest,' ',ndest);  // convert NULL pointer to blank filled string
  }
  else
  {
    if (nsrc < 0)
      nsrc = std::strlen(src);
    int nm = nsrc < ndest ? nsrc : ndest;
    std::memcpy(dest,src,nm);
    if(ndest > nm)
      std::memset(dest+nm,' ',ndest-nm);               // blank fill
  }
}
// splicer begin class.Group.C_definitions
// splicer end class.Group.C_definitions

SIDRE_IndexType SIDRE_Group_get_index(SIDRE_Group* self)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_index
  axom::sidre::IndexType SHC_rv = SH_this->getIndex();
  return SHC_rv;
  // splicer end class.Group.method.get_index
}

const char* SIDRE_Group_get_name(const SIDRE_Group* self)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_name
  const std::string & SHCXX_rv = SH_this->getName();
  const char* SHC_rv = SHCXX_rv.c_str();
  return SHC_rv;
  // splicer end class.Group.method.get_name
}

void SIDRE_Group_get_name_bufferify(const SIDRE_Group* self, char* SHF_rv,
                                    int NSHF_rv)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_name_bufferify
  const std::string & SHCXX_rv = SH_this->getName();
  if (SHCXX_rv.empty())
  {
    ShroudStrCopy(SHF_rv, NSHF_rv, NULL, 0);
  }
  else
  {
    ShroudStrCopy(SHF_rv, NSHF_rv, SHCXX_rv.data(), SHCXX_rv.size());
  }
  return;
  // splicer end class.Group.method.get_name_bufferify
}

void SIDRE_Group_get_path_bufferify(const SIDRE_Group* self, char* SHF_rv,
                                    int NSHF_rv)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_path_bufferify
  std::string SHCXX_rv = SH_this->getPath();
  if (SHCXX_rv.empty())
  {
    ShroudStrCopy(SHF_rv, NSHF_rv, NULL, 0);
  }
  else
  {
    ShroudStrCopy(SHF_rv, NSHF_rv, SHCXX_rv.data(), SHCXX_rv.size());
  }
  return;
  // splicer end class.Group.method.get_path_bufferify
}

void SIDRE_Group_get_path_name_bufferify(const SIDRE_Group* self, char* SHF_rv,
                                         int NSHF_rv)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_path_name_bufferify
  std::string SHCXX_rv = SH_this->getPathName();
  if (SHCXX_rv.empty())
  {
    ShroudStrCopy(SHF_rv, NSHF_rv, NULL, 0);
  }
  else
  {
    ShroudStrCopy(SHF_rv, NSHF_rv, SHCXX_rv.data(), SHCXX_rv.size());
  }
  return;
  // splicer end class.Group.method.get_path_name_bufferify
}

SIDRE_Group* SIDRE_Group_get_parent(const SIDRE_Group* self,
                                    SIDRE_Group* SHC_rv)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_parent
  const axom::sidre::Group* SHCXX_rv = SH_this->getParent();
  SHC_rv->addr = static_cast<void*>(const_cast<axom::sidre::Group*>(SHCXX_rv));
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.get_parent
}

size_t SIDRE_Group_get_num_groups(const SIDRE_Group* self)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_num_groups
  size_t SHC_rv = SH_this->getNumGroups();
  return SHC_rv;
  // splicer end class.Group.method.get_num_groups
}

size_t SIDRE_Group_get_num_views(const SIDRE_Group* self)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_num_views
  size_t SHC_rv = SH_this->getNumViews();
  return SHC_rv;
  // splicer end class.Group.method.get_num_views
}

SIDRE_DataStore* SIDRE_Group_get_data_store(const SIDRE_Group* self,
                                            SIDRE_DataStore* SHC_rv)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_data_store
  const axom::sidre::DataStore* SHCXX_rv = SH_this->getDataStore();
  SHC_rv->addr =
    static_cast<void*>(const_cast<axom::sidre::DataStore*>(SHCXX_rv));
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.get_data_store
}

bool SIDRE_Group_has_view(const SIDRE_Group* self, const char* path)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.has_view
  const std::string SHCXX_path(path);
  bool SHC_rv = SH_this->hasView(SHCXX_path);
  return SHC_rv;
  // splicer end class.Group.method.has_view
}

bool SIDRE_Group_has_view_bufferify(const SIDRE_Group* self, const char* path,
                                    int Lpath)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.has_view_bufferify
  const std::string SHCXX_path(path, Lpath);
  bool SHC_rv = SH_this->hasView(SHCXX_path);
  return SHC_rv;
  // splicer end class.Group.method.has_view_bufferify
}

bool SIDRE_Group_has_child_view(const SIDRE_Group* self, const char* name)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.has_child_view
  const std::string SHCXX_name(name);
  bool SHC_rv = SH_this->hasChildView(SHCXX_name);
  return SHC_rv;
  // splicer end class.Group.method.has_child_view
}

bool SIDRE_Group_has_child_view_bufferify(const SIDRE_Group* self,
                                          const char* name, int Lname)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.has_child_view_bufferify
  const std::string SHCXX_name(name, Lname);
  bool SHC_rv = SH_this->hasChildView(SHCXX_name);
  return SHC_rv;
  // splicer end class.Group.method.has_child_view_bufferify
}

SIDRE_IndexType SIDRE_Group_get_view_index(const SIDRE_Group* self,
                                           const char* name)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_view_index
  const std::string SHCXX_name(name);
  axom::sidre::IndexType SHC_rv = SH_this->getViewIndex(SHCXX_name);
  return SHC_rv;
  // splicer end class.Group.method.get_view_index
}

SIDRE_IndexType SIDRE_Group_get_view_index_bufferify(const SIDRE_Group* self,
                                                     const char* name,
                                                     int Lname)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_view_index_bufferify
  const std::string SHCXX_name(name, Lname);
  axom::sidre::IndexType SHC_rv = SH_this->getViewIndex(SHCXX_name);
  return SHC_rv;
  // splicer end class.Group.method.get_view_index_bufferify
}

const char* SIDRE_Group_get_view_name(const SIDRE_Group* self,
                                      SIDRE_IndexType idx)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_view_name
  const std::string & SHCXX_rv = SH_this->getViewName(idx);
  // C_error_pattern
  if (!axom::sidre::nameIsValid(SHCXX_rv))
  {
    return SIDRE_InvalidName;
  }

  const char* SHC_rv = SHCXX_rv.c_str();
  return SHC_rv;
  // splicer end class.Group.method.get_view_name
}

void SIDRE_Group_get_view_name_bufferify(const SIDRE_Group* self,
                                         SIDRE_IndexType idx, char* SHF_rv,
                                         int NSHF_rv)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_view_name_bufferify
  const std::string & SHCXX_rv = SH_this->getViewName(idx);
  // C_error_pattern
  if (!axom::sidre::nameIsValid(SHCXX_rv))
  {
    std::memset(SHF_rv, ' ', NSHF_rv);
    return;
  }

  if (SHCXX_rv.empty())
  {
    ShroudStrCopy(SHF_rv, NSHF_rv, NULL, 0);
  }
  else
  {
    ShroudStrCopy(SHF_rv, NSHF_rv, SHCXX_rv.data(), SHCXX_rv.size());
  }
  return;
  // splicer end class.Group.method.get_view_name_bufferify
}

SIDRE_View* SIDRE_Group_get_view_from_name(SIDRE_Group* self, const char* path,
                                           SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_view_from_name
  const std::string SHCXX_path(path);
  axom::sidre::View* SHCXX_rv = SH_this->getView(SHCXX_path);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.get_view_from_name
}

SIDRE_View* SIDRE_Group_get_view_from_name_bufferify(SIDRE_Group* self,
                                                     const char* path,
                                                     int Lpath,
                                                     SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_view_from_name_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::View* SHCXX_rv = SH_this->getView(SHCXX_path);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.get_view_from_name_bufferify
}

SIDRE_View* SIDRE_Group_get_view_from_index(SIDRE_Group* self,
                                            const SIDRE_IndexType idx,
                                            SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_view_from_index
  axom::sidre::View* SHCXX_rv = SH_this->getView(idx);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.get_view_from_index
}

SIDRE_IndexType SIDRE_Group_get_first_valid_view_index(const SIDRE_Group* self)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_first_valid_view_index
  axom::sidre::IndexType SHC_rv = SH_this->getFirstValidViewIndex();
  return SHC_rv;
  // splicer end class.Group.method.get_first_valid_view_index
}

SIDRE_IndexType SIDRE_Group_get_next_valid_view_index(const SIDRE_Group* self,
                                                      SIDRE_IndexType idx)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_next_valid_view_index
  axom::sidre::IndexType SHC_rv = SH_this->getNextValidViewIndex(idx);
  return SHC_rv;
  // splicer end class.Group.method.get_next_valid_view_index
}

SIDRE_View* SIDRE_Group_create_view_empty(SIDRE_Group* self, const char* path,
                                          SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_empty
  const std::string SHCXX_path(path);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_empty
}

SIDRE_View* SIDRE_Group_create_view_empty_bufferify(SIDRE_Group* self,
                                                    const char* path, int Lpath,
                                                    SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_empty_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_empty_bufferify
}

SIDRE_View* SIDRE_Group_create_view_from_type(SIDRE_Group* self,
                                              const char* path, int type,
                                              SIDRE_IndexType num_elems,
                                              SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_type
  const std::string SHCXX_path(path);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    num_elems);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_type
}

SIDRE_View* SIDRE_Group_create_view_from_type_bufferify(SIDRE_Group* self,
                                                        const char* path,
                                                        int Lpath, int type,
                                                        SIDRE_IndexType num_elems,
                                                        SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_type_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    num_elems);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_type_bufferify
}

SIDRE_View* SIDRE_Group_create_view_from_shape(SIDRE_Group* self,
                                               const char* path, int type,
                                               int ndims,
                                               SIDRE_IndexType* shape,
                                               SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_shape
  const std::string SHCXX_path(path);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    ndims, shape);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_shape
}

SIDRE_View* SIDRE_Group_create_view_from_shape_bufferify(SIDRE_Group* self,
                                                         const char* path,
                                                         int Lpath, int type,
                                                         int ndims,
                                                         SIDRE_IndexType* shape,
                                                         SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_shape_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    ndims, shape);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_shape_bufferify
}

SIDRE_View* SIDRE_Group_create_view_into_buffer(SIDRE_Group* self,
                                                const char* path,
                                                SIDRE_Buffer* buff,
                                                SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_into_buffer
  const std::string SHCXX_path(path);
  axom::sidre::Buffer* SHCXX_buff =
    static_cast<axom::sidre::Buffer*>(buff->addr);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_buff);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_into_buffer
}

SIDRE_View* SIDRE_Group_create_view_into_buffer_bufferify(SIDRE_Group* self,
                                                          const char* path,
                                                          int Lpath,
                                                          SIDRE_Buffer* buff,
                                                          SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_into_buffer_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::Buffer* SHCXX_buff =
    static_cast<axom::sidre::Buffer*>(buff->addr);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_buff);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_into_buffer_bufferify
}

SIDRE_View* SIDRE_Group_create_view_from_type_and_buffer(SIDRE_Group* self,
                                                         const char* path,
                                                         int type,
                                                         SIDRE_IndexType num_elems, SIDRE_Buffer* buff,
                                                         SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_type_and_buffer
  const std::string SHCXX_path(path);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::Buffer* SHCXX_buff =
    static_cast<axom::sidre::Buffer*>(buff->addr);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    num_elems, SHCXX_buff);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_type_and_buffer
}

SIDRE_View* SIDRE_Group_create_view_from_type_and_buffer_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type,
  SIDRE_IndexType num_elems, SIDRE_Buffer* buff, SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_type_and_buffer_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::Buffer* SHCXX_buff =
    static_cast<axom::sidre::Buffer*>(buff->addr);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    num_elems, SHCXX_buff);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_type_and_buffer_bufferify
}

SIDRE_View* SIDRE_Group_create_view_from_shape_and_buffer(SIDRE_Group* self,
                                                          const char* path,
                                                          int type, int ndims,
                                                          SIDRE_IndexType* shape, SIDRE_Buffer* buff,
                                                          SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_shape_and_buffer
  const std::string SHCXX_path(path);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::Buffer* SHCXX_buff =
    static_cast<axom::sidre::Buffer*>(buff->addr);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    ndims, shape, SHCXX_buff);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_shape_and_buffer
}

SIDRE_View* SIDRE_Group_create_view_from_shape_and_buffer_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type, int ndims,
  SIDRE_IndexType* shape, SIDRE_Buffer* buff, SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin
  // class.Group.method.create_view_from_shape_and_buffer_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::Buffer* SHCXX_buff =
    static_cast<axom::sidre::Buffer*>(buff->addr);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    ndims, shape, SHCXX_buff);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_shape_and_buffer_bufferify
}

SIDRE_View* SIDRE_Group_create_view_external(SIDRE_Group* self,
                                             const char* path,
                                             void* external_ptr,
                                             SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_external
  const std::string SHCXX_path(path);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, external_ptr);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_external
}

SIDRE_View* SIDRE_Group_create_view_external_bufferify(SIDRE_Group* self,
                                                       const char* path,
                                                       int Lpath,
                                                       void* external_ptr,
                                                       SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_external_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, external_ptr);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_external_bufferify
}

SIDRE_View* SIDRE_Group_create_view_from_type_external(SIDRE_Group* self,
                                                       const char* path,
                                                       int type,
                                                       SIDRE_IndexType num_elems, void* external_ptr,
                                                       SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_type_external
  const std::string SHCXX_path(path);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    num_elems, external_ptr);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_type_external
}

SIDRE_View* SIDRE_Group_create_view_from_type_external_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type,
  SIDRE_IndexType num_elems, void* external_ptr, SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_type_external_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    num_elems, external_ptr);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_type_external_bufferify
}

SIDRE_View* SIDRE_Group_create_view_from_shape_external(SIDRE_Group* self,
                                                        const char* path,
                                                        int type, int ndims,
                                                        SIDRE_IndexType* shape,
                                                        void* external_ptr,
                                                        SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_shape_external
  const std::string SHCXX_path(path);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    ndims, shape, external_ptr);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_shape_external
}

SIDRE_View* SIDRE_Group_create_view_from_shape_external_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type, int ndims,
  SIDRE_IndexType* shape, void* external_ptr, SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_from_shape_external_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createView(SHCXX_path, SHCXX_type,
                                                    ndims, shape, external_ptr);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_from_shape_external_bufferify
}

SIDRE_View* SIDRE_Group_create_view_and_allocate_nelems(SIDRE_Group* self,
                                                        const char* path,
                                                        int type,
                                                        SIDRE_IndexType num_elems,
                                                        SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_and_allocate_nelems
  const std::string SHCXX_path(path);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createViewAndAllocate(SHCXX_path,
                                                               SHCXX_type,
                                                               num_elems);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_and_allocate_nelems
}

SIDRE_View* SIDRE_Group_create_view_and_allocate_nelems_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type,
  SIDRE_IndexType num_elems, SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_and_allocate_nelems_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createViewAndAllocate(SHCXX_path,
                                                               SHCXX_type,
                                                               num_elems);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_and_allocate_nelems_bufferify
}

SIDRE_View* SIDRE_Group_create_view_and_allocate_shape(SIDRE_Group* self,
                                                       const char* path,
                                                       int type, int ndims,
                                                       SIDRE_IndexType* shape,
                                                       SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_and_allocate_shape
  const std::string SHCXX_path(path);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createViewAndAllocate(SHCXX_path,
                                                               SHCXX_type,
                                                               ndims, shape);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_and_allocate_shape
}

SIDRE_View* SIDRE_Group_create_view_and_allocate_shape_bufferify(
  SIDRE_Group* self, const char* path, int Lpath, int type, int ndims,
  SIDRE_IndexType* shape, SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_and_allocate_shape_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::TypeID SHCXX_type = axom::sidre::getTypeID(type);
  axom::sidre::View* SHCXX_rv = SH_this->createViewAndAllocate(SHCXX_path,
                                                               SHCXX_type,
                                                               ndims, shape);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_and_allocate_shape_bufferify
}

SIDRE_View* SIDRE_Group_create_view_scalar_int(SIDRE_Group* self,
                                               const char* path, int value,
                                               SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_scalar_int
  const std::string SHCXX_path(path);
  axom::sidre::View* SHCXX_rv =
    SH_this->createViewScalar<int>(SHCXX_path, value);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_scalar_int
}

SIDRE_View* SIDRE_Group_create_view_scalar_bufferify_int(SIDRE_Group* self,
                                                         const char* path,
                                                         int Lpath, int value,
                                                         SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_scalar_bufferify_int
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::View* SHCXX_rv =
    SH_this->createViewScalar<int>(SHCXX_path, value);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_scalar_bufferify_int
}

SIDRE_View* SIDRE_Group_create_view_scalar_long(SIDRE_Group* self,
                                                const char* path, long value,
                                                SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_scalar_long
  const std::string SHCXX_path(path);
  axom::sidre::View* SHCXX_rv = SH_this->createViewScalar<long>(SHCXX_path,
                                                                value);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_scalar_long
}

SIDRE_View* SIDRE_Group_create_view_scalar_bufferify_long(SIDRE_Group* self,
                                                          const char* path,
                                                          int Lpath, long value,
                                                          SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_scalar_bufferify_long
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::View* SHCXX_rv = SH_this->createViewScalar<long>(SHCXX_path,
                                                                value);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_scalar_bufferify_long
}

SIDRE_View* SIDRE_Group_create_view_scalar_float(SIDRE_Group* self,
                                                 const char* path, float value,
                                                 SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_scalar_float
  const std::string SHCXX_path(path);
  axom::sidre::View* SHCXX_rv = SH_this->createViewScalar<float>(SHCXX_path,
                                                                 value);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_scalar_float
}

SIDRE_View* SIDRE_Group_create_view_scalar_bufferify_float(SIDRE_Group* self,
                                                           const char* path,
                                                           int Lpath,
                                                           float value,
                                                           SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_scalar_bufferify_float
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::View* SHCXX_rv = SH_this->createViewScalar<float>(SHCXX_path,
                                                                 value);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_scalar_bufferify_float
}

SIDRE_View* SIDRE_Group_create_view_scalar_double(SIDRE_Group* self,
                                                  const char* path,
                                                  double value,
                                                  SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_scalar_double
  const std::string SHCXX_path(path);
  axom::sidre::View* SHCXX_rv = SH_this->createViewScalar<double>(SHCXX_path,
                                                                  value);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_scalar_double
}

SIDRE_View* SIDRE_Group_create_view_scalar_bufferify_double(SIDRE_Group* self,
                                                            const char* path,
                                                            int Lpath,
                                                            double value,
                                                            SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_scalar_bufferify_double
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::View* SHCXX_rv = SH_this->createViewScalar<double>(SHCXX_path,
                                                                  value);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_scalar_bufferify_double
}

SIDRE_View* SIDRE_Group_create_view_string(SIDRE_Group* self, const char* path,
                                           const char* value,
                                           SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_string
  const std::string SHCXX_path(path);
  const std::string SHCXX_value(value);
  axom::sidre::View* SHCXX_rv = SH_this->createViewString(SHCXX_path,
                                                          SHCXX_value);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_string
}

SIDRE_View* SIDRE_Group_create_view_string_bufferify(SIDRE_Group* self,
                                                     const char* path,
                                                     int Lpath,
                                                     const char* value,
                                                     int Lvalue,
                                                     SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_view_string_bufferify
  const std::string SHCXX_path(path, Lpath);
  const std::string SHCXX_value(value, Lvalue);
  axom::sidre::View* SHCXX_rv = SH_this->createViewString(SHCXX_path,
                                                          SHCXX_value);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_view_string_bufferify
}

void SIDRE_Group_destroy_view(SIDRE_Group* self, const char* path)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.destroy_view
  const std::string SHCXX_path(path);
  SH_this->destroyView(SHCXX_path);
  return;
  // splicer end class.Group.method.destroy_view
}

void SIDRE_Group_destroy_view_bufferify(SIDRE_Group* self, const char* path,
                                        int Lpath)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.destroy_view_bufferify
  const std::string SHCXX_path(path, Lpath);
  SH_this->destroyView(SHCXX_path);
  return;
  // splicer end class.Group.method.destroy_view_bufferify
}

void SIDRE_Group_destroy_view_and_data_name(SIDRE_Group* self, const char* path)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.destroy_view_and_data_name
  const std::string SHCXX_path(path);
  SH_this->destroyViewAndData(SHCXX_path);
  return;
  // splicer end class.Group.method.destroy_view_and_data_name
}

void SIDRE_Group_destroy_view_and_data_name_bufferify(SIDRE_Group* self,
                                                      const char* path,
                                                      int Lpath)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.destroy_view_and_data_name_bufferify
  const std::string SHCXX_path(path, Lpath);
  SH_this->destroyViewAndData(SHCXX_path);
  return;
  // splicer end class.Group.method.destroy_view_and_data_name_bufferify
}

void SIDRE_Group_destroy_view_and_data_index(SIDRE_Group* self,
                                             SIDRE_IndexType idx)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.destroy_view_and_data_index
  SH_this->destroyViewAndData(idx);
  return;
  // splicer end class.Group.method.destroy_view_and_data_index
}

SIDRE_View* SIDRE_Group_move_view(SIDRE_Group* self, SIDRE_View* view,
                                  SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.move_view
  axom::sidre::View* SHCXX_view = static_cast<axom::sidre::View*>(view->addr);
  axom::sidre::View* SHCXX_rv = SH_this->moveView(SHCXX_view);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.move_view
}

SIDRE_View* SIDRE_Group_copy_view(SIDRE_Group* self, SIDRE_View* view,
                                  SIDRE_View* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.copy_view
  axom::sidre::View* SHCXX_view = static_cast<axom::sidre::View*>(view->addr);
  axom::sidre::View* SHCXX_rv = SH_this->copyView(SHCXX_view);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.copy_view
}

bool SIDRE_Group_has_group(SIDRE_Group* self, const char* path)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.has_group
  const std::string SHCXX_path(path);
  bool SHC_rv = SH_this->hasGroup(SHCXX_path);
  return SHC_rv;
  // splicer end class.Group.method.has_group
}

bool SIDRE_Group_has_group_bufferify(SIDRE_Group* self, const char* path,
                                     int Lpath)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.has_group_bufferify
  const std::string SHCXX_path(path, Lpath);
  bool SHC_rv = SH_this->hasGroup(SHCXX_path);
  return SHC_rv;
  // splicer end class.Group.method.has_group_bufferify
}

bool SIDRE_Group_has_child_group(SIDRE_Group* self, const char* name)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.has_child_group
  const std::string SHCXX_name(name);
  bool SHC_rv = SH_this->hasChildGroup(SHCXX_name);
  return SHC_rv;
  // splicer end class.Group.method.has_child_group
}

bool SIDRE_Group_has_child_group_bufferify(SIDRE_Group* self, const char* name,
                                           int Lname)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.has_child_group_bufferify
  const std::string SHCXX_name(name, Lname);
  bool SHC_rv = SH_this->hasChildGroup(SHCXX_name);
  return SHC_rv;
  // splicer end class.Group.method.has_child_group_bufferify
}

SIDRE_IndexType SIDRE_Group_get_group_index(const SIDRE_Group* self,
                                            const char* name)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_group_index
  const std::string SHCXX_name(name);
  axom::sidre::IndexType SHC_rv = SH_this->getGroupIndex(SHCXX_name);
  return SHC_rv;
  // splicer end class.Group.method.get_group_index
}

SIDRE_IndexType SIDRE_Group_get_group_index_bufferify(const SIDRE_Group* self,
                                                      const char* name,
                                                      int Lname)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_group_index_bufferify
  const std::string SHCXX_name(name, Lname);
  axom::sidre::IndexType SHC_rv = SH_this->getGroupIndex(SHCXX_name);
  return SHC_rv;
  // splicer end class.Group.method.get_group_index_bufferify
}

const char* SIDRE_Group_get_group_name(const SIDRE_Group* self,
                                       SIDRE_IndexType idx)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_group_name
  const std::string & SHCXX_rv = SH_this->getGroupName(idx);
  // C_error_pattern
  if (!axom::sidre::nameIsValid(SHCXX_rv))
  {
    return SIDRE_InvalidName;
  }

  const char* SHC_rv = SHCXX_rv.c_str();
  return SHC_rv;
  // splicer end class.Group.method.get_group_name
}

void SIDRE_Group_get_group_name_bufferify(const SIDRE_Group* self,
                                          SIDRE_IndexType idx, char* SHF_rv,
                                          int NSHF_rv)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_group_name_bufferify
  const std::string & SHCXX_rv = SH_this->getGroupName(idx);
  // C_error_pattern
  if (!axom::sidre::nameIsValid(SHCXX_rv))
  {
    std::memset(SHF_rv, ' ', NSHF_rv);
    return;
  }

  if (SHCXX_rv.empty())
  {
    ShroudStrCopy(SHF_rv, NSHF_rv, NULL, 0);
  }
  else
  {
    ShroudStrCopy(SHF_rv, NSHF_rv, SHCXX_rv.data(), SHCXX_rv.size());
  }
  return;
  // splicer end class.Group.method.get_group_name_bufferify
}

SIDRE_Group* SIDRE_Group_get_group_from_name(SIDRE_Group* self,
                                             const char* path,
                                             SIDRE_Group* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_group_from_name
  const std::string SHCXX_path(path);
  axom::sidre::Group* SHCXX_rv = SH_this->getGroup(SHCXX_path);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.get_group_from_name
}

SIDRE_Group* SIDRE_Group_get_group_from_name_bufferify(SIDRE_Group* self,
                                                       const char* path,
                                                       int Lpath,
                                                       SIDRE_Group* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_group_from_name_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::Group* SHCXX_rv = SH_this->getGroup(SHCXX_path);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.get_group_from_name_bufferify
}

SIDRE_Group* SIDRE_Group_get_group_from_index(SIDRE_Group* self,
                                              SIDRE_IndexType idx,
                                              SIDRE_Group* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_group_from_index
  axom::sidre::Group* SHCXX_rv = SH_this->getGroup(idx);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.get_group_from_index
}

SIDRE_IndexType SIDRE_Group_get_first_valid_group_index(const SIDRE_Group* self)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_first_valid_group_index
  axom::sidre::IndexType SHC_rv = SH_this->getFirstValidGroupIndex();
  return SHC_rv;
  // splicer end class.Group.method.get_first_valid_group_index
}

SIDRE_IndexType SIDRE_Group_get_next_valid_group_index(const SIDRE_Group* self,
                                                       SIDRE_IndexType idx)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.get_next_valid_group_index
  axom::sidre::IndexType SHC_rv = SH_this->getNextValidGroupIndex(idx);
  return SHC_rv;
  // splicer end class.Group.method.get_next_valid_group_index
}

SIDRE_Group* SIDRE_Group_create_group(SIDRE_Group* self, const char* path,
                                      SIDRE_Group* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_group
  const std::string SHCXX_path(path);
  axom::sidre::Group* SHCXX_rv = SH_this->createGroup(SHCXX_path);
  // C_error_pattern
  if (SHCXX_rv == nullptr)
  {
    SHC_rv->addr = NULL;
    SHC_rv->idtor = 0;
    return NULL;
  }

  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_group
}

SIDRE_Group* SIDRE_Group_create_group_bufferify(SIDRE_Group* self,
                                                const char* path, int Lpath,
                                                SIDRE_Group* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.create_group_bufferify
  const std::string SHCXX_path(path, Lpath);
  axom::sidre::Group* SHCXX_rv = SH_this->createGroup(SHCXX_path);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.create_group_bufferify
}

void SIDRE_Group_destroy_group_name(SIDRE_Group* self, const char* path)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.destroy_group_name
  const std::string SHCXX_path(path);
  SH_this->destroyGroup(SHCXX_path);
  return;
  // splicer end class.Group.method.destroy_group_name
}

void SIDRE_Group_destroy_group_name_bufferify(SIDRE_Group* self,
                                              const char* path, int Lpath)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.destroy_group_name_bufferify
  const std::string SHCXX_path(path, Lpath);
  SH_this->destroyGroup(SHCXX_path);
  return;
  // splicer end class.Group.method.destroy_group_name_bufferify
}

void SIDRE_Group_destroy_group_index(SIDRE_Group* self, SIDRE_IndexType idx)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.destroy_group_index
  SH_this->destroyGroup(idx);
  return;
  // splicer end class.Group.method.destroy_group_index
}

SIDRE_Group* SIDRE_Group_move_group(SIDRE_Group* self, SIDRE_Group* grp,
                                    SIDRE_Group* SHC_rv)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.move_group
  axom::sidre::Group* SHCXX_grp = static_cast<axom::sidre::Group*>(grp->addr);
  axom::sidre::Group* SHCXX_rv = SH_this->moveGroup(SHCXX_grp);
  SHC_rv->addr = static_cast<void*>(SHCXX_rv);
  SHC_rv->idtor = 0;
  return SHC_rv;
  // splicer end class.Group.method.move_group
}

void SIDRE_Group_print(const SIDRE_Group* self)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.print
  SH_this->print();
  return;
  // splicer end class.Group.method.print
}

bool SIDRE_Group_is_equivalent_to(const SIDRE_Group* self, SIDRE_Group* other)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.is_equivalent_to
  const axom::sidre::Group* SHCXX_other =
    static_cast<const axom::sidre::Group*>(other->addr);
  bool SHC_rv = SH_this->isEquivalentTo(SHCXX_other);
  return SHC_rv;
  // splicer end class.Group.method.is_equivalent_to
}

void SIDRE_Group_save(const SIDRE_Group* self, const char* file_path,
                      const char* protocol)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.save
  const std::string SHCXX_file_path(file_path);
  const std::string SHCXX_protocol(protocol);
  SH_this->save(SHCXX_file_path, SHCXX_protocol);
  return;
  // splicer end class.Group.method.save
}

void SIDRE_Group_save_bufferify(const SIDRE_Group* self, const char* file_path,
                                int Lfile_path, const char* protocol,
                                int Lprotocol)
{
  const axom::sidre::Group* SH_this =
    static_cast<const axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.save_bufferify
  const std::string SHCXX_file_path(file_path, Lfile_path);
  const std::string SHCXX_protocol(protocol, Lprotocol);
  SH_this->save(SHCXX_file_path, SHCXX_protocol);
  return;
  // splicer end class.Group.method.save_bufferify
}

void SIDRE_Group_load_0(SIDRE_Group* self, const char* file_path,
                        const char* protocol)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.load_0
  const std::string SHCXX_file_path(file_path);
  const std::string SHCXX_protocol(protocol);
  SH_this->load(SHCXX_file_path, SHCXX_protocol);
  return;
  // splicer end class.Group.method.load_0
}

void SIDRE_Group_load_0_bufferify(SIDRE_Group* self, const char* file_path,
                                  int Lfile_path, const char* protocol,
                                  int Lprotocol)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.load_0_bufferify
  const std::string SHCXX_file_path(file_path, Lfile_path);
  const std::string SHCXX_protocol(protocol, Lprotocol);
  SH_this->load(SHCXX_file_path, SHCXX_protocol);
  return;
  // splicer end class.Group.method.load_0_bufferify
}

void SIDRE_Group_load_1(SIDRE_Group* self, const char* file_path,
                        const char* protocol, bool preserve_contents)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.load_1
  const std::string SHCXX_file_path(file_path);
  const std::string SHCXX_protocol(protocol);
  SH_this->load(SHCXX_file_path, SHCXX_protocol, preserve_contents);
  return;
  // splicer end class.Group.method.load_1
}

void SIDRE_Group_load_1_bufferify(SIDRE_Group* self, const char* file_path,
                                  int Lfile_path, const char* protocol,
                                  int Lprotocol, bool preserve_contents)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.load_1_bufferify
  const std::string SHCXX_file_path(file_path, Lfile_path);
  const std::string SHCXX_protocol(protocol, Lprotocol);
  SH_this->load(SHCXX_file_path, SHCXX_protocol, preserve_contents);
  return;
  // splicer end class.Group.method.load_1_bufferify
}

void SIDRE_Group_load_external_data(SIDRE_Group* self, const char* file_path)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.load_external_data
  const std::string SHCXX_file_path(file_path);
  SH_this->loadExternalData(SHCXX_file_path);
  return;
  // splicer end class.Group.method.load_external_data
}

void SIDRE_Group_load_external_data_bufferify(SIDRE_Group* self,
                                              const char* file_path,
                                              int Lfile_path)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.load_external_data_bufferify
  const std::string SHCXX_file_path(file_path, Lfile_path);
  SH_this->loadExternalData(SHCXX_file_path);
  return;
  // splicer end class.Group.method.load_external_data_bufferify
}

bool SIDRE_Group_rename(SIDRE_Group* self, const char* new_name)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.rename
  const std::string SHCXX_new_name(new_name);
  bool SHC_rv = SH_this->rename(SHCXX_new_name);
  return SHC_rv;
  // splicer end class.Group.method.rename
}

bool SIDRE_Group_rename_bufferify(SIDRE_Group* self, const char* new_name,
                                  int Lnew_name)
{
  axom::sidre::Group* SH_this = static_cast<axom::sidre::Group*>(self->addr);
  // splicer begin class.Group.method.rename_bufferify
  const std::string SHCXX_new_name(new_name, Lnew_name);
  bool SHC_rv = SH_this->rename(SHCXX_new_name);
  return SHC_rv;
  // splicer end class.Group.method.rename_bufferify
}

}  // extern "C"
