/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Copyright (c) 2017-2018, Lawrence Livermore National Security, LLC.
 *
 * Produced at the Lawrence Livermore National Laboratory
 *
 * LLNL-CODE-741217
 *
 * All rights reserved.
 *
 * This file is part of Axom.
 *
 * For details about use and distribution, please read axom/LICENSE.
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#ifndef MINT_UNSTRUCTUREDMESH_HPP_
#define MINT_UNSTRUCTUREDMESH_HPP_

// Axom includes
#include "axom/Macros.hpp"
#include "axom/Types.hpp"

// Mint includes
#include "mint/Array.hpp"
#include "mint/CellTypes.hpp"
#include "mint/ConnectivityArray.hpp"
#include "mint/Mesh.hpp"
#include "mint/MeshCoordinates.hpp"
#include "mint/MeshTypes.hpp"
#include "mint/config.hpp"

// Slic includes
#include "slic/slic.hpp"

// C/C++ includes
#include <cstring> // for std::memcpy

namespace axom
{
namespace mint
{

enum Topology
{
  SINGLE_SHAPE,
  MIXED_SHAPE
};

template < int TOPO >
struct topology_traits {};

template <>
struct topology_traits< SINGLE_SHAPE >
{
  constexpr static ConnectivityType cell_connec = NO_INDIRECTION;
};

template <>
struct topology_traits< MIXED_SHAPE >
{
  constexpr static ConnectivityType cell_connec = TYPED_INDIRECTION;
};

/*!
 * \class UnstructuredMesh
 *
 * \brief Provides the ability to store and operate on Unstructured meshes.
 *
 *  An <em> unstructured mesh </em> stores both node and topology information
 *  explicitly. This allows the flexibility of discretizing the solution
 *  domain using a variety of cell types not just quadrilateral (in 2D) or
 *  hexahedral (in 3D) cells. Due to this added flexibility, the use of
 *  <em> unstructured meshes </em> is more common when dealing with complex
 *  geometries. However, <em> unstructured meshes </em> require additional
 *  storage and generally incur some performance penalty to store, create and
 *  access mesh topology information respectively.
 *
 *  Mint classifies <em> unstructured meshes </em> in two basic types based on
 *  the underlying mesh topology:
 *
 *  * <b> Single Shape Topology </b>
 *
 *   In this case, the <em> unstructured mesh </em> consists of a single cell
 *   type, e.g., a quad or triangle mesh in 2D, or, a hex or tet mesh in 3D.
 *   In this case  the underlying implementation is optimized for the
 *   specified cell type (specified in the constructor).
 *
 *  * <b> Mixed Shape Topology </b>
 *
 *    When <em> mixed cell topology </em> is specified, the <em> unstructured
 *    mesh </em> can be composed of any of the supported cell types, e.g.,
 *    a mesh consisting of both quads and triangles. This mode incurs
 *    additional overhead for storage and access to mesh topology information,
 *    since it requires indirection.
 *
 *  The list of supported cell types for an <em> unstructured mesh </em> is
 *  available in CellTypes.hpp
 *
 * An UnstructuredMesh object may be constructed using (a) native storage,
 * (b) external storage, or, (c) with Sidre storage when Mint is compiled
 *  with Sidre support:
 *
 *  * <b> Native Storage </b> <br />
 *
 *    When using native storage, the Unstructured object owns all memory
 *    associated with the particle data. The storage can grow dynamically as
 *    needed by the application, i.e., adding more nodes/cells. Once the
 *    mesh object goes out-of-scope, all memory associated with it is
 *    returned to the system.
 *
 *  * <b> External Storage </b> <br />
 *
 *    An UnstructuredMesh may also be constructed from external, user-supplied
 *    buffers. In this case, all memory associated with the mesh data
 *    is owned by the caller. Consequently, the mesh cannot grow dynamically.
 *    All calls to resize(), append(), etc. will fail with an error.
 *
 *  * <b> Sidre </b> <br />
 *
 *    An UnstructuredMesh may also be constructed using Sidre as the back-end
 *    data-store manager. The mesh data is laid out in Sidre according to the
 *    <a href="http://llnl-conduit.readthedocs.io/en/latest/"> computational
 *    mesh blueprint </a> conventions. In this case, all operations are
 *    supported, including dynamically resizing the mesh and growing the
 *    associated storage as needed. However, Sidre owns all the memory. Once the
 *    mesh object goes out-of-scope, the data remains persistent in Sidre.
 *
 * \see mint::Mesh
 * \see mint::CellTypes
 */
template < Topology TOPO >
class UnstructuredMesh : public Mesh
{

  AXOM_STATIC_ASSERT( TOPO == SINGLE_SHAPE || TOPO == MIXED_SHAPE );

public:

  /*!
   * \brief Default constructor. Disabled.
   */
  UnstructuredMesh() = delete;

/// \name Native Storage Constructors
/// @{

