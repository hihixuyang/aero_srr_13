/* Auto-generated by genmsg_cpp for file /home/parallels/fuerte_workspace/oryxsrr/action_test/msg/FibonacciResult.msg */
#ifndef ACTION_TEST_MESSAGE_FIBONACCIRESULT_H
#define ACTION_TEST_MESSAGE_FIBONACCIRESULT_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace action_test
{
template <class ContainerAllocator>
struct FibonacciResult_ {
  typedef FibonacciResult_<ContainerAllocator> Type;

  FibonacciResult_()
  : sequence()
  {
  }

  FibonacciResult_(const ContainerAllocator& _alloc)
  : sequence(_alloc)
  {
  }

  typedef std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other >  _sequence_type;
  std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other >  sequence;


  typedef boost::shared_ptr< ::action_test::FibonacciResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::action_test::FibonacciResult_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct FibonacciResult
typedef  ::action_test::FibonacciResult_<std::allocator<void> > FibonacciResult;

typedef boost::shared_ptr< ::action_test::FibonacciResult> FibonacciResultPtr;
typedef boost::shared_ptr< ::action_test::FibonacciResult const> FibonacciResultConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::action_test::FibonacciResult_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::action_test::FibonacciResult_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace action_test

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::action_test::FibonacciResult_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::action_test::FibonacciResult_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::action_test::FibonacciResult_<ContainerAllocator> > {
  static const char* value() 
  {
    return "b81e37d2a31925a0e8ae261a8699cb79";
  }

  static const char* value(const  ::action_test::FibonacciResult_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xb81e37d2a31925a0ULL;
  static const uint64_t static_value2 = 0xe8ae261a8699cb79ULL;
};

template<class ContainerAllocator>
struct DataType< ::action_test::FibonacciResult_<ContainerAllocator> > {
  static const char* value() 
  {
    return "action_test/FibonacciResult";
  }

  static const char* value(const  ::action_test::FibonacciResult_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::action_test::FibonacciResult_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#result definition\n\
int32[] sequence\n\
\n\
";
  }

  static const char* value(const  ::action_test::FibonacciResult_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::action_test::FibonacciResult_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.sequence);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct FibonacciResult_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::action_test::FibonacciResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::action_test::FibonacciResult_<ContainerAllocator> & v) 
  {
    s << indent << "sequence[]" << std::endl;
    for (size_t i = 0; i < v.sequence.size(); ++i)
    {
      s << indent << "  sequence[" << i << "]: ";
      Printer<int32_t>::stream(s, indent + "  ", v.sequence[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // ACTION_TEST_MESSAGE_FIBONACCIRESULT_H
