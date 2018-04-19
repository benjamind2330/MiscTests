// ComponentSerializerDesign.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <deque>
#include <iostream>


// A very simplified example of a possible concreate object serializer similar to 
// that employed by the current code.
class ObjectSerializer {

public:
	template <typename T>
	void push(const T& in) {
		buffer.push_front(in);
	}

	template <typename T>
	void pop(T& out) {
		out = buffer.front();
		buffer.pop_front();
	}

	void clean() {
		buffer.clear();
	}

private:

	std::deque<int> buffer;
};

// The extensible routineInput type. This is part of a thing called concepts. The standard lib does heaps of 
// this (eg. std::sort and iterator types). The concept here is that the input type must overload the
// write and read concepts.
template <class TRoutineArgumentsType>
class RoutineArguments : private TRoutineArgumentsType {
public:

	TRoutineArgumentsType const & type() const {
		return *this;
	}

	TRoutineArgumentsType & type() {
		return *this;
	}




	template <class TRoutineArgumentsType>
	bool serialize(ObjectSerializer &ser, const RoutineArguments<TRoutineArgumentsType> &args) {
		return TRoutineArgumentsType::serialize(ser, args.type());
	}

	template <class TRoutineArgumentsType>
	bool deserialize(ObjectSerializer &ser, RoutineArguments<TRoutineArgumentsType> &args) {
		return TRoutineArgumentsType::deserialize(ser, args.type());
	}
	
};





// This would be the example of the responsibility of the person who is making the routine function.
// they would create classes like this that have whatever interface they want for setting data
// etc. Then as long as they appropriately fill the concept, they can be used as a request.
// there is even some compile time checks we can do with meta programming to make sure it is
// done right.
class GetStatusArguments {
public:

	GetStatusArguments()
	{}

	void setRobotNumber(int robotNumber) {
		_robotNumber = robotNumber;
	}


	void setStatusSwitch(int sswitch) {
		_statusSwitch = sswitch;
	}


	static bool serialize(ObjectSerializer &ser, const GetStatusArguments& input) {
		ser.clean();
		ser.push(input._robotNumber);
		ser.push(input._statusSwitch);
		// Could do error checking in here as well!
		return true;
	}

	static bool deserialize(ObjectSerializer &ser, GetStatusArguments& output) {
		ser.pop(output._statusSwitch);
		ser.pop(output._robotNumber);
		return true;
	}

	void print() const {
		std::cout << "R " << _robotNumber << " S " << _statusSwitch << "\n";
	}

private:
	int _robotNumber;
	int _statusSwitch;
};

// This is an example of the routine function which takes the RoutineInput with the concept that it
// cares about. This also ensures that the person using this routine knows they need to use the
// GetStatusInput implementation of the concept to do the right thing.
void fr_someStatusRoutine(ObjectSerializer &arguments, ObjectSerializer &results) {

	// Get the arguments
	RoutineArguments<GetStatusArguments> message;
	deserialize(arguments, message);

	// Use them however you want
	message.type().print();

	// Probably make the results
}

// This is an example of sending this object over a medium. This could be interprocess or local,
// or whatever.
ObjectSerializer mockMedium;

void sendToMedium(const ObjectSerializer &a) {
	mockMedium = a;
}

ObjectSerializer getFromMedium() {
	return mockMedium;
}


#include <stdint.h>
#include <iostream>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/smart_ptr/shared_array.hpp>


int main()
{
	// This would be ItpRequest or HostRequest Manager that creates the input.

	RoutineArguments<GetStatusArguments> message;

	// Doesnt matter which order the arguments are put.
	message.type().setStatusSwitch(2);
	message.type().setRobotNumber(1);
	message.type().setStatusSwitch(55);


	ObjectSerializer myStream;
	serialize(myStream, message);

	// Here is some indirection when it is sent over a medium like boost interprocess.  
	sendToMedium(myStream);

	// Here we get it and use it in the routine function of choice.
	ObjectSerializer args = getFromMedium(), output;
	fr_someStatusRoutine(args, output);

	// Obviously this is just an example. The ObjectSerializer needs work and this should
	// be built as a nice lib that is extensible with proper compile time checking 
	// and the right amount of instruction about how to make the data inputs for 
	// functionality routines.


	while (1);
	return 0;
}



class MoveRequestArgs
{
private:
	friend class boost::serialization::access;
	// When the class Archive corresponds to an output archive, the
	// & operator is defined similar to <<.  Likewise, when the class Archive
	// is a type of input archive the & operator is defined similar to >>.
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & robotNumber;
		ar & toLocation;
		ar & params;
	}
	int robotNumber;
	Location toLocation;
	Parameters params;
public:
...
};