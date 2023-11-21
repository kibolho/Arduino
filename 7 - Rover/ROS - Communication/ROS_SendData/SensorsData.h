// Generated by gencpp from file location_monitor/SensorsData.msg
// DO NOT EDIT!


#ifndef LOCATION_MONITOR_MESSAGE_SENSORSDATA_H
#define LOCATION_MONITOR_MESSAGE_SENSORSDATA_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace location_monitor
{
template <class ContainerAllocator>
struct SensorsData_
{
  typedef SensorsData_<ContainerAllocator> Type;

  SensorsData_()
    : yaw(0.0)
    , distance(0.0)
    , gps_degree(0.0)
    , gps_minute(0.0)
    , gps_second(0.0)  {
    }
  SensorsData_(const ContainerAllocator& _alloc)
    : yaw(0.0)
    , distance(0.0)
    , gps_degree(0.0)
    , gps_minute(0.0)
    , gps_second(0.0)  {
  (void)_alloc;
    }



   typedef double _yaw_type;
  _yaw_type yaw;

   typedef double _distance_type;
  _distance_type distance;

   typedef double _gps_degree_type;
  _gps_degree_type gps_degree;

   typedef double _gps_minute_type;
  _gps_minute_type gps_minute;

   typedef double _gps_second_type;
  _gps_second_type gps_second;




  typedef boost::shared_ptr< ::location_monitor::SensorsData_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::location_monitor::SensorsData_<ContainerAllocator> const> ConstPtr;

}; // struct SensorsData_

typedef ::location_monitor::SensorsData_<std::allocator<void> > SensorsData;

typedef boost::shared_ptr< ::location_monitor::SensorsData > SensorsDataPtr;
typedef boost::shared_ptr< ::location_monitor::SensorsData const> SensorsDataConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::location_monitor::SensorsData_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::location_monitor::SensorsData_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace location_monitor

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'location_monitor': ['/home/parallels/Desktop/Parallels Shared Folders/Home/Documents/catkin_ws2/src/location_monitor/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::location_monitor::SensorsData_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::location_monitor::SensorsData_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::location_monitor::SensorsData_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::location_monitor::SensorsData_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::location_monitor::SensorsData_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::location_monitor::SensorsData_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::location_monitor::SensorsData_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e528da2b383432a23aed48009740df7c";
  }

  static const char* value(const ::location_monitor::SensorsData_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe528da2b383432a2ULL;
  static const uint64_t static_value2 = 0x3aed48009740df7cULL;
};

template<class ContainerAllocator>
struct DataType< ::location_monitor::SensorsData_<ContainerAllocator> >
{
  static const char* value()
  {
    return "location_monitor/SensorsData";
  }

  static const char* value(const ::location_monitor::SensorsData_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::location_monitor::SensorsData_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 yaw       #\n\
float64 distance\n\
float64 gps_degree  \n\
float64 gps_minute \n\
float64 gps_second \n\
";
  }

  static const char* value(const ::location_monitor::SensorsData_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::location_monitor::SensorsData_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.yaw);
      stream.next(m.distance);
      stream.next(m.gps_degree);
      stream.next(m.gps_minute);
      stream.next(m.gps_second);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SensorsData_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::location_monitor::SensorsData_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::location_monitor::SensorsData_<ContainerAllocator>& v)
  {
    s << indent << "yaw: ";
    Printer<double>::stream(s, indent + "  ", v.yaw);
    s << indent << "distance: ";
    Printer<double>::stream(s, indent + "  ", v.distance);
    s << indent << "gps_degree: ";
    Printer<double>::stream(s, indent + "  ", v.gps_degree);
    s << indent << "gps_minute: ";
    Printer<double>::stream(s, indent + "  ", v.gps_minute);
    s << indent << "gps_second: ";
    Printer<double>::stream(s, indent + "  ", v.gps_second);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LOCATION_MONITOR_MESSAGE_SENSORSDATA_H