  /*!
   * \brief Constructs an Unstructured single topology mesh.
   *
   * \param [in] ndims the number of dimensions.
   * \param [in] cell_type the cell type of the mesh.
   * \param [in] node_capacity the number of nodes to allocate space for.
   * \param [in] cell_capacity the number of cells to allocate space for.
   *
   * \note This constructor is only active when TOPO == SINGLE_SHAPE.
   *
   * \post getCellType() == cell_type
   * \post getNumberOfNodes() == 0
   * \post getNumberOfCells() == 0
   */
  UnstructuredMesh( int ndims, CellType cell_type,
                    IndexType node_capacity=USE_DEFAULT,
                    IndexType cell_capacity=USE_DEFAULT ) :
    Mesh( ndims, UNSTRUCTURED_MESH ),
    m_coordinates( new MeshCoordinates( ndims, 0, node_capacity ) ),
    m_cell_connectivity( new CellConnectivity( cell_type, cell_capacity ) )
  {
    AXOM_STATIC_ASSERT_MSG( TOPO == SINGLE_SHAPE,
                            "This constructor is only active for single topology meshes." );

    initialize();
  }

  /*!
   * \brief Constructs an Unstructured mixed topology mesh.
   *
   * \param [in] ndims the number of dimensions.
   * \param [in] node_capacity the number of nodes to allocate space for.
   * \param [in] cell_capacity the number of cells to allocate space for.
   * \param [in] connectivity_capacity the number of vertices to allocate space
   *  for in the cell connectivity array.
   *
   * \note This constructor is only active when TOPO == MIXED_SHAPE.
   *
   * \post getCellType() == UNDEFINED_CELL
   * \post getNumberOfNodes() == 0
   * \post getNumberOfCells() == 0
   */
  UnstructuredMesh( int ndims, IndexType node_capacity=USE_DEFAULT,
                    IndexType cell_capacity=USE_DEFAULT,
                    IndexType connectivity_capacity=USE_DEFAULT ) :
    Mesh( ndims, UNSTRUCTURED_MESH ),
    m_coordinates( new MeshCoordinates( ndims, 0, node_capacity ) ),
    m_cell_connectivity( new CellConnectivity( cell_capacity,
                                               connectivity_capacity ) )
  {
    AXOM_STATIC_ASSERT_MSG( TOPO == MIXED_SHAPE,
                            "This constructor is only active for mixed topology meshes." );

    m_has_mixed_topology = true;
    initialize();
  }

/// @}

/// \name External Storage Constructors
/// @{

  /*!
   * \brief Constructs an Unstructured single topology mesh using the provided
   *  external buffers.
   *
   * \param [in] ndims the number of dimensions.
   * \param [in] cell_type the cell type of the mesh.
   * \param [in] n_cells the number of cells in the mesh.
   * \param [in] cell_capacity the number of cells able to be stored in the
   *  provided connectivity array.
   * \param [in] connectivity the connectivity array. Must be of length at least
   *  cell_capacity * getCellInfo( cell_type ).num_nodes.
   * \param [in] n_nodes the number of nodes in the mesh.
   * \param [in] node_capacity the number of nodes able to be stored in the
   *  provided coordinate arrays.
   * \param [in] x pointer to the x-coordinates
   * \param [in] y pointer to the y-coordinates (required only for 2D and 3D)
   * \param [in] z pointer to the z-coordinates (required only 3D)
   *
   * \note the provided coordinate arrays are to be of length at least
   *  node_capacity.
   * \note This constructor is only active when TOPO == SINGLE_SHAPE.
   *
   * \post getCellType() == cell_type
   * \post getNumberOfCells() == n_cells
   * \post getCellCapacity == cell_capacity
   * \post getNumberOfNodes() == n_nodes
   * \post getNodeCapacity() == node_capacity
   * \post isExternal() == true
   */
  UnstructuredMesh( int ndims, CellType cell_type,
                    IndexType n_cells, IndexType cell_capacity,
                    IndexType* connectivity, IndexType n_nodes,
                    IndexType node_capacity, double* x, double* y=AXOM_NULLPTR,
                    double* z=AXOM_NULLPTR ) :
    Mesh( ndims, UNSTRUCTURED_MESH ),
    m_coordinates( new MeshCoordinates( n_nodes, node_capacity, x, y, z ) ),
    m_cell_connectivity( new CellConnectivity( cell_type, n_cells, connectivity,
                                               cell_capacity ) )
  {
    AXOM_STATIC_ASSERT_MSG( TOPO == SINGLE_SHAPE,
                            "This constructor is only active for single topology meshes." );

    SLIC_ASSERT( x != AXOM_NULLPTR );
    SLIC_ASSERT( m_ndims < 2 || y != AXOM_NULLPTR );
    SLIC_ASSERT( m_ndims < 3 || z != AXOM_NULLPTR );

    initialize();
  }

