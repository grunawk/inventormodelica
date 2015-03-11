
#include <memory>
#include <string>

typedef std::basic_string<wchar_t, std::char_traits<wchar_t> > UTxString;

class MoBody;
typedef std::weak_ptr<MoBody>  MoBodyWPtr;
typedef std::shared_ptr<MoBody>  MoBodyPtr;

class MoBodyFrame;
typedef std::shared_ptr<MoBodyFrame> MoBodyFramePtr;
typedef std::weak_ptr<MoBodyFrame> MoBodyFrameWPtr;

class MoJoint;
typedef std::shared_ptr<MoJoint> MoJointPtr;

typedef unsigned long MoId;