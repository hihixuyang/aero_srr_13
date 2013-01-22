/* Auto-generated by genmsg_cpp for file /home/aruis/groovy_workspace/oryx_srr/OryxMessages/msg/Blob.msg */
#ifndef ORYXMESSAGES_MESSAGE_BLOB_H
#define ORYXMESSAGES_MESSAGE_BLOB_H
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


namespace OryxMessages
{
template <class ContainerAllocator>
struct Blob_ {
  typedef Blob_<ContainerAllocator> Type;

  Blob_()
  : x(0)
  , y(0)
  , size(0)
  , radius(0)
  {
  }

  Blob_(const ContainerAllocator& _alloc)
  : x(0)
  , y(0)
  , size(0)
  , radius(0)
  {
  }

  typedef int32_t _x_type;
  int32_t x;

  typedef int32_t _y_type;
  int32_t y;

  typedef int32_t _size_type;
  int32_t size;

  typedef int32_t _radius_type;
  int32_t radius;


  typedef boost::shared_ptr< ::OryxMessages::Blob_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::OryxMessages::Blob_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct Blob
typedef  ::OryxMessages::Blob_<std::allocator<void> > Blob;

typedef boost::shared_ptr< ::OryxMessages::Blob> BlobPtr;
typedef boost::shared_ptr< ::OryxMessages::Blob const> BlobConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::OryxMessages::Blob_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::OryxMessages::Blob_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace OryxMessages

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::OryxMessages::Blob_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::OryxMessages::Blob_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::OryxMessages::Blob_<ContainerAllocator> > {
  static const char* value() 
  {
    return "8cfb68607934ca46f726004e3324f44b";
  }

  static const char* value(const  ::OryxMessages::Blob_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x8cfb68607934ca46ULL;
  static const uint64_t static_value2 = 0xf726004e3324f44bULL;
};

template<class ContainerAllocator>
struct DataType< ::OryxMessages::Blob_<ContainerAllocator> > {
  static const char* value() 
  {
    return "OryxMessages/Blob";
  }

  static const char* value(const  ::OryxMessages::Blob_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::OryxMessages::Blob_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int32 x\n\
int32 y\n\
int32 size\n\
int32 radius\n\
\n\
";
  }

  static const char* value(const  ::OryxMessages::Blob_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::OryxMessages::Blob_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::OryxMessages::Blob_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.x);
    stream.next(m.y);
    stream.next(m.size);
    stream.next(m.radius);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Blob_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::OryxMessages::Blob_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::OryxMessages::Blob_<ContainerAllocator> & v) 
  {
    s << indent << "x: ";
    Printer<int32_t>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<int32_t>::stream(s, indent + "  ", v.y);
    s << indent << "size: ";
    Printer<int32_t>::stream(s, indent + "  ", v.size);
    s << indent << "radius: ";
    Printer<int32_t>::stream(s, indent + "  ", v.radius);
  }
};


} // namespace message_operations
} // namespace ros

#endif // ORYXMESSAGES_MESSAGE_BLOB_H