  /*!
   * \brief Constructs an Unstructured mixed topology mesh using the provided
   *  external buffers.
   *
   * \param [in] ndims the number of dimensions.
   * \param [in] n_cells the number of cells in the mesh.
   * \param [in] cell_capacity the number of cells able to be stored in the
   *  provided connectivity array.
   * \param [in] connectivity_capacity the number of vertices able to be stored
   *  in the provided connectivity array.
   * \param [in] connectivity the connectivity array. Must be Of length at least
   *  connectivity_capacity.
   * \param [in] offsets the offsets of each ID, of length at lesat
   *  cell_capacity + 1.
   * \param [in] types the array of cell types. Must be of length at least
   *  cell_capacity.
   * \param [in] n_nodes the number of nodes in the mesh.
   * \param [in] node_capacity the number of nodes able to be stored in the
   *  provided coordinate arrays.
   * \param [in] x pointer to the x-coordinates
   * \param [in] y pointer to the y-coordinates (required only for 2D and 3D)
   * \param [in] z pointer to the z-coordinates (required only 3D)
   *
   * \note the provided coordinate arrays are to be of length at least
   *  node_capacity.
   * \note This constructor is only active when TOPO == MIXED_SHAPE.
   *
   * \post getCellType() == UNDEFINED_CELL
   * \post getNumberOfCells() == n_cells
   * \post getCellCapacity == cell_capacity
   * \post getNumberOfNodes() == n_nodes
   * \post getNodeCapacity() == node_capacity
   * \post isExternal() == true
   */
  UnstructuredMesh( int ndims, IndexType n_cells, IndexType cell_capacity,
                    IndexType connectivity_capacity, IndexType* connectivity,
                    IndexType* offsets, CellType* types, IndexType n_nodes,
                    IndexType node_capacity, double* x, double* y=AXOM_NULLPTR,
                    double* z=AXOM_NULLPTR ) :
    Mesh( ndims, UNSTRUCTURED_MESH ),
    m_coordinates( new MeshCoordinates( n_nodes, node_capacity, x, y, z ) ),
    m_cell_connectivity( new CellConnectivity( n_cells, connectivity, offsets,
                                               types, cell_capacity,
                                               connectivity_capacity ) )
  {
    AXOM_STATIC_ASSERT_MSG( TOPO == MIXED_SHAPE,
                            "This constructor is only active for mixed topology meshes." );

    SLIC_ASSERT( x != AXOM_NULLPTR );
    SLIC_ASSERT( m_ndims < 2 || y != AXOM_NULLPTR );
    SLIC_ASSERT( m_ndims < 3 || z != AXOM_NULLPTR );

    m_has_mixed_topology = true;
    initialize();
  }

/// @}

/// \name Sidre Storage Constructors
/// @{

#ifdef MINT_USE_SIDRE

  /*!
   * \brief Creates an UnstructuredMesh instance from a given Sidre group that
   *  holds mesh data for an unstructured mesh according to the conventions
   *  described in the computational mesh blueprint.
   *
   * \param [in] group the sidre::Group to use.
   * \param [in] topo optional argument specifying the name of the topology
   *  associated with this Mesh instance.
   *
   * \note If a topology name is not provided, the implementation will construct
   *  a mesh based on the 1st topology group under the parent "topologies"
   *  group.
   *
   * \pre group != AXOM_NULLPTR.
   * \pre blueprint::isValidRootGroup( group ) == true
   * \post isInSidre() == true
   */
  UnstructuredMesh( sidre::Group* group, const std::string& topo="" ) :
    Mesh( group, topo ),
    m_coordinates( new MeshCoordinates( getCoordsetGroup() ) ),
    m_cell_connectivity( new CellConnectivity( getTopologyGroup() ) )
  {
    SLIC_ERROR_IF( m_type != UNSTRUCTURED_MESH,
                   "Supplied sidre::Group does not correspond to a UnstructuredMesh." );

    if ( TOPO == MIXED_SHAPE )
    {
      m_has_mixed_topology = true;
    }

    initialize();
  }

  /*!
   * \brief Creates an UnstructuredMesh instance on an empty Sidre group.
   *
   * \param [in] ndims the number of dimensions.
   * \param [in] cell_type the cell type of the mesh.
   * \param [in] group the sidre::Group to use.
   * \param [in] topo the name of the associated topology group.
   * \param [in] coordset the name of the associated coordset group.
   * \param [in] node_capacity the number of nodes to allocate space for.
   * \param [in] cell_capacity the number of cells to allocate space for.
   * \param [in] connectivity_capacity the number of vertices to allocate space
   *  for in the cell connectivity array.
   *
   * \note If a topology and coordset name are not provided a default name is
   *  used by the implementation.
   * \note The first two constructors are only active when
   *  TOPO == SINGLE_SHAPE and the last two are active only when
   *  TOPO == MIXED_SHAPE.
   *
   * \pre group != AXOM_NULLPTR.
   * \pre group->getNumGroups() == 0
   * \pre group->getNumViews() == 0
   * \post blueprint::isValidRootGroup( group )
   * \post getNumberOfNodes() == 0
   * \post getNumberOfCells() == 0
   * \post isInSidre() == true
   */
  /// @{

  UnstructuredMesh( int ndims, CellType cell_type, sidre::Group* group,
                    const std::string& topo, const std::string& coordset,
                    IndexType node_capacity=USE_DEFAULT,
                    IndexType cell_capacity=USE_DEFAULT ) :
    Mesh( ndims, UNSTRUCTURED_MESH, group, topo, coordset ),
    m_coordinates( new MeshCoordinates( getCoordsetGroup(), ndims, 0,
                                        node_capacity ) ),
    m_cell_connectivity( new CellConnectivity( cell_type, getTopologyGroup(),
                                               m_coordset, cell_capacity ) )
  {
    AXOM_STATIC_ASSERT_MSG( TOPO == SINGLE_SHAPE,
                            "This constructor is only active for single topology meshes." );
    initialize();
  }

  UnstructuredMesh( int ndims, CellType cell_type, sidre::Group* group,
                    IndexType node_capacity=USE_DEFAULT,
                    IndexType cell_capacity=USE_DEFAULT ) :
    UnstructuredMesh( ndims, cell_type, group, "", "", node_capacity,
                      cell_capacity )
  {}

