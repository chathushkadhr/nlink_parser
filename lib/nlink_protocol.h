#ifndef NLINK_PROTOCOL_H
#define NLINK_PROTOCOL_H
#include <functional>
#include <iostream>
#include "protocol_extracter/nprotocol_base.h"
//#include "nlink_parser/linktrack/init.h"

typedef void (*HandleDataCallback)();

class NLinkProtocol : public NProtocolBase
{
public:
  using NProtocolBase::NProtocolBase;

  void SetHandleDataCallback(HandleDataCallback handle)
  {
    std::cout<<"nlink_protocol.h/Line 14"<<std::endl;
    HandleDataCallback_ = handle;
  }

protected:
  virtual void HandleData(const uint8_t *data);
  virtual void UnpackFrameData(const uint8_t *data) = 0;
  bool Verify(const uint8_t *data) override;

private:
  HandleDataCallback HandleDataCallback_;
};

class NLinkProtocolVLength : public NLinkProtocol
{
public:
  using NLinkProtocol::NLinkProtocol;

protected:
  bool UpdateLength(const uint8_t *data, size_t available_bytes) override;
};

#endif // NLINK_PROTOCOL_H
