/* Auto-generated by genmsg_cpp for file /home/parallels/fuerte_workspace/oryxsrr/action_test/msg/FibonacciFeedback.msg */
#ifndef ACTION_TEST_MESSAGE_FIBONACCIFEEDBACK_H
#define ACTION_TEST_MESSAGE_FIBONACCIFEEDBACK_H
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
struct FibonacciFeedback_ {
  typedef FibonacciFeedback_<ContainerAllocator> Type;

  FibonacciFeedback_()
  : sequence()
  {
  }

  FibonacciFeedback_(const ContainerAllocator& _alloc)
  : sequence(_alloc)
  {
  }

  typedef std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other >  _sequence_type;
  std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other >  sequence;


  typedef boost::shared_ptr< ::action_test::FibonacciFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::action_test::FibonacciFeedback_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct FibonacciFeedback
typedef  ::action_test::FibonacciFeedback_<std::allocator<void> > FibonacciFeedback;

typedef boost::shared_ptr< ::action_test::FibonacciFeedback> FibonacciFeedbackPtr;
typedef boost::shared_ptr< ::action_test::FibonacciFeedback const> FibonacciFeedbackConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::action_test::FibonacciFeedback_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::action_test::FibonacciFeedback_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace action_test

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::action_test::FibonacciFeedback_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::action_test::FibonacciFeedback_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::action_test::FibonacciFeedback_<ContainerAllocator> > {
  static const char* value() 
  {
    return "b81e37d2a31925a0e8ae261a8699cb79";
  }

  static const char* value(const  ::action_test::FibonacciFeedback_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xb81e37d2a31925a0ULL;
  static const uint64_t static_value2 = 0xe8ae261a8699cb79ULL;
};

template<class ContainerAllocator>
struct DataType< ::action_test::FibonacciFeedback_<ContainerAllocator> > {
  static const char* value() 
  {
    return "action_test/FibonacciFeedback";
  }

  static const char* value(const  ::action_test::FibonacciFeedback_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::action_test::FibonacciFeedback_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#feedback\n\
int32[] sequence\n\
\n\
";
  }

  static const char* value(const  ::action_test::FibonacciFeedback_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::action_test::FibonacciFeedback_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.sequence);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct FibonacciFeedback_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::action_test::FibonacciFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::action_test::FibonacciFeedback_<ContainerAllocator> & v) 
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

#endif // ACTION_TEST_MESSAGE_FIBONACCIFEEDBACK_H