  UnstructuredMesh( int ndims, sidre::Group* group,
                    const std::string& topo, const std::string& coordset,
                    IndexType node_capacity=USE_DEFAULT,
                    IndexType cell_capacity=USE_DEFAULT,
                    IndexType connectivity_capacity=USE_DEFAULT ) :
    Mesh( ndims, UNSTRUCTURED_MESH, group, topo, coordset ),
    m_coordinates( new MeshCoordinates( getCoordsetGroup(), ndims, 0,
                                        node_capacity ) ),
    m_cell_connectivity( new CellConnectivity( getTopologyGroup(), m_coordset,
                                               cell_capacity,
                                               connectivity_capacity ) )
  {
    AXOM_STATIC_ASSERT_MSG( TOPO == MIXED_SHAPE,
                            "This constructor is only active for mixed topology meshes." );

    m_has_mixed_topology = true;
    initialize();
  }

  UnstructuredMesh( int ndims, sidre::Group* group,
                    IndexType node_capacity=USE_DEFAULT,
                    IndexType cell_capacity=USE_DEFAULT,
                    IndexType connectivity_capacity=USE_DEFAULT ) :
    UnstructuredMesh( ndims, group, "", "", node_capacity, cell_capacity,
                      connectivity_capacity )
  {}

  /// @}

#endif /* MINT_USE_SIDRE */

/// @}

/// \name Virtual methods
/// @{

  /*!
   * \brief Destructor, deletes the MeshCoordinates and ConnectivityArray.
   */
  virtual ~UnstructuredMesh()
  {
    if ( m_coordinates != AXOM_NULLPTR )
    {
      delete m_coordinates;
      m_coordinates = AXOM_NULLPTR;
    }
    if ( m_cell_connectivity != AXOM_NULLPTR )
    {
      delete m_cell_connectivity;
      m_cell_connectivity = AXOM_NULLPTR;
    }
  }

/// \name Cells
/// @{

  /*!
   * \brief Return the number of cells in the mesh.
   */
  virtual IndexType getNumberOfCells() const final override
  { return m_cell_connectivity->getNumberOfIDs(); }

  /*!
   * \brief Return the capacity for cells.
   */
  virtual IndexType getCellCapacity() const final override
  { return m_cell_connectivity->getIDCapacity(); }

  /*!
   * \brief Return the number of nodes associated with the given cell.
   *
   * \param [in] cellID the ID of the cell in question, this parameter is
   *  ignored if TOPO == SINGLE_SHAPE.
   *
   * \pre 0 <= cellID < getNumberOfCells()
   */
  virtual IndexType getNumberOfCellNodes( IndexType cellID=0 )
  const final override
  { return m_cell_connectivity->getNumberOfValuesForID( cellID ); }

  /*!
   * \brief Return the type of the given cell.
   *
   * \param [in] cellID the ID of the cell in question, this parameter is
   *  ignored if TOPO == SINGLE_SHAPE. If TOPO == MIXED_SHAPE and no
   *  cellID is provided the returned type is UNDEFINED_CELL.
   *
   * \pre 0 <= cellID < getNumberOfCells()
   */
  virtual CellType getCellType( IndexType cellID=-1 ) const final override
  { return m_cell_connectivity->getIDType( cellID ); }

  /*!
   * \brief Copy the connectivity of the given cell into the provided buffer.
   *  The buffer must be of length at least getNumberOfCellNodes( cellID ).
   *
   * \param [in] cellID the ID of the cell in question.
   * \param [out] cell the buffer into which the connectivity is copied.
   *
   * \return The number of nodes for the given cell.
   *
   * \pre cell != AXOM_NULLPTR
   * \pre 0 <= cellID < getNumberOfCells()
   */
  virtual
  IndexType getCell( IndexType cellID, IndexType* cell ) const final override
  {
    SLIC_ASSERT( cell != AXOM_NULLPTR );
    const IndexType n_cells = getNumberOfCellNodes( cellID );
    std::memcpy( cell, getCell( cellID ), n_cells * sizeof( IndexType ) );
    return n_cells;
  }

/// @}

/// \name Nodes
/// @{

  /*!
   * \brief Return the number of nodes in the mesh.
   */
  virtual IndexType getNumberOfNodes() const final override
  { return m_coordinates->numNodes(); }

  /*!
   * \brief Return the capacity for nodes.
   */
  virtual IndexType getNodeCapacity() const final override
  { return m_coordinates->capacity(); }

  /*!
   * \brief Copy the coordinates of the given node into the provided buffer.
   *
   * \param [in] nodeID the ID of the node in question.
   * \param [in] coords the buffer to copy the coordinates into, of length at
   *  least getDimension().
   *
   * \pre 0 <= nodeID < getNumberOfNodes()
   * \pre coords != AXOM_NULLPTR
   */
  virtual void getNode( IndexType nodeID, double* coords ) const final override
  { m_coordinates->getCoordinates( nodeID, coords ); }

  /*!
   * \brief Return a pointer to the array of nodal coordinates of the
   *  given dimension.
   *
   * \param [in] dim the dimension to return.
   *
   * \pre 0 <= dim < getDimension()
   */
  /// @{

  virtual double* getCoordinateArray( int dim ) final override
  { return m_coordinates->getCoordinateArray( dim ); }

  virtual const double* getCoordinateArray( int dim ) const final override
  { return m_coordinates->getCoordinateArray( dim ); }

