#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

#include "mpi.h"

namespace asctoolkit {
namespace lumberjack {

class BinaryTreeCommunicator: public Communicator {
	public:
		void setCommunicator(MPI_Comm comm);
		void pushMessagesOnceUpTree();
		void pushMessagesFullyUpTree();
		std::vector<MessageInfos> getMessages();
	private:
		MPI_Comm m_comm;
		std::vector<int> m_ranks;
};

}
}

#endif