/*
 /*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Copyright (c) 2017, Lawrence Livermore National Security, LLC.
 *
 * Produced at the Lawrence Livermore National Laboratory
 *
 * LLNL-CODE-xxxxxxx
 *
 * All rights reserved.
 *
 * This file is part of Axom.
 *
 * For details about use and distribution, please read axom/LICENSE.
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/*!
 * \file LumberjackStream.hpp
 *
 */

#ifndef LUMBERJACKSTREAM_HPP_
#define LUMBERJACKSTREAM_HPP_

#include "slic/LogStream.hpp"

#include "axom/Macros.hpp"
#include "axom/Types.hpp"

// C/C++ includes
#include <iostream> // for std::ostream

// MPI
#include <mpi.h> // For MPI

// Forward declarations
namespace axom {
namespace lumberjack {

class Lumberjack;
class Communicator;

}
}

namespace axom {
namespace slic {

/*!
 * \class LumberjackStream
 *
 * \brief A concrete instance of LogStream that dumps messages to a C++
 *  std::ostream object.
 *
 * \note The intent of this class is to illustrate how to using the Logging
 *  facility within an MPI distributed environment and provide a utility that
 *  could be useful for debugging problems at small scales.
 *
 * \warning Do not use this for large-scale production runs.
 * \warning The intent of this class is to be used primarily with std::cout,
 *  std::cerr, etc. It is suggested that applications do not use this class
 *  with an std::ofstream object.
 */
class LumberjackStream:public LogStream
{
public:
  LumberjackStream( std::ostream* stream, MPI_Comm comm, int ranksLimit );
  LumberjackStream( std::ostream* stream, MPI_Comm comm, int ranksLimit,
                    const std::string& format );
  LumberjackStream( std::ostream* stream,
                    axom::lumberjack::Lumberjack* lj );
  LumberjackStream( std::ostream* stream,
                    axom::lumberjack::Lumberjack* lj,
                    const std::string& format );

  virtual ~LumberjackStream();

  /*!
   * \brief Appends the given message to the stream.
   *
   * \param [in] msgLevel the level of the message.
   * \param [in] message the user-supplied message.
   * \param [in] tagName user-supplied tag to associate with the given message.
   * \param [in] fileName the file where this message is appended
   * \param [in] line the line within the file at which the message is appended.
   * \param [in] filter_duplicates optional parameter that indicates whether
   * duplicate messages resulting from running in parallel will be filtered out.
   *
   * \note This method doesn't put anything to the console. Instead the
   *  messages are cached locally to each ranks and are dumped to the console
   *  in rank order when flush is called.
   */
  virtual void append( message::Level msgLevel,
                       const std::string& message,
                       const std::string& tagName,
                       const std::string& fileName,
                       int line,
                       bool filter_duplicates );

  /*!
   * \brief Pushes all messages to the output node according to Lumberjack's
   *  Communication scheme. Then writes it to the given stream.
   */
  virtual void flush();

  /*!
   * \brief Pushes all messages once to their parent node according to Lumberjack's
   *  Communication scheme. This does not guarantee all messages have reached the
   *  output node. This does not write out to the given stream.
   */
  virtual void push();

  /*!
   * \brief Writes the messages that are at the output node to the given stream.
   *  It does not flush any messages and not all messages are guaranteed to be
   *  at the output node.
   */
  virtual void write();

private:
  void initializeLumberjack( MPI_Comm comm, int ranksLimit );
  void finalizeLumberjack();

  /// \name Private Members
  /// @{

  axom::lumberjack::Lumberjack* m_lj;
  axom::lumberjack::Communicator* m_ljComm;
  bool m_isLJOwnedBySLIC;
  std::ostream* m_stream;
  /// @}

  /*!
   * \brief Default constructor. Made private to prevent applications from
   *  using it. Instead the constructor that passes the underlying Lumberjack
   * instance
   *  should be used.
   */
  LumberjackStream(): m_lj( static_cast< axom::lumberjack::Lumberjack* >(
                              AXOM_NULLPTR) ),
    m_stream( static_cast< std::ostream* >(AXOM_NULLPTR) )
  { };

  DISABLE_COPY_AND_ASSIGNMENT(LumberjackStream);
  DISABLE_MOVE_AND_ASSIGNMENT(LumberjackStream);
};

} /* namespace slic */
} /* namespace axom */

#endif /* LUMBERJACKSTREAM_HPP_ */