  /// @}

/// @}

/// \name Faces
/// @{

  /*!
   * \brief Return the number of faces in the mesh.
   */
  virtual IndexType getNumberOfFaces() const final override
  {
    SLIC_ERROR( "NOT IMPLEMENTED!!!" );
    return 0;
  }

  /*!
   * \brief Return the capacity for faces.
   */
  virtual IndexType getFaceCapacity() const final override
  {
    SLIC_ERROR( "NOT IMPLEMENTED!!!" );
    return 0;
  }

/// @}

/// \name Edges
/// @{

  /*!
   * \brief Return the number of edges in the mesh.
   */
  virtual IndexType getNumberOfEdges() const final override
  {
    SLIC_ERROR( "NOT IMPLEMENTED!!!" );
    return 0;
  }

  /*!
   * \brief Return the capacity for edges.
   */
  virtual IndexType getEdgeCapacity() const final override
  {
    SLIC_ERROR( "NOT IMPLEMENTED!!!" );
    return 0;
  }

/// @}

  /*!
   * \brief Return true iff both the connectivity and coordinates are stored in
   *  external arrays.
   */
  virtual bool isExternal() const final override
  {
    bool connec_external = m_cell_connectivity->isExternal();
    bool coords_external = m_coordinates->isExternal();

    if ( connec_external != coords_external )
    {
      SLIC_WARNING( "External state not consistent." );
      return false;
    }

    return connec_external;
  }

/// @}

/// \name Attribute get/set Methods
/// @{

/// \name Cells
/// @{

  /*!
   * \brief Return the cell resize ratio.
   */
  double getCellResizeRatio() const
  { return m_cell_connectivity->getResizeRatio(); }

  /*!
   * \brief Set the cell resize ratio.
   *
   * \param [in] ratio the new cell resize ratio.
   *
   * \post getCellResizeRatio() == ratio
   */
  void setCellResizeRatio( double ratio )
  {
    m_cell_connectivity->setResizeRatio( ratio );
    m_mesh_fields[ CELL_CENTERED ]->setResizeRatio( ratio );
  }

  /*!
   * \brief Return the size of the connectivity array.
   */
  IndexType getCellConnectivitySize() const
  { return m_cell_connectivity->getNumberOfValues(); }

  /*!
   * \brief Return the capacity of the connectivity array.
   */
  IndexType getCellConnectivityCapacity() const
  { return m_cell_connectivity->getValueCapacity(); }

  /*!
   * \brief Reserve space for the given number of cells.
   *
   * \param [in] cell_capacity the number of cells to reserve space for.
   * \param [in] connectivity_capacity the ammount of space to reserve in the
   *  connectivity array. Ignored if TOPO == SINGLE_SHAPE.
   *
   * \post getCellCapacity() >= cell_capacity
   */
  void reserveCells( IndexType cell_capacity,
                     IndexType connectivity_capacity=USE_DEFAULT )
  {
    m_cell_connectivity->reserve( cell_capacity, connectivity_capacity );
    m_mesh_fields[ CELL_CENTERED ]->reserve( cell_capacity );
  }

  /*!
   * \brief Shrink the cell capacity to be equal to the number of cells.
   *
   * \post getCellCapacity() == getNumberOfCells()
   * \post getCellConnectivityCapacity() == getCellConnectivitySize()
   */
  void shrinkCells()
  {
    m_cell_connectivity->shrink();
    m_mesh_fields[ CELL_CENTERED ]->shrink();
  }

/// @}

/// \name Nodes
/// @{

  /*!
   * \brief Return the node resize ratio.
   */
  double getNodeResizeRatio() const
  { return m_coordinates->getResizeRatio(); }

  /*!
   * \brief Set the node resize ratio.
   *
   * \param [in] ratio the new node resize ratio.
   *
   * \post getNodeResizeRatio() == ratio
   */
  void setNodeResizeRatio( double ratio )
  {
    m_coordinates->setResizeRatio( ratio );
    m_mesh_fields[ NODE_CENTERED ]->setResizeRatio( ratio );
  }

  /*!
   * \brief Reserve space for the given number of nodes.
   *
   * \param [in] node_capacity the number of nodes to reserve space for.
   *
   * \post getNodeCapacity() >= node_capacity
   */
  void reserveNodes( IndexType node_capacity )
  {
    m_coordinates->reserve( node_capacity );
    m_mesh_fields[ NODE_CENTERED ]->reserve( node_capacity );
  }

  /*!
   * \brief Shrink the node capacity to be equal to the number of nodes.
   *
   * \post getNodeCapacity() == getNumberOfNodes()
   */
  void shrinkNodes()
  {
    m_coordinates->shrink();
    m_mesh_fields[ NODE_CENTERED ]->shrink();
  }

/// @}

/// \name Faces
/// @{

  /*!
   * \brief Return the face resize ratio.
   */
  double getFaceResizeRatio() const
  {
    SLIC_ERROR( "NOT IMPLEMENTED!!!" );
    return 0.0;
  }

/// @}

/// \name Edges
/// @{

  /*!
   * \brief Return the edge resize ratio.
   */
  double getEdgeResizeRatio() const
  {
    SLIC_ERROR( "NOT IMPLEMENTED!!!" );
    return 0.0;
  }

/// @}

  /*!
   * \brief Reserve space for the given number of nodes and cells.
   *
   * \param [in] node_capacity the number of nodes to reserve space for.
   * \param [in] cell_capacity the number of cells to reserve space for.
   * \param [in] connectivity_capacity the ammount of space to reserve in the
   *  connectivity array. Ignored if TOPO == SINGLE_SHAPE.
   *
   * \post getNodeCapacity() >= node_capacity
   * \post getCellCapacity() >= cell_capacity
   */
  void reserve( IndexType node_capacity, IndexType cell_capacity,
                IndexType connectivity_capacity=USE_DEFAULT )
  {
    reserveNodes( node_capacity );
    reserveCells( cell_capacity, connectivity_capacity );
  }

  /*!
   * \brief Shrink the node capacity to be equal to the number of nodes and the
   *  cell capacity to be equal to the number of cells.
   *
   * \post getNodeCapacity() == getNumberOfNodes()
   * \post getCellCapacity() == getNumberOfCells()
   * \post getCellConnectivityCapacity() == getCellConnectivitySize()
   */
  void shrink()
  {
    shrinkNodes();
    shrinkCells();
  }

  /*!
   * \brief Return true iff the mesh holds no nodes and no cells.
   */
  bool empty() const
  { return m_coordinates->empty() && m_cell_connectivity->empty(); }

  /*!
   * \brief Return true iff both the connectivity and coordinates are stored in
   *  sidre.
   */
  bool isInSidre() const
  {
    bool connec_sidre = m_cell_connectivity->isInSidre();
    bool coords_sidre = m_coordinates->isInSidre();

    if ( connec_sidre != coords_sidre )
    {
      SLIC_WARNING( "Sidre state not consistent." );
      return false;
    }

    return connec_sidre;
  }

/// @}

/// \name Data Access Methods
/// @{

/// \name Cells
/// @{

  /*!
   * \brief Return a pointer to the connectivity of the given cell. The
   *  buffer is guarenteed to be of length at least
   *  getNumberOfCellNodes( cellID ).
   *
   * \param [in] cellID the ID of the cell in question.
   *
   * \pre 0 <= cellID < getNumberOfCells()
   */
  /// @{

  IndexType* getCell( IndexType cellID )
  { return (*m_cell_connectivity)[ cellID ]; }

  const IndexType* getCell( IndexType cellID ) const
  { return (*m_cell_connectivity)[ cellID ]; }

  /// @}

  /*!
   * \brief Return a pointer to the connectivity array, of length
   *  getCellConnectivitySize().
   */
  /// @{

  IndexType* getCellConnectivityArray()
  { return m_cell_connectivity->getValuePtr(); }

  const IndexType* getCellConnectivityArray() const
  { return m_cell_connectivity->getValuePtr(); }

  /// @}

  /*!
   * \brief Return a constant pointer to the offset array, of length
   *  getNumberOfCells() + 1. Returns AXOM_NULLPTR if
   *  TOPO == SINGLE_SHAPE.
   */
  const IndexType* getCellOffsetsArray() const
  { return m_cell_connectivity->getOffsetPtr(); }

  /*!
   * \brief Return a constant pointer to the cell types array, of length
   *  getNumberOfCells(). Returns AXOM_NULLPTR if
   *  TOPO == SINGLE_SHAPE.
   */
  const CellType* getCellTypesArray() const
  { return m_cell_connectivity->getTypePtr(); }

  /*!
   * \brief Append a cell to the mesh.
   *
   * \param [in] connec the connectivity of the new cell.
   * \param [in] type the type of the new cell, ignored if
   *  TOPO == SINGLE_SHAPE.
   *
   * \pre connec != AXOM_NULLPTR
   */
  void appendCell( const IndexType* connec, CellType type=UNDEFINED_CELL )
  {
    IndexType n_values = (type == UNDEFINED_CELL) ?
                         0 : getCellInfo( type ).num_nodes;
    m_cell_connectivity->append( connec, n_values, type );
    m_mesh_fields[ CELL_CENTERED ]->resize( getNumberOfCells() );
  }

  /*!
   * \brief Append multiple cells to the mesh.
   *
   * \param [in] connec the connectivity of the new cells.
   * \param [in] n_cells the number of cells to append.
   * \param [in] offsets the offsets array of the cells to append, ignored
   *  if TOPO == SINGLE_SHAPE.
   * \param [in] types the types array of the new cells, ignored if
   *  TOPO == SINGLE_SHAPE.
   *
   * \pre connec != AXOM_NULLPTR
   * \pre n_cells >= 0
   */
  void appendCells( const IndexType* connec, IndexType n_cells,
                    const IndexType* offsets=AXOM_NULLPTR,
                    const CellType* types=AXOM_NULLPTR )
  {
    m_cell_connectivity->appendM( connec, n_cells, offsets, types );
    m_mesh_fields[ CELL_CENTERED ]->resize( getNumberOfCells() );
  }

  /*!
   * \brief Insert a cell in to the mesh at the given position.
   *
   * \param [in] connec the connectivity of the new cell.
   * \param [in] ID the position to insert at.
   * \param [in] n_values the number of values in the connectivity, ignored
   *  if TOPO == SINGLE_SHAPE.
   * \param [in] type the type of the new cells, ignored if
   *  TOPO == SINGLE_SHAPE.
   *
   * \pre connec != AXOM_NULLPTR
   * \pre 0 <= ID <= getNumberOfCells()
   */
  void insertCell( const IndexType* connec, IndexType ID,
                   CellType type=UNDEFINED_CELL )
  {
    IndexType n_values = (type == UNDEFINED_CELL) ?
                         0 : getCellInfo( type ).num_nodes;
    m_cell_connectivity->insert( connec, ID, n_values, type );
    m_mesh_fields[ CELL_CENTERED ]->emplace( ID, 1 );
  }

  /*!
   * \brief Insert multiple cells in to the mesh at the given position.
   *
   * \param [in] connec the connectivity of the new cells.
   * \param [in] start_ID the position to insert at.
   * \param [in] n_cells the number of cells to insert
   * \param [in] offsets the offsets array of the cells to append, ignored
   *  if TOPO == SINGLE_SHAPE.
   * \param [in] types the types array of the new cells, ignored if
   *  TOPO == SINGLE_SHAPE.
   *
   * \pre connec != AXOM_NULLPTR
   * \pre 0 <= start_ID <= getNumberOfCells()
   */
  void insertCells( const IndexType* connec, IndexType start_ID,
                    IndexType n_cells,
                    const IndexType* offsets=AXOM_NULLPTR,
                    const CellType* types=AXOM_NULLPTR )
  {
    m_cell_connectivity->insertM( connec, start_ID, n_cells, offsets, types );
    m_mesh_fields[ CELL_CENTERED ]->emplace( start_ID, n_cells );
  }

/// @}

/// \name Nodes
/// @{

  /*!
   * \brief Return the coordinate of the given dimension of the given node.
   *
   * \param [in] nodeID the ID of the node in question.
   * \param [in] dim the dimension to return.
   *
   * \pre 0 <= nodeID < getNumberOfNodes()
   * \pre 0 <= dim < getDimension()
   */
  double getNodeCoordinate( IndexType nodeID, int dim ) const
  { return m_coordinates->getCoordinate( nodeID, dim ); }

  /*!
   * \brief Appends a new node to the mesh.
   *
   * \param [in] x the first coordinate to append.
   * \param [in] y the second coordinate to append.
   * \param [in] z the third coordinate to append.
   *
   * \note Each method is valid only for the appropriate dimension of the mesh.
   */
  /// @{

  IndexType appendNode( double x )
  {
    IndexType n_index = m_coordinates->append( x );
    m_mesh_fields[ NODE_CENTERED ]->resize( getNumberOfNodes() );
    return n_index;
  }

  IndexType appendNode( double x, double y )
  {
    IndexType n_index = m_coordinates->append( x, y );
    m_mesh_fields[ NODE_CENTERED ]->resize( getNumberOfNodes() );
    return n_index;
  }


  IndexType appendNode( double x, double y, double z )
  {
    IndexType n_index = m_coordinates->append( x, y, z );
    m_mesh_fields[ NODE_CENTERED ]->resize( getNumberOfNodes() );
    return n_index;
  }

  /// @}

  /*!
   * \brief Appends multiple nodes to the mesh.
   *
   * \param [in] coords pointer to the nodes to append, of length
   *  n * getDimension().
   * \param [in] n the number of nodes to append.
   *
   * \note coords is assumed to be in the array of structs format, ie
   *  coords = {x0, y0, z0, x1, y1, z1, ..., xn, yn, zn}.
   *
   * \pre coords != AXOM_NULLPTR
   * \pre n >= 0
   */
  void appendNodes( const double* coords, IndexType n=1 )
  {
    m_coordinates->append( coords, n );
    m_mesh_fields[ NODE_CENTERED ]->resize( getNumberOfNodes() );
  }

  /*!
   * \brief Appends new nodes to the mesh.
   *
   * \param [in] x array of the first coordinates to append, of length n.
   * \param [in] y array of the second coordinates to append, of length n.
   * \param [in] z array of the third coordinates to append, of length n.
   * \param [in] n the number of coordinates to append.
   *
   * \note The first method is only valid for 2D meshes while the second
   *  is only for 3D.
   * \pre x != AXOM_NULLPTR
   * \pre y != AXOM_NULLPTR
   * \pre z != AXOM_NULLPTR
   * \pre n >= 0
   */
  /// @{

  void appendNodes( const double* x, const double* y, IndexType n )
  {
    m_coordinates->append( x, y, n );
    m_mesh_fields[ NODE_CENTERED ]->resize( getNumberOfNodes() );
  }

  void appendNodes( const double* x, const double* y, const double* z,
                    IndexType n )
  {
    m_coordinates->append( x, y, z, n );
    m_mesh_fields[ NODE_CENTERED ]->resize( getNumberOfNodes() );
  }

  /// @}

  /*!
   * \brief Insert a node to the mesh.
   *
   * \param [in] nodeID the position to insert at.
   * \param [in] x the value of the first coordinate to insert.
   * \param [in] y the value of the second coordinate to insert.
   * \param [in] z the value of the third coordinate to insert.
   * \param [in] update_connectivity if true will update the connectivity so
   *  that all elements remain connected to the same coordinates as before.
   *
   * \note Each method is valid only for the appropriate dimension of the mesh.
   * \pre 0 <= nodeID <= getNumberOfNodes
   */
  /// @{

  void insertNode( IndexType nodeID, double x, bool update_connectivity=true )
  {
    m_coordinates->insert( nodeID, x );
    m_mesh_fields[ NODE_CENTERED ]->emplace( nodeID, 1 );
    if ( update_connectivity )
    {
      cellConnectivityUpdateInsert( nodeID, 1 );
    }
  }

  void insertNode( IndexType nodeID, double x, double y,
                   bool update_connectivity=true )
  {
    m_coordinates->insert( nodeID, x, y );
    m_mesh_fields[ NODE_CENTERED ]->emplace( nodeID, 1 );
    if ( update_connectivity )
    {
      cellConnectivityUpdateInsert( nodeID, 1 );
    }
  }

  void insertNode( IndexType nodeID, double x, double y, double z,
                   bool update_connectivity=true )
  {
    m_coordinates->insert( nodeID, x, y, z );
    m_mesh_fields[ NODE_CENTERED ]->emplace( nodeID, 1 );
    if ( update_connectivity )
    {
      cellConnectivityUpdateInsert( nodeID, 1 );
    }
  }

  /// @}

  /*!
   * \brief Inserts multiple nodes to the mesh.
   *
   * \param [in] coords pointer to the nodes to insert, of length
   *  n * getDimension().
   * \param [in] n the number of nodes to append.
   * \param [in] update_connectivity if true will update the connectivity so
   *  that all elements remain connected to the same coordinates as before.
   *
   * \note coords is assumed to be in the array of structs format, ie
   *  coords = {x0, y0, z0, x1, y1, z1, ..., xn, yn, zn}.
   *
   * \pre 0 <= nodeID <= getNumberOfNodes
   * \pre coords != AXOM_NULLPTR
   * \pre n >= 0
   */
  void insertNodes( IndexType nodeID, const double* coords, IndexType n=1,
                    bool update_connectivity=true )
  {
    m_coordinates->insert( nodeID, coords, n );
    m_mesh_fields[ NODE_CENTERED ]->emplace( nodeID, n );
    if ( update_connectivity )
    {
      cellConnectivityUpdateInsert( nodeID, n );
    }
  }

  /*!
   * \brief Insert multiple nodes to the mesh.
   *
   * \param [in] nodeID the position to insert at.
   * \param [in] x the array of the first coordinates to insert.
   * \param [in] y the array of the second coordinates to insert.
   * \param [in] z the array of the third coordinates to insert.
   * \param [in] n the number of nodes to insert.
   * \param [in] update_connectivity if true will update the connectivity so
   *  that all elements remain connected to the same coordinates as before.
   *
   * \note The first method is only valid for 2D meshes while the second
   *  is only for 3D.
   * \pre 0 <= nodeID <= getNumberOfNodes
   * x != AXOM_NULLPTR
   * y != AXOM_NULLPTR
   * z != AXOM_NULLPTR
   * \pre n >= 0
   */
  /// @{

  void insertNodes( IndexType nodeID, const double* x, const double* y,
                    IndexType n, bool update_connectivity=true )
  {
    m_coordinates->insert( nodeID, x, y, n );
    m_mesh_fields[ NODE_CENTERED ]->emplace( nodeID, n );
    if ( update_connectivity )
    {
      cellConnectivityUpdateInsert( nodeID, n );
    }
  }


  void insertNodes( IndexType nodeID, const double* x, const double* y,
                    const double* z, IndexType n,
                    bool update_connectivity=true )
  {
    m_coordinates->insert( nodeID, x, y, z, n );
    m_mesh_fields[ NODE_CENTERED ]->emplace( nodeID, n );
    if ( update_connectivity )
    {
      cellConnectivityUpdateInsert( nodeID, n );
    }
  }

  /// @}

/// @}

/// @}

private:

  /*!
   * \brief Update the connectivity given an nodal insert at position pos of
   *  length n.
   *
   * \param [in] pos the position of the insert.
   * \param [in] n the length of the insert.
   */
  void cellConnectivityUpdateInsert( IndexType pos, IndexType n )
  {
    SLIC_ASSERT( 0 <= pos && pos < getNumberOfNodes() );

    const IndexType n_values = getCellConnectivitySize();
    IndexType* values = getCellConnectivityArray();
    SLIC_ASSERT( n_values == 0 || values != AXOM_NULLPTR );

    for ( IndexType i = 0 ; i < n_values ; ++i )
    {
      if ( values[ i ] >= pos )
      {
        values[ i ] += n;
      }
    }
  }

  /*!
   * \brief Performs common initialization.
   */
  void initialize()
  {
    m_explicit_coords = true;
    m_explicit_connectivity = true;
    m_mesh_fields[ NODE_CENTERED ]->setResizeRatio( getNodeResizeRatio() );
    m_mesh_fields[ CELL_CENTERED ]->setResizeRatio( getCellResizeRatio() );
    m_mesh_fields[ NODE_CENTERED ]->reserve( m_coordinates->capacity() );
    m_mesh_fields[ CELL_CENTERED ]->reserve(
      m_cell_connectivity->getIDCapacity() );
  }

  using CellConnectivity =
          ConnectivityArray< topology_traits< TOPO >::cell_connec >;

  MeshCoordinates* m_coordinates;
  CellConnectivity* m_cell_connectivity;

  DISABLE_COPY_AND_ASSIGNMENT( UnstructuredMesh );
  DISABLE_MOVE_AND_ASSIGNMENT( UnstructuredMesh );
};

} /* namespace mint */
} /* namespace axom */

#endif /* MINT_UNSTRUCTUREDMESH_HPP_ */
